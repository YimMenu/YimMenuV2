#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class InfiniteParachutes : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (auto player = Self::GetPlayer())
			{
				PLAYER::SET_PLAYER_HAS_RESERVE_PARACHUTE(player.GetId());
			}

			if (auto ped = Self::GetPed())
			{
				if (!WEAPON::HAS_PED_GOT_WEAPON(ped.GetHandle(), "GADGET_PARACHUTE"_J, false))
				{
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped.GetHandle(), "GADGET_PARACHUTE"_J, 1, false);
				}
			}
		}

		virtual void OnDisable() override
		{

		}
	};

	static InfiniteParachutes _InfiniteParachutes{"infiniteparachutes", "Infinite Parachutes", "Always have a parachute."};
};