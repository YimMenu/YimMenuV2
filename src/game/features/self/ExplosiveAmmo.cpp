#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Pools.hpp"

#include <game/gta/Natives.hpp>

namespace YimMenu::Features
{
	class ExplosiveAmmo : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;
		virtual void OnTick() override
		{
			MISC::SET_EXPLOSIVE_AMMO_THIS_FRAME(Self::GetPlayer().GetId());
		}
	};

	static ExplosiveAmmo _ExplosiveAmmo{"ExplosiveAmmo", "Explosive Ammo", "Every bullet you shoot explodes."};

}