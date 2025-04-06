#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"
#include "game/frontend//submenus/Recovery/StatEditor.hpp"
#include "game/gta/Stats.hpp"

namespace YimMenu::Features
{
	class AddRp100K : public Command
	{
		using Command::Command;


		virtual void OnCall() override
		{
			int current_rp = YimMenu::Submenus::GetStatInt("CHAR_XP_FM");
			YimMenu::Submenus::SetStatInt("CHAR_XP_FM", current_rp + 100000);
		}
	};
	static AddRp100K _AddRp{"addrp100k", "Add 100k RP", "Add 100.000 RP (Don't use it to much)."};
}