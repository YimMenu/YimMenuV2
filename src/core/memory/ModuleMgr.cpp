#include "ModuleMgr.hpp"

#include "core/util/Joaat.hpp"

namespace YimMenu
{
	Module* ModuleMgr::Get(const std::string_view name)
	{
		return Get(Joaat(name));
	}

	Module* ModuleMgr::Get(joaat_t hash)
	{
		if (const auto& it = m_CachedModules.find(hash); it != m_CachedModules.end())
		{
			return it->second.get();
		}
		return nullptr;
	}

	bool ModuleMgr::LoadModules()
	{
		m_CachedModules.clear();

		m_ManualMapped = true;

		const auto peb = reinterpret_cast<PPEB>(NtCurrentTeb()->ProcessEnvironmentBlock);
		if (!peb)
			return false;

		const auto ldrData = peb->Ldr;
		if (!ldrData)
			return false;

		const auto moduleList = &ldrData->InMemoryOrderModuleList;
		auto moduleEntry = moduleList->Flink;
		for (; moduleList != moduleEntry; moduleEntry = moduleEntry->Flink)
		{
			const auto tableEntry = CONTAINING_RECORD(moduleEntry, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
			if (!tableEntry)
				continue;

			if (tableEntry->FullDllName.Buffer)
			{
				auto module = std::make_unique<Module>(tableEntry);

				if (module->Base() == reinterpret_cast<uint64_t>(g_DllInstance))
					m_ManualMapped = false;

				m_CachedModules.insert({Joaat(module->Name()), std::move(module)});
			}
		}

		return true;
	}

	std::unordered_multimap<std::uint32_t, std::unique_ptr<Module>>& ModuleMgr::GetModules()
	{
		return m_CachedModules;
	}

	bool ModuleMgr::IsManualMapped()
	{
		return m_ManualMapped;
	}
}