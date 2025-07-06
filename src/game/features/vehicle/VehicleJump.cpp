#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "types/pad/ControllerInputs.hpp"

namespace YimMenu::Features
{
	class VehicleJump : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			auto veh = Self::GetVehicle();
			if (!veh)
				return;

			// Disable default handbrake action to capture input manually
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE, false);

			if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(
				    veh.GetHandle(),
				    1, // force type
				    0.0f,
				    0.0f,
				    20.0f, // force vector (x,y,z) - strong upwards force
				    0.0f,
				    0.0f,
				    0.0f, // offset vector
				    0,
				    0,
				    1,
				    1,
				    0,
				    1); // other params: apply force to center, etc.
			}
		}
	};

	static VehicleJump _VehicleJump{"vehjump", "Vehicle Jump", "Allows the vehicle to jump when the handbrake is pressed"};
}
