#include "core/commands/Command.hpp"
#include "types/script/ScriptEvent.hpp"

namespace YimMenu::Features
{
	class ForceLaunchHeist : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			SCRIPT_EVENT_COMMAND event;
			event.Command = SCRIPT_EVENT_COMMAND::eCommand::LaunchHeist;
			event.SetAllPlayers();
			event.Send();
		}
	};

	static ForceLaunchHeist _ForceLaunchHeist{"forcelaunchheist", "Force Launch Heist", "Forces the heist to launch from the setup screen"};
}