#include "game/hooks/Hooks.hpp"
#include "core/hooking/DetourHook.hpp"
#include "game/backend/CustomMatchmaking.hpp"

namespace YimMenu::Hooks
{
	bool Matchmaking::MatchmakingSessionDetailSendResponse(rage::netConnectionManager* mgr, void* request_frame, rage::rlSessionDetailMsg* msg)
	{
		CustomMatchmaking::OnSendSessionDetailResponse(msg);
		return BaseHook::Get<Matchmaking::MatchmakingSessionDetailSendResponse, DetourHook<decltype(&Matchmaking::MatchmakingSessionDetailSendResponse)>>()->Original()(mgr, request_frame, msg);
	}
}