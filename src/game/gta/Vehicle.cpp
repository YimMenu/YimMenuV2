#include "Vehicle.hpp"
#include "Natives.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/data/VehicleValues.hpp"
#include "game/gta/data/Vehicles.hpp"

namespace YimMenu
{
	Vehicle Vehicle::Create(std::uint32_t model, rage::fvector3 coords, float heading, bool setOnGroundProperly)
	{
		ENTITY_ASSERT_SCRIPT_CONTEXT();
		if (!STREAMING::IS_MODEL_IN_CDIMAGE(model))
		{
#ifdef ENTITY_DEBUG
			LOGF(WARNING, "Invalid model passed to Vehicle::Create: 0x{:X}", model);
#endif
			return nullptr;
		}

		for (int i = 0; !STREAMING::HAS_MODEL_LOADED(model); i++)
		{
			STREAMING::REQUEST_MODEL(model);
			ScriptMgr::Yield();

			if (i > 30)
			{
#ifdef ENTITY_DEBUG
				LOGF(WARNING, "Model 0x{:X} failed to load after 30 ticks, bailing out", model);
#endif
				return nullptr;
			}
		}

		Pointers.SpectatePatch->Apply();
		auto veh = Vehicle(VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, heading, true, false, false));
		Pointers.SpectatePatch->Restore();

		if (!veh)
		{
#ifdef ENTITY_DEBUG
			LOGF(WARNING, "CREATE_VEHICLE failed when creating a vehicle with model {:X}", model);
#endif
			return nullptr;
		}

