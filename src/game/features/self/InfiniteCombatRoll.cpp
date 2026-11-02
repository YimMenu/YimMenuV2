#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Stats.hpp"

namespace YimMenu::Features
{
	class InfiniteCombatRoll : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!*Pointers.IsSessionStarted)
			{
				for (int i = 0; i <= 2; i++)
					Stats::SetInt("SP" + std::to_string(i) + "_SHOOTING_ABILITY", 150);
			}
			else
			{
				Stats::SetInt("MPX_SHOOTING_ABILITY", 150);
			}
		}
	};

	static InfiniteCombatRoll _InfiniteCombatRoll{"infinitecombatroll", "Infinite Combat Roll", "Allows you to roll infinitely"};
};