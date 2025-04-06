#include "core/commands/Command.hpp"
#include "game/gta/StatsEditor.hpp"
#include "game/backend/AnticheatBypass.hpp"

namespace YimMenu::Features
{
	class AddRp10K : public Command
	{
		using Command::Command;


		virtual void OnCall() override
		{
			if (AnticheatBypass::IsFSLLoaded())
			{
				int current_rp = StatsEditor::GetStatInt("CHAR_XP_FM");
				StatsEditor::SetStatInt("CHAR_XP_FM", current_rp + 10000);
			}
		}
	};
	static AddRp10K _AddRp{"addrp10k", "Add 10k RP", "Add 10.000 RP (Don't use it to much)."};
}