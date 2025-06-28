#include "PersonalVehicles.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/data/VehicleValues.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/Stats.hpp"
#include "types/script/globals/GPBD_FM.hpp"
#include "types/script/globals/MPSV.hpp"
#include "types/script/globals/FreemodeGeneral.hpp"
#include "types/script/globals/g_SavedMPGlobals.hpp"

#define MAX_GARAGE_NUM 33

namespace YimMenu
{
	// TO-DO: Use script functions for these instead?

	static int GetPropertyGarageOffset(int property)
	{
		switch (property)
		{
		case 0: return 13 * 0;
		case 1: return 13 * 1;
		case 2: return 13 * 2;
		case 3: return 13 * 3;
		case 4: return 13 * 4;
		//Property 5 is not used.
		case 6: return 65;
		case 7: return 75;
		case 8: return 88;
		case 9: return 108;
		case 10: return 128;
		case 11: return 148;
		case 12: return 159;
		case 13: return 179;
		case 14: return 191;
		case 15: return 192;
		case 16: return 202;
		case 17: return 212;
		case 18: return 227;
		case 19: return 237;
		case 20: return 247;
		case 21: return 258;
		case 22: return 268;
		case 23: return 281;
		case 24: return 294;
		case 25: return 307;
		case 26: return 317;
		case 27: return 337;
		case 28: return 350;
		case 29: return 363;
		case 30: return 415; // The Vinewood Club Garage
		case 31: return 515;
		case 32: return 537;
		case MAX_GARAGE_NUM + 0: return 156; // Mobile Operations Center
		case MAX_GARAGE_NUM + 1: return 224; // Nightclub B1
		case MAX_GARAGE_NUM + 2: return 223; // Terrorbyte
		case MAX_GARAGE_NUM + 3: return 278; // Kosatka
		}

		return -1;
	}

	static int GetPropertyGarageSize(int property)
	{
		switch (property)
		{
		case MAX_GARAGE_NUM + 0: // Mobile Operations Center
		case MAX_GARAGE_NUM + 2: // Terrorbyte
		case MAX_GARAGE_NUM + 3: // Kosatka
		case 14: return 1;
		case 31: return 2;
		case MAX_GARAGE_NUM + 1: return 3; // Nightclub B1
		case 11: return 8;
		case 6:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 32:
		case 25: return 10;
		case 13: return 11;
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 7:
		case 23:
		case 24:
		case 27:
		case 28: return 13;
		case 8:
		case 9:
		case 10:
		case 12:
		case 26: return 20;
		case 29: return 50;
		case 30: return 100; // The Vinewood Club Garage
		}

		return -1;
	}

	static int GetPropertyStatState(int property)
	{
		std::string stat = "";
		switch (property)
		{
		case 0: stat = "MPX_PROPERTY_HOUSE"; break;
		case 1: stat = "MPX_MULTI_PROPERTY_1"; break;
		case 2: stat = "MPX_MULTI_PROPERTY_2"; break;
		case 3: stat = "MPX_MULTI_PROPERTY_3"; break;
		case 4: stat = "MPX_MULTI_PROPERTY_4"; break;
		case 5: stat = "MPX_PROP_OFFICE"; break;
		case 6: stat = "MPX_PROP_CLUBHOUSE"; break;
		case 7: stat = "MPX_MULTI_PROPERTY_5"; break;
		case 8: stat = "MPX_PROP_OFFICE_GAR1"; break;
		case 9: stat = "MPX_PROP_OFFICE_GAR2"; break;
		case 10: stat = "MPX_PROP_OFFICE_GAR3"; break;
		case 11: stat = "MPX_PROP_IE_WAREHOUSE"; break;
		case 12: stat = "MPX_PROP_HANGAR"; break;
		case 13: stat = "MPX_PROP_DEFUNCBASE"; break;
		case 14: stat = "MPX_PROP_NIGHTCLUB"; break;
		case 15: stat = "MPX_PROP_MEGAWARE_GAR1"; break;
		case 16: stat = "MPX_PROP_MEGAWARE_GAR2"; break;
		case 17: stat = "MPX_PROP_MEGAWARE_GAR3"; break;
		case 18: stat = "MPX_PROP_ARENAWARS_GAR1"; break;
		case 19: stat = "MPX_PROP_ARENAWARS_GAR2"; break;
		case 20: stat = "MPX_PROP_ARENAWARS_GAR3"; break;
		case 21: stat = "MPX_PROP_CASINO_GAR1"; break;
		case 22: stat = "MPX_PROP_ARCADE_GAR1"; break;
		case 23: stat = "MPX_MULTI_PROPERTY_6"; break;
		case 24: stat = "MPX_MULTI_PROPERTY_7"; break;
		case 25: stat = "MPX_PROP_AUTO_SHOP"; break;
		case 26: stat = "MPX_PROP_SECURITY_OFFICE_GAR"; break;
		case 27: stat = "MPX_MULTI_PROPERTY_8"; break;
		case 28: stat = "MPX_MULTI_PROPERTY_9"; break;
		case 29: stat = "MPX_MULTSTOREY_GAR_OWNED"; break;
		case 30: return 1; // *Pointers.HasGTAPlus; is this a good idea?
		case 31: stat = "MPX_PROP_BAIL_OFFICE"; break;
		case 32: stat = "MPX_PROP_HACKER_DEN"; break;
		case MAX_GARAGE_NUM + 0:
		case MAX_GARAGE_NUM + 1:
		case MAX_GARAGE_NUM + 2:
		case MAX_GARAGE_NUM + 3: return 1;
		default: return -1;
		}

		return Stats::GetInt(stat);
	}

