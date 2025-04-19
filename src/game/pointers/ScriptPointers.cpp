#include "ScriptPointers.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Scripts.hpp"
#include "types/script/scrProgram.hpp"

namespace YimMenu
{
	constexpr std::array requiredScripts = {
		"freemode"_J,
		"shop_controller"_J,
		"fm_mission_controller"_J,
		"AM_MP_VEHICLE_REWARD"_J
	};

	static bool LoadRequiredScripts()
	{
		if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("startup"_J) > 0)
			return false;

		bool loaded = true;

		for (auto& script : requiredScripts)
		{
			if (!SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(script))
			{
				SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(script);
				loaded = false;
			}
		}

		return loaded;
	}

	ScriptPointers::ScriptPointer::ScriptPointer(rage::scrProgram* program) :
	    m_Program(program),
	    m_Address(0)
	{
	}

	ScriptPointers::ScriptPointer::ScriptPointer(rage::scrProgram* program, std::uint32_t address) :
	    m_Program(program),
	    m_Address(address)
	{
	}

	ScriptPointers::ScriptPointer ScriptPointers::ScriptPointer::Add(std::uint32_t offset)
	{
		return ScriptPointer(m_Program, m_Address + offset);
	}

	ScriptPointers::ScriptPointer ScriptPointers::ScriptPointer::Sub(std::uint32_t offset)
	{
		return ScriptPointer(m_Program, m_Address - offset);
	}

	ScriptPointers::ScriptPointer ScriptPointers::ScriptPointer::Rip()
	{
		std::uint8_t* bytes = m_Program->GetCodeAddress(m_Address);
		std::uint32_t value = bytes[0] + (bytes[1] << 8) + (bytes[2] << 16);
		return ScriptPointer(m_Program, value);
	}

	ScriptPointers::ScriptPointer ScriptPointers::ScriptPointer::Scan(SimplePattern pattern)
	{
		if (auto result = Scripts::GetCodeLocationByPattern(m_Program, pattern))
		{
			LOG(INFO) << "Found pattern at " << HEX(result.value()) << " in script " << m_Program->m_Name;
			return ScriptPointer(m_Program, result.value());
		}

		LOG(FATAL) << "Failed to find pattern in script " << m_Program->m_Name;
		return ScriptPointer(m_Program);
	}

	ScriptPointers::ScriptPointers() :
	    m_CacheFile(FileMgr::GetProjectFile("./scr_pointers.bin"))
	{
	}

	void ScriptPointers::RunScriptImpl()
	{
		while (true)
		{
			ScriptMgr::Yield();

			m_CacheFile.Load();
			if (m_CacheFile.UpToDate(ModuleMgr.Get("GTA5_Enhanced.exe"_J)->GetNtHeader()->FileHeader.TimeDateStamp))
			{
				LOG(INFO) << "Loading script pointers from cache.";
				Load();
				return;
			}

			if (!LoadRequiredScripts())
				continue;

			auto freemode              = Scripts::FindScriptProgram("freemode"_J);
			auto shop_controller       = Scripts::FindScriptProgram("shop_controller"_J);
			auto fm_mission_controller = Scripts::FindScriptProgram("fm_mission_controller"_J);
			auto AM_MP_VEHICLE_REWARD  = Scripts::FindScriptProgram("AM_MP_VEHICLE_REWARD"_J);
			if (!freemode || !shop_controller || !fm_mission_controller || !AM_MP_VEHICLE_REWARD)
				continue;

			ScriptPointer scanner{};

			scanner = ScriptPointer(freemode);
			AddPointer("GlobalPlayerBD"_J, scanner.Scan("61 ? ? ? 49 ? ? 46 ? ? 42 ? 5D ? ? ? 56 ? ? 5D").Add(1).Rip().As<std::uint32_t>());
			AddPointer("GPBD_FM"_J, scanner.Scan("61 ? ? ? 49 ? ? 46 ? ? 40 ? 25 ? 2C ? ? ? 55 ? ? 2C ? ? ? 61 ? ? ? 49 ? ? 46 ? ? 40 ? 25 ? 2C ? ? ? 5D ? ? ? 56").Add(1).Rip().As<std::uint32_t>());
			AddPointer("GPBD_FM_2"_J, scanner.Scan("61 ? ? ? 34 ? 41 ? 25 ? 82 1F 56 ? ? 71").Add(1).Rip().As<std::uint32_t>());
			AddPointer("GPBD_FM_3"_J, scanner.Scan("61 ? ? ? 49 ? ? 41 ? 5D ? ? ? 56 ? ? 38 ? 61 ? ? ? 49 ? ? 41 ? 38 ? 08 2E").Add(1).Rip().As<std::uint32_t>());
			AddPointer("GPBD_Kicking"_J, scanner.Scan("61 ? ? ? 34 ? 35 ? 72 57").Add(1).Rip().As<std::uint32_t>());
			AddPointer("GPBD_MissionName"_J, scanner.Scan("61 ? ? ? 34 ? 32 25 ? 62").Add(1).Rip().As<std::uint32_t>());
			AddPointer("GSBD"_J, scanner.Scan("61 ? ? ? 48 ? ? 72 2C ? ? ? 5D").Add(1).Rip().As<std::uint32_t>());
			AddPointer("GSBD_BlockB"_J, scanner.Scan("61 ? ? ? 46 ? ? 34 ? 5D ? ? ? 72").Add(1).Rip().As<std::uint32_t>());
			AddPointer("GSBD_FM"_J, scanner.Scan("61 ? ? ? 46 ? ? 41 ? 71 5C ? ? 72").Add(1).Rip().As<std::uint32_t>());
			AddPointer("GSBD_FM_Events"_J, scanner.Scan("61 ? ? ? 41 ? 38 ? 30 61 ? ? ? 41").Add(1).Rip().As<std::uint32_t>());
			AddPointer("GSBD_Kicking"_J, scanner.Scan("61 ? ? ? 36 ? 38 ? 2F").Add(1).Rip().As<std::uint32_t>());
			AddPointer("GSBD_PropertyInstances"_J, scanner.Scan("61 ? ? ? 34 ? 32 5D ? ? ? 2A 56 ? ? 38 ? 61 ? ? ? 46").Add(1).Rip().As<std::uint32_t>());
			AddPointer("g_AMC_playerBD"_J, scanner.Scan("61 ? ? ? 34 ? 34 ? 71").Add(1).Rip().As<std::uint32_t>());
			AddPointer("GSBD_RandomEvents"_J, scanner.Scan("61 ? ? ? 40 ? 34 ? 40 ? 38 ? 61 ? ? ? 40 ? 34 ? 40 ? 5D").Add(1).Rip().As<std::uint32_t>());
			AddPointer("FMRandomEvents"_J, scanner.Scan("4F ? ? 40 ? 5D ? ? ? 5D ? ? ? 4F").Add(1).Rip().As<std::uint16_t>());
			AddPointer("GetNumFMMCVariations"_J, scanner.Scan("5D ? ? ? 01 72 02 39 04").Add(1).Rip().As<std::uint32_t>());

			scanner = ScriptPointer(shop_controller);
			AddPointer("SendToClouds"_J, scanner.Scan("2D 00 02 00 00 72 5D ? ? ? 72").As<std::uint32_t>());

			scanner = ScriptPointer(fm_mission_controller);
			AddPointer("DoTeamSwap"_J, scanner.Scan("2D 02 04 00 00 38 00 50").As<std::uint32_t>());

			scanner = ScriptPointer(AM_MP_VEHICLE_REWARD);
			AddPointer("VehicleRewardData"_J, scanner.Scan("3A ? 40 ? 5D ? ? ? 2A").Add(1).Rip().As<std::uint8_t>());
			AddPointer("GiveVehicleReward"_J, scanner.Scan("2D 0C 1E 00 00").As<std::uint32_t>());

			for (auto& script : requiredScripts)
				SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(script);

			LOG(INFO) << "Saving " << m_ScriptPointers.size() << " script pointers to cache.";
			Save();
			return;
		}
	}

	void ScriptPointers::Save()
	{
		auto dataSize = sizeof(std::uint32_t) + sizeof(scrPointerSaveStruct) * m_ScriptPointers.size();
		auto data     = std::make_unique<uint8_t[]>(dataSize);
		auto dataPtr  = data.get();

		*(std::uint32_t*)dataPtr = m_ScriptPointers.size();
		dataPtr += sizeof(std::uint32_t);

		for (auto& [hash, val] : m_ScriptPointers)
		{
			auto saveStruct       = (scrPointerSaveStruct*)dataPtr;
			saveStruct->m_Hash    = hash;
			saveStruct->m_Address = val;
			dataPtr += sizeof(scrPointerSaveStruct);
		}

		m_CacheFile.SetHeaderVersion(ModuleMgr.Get("GTA5_Enhanced.exe"_J)->GetNtHeader()->FileHeader.TimeDateStamp);
		m_CacheFile.SetData(std::move(data), dataSize);
		m_CacheFile.Write();
	}

	void ScriptPointers::Load()
	{
		auto data = m_CacheFile.Data();

		auto numPointers = *(std::uint32_t*)data;
		data += sizeof(std::uint32_t);

		for (int i = 0; i < numPointers; i++)
		{
			auto saveStruct = (scrPointerSaveStruct*)data;
			m_ScriptPointers.emplace(saveStruct->m_Hash, saveStruct->m_Address);
			data += sizeof(scrPointerSaveStruct);
		}
	}
}