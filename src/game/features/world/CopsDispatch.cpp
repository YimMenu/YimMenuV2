#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Pools.hpp"

#include <game/gta/Natives.hpp>

namespace YimMenu::Features
{
	class CopsDispatch : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;
		virtual void OnTick() override
		{
			PLAYER::SET_DISPATCH_COPS_FOR_PLAYER(Self::GetPlayer().GetId(), FALSE);
		}

		virtual void OnDisable() override
		{
			PLAYER::SET_DISPATCH_COPS_FOR_PLAYER(Self::GetPlayer().GetId(), TRUE);
		}
	};

	static CopsDispatch _CopsDispatch{"CopsDispatch", "Cops Dispatch", "When you are wanted, no police will be spawned."};

}