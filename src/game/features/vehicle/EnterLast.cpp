#include "core/commands/Command.hpp"
#include "game/gta/Vehicle.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/data/VehicleValues.hpp"

namespace YimMenu::Features
{
	class EnterLastVehicle : Command
	{
		using Command::Command;
			
		virtual void OnCall() override
		{
			auto vehicleHandle = PLAYER::GET_PLAYERS_LAST_VEHICLE();

			if (vehicleHandle != 0 && vehicleHandle != Self::GetVehicle().GetHandle()) {
				// TODO This logic should probably be moved into the Vehicle class
				for (int seat = (int)SeatPositions::SEAT_DRIVER; seat < (int)SeatPositions::SEAT_BACKPASSENGER; seat++)
				{
					if (VEHICLE::IS_VEHICLE_SEAT_FREE(vehicleHandle, seat, true))
					{
						PED::SET_PED_INTO_VEHICLE(Self::GetPed().GetHandle(), vehicleHandle, seat);
						break;
					}
				}
			}
		}
	};

	static EnterLastVehicle _EnterLastVehicle{"enterlastvehicle", "Enter last vehicle", "Enters the last vehicle you were in."};
};