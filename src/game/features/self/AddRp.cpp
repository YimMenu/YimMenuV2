#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"
#include "game/backend/Self.hpp"
#include "game/frontend//submenus/Recovery/StatEditor.hpp"

namespace YimMenu::Features
{
	class AddRp : public Command
	{
		using Command::Command;


		virtual void OnCall() override
		{
			int current_rp = YimMenu::Submenus::GetStatInt("CHAR_XP_FM");
			YimMenu::Submenus::SetStatInt("CHAR_XP_FM", current_rp + 100000);
		}
	};
	static AddRp _AddRp{"addrp", "Add 10k RP", "Add 10.000 RP."};
}