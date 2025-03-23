#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/backend/Players.hpp"

namespace YimMenu::Hooks
{
	void Info::AssignPhysicalIndex(CNetworkPlayerMgr* mgr, CNetGamePlayer* player, std::uint8_t index)
	{
		if (!g_Running)
			return BaseHook::Get<Info::AssignPhysicalIndex, DetourHook<decltype(&Info::AssignPhysicalIndex)>>()->Original()(mgr, player, index);

		if (index != 255)
		{
			BaseHook::Get<Info::AssignPhysicalIndex, DetourHook<decltype(&Info::AssignPhysicalIndex)>>()->Original()(mgr, player, index);
			Players::OnPlayerJoin(player);
		}
		else
		{
			Players::OnPlayerLeave(player);
			BaseHook::Get<Info::AssignPhysicalIndex, DetourHook<decltype(&Info::AssignPhysicalIndex)>>()->Original()(mgr, player, index);
		}
	}
}