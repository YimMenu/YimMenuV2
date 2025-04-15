#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class SlideRun : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (auto ped = Self::GetPed())
			{
				if (PED::IS_PED_RAGDOLL(ped.GetHandle()))
					return;

				if (TASK::IS_PED_RUNNING(ped.GetHandle()) || TASK::IS_PED_SPRINTING(ped.GetHandle()))
					ENTITY::APPLY_FORCE_TO_ENTITY(ped.GetHandle(), 1, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 1, 1, true, false, true);
			}
		}
	};

	static SlideRun _SlideRun{"sliderun", "Sliding Run", "your Player will Sliding like Flash"};
}
