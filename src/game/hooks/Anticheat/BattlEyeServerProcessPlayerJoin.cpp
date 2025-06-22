#include "core/hooking/DetourHook.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/commands/Commands.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/gta/Natives.hpp"
#include "types/battleye/CBattlEyePlayerModifyContext.hpp"
#include "game/backend/AnticheatBypass.hpp"

namespace YimMenu::Hooks
{
	bool Anticheat::BattlEyeServerProcessPlayerJoin(CBattlEyePlayerModifyInterface* server_iface, CBattlEyePlayerModifyContext* context)
	{
		if (!AnticheatBypass::IsBattlEyeRunning())
		{
			if (context->m_IsLocal)
			{
				if (NETWORK::NETWORK_SESSION_IS_CLOSED_FRIENDS() || NETWORK::NETWORK_SESSION_IS_CLOSED_CREW() || NETWORK::NETWORK_SESSION_IS_SOLO() || NETWORK::NETWORK_SESSION_IS_PRIVATE())
				{
					return true;
				}
			}

			static auto cheater_pool = Commands::GetCommand<BoolCommand>("cheaterpool"_J);
			if (cheater_pool->GetState())
			{
				return true;
			}
		}

		return BaseHook::Get<Anticheat::BattlEyeServerProcessPlayerJoin, DetourHook<decltype(&Anticheat::BattlEyeServerProcessPlayerJoin)>>()->Original()(server_iface, context);
	}
}