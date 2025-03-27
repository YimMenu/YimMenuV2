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
			PLAYER::SET_PLAYER_HAS_RESERVE_PARACHUTE(Self::GetPlayer().GetId());

			if (auto ped = Self::GetPed())
			{
				if (!ped.HasWeapon("GADGET_PARACHUTE"_J))
					ped.GiveWeapon("GADGET_PARACHUTE"_J);
			}
		}
	};

	static InfiniteParachutes _InfiniteParachutes{"infiniteparachutes", "Infinite Parachutes", "Always have a parachute"};
};