#include "core/commands/BoolCommand.hpp"
#include "core/commands/IntCommand.hpp"
#include "game/commands/PlayerCommand.hpp"
#include "types/script/ScriptEvent.hpp"
#include "types/script/globals/GSBD_FM_Events.hpp"
#include <game/gta/Natives.hpp>

namespace YimMenu::Features
{
	static IntCommand _BountyAmount{"bountyamount", "Bounty Amount", "The bounty amount to set", 1, 10000, 9000};
	static BoolCommand _AnonymousBounty{"anonymousbounty", "Anonymous Bounty", "Sets the bounty as anonymous"};

	class SetBounty : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			SCRIPT_EVENT_BOUNTY bounty;
			bounty.Target = player.GetId();
			bounty.FromPed = _AnonymousBounty.GetState();
			bounty.Amount = _BountyAmount.GetState();
			bounty.BountyFlags = 1;
			bounty.AntiReplayValue1 = GSBD_FM_Events::Get()->AntiReplayValue1;
			bounty.AntiReplayValue2 = GSBD_FM_Events::Get()->AntiReplayValue2;
			bounty.SetAllPlayers();
			bounty.Send();
			Sleep(5000);
			MONEY::NETWORK_EARN_FROM_BOUNTY(_BountyAmount.GetState(), player.GetHandle(), nullptr, 0);
		}
	};

	static SetBounty _SetBounty{"setbounty", "Set Bounty", "Sets the specified bounty to the player"};
}