		DECORATOR::DECOR_SET_INT(veh.GetHandle(), "MPBitset", 0);
		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NETWORK::VEH_TO_NET(veh.GetHandle()), true);
		if (setOnGroundProperly)
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh.GetHandle(), 0);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

		return veh;
	}

	void Vehicle::Fix()
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		ENTITY_ASSERT_SCRIPT_CONTEXT();

		if (!VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(GetHandle()))
			return;

		// this is what carmod_shop does to repair your vehicle
		VEHICLE::SET_VEHICLE_FIXED(GetHandle());
		ENTITY::SET_ENTITY_HEALTH(GetHandle(), 1000, 0, 0);
		VEHICLE::SET_VEHICLE_ENGINE_HEALTH(GetHandle(), 1000.f);
		VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(GetHandle(), 1000.f);
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(GetHandle(), 0.f);
		GRAPHICS::REMOVE_DECALS_FROM_VEHICLE(GetHandle());
		ENTITY::FORCE_ENTITY_AI_AND_ANIMATION_UPDATE(GetHandle());
		/*if (ENTITY::GET_ENTITY_MODEL(GetHandle()) == "brawler"_J)
		{
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(GetHandle(), 1084227584);
			PHYSICS::ACTIVATE_PHYSICS(GetHandle());
		}*/
	}

	int Vehicle::GetGear()
	{
		ENTITY_ASSERT_VALID();

		return VEHICLE::_GET_VEHICLE_CURRENT_DRIVE_GEAR(GetHandle());
	}

	float Vehicle::GetRevRatio()
	{
		ENTITY_ASSERT_VALID();

		return VEHICLE::_GET_VEHICLE_CURRENT_REV_RATIO(GetHandle());
	}

	float Vehicle::GetMaxSpeed()
	{
		ENTITY_ASSERT_VALID();

		return VEHICLE::GET_VEHICLE_ESTIMATED_MAX_SPEED(GetHandle());
	}

	void Vehicle::Upgrade()
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		ENTITY_ASSERT_SCRIPT_CONTEXT();

		auto veh = GetHandle();

		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);

		for (int t = (int)VehicleModType::MOD_SPOILERS; t < (int)VehicleModType::MOD_LIGHTBAR; t++)
		{
			VEHICLE::SET_VEHICLE_MOD(veh, t, VEHICLE::GET_NUM_VEHICLE_MODS(veh, t) - 1, false);
		}

		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);
	}

	std::string Vehicle::GetPlateText()
	{
		ENTITY_ASSERT_VALID();

		return VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(GetHandle());
	}

	void Vehicle::SetPlateText(std::string_view text)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();

		if (text.length() > 8)
		{
			return;
		}

		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(GetHandle(), text.data());
	}

	bool Vehicle::IsSeatFree(int seat)
	{
		ENTITY_ASSERT_VALID();

		return VEHICLE::IS_VEHICLE_SEAT_FREE(GetHandle(), seat, true);
	}

	bool Vehicle::SupportsBoost()
	{
		ENTITY_ASSERT_VALID();

		return VEHICLE::GET_HAS_ROCKET_BOOST(GetHandle());
	}

	bool Vehicle::IsBoostActive()
	{
		ENTITY_ASSERT_VALID();

		return VEHICLE::IS_ROCKET_BOOST_ACTIVE(GetHandle());
	}

	void Vehicle::SetBoostCharge(int percentage)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();

		if (!SupportsBoost())
			return;

		VEHICLE::SET_ROCKET_BOOST_FILL(GetHandle(), percentage);
	}

	void Vehicle::LowerStance(bool lower)
	{
		ENTITY_ASSERT_VALID();

		VEHICLE::SET_REDUCED_SUSPENSION_FORCE(GetHandle(), lower);
	}

	void Vehicle::BringToHalt(float distance, int duration)
	{
		ENTITY_ASSERT_VALID();

		VEHICLE::BRING_VEHICLE_TO_HALT(GetHandle(), distance, duration, FALSE);
	}

	bool Vehicle::SetOnGroundProperly()
	{
		ENTITY_ASSERT_VALID();

		return VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(GetHandle(), 5.f);
	}

	std::string Vehicle::GetFullName()
	{
		auto model = ENTITY::GET_ENTITY_MODEL(GetHandle());
		std::string gxt = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(model);
		std::string display = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(gxt.c_str());

		std::string finalName = display == "NULL" ? gxt : display;

		std::string maker = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MAKE_NAME_FROM_VEHICLE_MODEL(model));
		if (maker != "NULL")
			finalName = maker + " " + finalName;

		int id = VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(model);
		finalName = std::string(g_VehicleClassNames[id]) + " " + finalName;

		return finalName;
	}

	std::map<int, int32_t> Vehicle::GetOwnedMods()
	{
		auto vehicle = GetHandle();
		std::map<int, int32_t> ownedMods;

		for (int i = (int)CustomVehicleModType::MOD_SECONDARY_CUSTOM; i <= (int)CustomVehicleModType::MOD_MODEL_HASH; i++)
		{
			ownedMods[i] = 0;
		}

		ownedMods[(int)CustomVehicleModType::MOD_MODEL_HASH] = ENTITY::GET_ENTITY_MODEL(vehicle);

		ownedMods[(int)CustomVehicleModType::MOD_PLATE_STYLE] = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle);
		ownedMods[(int)CustomVehicleModType::MOD_WINDOW_TINT] = VEHICLE::GET_VEHICLE_WINDOW_TINT(vehicle);
		ownedMods[(int)CustomVehicleModType::MOD_WHEEL_TYPE] = VEHICLE::GET_VEHICLE_WHEEL_TYPE(vehicle);

		VEHICLE::GET_VEHICLE_COLOURS(vehicle, &ownedMods[(int)CustomVehicleModType::MOD_PRIMARY_COL], &ownedMods[(int)CustomVehicleModType::MOD_SECONDARY_COL]);
		VEHICLE::GET_VEHICLE_EXTRA_COLOURS(vehicle, &ownedMods[(int)CustomVehicleModType::MOD_PEARLESCENT_COL], &ownedMods[(int)CustomVehicleModType::MOD_WHEEL_COL]);
		VEHICLE::GET_VEHICLE_EXTRA_COLOUR_5(vehicle, &ownedMods[(int)CustomVehicleModType::MOD_INTERIOR_COL]);
		VEHICLE::GET_VEHICLE_EXTRA_COLOUR_6(vehicle, &ownedMods[(int)CustomVehicleModType::MOD_DASHBOARD_COL]);

		ownedMods[(int)CustomVehicleModType::MOD_PRIMARY_CUSTOM] = VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(vehicle);
		if (ownedMods[(int)CustomVehicleModType::MOD_PRIMARY_CUSTOM])
		{
			VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, &ownedMods[(int)CustomVehicleModType::MOD_PRIMARY_COL_R], &ownedMods[(int)CustomVehicleModType::MOD_PRIMARY_COL_G], &ownedMods[(int)CustomVehicleModType::MOD_PRIMARY_COL_B]);
		}

		ownedMods[(int)CustomVehicleModType::MOD_SECONDARY_CUSTOM] = VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(vehicle);
		if (ownedMods[(int)CustomVehicleModType::MOD_SECONDARY_CUSTOM])
		{
			VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, &ownedMods[(int)CustomVehicleModType::MOD_SECONDARY_COL_R], &ownedMods[(int)CustomVehicleModType::MOD_SECONDARY_COL_G], &ownedMods[(int)CustomVehicleModType::MOD_SECONDARY_COL_B]);
		}

		ownedMods[(int)VehicleModType::MOD_TYRE_SMOKE] = VEHICLE::IS_TOGGLE_MOD_ON(vehicle, (int)VehicleModType::MOD_TYRE_SMOKE);
		if (ownedMods[(int)VehicleModType::MOD_TYRE_SMOKE])
		{
			VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, &ownedMods[(int)CustomVehicleModType::MOD_TIRESMOKE_COL_R], &ownedMods[(int)CustomVehicleModType::MOD_TIRESMOKE_COL_G], &ownedMods[(int)CustomVehicleModType::MOD_TIRESMOKE_COL_B]);
		}

		ownedMods[(int)VehicleModType::MOD_XENON_LIGHTS] = VEHICLE::IS_TOGGLE_MOD_ON(vehicle, (int)VehicleModType::MOD_XENON_LIGHTS);
		if (ownedMods[(int)VehicleModType::MOD_XENON_LIGHTS])
		{
			ownedMods[(int)CustomVehicleModType::MOD_XENON_COL] = (int8_t)VEHICLE::GET_VEHICLE_XENON_LIGHT_COLOR_INDEX(vehicle);
		}

		ownedMods[(int)CustomVehicleModType::MOD_NEON_LEFT_ON] = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, (int)NeonLightLocations::NEON_LEFT);
		ownedMods[(int)CustomVehicleModType::MOD_NEON_RIGHT_ON] = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, (int)NeonLightLocations::NEON_RIGHT);
		ownedMods[(int)CustomVehicleModType::MOD_NEON_FRONT_ON] = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, (int)NeonLightLocations::NEON_FRONT);
		ownedMods[(int)CustomVehicleModType::MOD_NEON_BACK_ON] = VEHICLE::GET_VEHICLE_NEON_ENABLED(vehicle, (int)NeonLightLocations::NEON_BACK);
		VEHICLE::GET_VEHICLE_NEON_COLOUR(vehicle, &ownedMods[(int)CustomVehicleModType::MOD_NEON_COL_R], &ownedMods[(int)CustomVehicleModType::MOD_NEON_COL_G], &ownedMods[(int)CustomVehicleModType::MOD_NEON_COL_B]);

		ownedMods[(int)CustomVehicleModType::MOD_TIRE_CAN_BURST] = VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(vehicle);
		ownedMods[(int)CustomVehicleModType::MOD_DRIFT_TIRE] = VEHICLE::GET_DRIFT_TYRES_SET(vehicle);
		ownedMods[(int)VehicleModType::MOD_TURBO] = VEHICLE::IS_TOGGLE_MOD_ON(vehicle, (int)VehicleModType::MOD_TURBO);

		ownedMods[(int)CustomVehicleModType::MOD_FRONTWHEEL_VAR] = VEHICLE::GET_VEHICLE_MOD_VARIATION(vehicle, (int)VehicleModType::MOD_FRONTWHEEL);
		ownedMods[(int)CustomVehicleModType::MOD_REARWHEEL_VAR] = VEHICLE::GET_VEHICLE_MOD_VARIATION(vehicle, (int)VehicleModType::MOD_REARWHEEL);

		for (int slot = (int)VehicleModType::MOD_SPOILERS; slot <= (int)VehicleModType::MOD_LIGHTBAR; slot++)
			if (VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, slot) > 0)
				ownedMods[slot] = VEHICLE::GET_VEHICLE_MOD(vehicle, slot);

		for (int extra = (int)CustomVehicleModType::MOD_EXTRA_14; extra <= (int)CustomVehicleModType::MOD_EXTRA_1; ++extra)
			if (auto id = (extra - (int)CustomVehicleModType::MOD_EXTRA_1) * -1; VEHICLE::DOES_EXTRA_EXIST(vehicle, id))
				ownedMods[extra] = VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(vehicle, id);

		return ownedMods;
	}

	Vector3 Vehicle::GetSpawnLocRelToPed(int ped, joaat_t hash)
	{
		Vector3 min, max;
		MISC::GET_MODEL_DIMENSIONS(hash, &min, &max);
		return ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.f, (max - min).y, 0.f);
	}
}