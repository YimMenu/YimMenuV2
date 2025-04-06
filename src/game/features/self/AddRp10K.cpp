#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"
#include "game/backend/Self.hpp"
#include "game/frontend//submenus/Recovery/StatEditor.hpp"

namespace YimMenu::Features
{
	class AddRp10K : public Command
	{
		using Command::Command;


		virtual void OnCall() override
		{
			int current_rp = YimMenu::Submenus::GetStatInt("CHAR_XP_FM");
			YimMenu::Submenus::SetStatInt("CHAR_XP_FM", current_rp + 10000);
		}
	};
	static AddRp10K _AddRp{"addrp10k", "Add 10k RP", "Add 10.000 RP."};
}