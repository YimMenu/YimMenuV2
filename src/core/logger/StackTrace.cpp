#include "StackTrace.hpp"

#include <dbghelp.h>
#include <winternl.h>

namespace YimMenu
{
	StackTrace::StackTrace() :
	    m_FramePointers(32)
	{
		SymInitialize(GetCurrentProcess(), nullptr, true);
	}

	StackTrace::~StackTrace()
	{
		SymCleanup(GetCurrentProcess());
	}

	const std::vector<uint64_t>& StackTrace::GetFramePointers()
	{
		return m_FramePointers;
	}

	void StackTrace::NewStackTrace(EXCEPTION_POINTERS* exception_info)
	{
		static std::mutex m;
		std::lock_guard lock(m);

		m_ExceptionInfo = exception_info;

		Clear();

		m_Dump << ExceptionCodeToString(exception_info->ExceptionRecord->ExceptionCode) << '\n';

		DumpModuleInfo();
		DumpRegisters();
		DumpStacktrace();
		DumpExceptionInfo();

		m_Dump << "\n--------End of exception--------\n";
	}

	std::string StackTrace::GetString() const
	{
		return m_Dump.str();
	}

	void StackTrace::Clear()
	{
		m_Dump.str("");
		m_Dump.clear();
	}

	// I'd prefer to make some sort of global instance that cache all modules once instead of doing this every time
	void StackTrace::DumpModuleInfo()
	{
		// modules cached already
		if (m_Modules.size())
			return;

		m_Dump << "Dumping modules:\n";

		const auto peb = reinterpret_cast<PPEB>(NtCurrentTeb()->ProcessEnvironmentBlock);
		if (!peb)
			return;

		const auto ldr_data = peb->Ldr;
		if (!ldr_data)
			return;

		const auto module_list = &ldr_data->InMemoryOrderModuleList;
		auto module_entry = module_list->Flink;
		for (; module_list != module_entry; module_entry = module_entry->Flink)
		{
			const auto table_entry = CONTAINING_RECORD(module_entry, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
			if (!table_entry)
				continue;

			if (table_entry->FullDllName.Buffer)
			{
				auto mod_info = ModuleInfo(table_entry->FullDllName.Buffer, table_entry->DllBase);

				m_Dump << mod_info.m_Name << " Base Address: " << HEX(mod_info.m_Base) << " Size: " << mod_info.m_Size << '\n';

				m_Modules.emplace_back(std::move(mod_info));
			}
		}
	}

	void StackTrace::DumpRegisters()
	{
		const auto context = m_ExceptionInfo->ContextRecord;

		m_Dump << "Dumping registers:\n"
		       << "RAX: " << HEX(context->Rax) << '\n'
		       << "RCX: " << HEX(context->Rcx) << '\n'
		       << "RDX: " << HEX(context->Rdx) << '\n'
		       << "RBX: " << HEX(context->Rbx) << '\n'
		       << "RSI: " << HEX(context->Rsi) << '\n'
		       << "RDI: " << HEX(context->Rdi) << '\n'
		       << "RSP: " << HEX(context->Rsp) << '\n'
		       << "RBP: " << HEX(context->Rbp) << '\n'
		       << "R8:  " << HEX(context->R8) << '\n'
		       << "R9:  " << HEX(context->R9) << '\n'
		       << "R10: " << HEX(context->R10) << '\n'
		       << "R11: " << HEX(context->R11) << '\n'
		       << "R12: " << HEX(context->R12) << '\n'
		       << "R13: " << HEX(context->R13) << '\n'
		       << "R14: " << HEX(context->R14) << '\n'
		       << "R15: " << HEX(context->R15) << '\n';
	}

	void StackTrace::DumpStacktrace()
	{
		m_Dump << "Dumping stacktrace:";
		GrabStacktrace();

		// alloc once
		char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME];
		auto symbol = reinterpret_cast<SYMBOL_INFO*>(buffer);
		symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		symbol->MaxNameLen = MAX_SYM_NAME;

		DWORD64 displacement64;
		DWORD displacement;


		IMAGEHLP_LINE64 line;
		line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

		for (size_t i = 0; i < m_FramePointers.size() && m_FramePointers[i]; ++i)
		{
			const auto addr = m_FramePointers[i];
			const auto module_info = GetModuleByAddress(addr);

			m_Dump << "\n[" << i << "]\t";
			if (SymFromAddr(GetCurrentProcess(), addr, &displacement64, symbol))
			{
				if (SymGetLineFromAddr64(GetCurrentProcess(), addr, &displacement, &line))
				{
					m_Dump << line.FileName << " L: " << line.LineNumber << ' ' << std::string_view(symbol->Name, symbol->NameLen);

					continue;
				}

				if (module_info)
				{
					m_Dump << module_info->m_Name << ' ' << std::string_view(symbol->Name, symbol->NameLen) << " ("
					       << module_info->m_Name << '+' << HEX(addr - module_info->m_Base) << ')';

					continue;
				}

				m_Dump << HEX(addr) << ' ' << std::string_view(symbol->Name, symbol->NameLen);

				continue;
			}

			if (module_info)
			{
				m_Dump << module_info->m_Name << '+' << HEX(addr - module_info->m_Base) << ' ' << HEX(addr);

				continue;
			}

			m_Dump << HEX(addr);
		}
	}

