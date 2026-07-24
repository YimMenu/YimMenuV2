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

	static IntCommand _NightclubPopularityInterval{"nightclubpopularityinterval", "Popularity Loop Interval (min)", "The interval between popularity maintenance.", 0, 60, 5};
	static IntCommand _NightclubSafeInterval{"nightclubsafeinterval", "Safe Collection Interval (min)", "The interval between safe collection.", 0, 60, 5};
	static IntCommand _NightclubPayTimeInterval{"nightclubpaytimeinterval", "Pay Time Reset Interval (min)", "The interval between pay time reset.", 0, 60, 5};

	class KeepNightclubPopularityLoop : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			static auto last_run = std::chrono::steady_clock::now() - std::chrono::hours(1);
			auto now             = std::chrono::steady_clock::now();

			if (std::chrono::duration_cast<std::chrono::minutes>(now - last_run).count() >= _NightclubPopularityInterval.GetState())
			{
				Stats::SetInt("mp0_club_popularity", 1000);
				Stats::SetInt("mp1_club_popularity", 1000);
				last_run = now;
			}
		}
	};

	class AutoCollectNightclubSafeLoop : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			static auto last_run = std::chrono::steady_clock::now() - std::chrono::hours(1);
			auto now             = std::chrono::steady_clock::now();

			if (std::chrono::duration_cast<std::chrono::minutes>(now - last_run).count() >= _NightclubSafeInterval.GetState())
			{
				if (GPBD_FM::Get()->Entries[Self::GetPlayer().GetId()].PropertyData.NightclubData.SafeCashValue >= 250000)
				{
					*ScriptGlobal(2708943).As<BOOL*>() = TRUE;
				}
				last_run = now;
			}
		}
	};

	class AutoResetNightclubPayTimeLoop : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			static auto last_run = std::chrono::steady_clock::now() - std::chrono::hours(1);
			auto now             = std::chrono::steady_clock::now();

			if (std::chrono::duration_cast<std::chrono::minutes>(now - last_run).count() >= _NightclubPayTimeInterval.GetState())
			{
				Stats::SetInt("mp0_club_pay_time_left", -1);
				Stats::SetInt("mp1_club_pay_time_left", -1);
				last_run = now;
			}
		}
	};

	static KeepNightclubPopularityLoop _KeepNightclubPopularity{"keepnightclubpopularity", "Keep Nightclub Popularity Max", "Continuously sets nightclub popularity to 100%."};
	static AutoCollectNightclubSafeLoop _AutoCollectNightclubSafe{"autocollectnightclubsafe", "Auto Collect Nightclub Safe", "Automatically collects nightclub safe earnings when full."};
	static AutoResetNightclubPayTimeLoop _AutoResetNightclubPayTime{"autoresetnightclubpaytime", "Auto Reset Pay Time Left", "Automatically resets the nightclub pay time left."};
}
