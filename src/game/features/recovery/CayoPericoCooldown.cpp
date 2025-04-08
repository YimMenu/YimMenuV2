#include "core/commands/Command.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Stats.hpp"

namespace YimMenu::Features
{
	class CayoPericoCooldown : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			std::string index = "MP" + std::to_string(Stats::GetCharIndex()) + "_";
			Stats::SetInt(index + "H4_TARGET_POSIX", 1659643454);
			Stats::SetInt(index + "H4_COOLDOWN", 0);
			Stats::SetInt(index + "H4_COOLDOWN_HARD", 0);
			Stats::SetInt(index + "H4_TARGET_POSIX", 1659429119);
			Stats::SetInt(index + "H4_COOLDOWN", 0);
			Stats::SetInt(index + "H4_COOLDOWN_HARD", 0);
		}
	};

	static CayoPericoCooldown _CayoPericoCooldown{"cayopericocooldown", "Cooldown skip for Cayo Perico Heist", "Skips the cooldown between each Cayo Perico heist."};
}