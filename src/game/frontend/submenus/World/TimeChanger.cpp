#include "core/commands/Command.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	static IntCommand _HourSlider{"timeslider_hour", "Hour", "Select hour", 0, 23, 12};
	static IntCommand _MinuteSlider{"timeslider_minute", "Minute", "Select minute", 0, 59, 0};
	static IntCommand _SecondSlider{"timeslider_second", "Second", "Select second", 0, 59, 0};

	class SetTime : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(_HourSlider.GetState(), _MinuteSlider.GetState(), _SecondSlider.GetState());
		}
	};

	class FreezeTime : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(_HourSlider.GetState(), _MinuteSlider.GetState(), _SecondSlider.GetState());
		}

		virtual void OnDisable() override
		{
			NETWORK::NETWORK_CLEAR_CLOCK_TIME_OVERRIDE();
		}
	};

	static SetTime _SetTime{"settime", "Set Time", "Set clock to selected time"};
	static FreezeTime _FreezeTime{"freezetime", "Freeze Time", "Freeze the clock time at selected values"};
}
