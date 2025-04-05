#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class Clear : Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Self::GetPed().Clear();
		}
	};

	static Clear _Clear{"clear", "Clear", "Clears all the dirt and blood on you."};
}