	void StackTrace::DumpExceptionInfo()
	{
		DWORD exception_code = m_ExceptionInfo->ExceptionRecord->ExceptionCode;

		constexpr DWORD msvc_exception_code = 0xe06d7363;
		if (exception_code == msvc_exception_code)
		{
			m_Dump << '\n'
			       << reinterpret_cast<const std::exception*>(m_ExceptionInfo->ExceptionRecord->ExceptionInformation[1])->what() << '\n';
		}
		else if (exception_code == EXCEPTION_ACCESS_VIOLATION || exception_code == EXCEPTION_IN_PAGE_ERROR)
		{
			const auto flag = m_ExceptionInfo->ExceptionRecord->ExceptionInformation[0];
			const auto addr = m_ExceptionInfo->ExceptionRecord->ExceptionInformation[1];

			switch (flag)
			{
			case EXCEPTION_READ_FAULT:
				m_Dump << '\n'
				       << "Attempted to read from " << HEX(addr) << '\n';
				break;
			case EXCEPTION_WRITE_FAULT:
				m_Dump << '\n'
				       << "Attempted to write to " << HEX(addr) << '\n';
				break;
			case EXCEPTION_EXECUTE_FAULT:
				m_Dump << '\n'
				       << "Attempted to execute at " << HEX(addr) << '\n';
				break;
			default: m_Dump << '\n'
				            << "Inaccessible data at " << HEX(addr) << '\n';
			}

			if (exception_code == EXCEPTION_IN_PAGE_ERROR)
			{
				m_Dump << "NTSTATUS code " << HEX(m_ExceptionInfo->ExceptionRecord->ExceptionInformation[2]) << '\n';
			}
		}
	}

	void StackTrace::GrabStacktrace()
	{
		CONTEXT context = *m_ExceptionInfo->ContextRecord;

		STACKFRAME64 frame{};
		frame.AddrPC.Mode = AddrModeFlat;
		frame.AddrFrame.Mode = AddrModeFlat;
		frame.AddrStack.Mode = AddrModeFlat;
		frame.AddrPC.Offset = context.Rip;
		frame.AddrFrame.Offset = context.Rbp;
		frame.AddrStack.Offset = context.Rsp;

		for (size_t i = 0; i < m_FramePointers.size(); ++i)
		{
			if (!StackWalk64(IMAGE_FILE_MACHINE_AMD64, GetCurrentProcess(), GetCurrentThread(), &frame, &context, nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr))
			{
				break;
			}
			m_FramePointers[i] = frame.AddrPC.Offset;
		}
	}

	const StackTrace::ModuleInfo* StackTrace::GetModuleByAddress(uint64_t addr) const
	{
		for (auto& mod_info : m_Modules)
		{
			if (mod_info.m_Base < addr && addr < mod_info.m_Base + mod_info.m_Size)
			{
				return &mod_info;
			}
		}
		return nullptr;
	}

	std::string StackTrace::ExceptionCodeToString(const DWORD code)
	{
#define MAP_PAIR_STRINGIFY(x) \
	{                         \
		x, #x                 \
	}
		static const std::map<DWORD, std::string> exceptions = {MAP_PAIR_STRINGIFY(EXCEPTION_ACCESS_VIOLATION), MAP_PAIR_STRINGIFY(EXCEPTION_ARRAY_BOUNDS_EXCEEDED), MAP_PAIR_STRINGIFY(EXCEPTION_DATATYPE_MISALIGNMENT), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_DENORMAL_OPERAND), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_DIVIDE_BY_ZERO), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_INEXACT_RESULT), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_INEXACT_RESULT), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_INVALID_OPERATION), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_OVERFLOW), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_STACK_CHECK), MAP_PAIR_STRINGIFY(EXCEPTION_FLT_UNDERFLOW), MAP_PAIR_STRINGIFY(EXCEPTION_ILLEGAL_INSTRUCTION), MAP_PAIR_STRINGIFY(EXCEPTION_IN_PAGE_ERROR), MAP_PAIR_STRINGIFY(EXCEPTION_INT_DIVIDE_BY_ZERO), MAP_PAIR_STRINGIFY(EXCEPTION_INT_OVERFLOW), MAP_PAIR_STRINGIFY(EXCEPTION_INVALID_DISPOSITION), MAP_PAIR_STRINGIFY(EXCEPTION_NONCONTINUABLE_EXCEPTION), MAP_PAIR_STRINGIFY(EXCEPTION_PRIV_INSTRUCTION), MAP_PAIR_STRINGIFY(EXCEPTION_STACK_OVERFLOW), MAP_PAIR_STRINGIFY(EXCEPTION_BREAKPOINT), MAP_PAIR_STRINGIFY(EXCEPTION_SINGLE_STEP)};

		if (const auto& it = exceptions.find(code); it != exceptions.end())
			return it->second;

		return "UNKNOWN_EXCEPTION: CODE: " + std::to_string(code);
	}
}