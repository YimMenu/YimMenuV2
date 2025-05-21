#include "core/commands/Command.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	static IntCommand _HourSlider{"hour_slider", "Hour", "Set hour (0–23)", 0, 23, 12};
	static IntCommand _MinuteSlider{"minute_slider", "Minute", "Set minute (0–59)", 0, 59, 0};
	static IntCommand _SecondSlider{"second_slider", "Second", "Set second (0–59)", 0, 59, 0};

	class SetNetworkTime : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(_HourSlider.GetState(), _MinuteSlider.GetState(), _SecondSlider.GetState());
		}
	};

	class FreezeNetworkTime : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;
		int frozenHour{}, frozenMinute{}, frozenSecond{};

		virtual void OnEnable() override
		{
			frozenHour   = _HourSlider.GetState();
			frozenMinute = _MinuteSlider.GetState();
			frozenSecond = _SecondSlider.GetState();
		}

		virtual void OnTick() override
		{
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(frozenHour, frozenMinute, frozenSecond);
		}

		virtual void OnDisable() override
		{
			NETWORK::NETWORK_CLEAR_CLOCK_TIME_OVERRIDE();
		}
	};

	static SetNetworkTime _SetTime{"setnetworktime", "Set Time", "Sets the current online time"};
	static FreezeNetworkTime _FreezeTime{"freezenetworktime", "Freeze Time", "Freezes the online clock at the selected time"};
}
