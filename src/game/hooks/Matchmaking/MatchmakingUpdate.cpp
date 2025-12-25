#include "game/hooks/Hooks.hpp"
#include "core/hooking/DetourHook.hpp"
#include "game/backend/CustomMatchmaking.hpp"

namespace YimMenu::Hooks
{
	bool Matchmaking::MatchmakingUpdate(int profile_index, MatchmakingId* id, int num_slots, int available_slots, rage::rlSessionInfo* info, MatchmakingAttributes* data, rage::rlTaskStatus* status)
	{
		CustomMatchmaking::OnUpdate(num_slots, available_slots, info, data, id);
		return BaseHook::Get<Matchmaking::MatchmakingUpdate, DetourHook<decltype(&Matchmaking::MatchmakingUpdate)>>()->Original()(profile_index, id, num_slots, available_slots, info, data, status);
	}
}