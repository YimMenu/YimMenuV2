#include "core/commands/Command.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "core/commands/IntCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/Stats.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/script/globals/GPBD_FM.hpp"

namespace YimMenu::Features
{
	class MaxNightclubPopularityCommand : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			// Set popularity to max (1.0f)
			GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.NightclubData.Popularity = 1.0f;
		}
	};

	static MaxNightclubPopularityCommand _MaxNightclubPopularity{"maxnightclubpopularity", "Max Nightclub Popularity", "Sets your nightclub popularity to 100%."};

	static IntCommand _NightclubLoopInterval{"nightclubloopinterval", "Loop Interval (ms)", "The interval between popularity maintenance and safe collection.", 1000, 30000, 7000};

	class KeepNightclubPopularityLoop : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			static auto last_run = std::chrono::steady_clock::now();
			auto now = std::chrono::steady_clock::now();

			if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_run).count() >= _NightclubLoopInterval.GetState())
			{
				// Set popularity to max
				Stats::SetInt("mpx_club_popularity", 1000);
				Stats::SetInt("mpx_club_pay_time_left", -1);

				// Collect safe earnings
				*ScriptGlobal(2708943).As<BOOL*>() = TRUE;
				
				last_run = now;
			}
		}
	};

	static KeepNightclubPopularityLoop _KeepNightclubPopularity{"keepnightclubpopularity", "Keep Nightclub Popularity Max", "Continuously sets nightclub popularity and collects earnings."};
}
