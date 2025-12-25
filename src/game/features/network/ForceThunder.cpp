#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Scripts.hpp"
#include "types/script/globals/GPBD_FM_3.hpp"

namespace YimMenu::Features
{
	class ForceThunder : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (auto global = GPBD_FM_3::Get(); global && Scripts::SafeToModifyFreemodeBroadcastGlobals())
			{
				global->Entries[Self::GetPlayer().GetId()].BossGoon.ActiveFreemodeEvents[0] |= (1 << 9);
				global->Entries[Self::GetPlayer().GetId()].BossGoon.ActiveFreemodeEvents[0] |= (1 << 10);
				global->Entries[Self::GetPlayer().GetId()].BossGoon.ActiveFreemodeEvents[0] |= (1 << 11);
			}
		}

		virtual void OnDisable() override
		{
			if (auto global = GPBD_FM_3::Get(); global && Scripts::SafeToModifyFreemodeBroadcastGlobals())
			{
				global->Entries[Self::GetPlayer().GetId()].BossGoon.ActiveFreemodeEvents[0] &= ~(1 << 9);
				global->Entries[Self::GetPlayer().GetId()].BossGoon.ActiveFreemodeEvents[0] &= ~(1 << 10);
				global->Entries[Self::GetPlayer().GetId()].BossGoon.ActiveFreemodeEvents[0] &= ~(1 << 11);
			}
		}
	};

	static ForceThunder _ForceThunder{"forcethunder", "Force Thunder", "Forces the weather to thunder for all players in the session"};
}