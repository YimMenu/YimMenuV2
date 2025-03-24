#include "core/commands/StringCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/commands/BoolCommand.hpp"
#include "game/gta/VehicleValues.hpp"

namespace YimMenu::Features
{
	static StringCommand _VehicleModelname{"vehmodelname", "Vehicle model name", "The model name of the vehicle you wish to spawn."};
	static BoolCommand _SpawnInVehicle{"spawninvehicle", "Spawn in vehicle", "Enter vehicle once it is spawned", false};
	static BoolCommand _SpawnWithMaximumUpgrades{"spawnupgraded", "Spawn with maximum upgrades", "Spawn vehicle with maximum upgrades", false};

	class SpawnVehicle : public Command {
		using Command::Command;

		virtual void OnCall() override
		{
			auto model = _VehicleModelname.GetString();

			Hash modelHash = Joaat(model);

			if (!modelHash)
			{
				LOG(WARNING) << "Couldn't spawn vehicle because no model name was specified.";
				return;
			}

			if (STREAMING::IS_MODEL_IN_CDIMAGE(modelHash))
			{
				STREAMING::REQUEST_MODEL(modelHash);

				while (!STREAMING::HAS_MODEL_LOADED(modelHash)) {
					ScriptMgr::Yield();
				}

				auto veh = VEHICLE::CREATE_VEHICLE(modelHash,
				    Self::GetPed().GetPosition().x + 10,
				    Self::GetPed().GetPosition().y,
				    Self::GetPed().GetPosition().z,
				    0,
				    true,
				    true,
					true
				);

				VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true, true);
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, false);

				DECORATOR::DECOR_SET_INT(veh, "MPBitset", 1);

				ScriptMgr::Yield();

				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(modelHash);

				if (_SpawnInVehicle.GetState())
				{
					PED::SET_PED_INTO_VEHICLE(Self::GetPed().GetHandle(), veh, -1);
				}

				if (_SpawnWithMaximumUpgrades.GetState())
				{
					VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
				
					for (int t = MOD_SPOILERS; t < MOD_LIGHTBAR; t++) {
						VEHICLE::SET_VEHICLE_MOD(veh, t, VEHICLE::GET_NUM_VEHICLE_MODS(veh, t) - 1, false);
					}

					VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);
				}
			}
		}
	};

	static SpawnVehicle _SpawnVehicle{"spawnvehicle", "Spawn Vehicle", "Spawns a vehicle at your current location"};
}