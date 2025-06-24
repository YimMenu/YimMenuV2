#include "game/hooks/Hooks.hpp"
#include "core/hooking/DetourHook.hpp"
#include "game/backend/CustomMatchmaking.hpp"

namespace YimMenu::Hooks
{
	bool Matchmaking::MatchmakingUnadvertise(int profile_index, MatchmakingId* id, rage::rlTaskStatus* status)
	{
		if (!CustomMatchmaking::OnUnadvertise(id))
		{
			status->m_Status = 2;
			return true;
		}
		return BaseHook::Get<Matchmaking::MatchmakingUnadvertise, DetourHook<decltype(&Matchmaking::MatchmakingUnadvertise)>>()->Original()(profile_index, id, status);
	}
}