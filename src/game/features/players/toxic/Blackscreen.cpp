#include "game/backend/Self.hpp"
#include "game/commands/PlayerCommand.hpp"
#include "types/script/globals/GlobalPlayerBD.hpp"
#include "types/script/ScriptEvent.hpp"

namespace YimMenu::Features
{
	class Blackscreen : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			OnCall(std::vector{player});
		}

		virtual void OnCall(const std::vector<Player>& players) override
		{
			SCRIPT_EVENT_SEND_TO_PROPERTY message;
			message.Owner = Self::GetPlayer().GetId();
			message.PropertyIndex = 114;
			message.SubProperyIndex = 999;
			message.MissionPassNotify1 = true;
			message.MissionPassNotify2 = true;
			message.PAD_0004 = 999;
			message.Variation = 999;
			message.Flags = 3; 
			for (auto& player : players)
				message.SetPlayer(player.GetId());
			message.Send();
		}
	};

	static Blackscreen _Blackscreen{"blackscreen", "Blackscreen", "Forces the player into an infinite loading screen that can only be fixed by restarting the game"};
}