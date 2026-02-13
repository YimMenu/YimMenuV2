#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "core/commands/Command.hpp"
#include "core/frontend/Notifications.hpp"

namespace YimMenu::Features
{
	class TeleportToNearestVehicle : public Command
	{
	public:
		using Command::Command;

		virtual void OnCall() override
		{
			constexpr float SEARCH_RADIUS = 500.0f; // Search radius in GTA units
			auto self_ped = Self::GetPed();
			
			if (!self_ped)
			{
				Notifications::Show("Teleport", "Failed to get player ped");
				return;
			}

			auto self_pos = self_ped.GetPosition();
			Vehicle closest_vehicle = VEHICLE::GET_CLOSEST_VEHICLE(
				self_pos.x,
				self_pos.y,
				self_pos.z,
				SEARCH_RADIUS,
				0,  // 0 = any model
				70  // flags
			);

			if (!closest_vehicle)
			{
				Notifications::Show("Teleport", "No vehicles found nearby");
				return;
			}

			// Check if we can find an empty seat
			int seat_index = -1; // -1 is driver seat
			for (int i = -1; i < VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(closest_vehicle); i++)
			{
				if (VEHICLE::IS_VEHICLE_SEAT_FREE(closest_vehicle, i))
				{
					seat_index = i;
					break;
				}
			}

			if (seat_index == -2) // No free seats found
			{
				Notifications::Show("Teleport", "No free seats in nearest vehicle");
				return;
			}

			// Teleport to vehicle and enter it
			auto vehicle_pos = Vehicle(closest_vehicle).GetPosition();
			self_ped.TeleportTo(vehicle_pos);
			PED::SET_PED_INTO_VEHICLE(self_ped.GetHandle(), closest_vehicle, seat_index);
			Notifications::Show("Teleport", "Teleported to nearest vehicle");
		}
	};

	static TeleportToNearestVehicle _TeleportToNearestVehicle{"tpnearestVehicle", "Teleport to Nearest Vehicle", "Teleports you into the nearest vehicle"};
}