	static std::string GetStaticPropertyName(int property, int garageSlotIterator)
	{
		switch (property)
		{
		case 12: // Hangar
		{
			auto id = GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.HangarData.Index;
			switch (id)
			{
			case 1: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_HANGAR_1"); // LSIA Hangar 1
			case 2: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_HANGAR_2"); // LSIA Hangar A17
			case 3: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_HANGAR_3"); // Fort Zancudo Hangar A2
			case 4: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_HANGAR_4"); // Fort Zancudo Hangar 3497
			case 5: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_HANGAR_5"); // Fort Zancudo Hangar 3499
			}
			break;
		}
		case 13: // Facility
		{
			auto id = GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.DefunctBaseData.Index;
			switch (id)
			{
			case 1: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_1"); // Grand Senora Desert Facility
			case 2: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_2"); // Route 68 Facility
			case 3: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_3"); // Sandy Shores Facility
			case 4: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_4"); // Mount Gordo Facility
			case 5: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_6"); // Paleto Bay Facility
			case 6: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_7"); // Lago Zancudo Facility
			case 7: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_8"); // Zancudo River Facility
			case 8: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_9"); // Ron Alternates Wind Farm Facility
			case 9: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_10"); // Land Act Reservoir Facility
			}
			break;
		}
		case 14: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_CLUBG"); // Nightclub Service Entrance
		case 15: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_GAR1"); // Nightclub B2
		case 16: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_GAR2"); // Nightclub B3
		case 17: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_GAR3"); // Nightclub B4
		case 18: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("ARENA_GAR_F0"); // Arena Workshop
		case 19: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("ARENA_GAR_F1"); // Arena Workshop B1
		case 20: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("ARENA_GAR_F2"); // Arena Workshop B2
		case 21: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("CASINO_GARNAME"); // Casino Penthouse
		case 22: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("ARCADE_GARNAME"); // Arcade
		case 25: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("AUT_SHP_GAR"); // Auto Shop
		case 26: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("FIXER_GARNAME"); // Agency
		case 29:
		{
			int level = (garageSlotIterator - 1) / 10;
			switch (level)
			{
			case 0: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MSG_B1"); // Eclipse Blvd Garage B1
			case 1: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MSG_B2"); // Eclipse Blvd Garage B2
			case 2: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MSG_B3"); // Eclipse Blvd Garage B3
			case 3: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MSG_B4"); // Eclipse Blvd Garage B4
			case 4: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MSG_B5"); // Eclipse Blvd Garage B5
			}
		}
		case 30:
		{
			int level = (garageSlotIterator - 1) / 10;
			switch (level)
			{
			case 0: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("VPG_B1"); // Basement Level 1
			case 1: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("VPG_B2"); // Basement Level 2
			case 2: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("VPG_B3"); // Basement Level 3
			case 3: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("VPG_B4"); // Basement Level 4
			case 4: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("VPG_B5"); // Basement Level 5
			}
		}
		case 31: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("BO_GARNAME"); // Bail Office
		case 32: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("HD_GARNAME"); // Garment Factory
		case MAX_GARAGE_NUM + 0: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("GRTRUCK"); // Mobile Operations Center
		case MAX_GARAGE_NUM + 1: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_GAR0"); // Nightclub B1
		case MAX_GARAGE_NUM + 2: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_CLUBT"); // Terrorbyte
		case MAX_GARAGE_NUM + 3: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_SUB"); // Kosatka
		}

		return std::string();
	}

