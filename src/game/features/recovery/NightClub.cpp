#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Stats.hpp"

#include <ctime>

namespace YimMenu::Features
{
	class NightClubSafePayout : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;
		bool running = false;
		int time1    = 1;

		virtual void OnTick() override
		{
			time_t timestamp;
			time(&timestamp);
			if (time1 + 5 < timestamp)
			{
				time1   = timestamp;
				running = true;
				Stats::SetInt("MPX_CLUB_POPULARITY", 850); //Sets club popularity to 850 (loses 50 per payout)
				Stats::SetInt("MPX_CLUB_PAY_TIME_LEFT", 1000); //Triggers instant payout and removes payout timeout (int Time is in milliseconds)
				Stats::SetInt("MPX_NIGHTCLUB_EARNINGS", 250000); //Manipulates the total earnings
			}
		}

		virtual void OnDisable() override
		{
			running = false;
		}
	};

	static NightClubSafePayout _NightClubSafePayout{"nightclubsafe", "Trigger nightclub safe payout", "Triggers nighclub safe payout"};
}