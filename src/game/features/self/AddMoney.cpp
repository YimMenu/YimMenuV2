#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"
#include "game/frontend//submenus/Recovery/StatEditor.hpp"
#include "game/gta/Stats.hpp"

namespace YimMenu::Features
{
	class AddMoney : public Command
	{
		using Command::Command;


		virtual void OnCall() override
		{
			int current_money = YimMenu::Submenus::GetStatInt("BANK_BALANCE");
			YimMenu::Submenus::SetStatInt("BANK_BALANCE", current_money + 10000000);
		}
	};
	static AddMoney _AddMoney{"addmoney", "Add 10M $", "Add 10.000.000^$ (Don't use it to much)."};
}