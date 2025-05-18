#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Stats.hpp"
#include <ctime>

namespace YimMenu::Features
{
	class Arcade : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;
        bool running = false;
        int time1 = 1;

		virtual void OnTick() override
		{
			time_t timestamp;
			time(&timestamp);
            if (time1 + 5 < timestamp) //inefficient because of only 5k
            {
            time1 = timestamp;
            running = true;
            Stats::SetInt("MPX_ARCADE_PAY_TIME_LEFT", 1000); //Triggers instant payout and removes payout timeout (int Time is in milliseconds)
            }
		}

        virtual void OnDisable() override
        {
            running = false;
        }
	};

	static Arcade _Arcade{"arcadesafe", "Trigger arcade safe payout", "Triggers arcade safe payout"};
}