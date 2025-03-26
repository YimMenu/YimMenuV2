#include "core/commands/StringCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/commands/BoolCommand.hpp"
#include "game/gta/data/VehicleValues.hpp"
#include "core/frontend/Notifications.hpp"

namespace YimMenu::Features
{
	static StringCommand _VehicleModelname{"vehmodelname", "Vehicle model name", "The model name of the vehicle you wish to spawn."};
	static BoolCommand _SpawnInVehicle{"spawninvehicle", "Spawn in vehicle", "Enter vehicle once it is spawned", false};
	static BoolCommand _SpawnWithMaximumUpgrades{"spawnupgraded", "Spawn with maximum upgrades", "Spawn vehicle with maximum upgrades", false};
	static BoolCommand _UseCustomLicensePlate{"usecustomlicenseplate", "Use custom license plate", "Use a custom license plate for the vehicle", false};
	static StringCommand _CustomLicensePlate{"customlicenseplate", "Custom license plate", "The custom license plate for the vehicle"};

	class SpawnVehicle : public Command {
		using Command::Command;

		virtual void OnCall() override
		{
			auto model = _VehicleModelname.GetString();
			
			if (!model.length())
			{
				Notifications::Show("Spawn Vehicle", "No model name provided.", NotificationType::Error);
				return;
			}

			Hash modelHash = Joaat(model);

			assert(modelHash != 0);

			if (STREAMING::IS_MODEL_IN_CDIMAGE(modelHash))
			{
				rage::fvector3 coords = Self::GetPed().GetPosition();
				auto veh              = Vehicle::Create(modelHash, coords, Self::GetPed().GetHeading());
				auto vehHandle        = veh.GetHandle();

				if (_SpawnInVehicle.GetState())
				{
					PED::SET_PED_INTO_VEHICLE(Self::GetPed().GetHandle(), vehHandle, (int)SeatPositions::SEAT_DRIVER);
				}

				if (_SpawnWithMaximumUpgrades.GetState())
				{
					veh.Upgrade();
				}

				if (_UseCustomLicensePlate.GetState())
				{
					std::string licensePlate = _CustomLicensePlate.GetString();

					if (licensePlate.length() > 8)
					{
						Notifications::Show("Spawn Vehicle", "License plate must be 8 characters or less.", NotificationType::Error);
					}
					else if (licensePlate.length() > 0)
					{
						veh.SetPlateText(licensePlate);
					}				
				}
			}
			else
			{
				Notifications::Show("Spawn Vehicle", "Invalid model name provided.", NotificationType::Error);
			}
		}
	};

	static SpawnVehicle _SpawnVehicle{"spawnvehicle", "Spawn Vehicle", "Spawns a vehicle at your current location"};
}