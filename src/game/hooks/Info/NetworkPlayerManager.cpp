#include "core/hooking/DetourHook.hpp"
#include "game/backend/Players.hpp"
#include "game/hooks/Hooks.hpp"

namespace YimMenu::Hooks
{
	void Info::NetworkPlayerMgrInit(CNetworkPlayerMgr* mgr, uint64_t a2, uint32_t a3, uint32_t a4[4])
	{
		if (!g_Running)
			return BaseHook::Get<Info::NetworkPlayerMgrInit, DetourHook<decltype(&Info::NetworkPlayerMgrInit)>>()->Original()(mgr, a2, a3, a4);

		Players::Init();
		BaseHook::Get<Info::NetworkPlayerMgrInit, DetourHook<decltype(&Info::NetworkPlayerMgrInit)>>()->Original()(mgr, a2, a3, a4);
	}

	void Info::NetworkPlayerMgrShutdown(CNetworkPlayerMgr* mgr)
	{
		if (!g_Running)
			return BaseHook::Get<Info::NetworkPlayerMgrShutdown, DetourHook<decltype(&Info::NetworkPlayerMgrShutdown)>>()->Original()(mgr);

		Players::Shutdown();
		BaseHook::Get<Info::NetworkPlayerMgrShutdown, DetourHook<decltype(&Info::NetworkPlayerMgrShutdown)>>()->Original()(mgr);
	}
}