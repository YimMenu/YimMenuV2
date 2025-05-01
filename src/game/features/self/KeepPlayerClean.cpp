#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class ClearDamage : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!Self::GetPed())
				return;

			Self::GetPed().ClearDamage();
		}
	};

	static ClearDamage _ClearDamage{"keepplayerclean", "Keep Player Clean", "Keeps the player clean from any blood, dirt, water."};
}