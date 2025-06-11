#include "Tunables.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/gta/data/StackSizes.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Scripts.hpp"
#include "types/script/scrProgram.hpp"

namespace YimMenu
{
	struct TUNABLES_LAUNCH_DATA
	{
		SCR_INT Context;
		SCR_INT ContentModifier;
	};
	static_assert(sizeof(TUNABLES_LAUNCH_DATA) == 2 * 8);

	static void TunablesWaitHook(rage::scrNativeCallContext* src)
	{
		if (Tunables::CachingTunables())
			return;

		BUILTIN::WAIT(src->GetArg<int>(0));
	}

	static void TunablesGetIntHook(rage::scrNativeCallContext* src)
	{
		if (Tunables::CachingTunables())
		{
			Tunables::AddJunkValue(Tunables::GetCurrentJunkVal(), src->GetArg<Hash>(0));
			src->SetReturnValue<int>(Tunables::IncrementJunkVal());
			return;
		}

		src->SetReturnValue<int>(NETWORK::_NETWORK_GET_TUNABLES_REGISTRATION_INT(src->GetArg<Hash>(0), src->GetArg<int>(1)));
	}

	static void TunablesGetBoolHook(rage::scrNativeCallContext* src)
	{
		if (Tunables::CachingTunables())
		{
			Tunables::AddJunkValue(Tunables::GetCurrentJunkVal(), src->GetArg<Hash>(0));
			src->SetReturnValue<int>(Tunables::IncrementJunkVal());
			return;
		}

		src->SetReturnValue<BOOL>(NETWORK::_NETWORK_GET_TUNABLES_REGISTRATION_BOOL(src->GetArg<Hash>(0), src->GetArg<BOOL>(1)));
	}

	static void TunablesGetFloatHook(rage::scrNativeCallContext* src)
	{
		if (Tunables::CachingTunables())
		{
			Tunables::AddJunkValue(Tunables::GetCurrentJunkVal(), src->GetArg<Hash>(0));
			src->SetReturnValue<int>(Tunables::IncrementJunkVal());
			return;
		}

		src->SetReturnValue<float>(NETWORK::_NETWORK_GET_TUNABLES_REGISTRATION_FLOAT(src->GetArg<Hash>(0), src->GetArg<float>(1)));
	}

	Tunables::Tunables() :
	    m_CacheFile(FileMgr::GetProjectFile("./tunables.bin"))
	{
	}

	void Tunables::RunScriptImpl()
	{
		NativeHooks::AddHook("tuneables_processing"_J, NativeIndex::WAIT, &TunablesWaitHook);
		NativeHooks::AddHook("tuneables_processing"_J, NativeIndex::_NETWORK_GET_TUNABLES_REGISTRATION_INT, &TunablesGetIntHook);
		NativeHooks::AddHook("tuneables_processing"_J, NativeIndex::_NETWORK_GET_TUNABLES_REGISTRATION_BOOL, &TunablesGetBoolHook);
		NativeHooks::AddHook("tuneables_processing"_J, NativeIndex::_NETWORK_GET_TUNABLES_REGISTRATION_FLOAT, &TunablesGetFloatHook);

		while (true)
		{
			ScriptMgr::Yield();

			m_CacheFile.Load();

			if (m_CacheFile.UpToDate(ModuleMgr.Get("GTA5_Enhanced.exe"_J)->GetNtHeader()->FileHeader.TimeDateStamp))
			{
				m_Loading = true;
				Load();
			}

			if (m_Initialized || m_Loading)
				return;

			if (!m_ScriptStarted && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("tuneables_processing"_J) > 0)
				continue;

			if (!m_ScriptStarted)
			{
				// Wait for required global blocks to be loaded
				if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("startup"_J) > 0)
					continue;

				SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH("tuneables_processing"_J);
				SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH("tunables_registration"_J);

				if (auto program = Scripts::FindScriptProgram("tunables_registration"_J); program && SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED("tuneables_processing"_J) && SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED("tunables_registration"_J))
				{
					m_NumTunables = program->m_GlobalCount - TUNABLE_BASE_ADDRESS;

					TUNABLES_LAUNCH_DATA args;
					args.Context = 6;          // BASE_GLOBALS
					args.ContentModifier = 27; // MP_FM_RANDOM
					if (!BUILTIN::START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS("tuneables_processing"_J, &args, SCR_SIZEOF(args), static_cast<int>(eStackSizes::DEFAULT)))
					{
						LOG(FATAL) << "Failed to start tuneables_processing. Cannot cache tunables.";
						return;
					}

					m_TunablesBackup = std::make_unique<std::uint64_t[]>(m_NumTunables);
					std::memcpy(m_TunablesBackup.get(), ScriptGlobal(TUNABLE_BASE_ADDRESS).As<void*>(), m_NumTunables * 8);

					SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED("tuneables_processing"_J);
					SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED("tunables_registration"_J);
					m_ScriptStarted = true;
				}
			}
			else
			{
				if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("tuneables_processing"_J) == 0)
				{
					for (int i = 0; i < m_NumTunables; i++)
					{
						auto value = *ScriptGlobal(TUNABLE_BASE_ADDRESS).At(i).As<int*>();
						if (auto it = m_JunkValues.find(value); it != m_JunkValues.end())
						{
							m_Tunables.emplace(it->second, TUNABLE_BASE_ADDRESS + i);
						}
					}

					std::memcpy(ScriptGlobal(TUNABLE_BASE_ADDRESS).As<void*>(), m_TunablesBackup.get(), m_NumTunables * 8);

					if (m_Tunables.size() == 0)
					{
						LOG(FATAL) << "Failed to cache tunables.";
						return;
					}

					LOG(INFO) << "Saving " << m_Tunables.size() << " tunables to cache.";
					Save();

					m_ScriptStarted = false;
					m_TunablesBackup.release();
					m_JunkValues.clear();
					m_Initialized = true;
				}
			}
		}
	}

	void Tunables::Save()
	{
		auto dataSize = sizeof(std::uint32_t) + sizeof(TunableSaveStruct) * m_Tunables.size();
		auto data = std::make_unique<uint8_t[]>(dataSize);
		auto dataPtr = data.get();

		*(std::uint32_t*)dataPtr = m_Tunables.size();
		dataPtr += sizeof(std::uint32_t);

		for (auto& [hash, val] : m_Tunables)
		{
			auto saveStruct = (TunableSaveStruct*)dataPtr;
			saveStruct->m_Hash = hash;
			saveStruct->m_Offset = val;
			dataPtr += sizeof(TunableSaveStruct);
		}

		m_CacheFile.SetHeaderVersion(ModuleMgr.Get("GTA5_Enhanced.exe"_J)->GetNtHeader()->FileHeader.TimeDateStamp);
		m_CacheFile.SetData(std::move(data), dataSize);
		m_CacheFile.Write();
	}

	void Tunables::Load()
	{
		auto data = m_CacheFile.Data();

		auto numTunables = *(std::uint32_t*)data;
		data += sizeof(std::uint32_t);

		for (int i = 0; i < numTunables; i++)
		{
			auto saveStruct = (TunableSaveStruct*)data;
			m_Tunables.emplace(saveStruct->m_Hash, saveStruct->m_Offset);
			data += sizeof(TunableSaveStruct);
		}

		m_Initialized = true;
		m_Loading = false;

		LOG(INFO) << "Loaded " << m_Tunables.size() << " tunables from cache.";
	}

	bool Tunable::IsReady()
	{
		if (m_Global)
			return true;

		m_Global = Tunables::GetTunable(m_Hash);

		if (m_Global)
			return true;

		return false;
	}
}