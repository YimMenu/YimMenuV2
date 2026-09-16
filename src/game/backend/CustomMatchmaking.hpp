#pragma once
#include "types/network/rlSessionInfo.hpp"
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
	namespace Features
	{
		static std::vector<std::pair<int, const char*>> g_RegionCodes = {
		    {0, "CIS"},
		    {1, "South America"},
		    {2, "US East"},
		    {3, "Europe"},
		    {4, "China"},
		    {5, "Australia"},
		    {6, "US West"},
		    {7, "Japan"},
		    {8, "Unknown"},
		};

		static std::vector<std::pair<int, const char*>> g_LanguageTypes = {
		    {0, "English"},
		    {1, "French"},
		    {2, "German"},
		    {3, "Italian"},
		    {4, "Spanish (Spain)"},
		    {5, "Portuguese (Brazil)"},
		    {6, "Polish"},
		    {7, "Russian"},
		    {8, "Korean"},
		    {9, "Chinese (Traditional)"},
		    {10, "Japanese"},
		    {11, "Spanish (Mexico)"},
		    {12, "Chinese (Simplified)"},
		};
	}

	class CustomMatchmaking
	{
		bool OnAdvertiseImpl(int& num_slots, int& available_slots, rage::rlSessionInfo* info, MatchmakingAttributes* attrs, MatchmakingId* id, rage::rlTaskStatus* status);
		void OnUpdateImpl(int& num_slots, int& available_slots, rage::rlSessionInfo* info, MatchmakingAttributes* attrs, MatchmakingId* id);
		bool OnUnadvertiseImpl(MatchmakingId* id);
		void OnSendSessionDetailResponseImpl(rage::rlSessionDetailMsg* message);

		bool MatchmakeImpl(std::optional<int> constraint = std::nullopt, std::optional<bool> enforce_player_limit = std::nullopt);


		CustomMatchmaking();

		static CustomMatchmaking& GetInstance()
		{
			static CustomMatchmaking instance;
			return instance;
		}

	public:
		constexpr static int MAX_SESSIONS_TO_FIND = 1000;

		struct SessionAttributes
		{
			int m_Discriminator;
			int m_PlayerCount;
			int m_Region;
			int m_Language;
			int m_MultiplexCount = 1;
		};

		struct Session
		{
			rage::rlSessionInfo m_Info;
			SessionAttributes m_Attributes;
			bool m_IsValid;
		};

	private:
		int m_NumSessionsFound = 0;
		int m_NumValidSessions = 0;
		bool m_Active = false;
		Session m_FoundSessions[MAX_SESSIONS_TO_FIND];

		std::unordered_map<std::uint32_t, std::vector<MatchmakingId>> m_MultiplexedSessions;


	public:
		static bool Matchmake(std::optional<int> constraint = std::nullopt, std::optional<bool> enforce_player_limit = std::nullopt)
		{
			return GetInstance().MatchmakeImpl(constraint, enforce_player_limit);
		}

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

		static int GetNumFoundSessions()
		{
			return GetInstance().m_NumSessionsFound;
		}

		static int GetNumValidSessions()
		{
			return GetInstance().m_NumValidSessions;
		}

		static Session* GetFoundSessions()
		{
			return GetInstance().m_FoundSessions;
		}

		static bool IsActive()
		{
			return GetInstance().m_Active;
		}
	};
}