#pragma once
#include "types/network/rlTaskStatus.hpp"
#include "types/network/MatchmakingId.hpp"

namespace rage
{
	class rlSessionInfo;
	class rlSessionDetailMsg;
}

class MatchmakingAttributes;
class MatchmakingId;

namespace YimMenu
{
	class CustomMatchmaking
	{
		bool OnAdvertiseImpl(int& num_slots, int& available_slots, rage::rlSessionInfo* info, MatchmakingAttributes* attrs, MatchmakingId* id, rage::rlTaskStatus* status);
		void OnUpdateImpl(int& num_slots, int& available_slots, rage::rlSessionInfo* info, MatchmakingAttributes* attrs, MatchmakingId* id);
		bool OnUnadvertiseImpl(MatchmakingId* id);
		void OnSendSessionDetailResponseImpl(rage::rlSessionDetailMsg* message);

		CustomMatchmaking();

		static CustomMatchmaking& GetInstance()
		{
			static CustomMatchmaking instance;
			return instance;
		}

		std::unordered_map<std::uint32_t, std::vector<MatchmakingId>> m_MultiplexedSessions;

	public:
		static bool OnAdvertise(int& num_slots, int& available_slots, rage::rlSessionInfo* info, MatchmakingAttributes* attrs, MatchmakingId* id, rage::rlTaskStatus* status)
		{
			return GetInstance().OnAdvertiseImpl(num_slots, available_slots, info, attrs, id, status);
		}

		static void OnUpdate(int& num_slots, int& available_slots, rage::rlSessionInfo* info, MatchmakingAttributes* attrs, MatchmakingId* id)
		{
			return GetInstance().OnUpdateImpl(num_slots, available_slots, info, attrs, id);
		}

		static bool OnUnadvertise(MatchmakingId* id)
		{
			return GetInstance().OnUnadvertiseImpl(id);
		}

		static void OnSendSessionDetailResponse(rage::rlSessionDetailMsg* message)
		{
			return GetInstance().OnSendSessionDetailResponseImpl(message);
		}
	};
}