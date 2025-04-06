#include "core/commands/Command.hpp"
#include "game/gta/StatsEditor.hpp"
#include "game/backend/AnticheatBypass.hpp"

namespace YimMenu::Features
{
	class AddMoney : public Command
	{
		using Command::Command;


		virtual void OnCall() override
		{
			if (AnticheatBypass::IsFSLLoaded())
			{
				int current_money = StatsEditor::GetStatInt("BANK_BALANCE");
				StatsEditor::SetStatInt("BANK_BALANCE", current_money + 10000000);
			}
		}
	};
	static AddMoney _AddMoney{"addmoney", "Add 10M $", "Add 10.000.000^$ (Don't use it to much)."};
}