#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class LowerVehicleStance : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			auto veh = Self::GetVehicle();
			if (veh)
			{
				veh.LowerStance(true);
			}
		}

		virtual void OnDisable() override
		{
			auto veh = Self::GetVehicle();
			if (veh)
			{
				veh.LowerStance(false);
			}
		}
	};

	static LowerVehicleStance _LowerVehicleStance{"lowervehiclestance", "Lower Vehicle Stance", "Lowers your current vehicle's stance. Only some vehicles are supported"};
}