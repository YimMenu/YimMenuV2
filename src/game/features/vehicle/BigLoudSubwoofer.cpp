#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Pools.hpp"

namespace YimMenu::Features
{
	class AllVehsLoudRadio : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			for (auto veh : Pools::GetVehicles())
			{
				veh.ForceControl();
				auto handle = veh.GetHandle();
				auto target_veh = Vehicle(handle);
				if (target_veh.RequestControl())
					AUDIO::SET_VEHICLE_RADIO_ENABLED(handle, 1);
					AUDIO::SET_VEHICLE_RADIO_LOUD(handle, 1);
				  VEHICLE::SET_VEHICLE_ENGINE_ON(handle, 1, 1, 0);
			}
			return;
		}
	};

	static AllVehsLoudRadio _AllVehsLoudRadio{"loudsubwoffer", "Subwoofer", "Enables loud radio on vehicles, Players can hear it."};
}
