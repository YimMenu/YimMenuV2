#include "ScriptFunction.hpp"
#include "game/backend/ScriptPointers.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/Scripts.hpp"
#include "game/gta/ScriptPointer.hpp"
#include "types/script/scrThread.hpp"
#include "types/script/scrProgram.hpp"
#include "types/rage/tlsContext.hpp"

namespace YimMenu
{
	ScriptFunction::ScriptFunction(const joaat_t script, ScriptPointer ptr) :
	    m_Script(script),
	    m_Pointer(ptr),
	    m_Pc(0)
	{
	}

	void ScriptFunction::CallImpl(const std::vector<uint64_t>& args, void* returnValue, std::uint32_t returnSize)
	{
		auto thread = Scripts::FindScriptThread(m_Script);
		auto program = Scripts::FindScriptProgram(m_Script);

		if (!thread || !program)
			return;

		if (!m_Pc)
		{
			if (auto address = ScriptPointers::GetPointer(m_Script, Joaat(m_Pointer.GetName())))
			{
				m_Pc = address;
			}
			else
			{
				m_Pc = m_Pointer.Scan(program).As<std::uint32_t>();
				ScriptPointers::CachePointer(m_Script, Joaat(m_Pointer.GetName()), m_Pc);
			}

			if (!m_Pc) // if still not valid
				return;
		}

		auto tlsCtx = rage::tlsContext::Get();
		auto stack = (std::uint64_t*)thread->m_Stack;
		auto ogThread = tlsCtx->m_CurrentScriptThread;
		tlsCtx->m_CurrentScriptThread = thread;
		tlsCtx->m_ScriptThreadActive = true;
		rage::scrThread::Context ctx = thread->m_Context;
		auto topStack = ctx.m_StackPointer;

		for (auto& arg : args)
			stack[ctx.m_StackPointer++] = arg;

		stack[ctx.m_StackPointer++] = 0;
		ctx.m_ProgramCounter = m_Pc;
		ctx.m_State = rage::scrThread::State::IDLE;

		Pointers.ScriptVM(stack, Pointers.ScriptGlobals, program, &ctx);

		tlsCtx->m_CurrentScriptThread = ogThread;
		tlsCtx->m_ScriptThreadActive = ogThread != nullptr;

		if (returnValue)
			std::memcpy(returnValue, stack + topStack, returnSize);
	}
}