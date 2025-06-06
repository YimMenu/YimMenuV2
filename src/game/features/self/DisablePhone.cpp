#include "core/commands/LoopedCommand.hpp"
#include "game/gta/ScriptGlobal.hpp"

namespace YimMenu::Features
{
	class DisablePhone : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			*ScriptGlobal(2707980).As<int*>() = 1;
		}

		virtual void OnDisable() override
		{
			*ScriptGlobal(2707980).As<int*>() = 0;
		}
	};

	static DisablePhone _DisablePhone{"disablephone", "Disable Phone", "Disable your Phone avoid getting Calls"};
}
