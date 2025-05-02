#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Pools.hpp"
#include "game/backend/Self.hpp"
#include <game/gta/Natives.hpp>

namespace YimMenu::Features
{
	class PedIgnore : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnEnable() override
		{
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(Self::GetPlayer().GetId(), TRUE);
			PLAYER::SET_POLICE_IGNORE_PLAYER(Self::GetPlayer().GetId(), TRUE);
		}

		virtual void OnTick() override
		{
			for (auto ped : Pools::GetPeds())
			{
				if (!ped.IsPlayer() && !PED::GET_PED_CONFIG_FLAG(ped.GetHandle(), 17, true))
				{ // Flag 17 = PED_FLAG_BLOCK_NON_TEMPORARY_EVENTS
					PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped.GetHandle(), true);
					TASK::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped.GetHandle(), true);
				}
			}
		}

		virtual void OnDisable() override
		{
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(Self::GetPlayer().GetId(), FALSE);
			PLAYER::SET_POLICE_IGNORE_PLAYER(Self::GetPlayer().GetId(), FALSE);
		}
	};

	static PedIgnore _PedIgnore{"pedsignore", "Peds Ignore", "Nearby peds will ignore you and become oblivious to your actions."};

}