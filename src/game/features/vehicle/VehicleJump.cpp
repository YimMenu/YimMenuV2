#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "types/pad/ControllerInputs.hpp"
// This can literally be recycled almost word
namespace YimMenu::Features
{
	class VehicleJump : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			auto veh = Self::GetVehicle();   // Check if player is in the vehicle
			if (!veh)			 // If not, then don't do anything.
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
				    20.0f, // X Y Z - modifies the Z force (responsible for up or down) - strong upwards force
				    0.0f,
				    0.0f,
				    0.0f,
				    0,
				    0,
				    1,
				    1,
				    0,
				    1);
			}
		}
	};

	static VehicleJump _VehicleJump{"vehjump", "Vehicle Jump", "Allows the vehicle to jump when the handbrake is pressed"};   // this is literally almost a word-for-word recycle of the version found in the legacy version of YimMenu
}
