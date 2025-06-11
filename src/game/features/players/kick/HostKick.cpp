#include "game/commands/PlayerCommand.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class HostKick : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;
		virtual void OnCall(Player player) override
		{
			NETWORK::NETWORK_SESSION_KICK_PLAYER(player.GetId());
		}
	};

	static HostKick _HostKick{"HKick", "Host Kick", "Only available as host and the target is unblockable"};
}