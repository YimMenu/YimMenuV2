#include "core/commands/Command.hpp"
#include "core/commands/StringCommand.hpp"
#include "game/gta/Stats.hpp"
#include "core/frontend/Notifications.hpp"

namespace YimMenu::Features
{
	static StringCommand _RankWanted{"rankwanted", "Rank Wanted", "Sets your wanted level to the rank you want."};

	class SetRpRank : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto rank = _RankWanted.GetString();

			if (!rank.length())
			{
				Notifications::Show("Rank Wanted", "Please input a number.", NotificationType::Error);
				return;
			}

			int intRank;
			try
			{
				intRank = std::stoi(rank);
				if (intRank < 1 || intRank > 8000)
				{
					Notifications::Show("Rank Wanted", "Please enter a number between 1 and 8000.", NotificationType::Error);
					return;
				}
			}
			catch (const std::invalid_argument& e)
			{
				Notifications::Show("Rank Wanted", "Invalid input. Please enter a valid number.", NotificationType::Error);
				return;
			}

			double xp = 25 * intRank * intRank + 23575 * intRank - 1023150; // Source: https://gta.fandom.com/wiki/Rank

			Stats::SetInt("MPX_CHAR_SET_RP_GIFT_ADMIN", xp);
			Notifications::Show("Rank Wanted", "You have been given the rank you wanted, you need to change session.", NotificationType::Success);
		}
	};

	static SetRpRank _SetRpRank{"setrprank", "Sets your RP Rank", "Gives you the level you want by admin gift."};
}