#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class KeepPlayerClean : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!Self::GetPed())
				return;

			Self::GetPed().ClearDamage();
		}
	};

	static KeepPlayerClean _KeepPlayerClean{"keepplayerclean", "Keep Player Clean", "Keeps the player clean from any blood, dirt, water."};
}