#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Pools.hpp"
#include "game/backend/Self.hpp"
#include <game/gta/Natives.hpp>

namespace YimMenu::Features
{
	class PedIgnore : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;
		virtual void OnTick() override
		{
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(Self::GetPlayer().GetId(), TRUE);
			PLAYER::SET_POLICE_IGNORE_PLAYER(Self::GetPlayer().GetId(), TRUE);
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS_FOR_AMBIENT_PEDS_THIS_FRAME(TRUE);
			PED::SET_PED_RESET_FLAG(Self::GetPed().GetHandle(), 124, true);
		}

		virtual void OnDisable() override
		{
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(Self::GetPlayer().GetId(), FALSE);
			PLAYER::SET_POLICE_IGNORE_PLAYER(Self::GetPlayer().GetId(), FALSE);
		}
	};

	static PedIgnore _PedIgnore{"pedsignore", "Peds Ignore", "Nearby peds will ignore you and become oblivious to your actions."};

}