#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"

namespace YimMenu::Features
{
	class CayoPericoCooldown : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Stats::SetInt("MPX_H4_TARGET_POSIX", 1);
			Stats::SetInt("MPX_H4_COOLDOWN", 1);
			Stats::SetInt("MPX_H4_COOLDOWN_HARD", 1);
		}
	};

	static CayoPericoCooldown _CayoPericoCooldown{"skipcayocooldown", "Cooldown skip for Cayo Perico Heist", "Skips the cooldown between each Cayo Perico heist"};
}