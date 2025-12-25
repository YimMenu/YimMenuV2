#include "game/hooks/Hooks.hpp"
#include "core/hooking/DetourHook.hpp"
#include "game/backend/CustomMatchmaking.hpp"

namespace YimMenu::Hooks
{
	bool Matchmaking::MatchmakingAdvertise(int profile_index, int num_slots, int available_slots, MatchmakingAttributes* data, std::uint64_t session_id, rage::rlSessionInfo* info, MatchmakingId* out_id, rage::rlTaskStatus* status)
	{
		if (!CustomMatchmaking::OnAdvertise(num_slots, available_slots, info, data, out_id, status))
			return true;

		return BaseHook::Get<Matchmaking::MatchmakingAdvertise, DetourHook<decltype(&Matchmaking::MatchmakingAdvertise)>>()->Original()(profile_index, num_slots, available_slots, data, session_id, info, out_id, status);
	}
}