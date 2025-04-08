#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class StandOnVehicles : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			PED::SET_PED_RESET_FLAG(Self::GetPed().GetHandle(), 274, true);
		}
	};

	static StandOnVehicles _StandOnVehicles{"standonvehicles", "Stand On Vehicles", "Prevents you from ragdolling when standing on top of vehicles."};
};
