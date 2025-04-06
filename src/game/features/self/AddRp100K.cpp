#include "core/commands/Command.hpp"
#include "game/gta/StatsEditor.hpp"
#include "game/backend/AnticheatBypass.hpp"

namespace YimMenu::Features
{
	class AddRp100K : public Command
	{
		using Command::Command;


		virtual void OnCall() override
		{
			if (AnticheatBypass::IsFSLLoaded())
			{
				int current_rp = StatsEditor::GetStatInt("CHAR_XP_FM");
				StatsEditor::SetStatInt("CHAR_XP_FM", current_rp + 100000);
			}
		}
	};
	static AddRp100K _AddRp{"addrp100k", "Add 100k RP", "Add 100.000 RP (Don't use it to much)."};
}