	PersonalVehicles::PersonalVehicle::PersonalVehicle(int id, MPSV_Entry* data) :
		m_Id(id),
		m_Data(data)
	{
		m_Model = m_Data->VehicleModel;
		m_Plate = m_Data->NumberPlateText;
		m_Name  = std::format("{} ({})", HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(m_Model)), m_Plate);

		SetGarage();
		SetOwnedMods();
	}

	int PersonalVehicles::PersonalVehicle::GetId()
	{
		return m_Id;
	}

	MPSV_Entry* PersonalVehicles::PersonalVehicle::GetData()
	{
		return m_Data;
	}

	joaat_t PersonalVehicles::PersonalVehicle::GetModel()
	{
		return m_Model;
	}

	std::string PersonalVehicles::PersonalVehicle::GetPlate()
	{
		return m_Plate;
	}

	std::string PersonalVehicles::PersonalVehicle::GetName()
	{
		return m_Name;
	}

	std::string PersonalVehicles::PersonalVehicle::GetGarage()
	{
		return m_Garage;
	}

	std::map<int, int32_t> PersonalVehicles::PersonalVehicle::GetOwnedMods()
	{
		return m_OwnedMods;
	}

	void PersonalVehicles::PersonalVehicle::SetGarage()
	{
		for (int propertyIterator = 0; propertyIterator < MAX_GARAGE_NUM + 4; propertyIterator++)
		{
			auto propertyStatState = GetPropertyStatState(propertyIterator);
			if (propertyStatState > 0)
			{
				auto garageSize   = GetPropertyGarageSize(propertyIterator);
				auto garageOffset = GetPropertyGarageOffset(propertyIterator);
				for (int garageSlotIterator = 1; garageSlotIterator <= garageSize; garageSlotIterator++)
				{
					auto itemInSlot = *ScriptGlobal(1940530).At(garageOffset).At(garageSlotIterator).As<int*>() - 1;
					if (itemInSlot == m_Id)
					{
						auto staticPropertyString = GetStaticPropertyName(propertyIterator, garageSlotIterator);
						if (staticPropertyString.empty())
						{
							m_Garage = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ScriptGlobal(1312335).At(propertyStatState, 1951).At(16).As<const char*>());
						}
						else
						{
							m_Garage = staticPropertyString;
						}
						return;
					}
				}
			}
		}
	}

	void PersonalVehicles::PersonalVehicle::SetOwnedMods()
	{
		for (int i = static_cast<int>(CustomVehicleModType::MOD_SECONDARY_CUSTOM); i <= static_cast<int>(CustomVehicleModType::MOD_MODEL_HASH); i++)
		{
			m_OwnedMods[i] = 0;
		}

		auto xenonLights = m_Data->ModTypes[static_cast<int>(VehicleModType::MOD_XENON_LIGHTS)];
		auto flags1 = m_Data->Flags1;
		auto tyreType = m_Data->TyreType;
		auto pvFlags = m_Data->PersonalVehicleFlags;

		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_MODEL_HASH)] = m_Data->VehicleModel;
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_PLATE_STYLE)] = m_Data->NumberPlateTextIndex;
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_WINDOW_TINT)] = m_Data->WindowTint;
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_WHEEL_TYPE)] = m_Data->WheelType;
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_PRIMARY_COL)] = m_Data->Colours1;
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_SECONDARY_COL)] = m_Data->Colours2;
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_PEARLESCENT_COL)] = m_Data->ExtraColours1;
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_WHEEL_COL)] = m_Data->ExtraColours2;
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_INTERIOR_COL)] = m_Data->ExtraColour5;
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_DASHBOARD_COL)] = m_Data->ExtraColour6;

		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_PRIMARY_CUSTOM)] = flags1.IsSet(13);
		if (m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_PRIMARY_CUSTOM)])
		{
			m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_PRIMARY_COL_R)] = m_Data->CustomPrimaryColourR;
			m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_PRIMARY_COL_G)] = m_Data->CustomPrimaryColourG;
			m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_PRIMARY_COL_B)] = m_Data->CustomPrimaryColourB;
		}

		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_SECONDARY_CUSTOM)] = flags1.IsSet(12);
		if (m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_SECONDARY_CUSTOM)])
		{
			m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_SECONDARY_COL_R)] = m_Data->CustomPrimaryColourR;
			m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_SECONDARY_COL_G)] = m_Data->CustomPrimaryColourG;
			m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_SECONDARY_COL_B)] = m_Data->CustomPrimaryColourB;
		}

		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_TIRESMOKE_COL_R)] = m_Data->TyreSmokeR;
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_TIRESMOKE_COL_G)] = m_Data->TyreSmokeG;
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_TIRESMOKE_COL_B)] = m_Data->TyreSmokeB;
		m_OwnedMods[static_cast<int>(VehicleModType::MOD_TYRE_SMOKE)] = !(m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_TIRESMOKE_COL_R)] == 255 && m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_TIRESMOKE_COL_G)] == 255 && m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_TIRESMOKE_COL_B)] == 255);

		if (xenonLights > 0)
		{
			m_OwnedMods[static_cast<int>(VehicleModType::MOD_XENON_LIGHTS)] = 1;
			m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_XENON_COL)] = xenonLights - 2;
		}
		else
		{
			m_OwnedMods[static_cast<int>(VehicleModType::MOD_XENON_LIGHTS)] = 0;
		}

		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_NEON_LEFT_ON)] = flags1.IsSet(30);
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_NEON_RIGHT_ON)] = flags1.IsSet(31);
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_NEON_FRONT_ON)] = flags1.IsSet(28);
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_NEON_BACK_ON)] = flags1.IsSet(29);
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_NEON_COL_R)] = m_Data->NeonColourR;
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_NEON_COL_G)] = m_Data->NeonColourG;
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_NEON_COL_B)] = m_Data->NeonColourB;

		if (tyreType != 0)
		{
			m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_TIRE_CAN_BURST)] = tyreType > 1;
			m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_DRIFT_TIRE)] = tyreType == 3;
		}
		else
		{
			m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_TIRE_CAN_BURST)] = flags1.IsSet(9);
		}

		m_OwnedMods[static_cast<int>(VehicleModType::MOD_TURBO)] = m_Data->ModTypes[static_cast<int>(VehicleModType::MOD_TURBO)];
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_FRONTWHEEL_VAR)] = m_Data->ModVariation[0] != 0;
		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_REARWHEEL_VAR)] = m_Data->ModVariation[1] != 0;

		for (int slot = static_cast<int>(VehicleModType::MOD_SPOILERS); slot <= static_cast<int>(VehicleModType::MOD_LIGHTBAR); slot++)
		{
			if (slot == static_cast<int>(VehicleModType::MOD_TURBO) || slot == static_cast<int>(VehicleModType::MOD_TYRE_SMOKE) || slot == static_cast<int>(VehicleModType::MOD_XENON_LIGHTS))
				continue;

			auto val = m_Data->ModTypes[slot] - 1;
			if (val != -1)
			{
				m_OwnedMods[slot] = val;
			}
		}

		for (int extra = static_cast<int>(CustomVehicleModType::MOD_EXTRA_14); extra <= static_cast<int>(CustomVehicleModType::MOD_EXTRA_1); extra++)
		{
			auto extraId = (extra - static_cast<int>(CustomVehicleModType::MOD_EXTRA_1)) * -1;
			m_OwnedMods[extra] = flags1.IsSet(extraId - 1);
		}

		m_OwnedMods[static_cast<int>(CustomVehicleModType::MOD_HAS_CLAN_LOGO)] = pvFlags.IsSet(static_cast<ePersonalVehicleFlags>(8));
	}

	int PersonalVehicles::PersonalVehicle::GetCurrentId()
	{
		if (auto savedMPGlobals = g_SavedMPGlobals::Get())
		{
			return savedMPGlobals->Entries[0].GeneralSaved.LastSavedCar;
		}

		return -1;
	}

	int PersonalVehicles::PersonalVehicle::GetCurrentHandle()
	{
		if (auto freemodeGeneral = FreemodeGeneral::Get())
		{
			return freemodeGeneral->PersonalVehicleIndex;
		}

		return -1;
	}

	bool PersonalVehicles::PersonalVehicle::DespawnCurrent()
	{
		if (auto MPSV = MPSV::Get())
		{
			MPSV->Entries[GetCurrentId()].PersonalVehicleFlags.Clear(ePersonalVehicleFlags::TRIGGER_SPAWN_TOGGLE);
			for (int i = 0; GetCurrentHandle() != -1; i++)
			{
				ScriptMgr::Yield(100ms);
				if (i > 30)
					return false;
			}
			return true;
		}

		return false;
	}

	bool PersonalVehicles::PersonalVehicle::Repair()
	{
		if (auto MPSV = MPSV::Get())
		{
			if (MPSV->Entries[m_Id].PersonalVehicleFlags.IsSet(ePersonalVehicleFlags::DESTROYED) && MPSV->Entries[m_Id].PersonalVehicleFlags.IsSet(ePersonalVehicleFlags::HAS_INSURANCE))
			{
				MPSV->Entries[m_Id].PersonalVehicleFlags.Clear(ePersonalVehicleFlags::DESTROYED);
				MPSV->Entries[m_Id].PersonalVehicleFlags.Clear(ePersonalVehicleFlags::IMPOUNDED);
				MPSV->Entries[m_Id].PersonalVehicleFlags.Clear(ePersonalVehicleFlags::UNK2);
				return true;
			}
		}

		return false;
	}

	bool PersonalVehicles::PersonalVehicle::Summon(bool bring)
	{
		if (auto freemodeGeneral = FreemodeGeneral::Get())
		{
			if (freemodeGeneral->RequestedPersonalVehicleId != -1)
				return false;

			if (!DespawnCurrent())
			{
				LOG(WARNING) << "Timed out despawning personal vehicle.";
				return false;
			}

			Repair();
			
			ScriptMgr::Yield(100ms);

			if (bring)
				freemodeGeneral->NodeDistanceCheck = 0;
			freemodeGeneral->PersonalVehicleRequested   = TRUE; // am_pi_menu also sets the field 956 but I guess we don't need that
			freemodeGeneral->Exec1Impound               = FALSE; // not really sure what this does
			freemodeGeneral->RequestedPersonalVehicleId = m_Id;

			ScriptMgr::Yield(100ms);

			*ScriptLocal("freemode"_J, 19447).At(176).As<int*>() = 0;

			if (bring)
			{
				for (int i = 0; GetCurrentHandle() == -1; i++)
				{
					ScriptMgr::Yield(100ms);
					if (i > 30)
						break;
				}

				auto handle = Vehicle(GetCurrentHandle());
				auto coords = Self::GetPed().GetPosition();
				handle.SetPosition(coords);
				Self::GetPed().SetInVehicle(handle.GetHandle());
			}

			return true;
		}

		return false;
	}

	void PersonalVehicles::RefreshPersonalVehiclesImpl()
	{
		const auto now = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(now - m_LastUpdate) < 10s)
			return;

		m_LastUpdate = std::chrono::high_resolution_clock::now();

		FiberPool::Push([] {
			RegisterVehicles();
			RefreshGarages();
		});
	}

	void PersonalVehicles::RefreshGaragesImpl()
	{
		m_Garages.clear();
		for (const auto& [name, ptr] : GetPersonalVehicles())
		{
			if (auto garageName = ptr->GetGarage(); !garageName.empty())
			{
				m_Garages.emplace(garageName);
			}
		}
	}

	void PersonalVehicles::RegisterVehiclesImpl()
	{
		if (auto mpsv = MPSV::Get())
		{
			const auto arraySize = *(int*)mpsv;

			for (int i = 0; i < arraySize; i++)
			{
				if (i % 100 == 0)
					ScriptMgr::Yield();

				auto data = &MPSV::Get()->Entries[i];

				const auto model  = data->VehicleModel;
				const auto& it    = m_PVLookup.find(i);
				const auto exists = it != m_PVLookup.end();

				if (STREAMING::IS_MODEL_A_VEHICLE(model))
				{
					auto veh = std::make_unique<PersonalVehicle>(i, data);

					if (exists)
					{
						if (veh->GetName() != it->second)
						{
							m_PersonalVehicles.erase(it->second);

							it->second = veh->GetName();
							m_PersonalVehicles.emplace(veh->GetName(), std::move(veh));
						}
						else
						{
							m_PersonalVehicles[veh->GetName()]->SetGarage();
						}

						continue;
					}

					m_PVLookup.emplace(i, veh->GetName());
					m_PersonalVehicles.emplace(veh->GetName(), std::move(veh));
					continue;
				}

				if (exists)
				{
					m_PersonalVehicles.erase(it->second);
					m_PVLookup.erase(i);
				}
			}
		}
	}
}