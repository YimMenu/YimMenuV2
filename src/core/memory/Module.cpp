#include "Module.hpp"

namespace YimMenu
{
	Module::Module(LDR_DATA_TABLE_ENTRY* dllEntry) :
	    m_Path(dllEntry->FullDllName.Buffer),
	    m_Name(m_Path.filename().string()),
	    m_Base(dllEntry->DllBase),
	    m_Size(0)
	{
		const auto ntHeader = GetNtHeader();
		if (ntHeader)
		{
			m_Size = ntHeader->OptionalHeader.SizeOfCode;
		}
	}

	const std::string_view Module::Name() const
	{
		return m_Name;
	}

	void** Module::GetImport(const std::string_view moduleName, const std::string_view symbolName) const
	{
		const auto ntHeader = GetNtHeader();
		if (!ntHeader)
			return nullptr;

		const auto imageDataDirectory = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];

		auto importDescriptor = m_Base.Add(imageDataDirectory.VirtualAddress).As<IMAGE_IMPORT_DESCRIPTOR*>();
		for (; importDescriptor->Name; importDescriptor++)
		{
			if (const auto modName = m_Base.Add(importDescriptor->Name).As<const char*>(); strcmp(modName, moduleName.data()))
				continue;

			auto firstThunk = m_Base.Add(importDescriptor->FirstThunk).As<IMAGE_THUNK_DATA*>();
			auto origThunk = m_Base.Add(importDescriptor->OriginalFirstThunk).As<IMAGE_THUNK_DATA*>();
			for (; origThunk->u1.AddressOfData != 0; firstThunk++, origThunk++)
			{
				if (const auto importData = m_Base.Add(origThunk->u1.AddressOfData).As<IMAGE_IMPORT_BY_NAME*>();
				    strcmp(importData->Name, symbolName.data()))
					continue;
				return reinterpret_cast<void**>(&firstThunk->u1.Function);
			}
		}
		return nullptr;
	}

	bool Module::Valid() const
	{
		return m_Size;
	}

	IMAGE_NT_HEADERS* Module::GetNtHeader() const
	{
		if (!m_Base)
			return nullptr;

		const auto offset = m_Base.As<IMAGE_DOS_HEADER*>()->e_lfanew;
		return m_Base.Add(offset).As<IMAGE_NT_HEADERS*>();
	}
}