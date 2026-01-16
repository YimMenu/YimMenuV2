#include "CustomMatchmaking.hpp"
#include "core/util/Joaat.hpp"
#include "types/network/MatchmakingId.hpp"
#include "types/network/rlSessionDetail.hpp"
#include "types/network/NetworkGameFilterMatchmakingComponent.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/hooks/Hooks.hpp"
#include "core/hooking/DetourHook.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"

namespace YimMenu::Features
{
	static std::vector<std::pair<int, const char*>> g_SortMethods = {
	    {0, "Off"},
	    {1, "Player Count"},
	};
	static std::vector<std::pair<int, const char*>> g_SortDirections = {
	    {0, "Ascending"},
	    {1, "Descending"},
	};

	BoolCommand _SpoofRegionType{
	    "mmspoofregiontype",
	    "Spoof Region Type",
	    "Spoofs the region type of the session"};
	ListCommand _RegionType{
	    "mmregiontype",
	    "Region Type",
	    "The region to spoof the session to",
	    g_RegionCodes};

	BoolCommand _SpoofLanguage{
	    "mmspooflanguage",
	    "Spoof Language",
	    "Spoofs the session language"};
	ListCommand _Language{
	    "mmlanguage",
	    "Language",
	    "The language to spoof the session to",
	    g_LanguageTypes};

	BoolCommand _SpoofPlayerCount{
	    "mmspoofplayercount",
	    "Spoof Player Count",
	    "Spoofs the session player count"};
	IntCommand _PlayerCount{
	    "mmplayercount",
	    "Player Count",
	    "The player count to spoof the session to",
	    1,
	    32,
	    25};

	BoolCommand _MultiplexSession{
	    "mmmultiplexsession",
	    "Multiplex Session",
	    "Makes your session much more visible to other players by hosting multiple instances of it. High values may fill your session in seconds. Use at your own risk"};
	IntCommand _MultiplexCount{
	    "mmmultiplexsessioncount",
	    "Multiplex Session Count",
	    "The number of sessions to advertise for matchmaking",
	    2,
	    7,
	    5};

	BoolCommand _LanguageFilterEnabled{
	    "mmlanguagefilterenabled",
	    "Filter By Language",
	    "Filter sessions by language"};
	ListCommand _LanguageFilter{
	    "mmlanguagefilter",
	    "Language",
	    "The language to filter",
	    g_LanguageTypes};
	BoolCommand _FilterMultiplexedSessions{
	    "mmfiltermultiplexedsessions",
	    "Filter Multiplexed Sessions",
	    "Filter out multiplexed sessions"};

	BoolCommand _PlayerCountFilterEnabled{
	    "mmplayercountfilterenabled",
	    "Filter By Player Count",
	    "Filter by player count"};
	IntCommand _PlayerCountFilterMin{
	    "mmplayercountfiltermin",
	    "Player Count Minimum",
	    "Minimum players filter",
	    1,
	    32,
	    25};
	IntCommand _PlayerCountFilterMax{
	    "mmplayercountfiltermax",
	    "Player Count Maximum",
	    "Maximum players filter",
	    1,
	    32,
	    25};

	ListCommand _SortMethod{
	    "mmsortmethod",
	    "Sort By",
	    "",
	    g_SortMethods};
	ListCommand _SortDirection{
	    "mmsortdirection",
	    "Sort Direction",
	    "",
	    g_SortDirections};
}

namespace YimMenu
{
	static std::uint32_t GetIdHash(MatchmakingId* id)
	{
		return Joaat(id->m_data1);
	}

	static void PatchMatchmakingAttrs(MatchmakingAttributes* attrs)
	{
		if (Features::_SpoofRegionType.GetState())
		{
			attrs->m_ParamValues[4] = Features::_RegionType.GetState();
		}

		if (Features::_SpoofLanguage.GetState())
		{
			attrs->m_ParamValues[3] = Features::_Language.GetState();
		}

		if (Features::_SpoofPlayerCount.GetState())
		{
			attrs->m_ParamValues[2] = Features::_PlayerCount.GetState();
		}
	}

	CustomMatchmaking::CustomMatchmaking()
	{
	}

	bool CustomMatchmaking::MatchmakeImpl(std::optional<int> constraint, std::optional<bool> enforce_player_limit)
	{
		for (auto& session : m_FoundSessions)
		{
			session.m_IsValid = true;
		}

		NetworkGameFilterMatchmakingComponent component{};
		strcpy(component.m_FilterName, "Group");
		component.m_FilterType = 1;
		component.m_GameMode = 0;
		component.m_NumParameters = 0;
		component.m_SessionType = 25600;

		if (constraint)
		{
			component.SetParameter("MMATTR_DISCRIMINATOR", 0, constraint.value());
		}

		component.SetParameter("MMATTR_MM_GROUP_2", 2, 30);

		rage::rlTaskStatus state{};
		static rage::rlSessionInfo result_sessions[MAX_SESSIONS_TO_FIND];

		m_Active = true;
		m_NumValidSessions = 0;

		if (BaseHook::Get<Hooks::Matchmaking::MatchmakingFindSessions, DetourHook<decltype(&Hooks::Matchmaking::MatchmakingFindSessions)>>()->Original()(0, 1, &component, MAX_SESSIONS_TO_FIND, result_sessions, &m_NumSessionsFound, &state))
		{
			while (state.m_Status == 1)
				ScriptMgr::Yield();

			if (state.m_Status == 3)
			{
				std::unordered_map<std::uint64_t, Session*> stok_map = {};

				for (int i = 0; i < m_NumSessionsFound; i++)
				{
					m_FoundSessions[i].m_Info = result_sessions[i];

					if (auto it = stok_map.find(m_FoundSessions[i].m_Info.m_SessionToken); it != stok_map.end())
					{
						if (Features::_FilterMultiplexedSessions.GetState())
						{
							it->second->m_IsValid = false;
						}

						it->second->m_Attributes.m_MultiplexCount++;
						m_FoundSessions[i].m_IsValid = false;
						continue;
					}

					if (enforce_player_limit.has_value() && enforce_player_limit.value()
					    && m_FoundSessions[i].m_Attributes.m_PlayerCount >= 30)
						m_FoundSessions[i].m_IsValid = false;

					if (Features::_LanguageFilterEnabled.GetState()
					    && m_FoundSessions[i].m_Attributes.m_Language != Features::_LanguageFilter.GetState())
						m_FoundSessions[i].m_IsValid = false;

					if (Features::_PlayerCountFilterEnabled.GetState()
					    && (m_FoundSessions[i].m_Attributes.m_PlayerCount < Features::_PlayerCountFilterMin.GetState()
					        || m_FoundSessions[i].m_Attributes.m_PlayerCount > Features::_PlayerCountFilterMax.GetState()))
					{
						m_FoundSessions[i].m_IsValid = false;
					}

					stok_map.emplace(m_FoundSessions[i].m_Info.m_SessionToken, &m_FoundSessions[i]);
				}

				if (Features::_SortMethod.GetState() != 0)
				{
					std::qsort(m_FoundSessions, m_NumSessionsFound, sizeof(Session), [](const void* a1, const void* a2) -> int {
						std::strong_ordering result;

						if (Features::_SortMethod.GetState() == 1)
						{
							result = (((Session*)(a1))->m_Attributes.m_PlayerCount <=> ((Session*)(a2))->m_Attributes.m_PlayerCount);
						}

						if (result == 0)
							return 0;

						if (result > 0)
							return Features::_SortDirection.GetState() ? -1 : 1;

						if (result < 0)
							return Features::_SortDirection.GetState() ? 1 : -1;


						std::unreachable();
					});
				}

				m_Active = false;
				return true;
			}
		}
		else
		{
			m_Active = false;
			return false;
		}

		m_Active = false;
		return false;
	}

	bool CustomMatchmaking::OnAdvertiseImpl(int& num_slots, int& available_slots, rage::rlSessionInfo* info, MatchmakingAttributes* attrs, MatchmakingId* id, rage::rlTaskStatus* status)
	{
		PatchMatchmakingAttrs(attrs);

		if (!Features::_MultiplexSession.GetState())
			return true; // let the default game code run

		if (status->m_Status)
			return false;

		status->m_Status = 1; // set task in progress

		auto num_slots_copy = num_slots;
		auto available_slots_copy = available_slots;
		FiberPool::Push([this, num_slots_copy, available_slots_copy, info, attrs, id, status] {
			rage::rlTaskStatus first_advert_status;
			if (!BaseHook::Get<Hooks::Matchmaking::MatchmakingAdvertise, DetourHook<decltype(&Hooks::Matchmaking::MatchmakingAdvertise)>>()->Original()(0, num_slots_copy, available_slots_copy, attrs, -1, info, id, &first_advert_status))
			{
				LOGF(WARNING, "OnAdvertiseImpl(): MatchmakingAdvertise returned false for the initial advertisement");
				status->m_Status = 2;
				return;
			}

			while (first_advert_status.m_Status == 1)
				ScriptMgr::Yield();

			if (first_advert_status.m_Status == 2)
			{
				LOGF(WARNING, "OnAdvertiseImpl(): MatchmakingAdvertise failed for the initial advertisement with code {}", status->m_ErrorCode);
				status->m_Status = 2;
				return;
			}

			auto id_hash = GetIdHash(id);

			m_MultiplexedSessions.emplace(id_hash, std::vector<MatchmakingId>{});

			// create the multiplexed sessions
			for (int i = 0; i < Features::_MultiplexCount.GetState() - 1; i++)
			{
				FiberPool::Push([this, num_slots_copy, available_slots_copy, info, attrs, status, id_hash, i] {
					rage::rlTaskStatus additional_advert_status;
					MatchmakingId additional_id;

					if (!BaseHook::Get<Hooks::Matchmaking::MatchmakingAdvertise, DetourHook<decltype(&Hooks::Matchmaking::MatchmakingAdvertise)>>()->Original()(0, num_slots_copy, available_slots_copy, attrs, -1, info, &additional_id, &additional_advert_status))
					{
						LOGF(WARNING, "OnAdvertiseImpl(): MatchmakingAdvertise returned false for additional advertisement {}", i);
						return;
					}

					while (additional_advert_status.m_Status == 1)
						ScriptMgr::Yield();

					if (additional_advert_status.m_Status == 2)
					{
						LOGF(WARNING, "OnAdvertiseImpl(): MatchmakingAdvertise failed for the additional advertisement {} with code {}", i, status->m_ErrorCode);
						return;
					}

					if (auto it = m_MultiplexedSessions.find(id_hash); it != m_MultiplexedSessions.end())
						it->second.push_back(additional_id);
				});
			}

			status->m_Status = 3; // signal success to game
		});

		return false; // we're handling the request now
	}

	void CustomMatchmaking::OnUpdateImpl(int& num_slots, int& available_slots, rage::rlSessionInfo* info, MatchmakingAttributes* attrs, MatchmakingId* id)
	{
		PatchMatchmakingAttrs(attrs);
		auto hash = GetIdHash(id);

		// check if the game is trying to update a session we've multiplexed
		if (auto it = m_MultiplexedSessions.find(hash); it != m_MultiplexedSessions.end())
		{
			for (auto& session : it->second)
			{
				auto num_slots_copy = num_slots;
				auto available_slots_copy = available_slots;
				FiberPool::Push([session, num_slots_copy, available_slots_copy, info, attrs]() {
					auto session_copy = session;                                                                                                                                                                                    // the compiler doesn't like it if I use session directly
					BaseHook::Get<Hooks::Matchmaking::MatchmakingUpdate, DetourHook<decltype(&Hooks::Matchmaking::MatchmakingUpdate)>>()->Original()(0, &session_copy, num_slots_copy, available_slots_copy, info, attrs, nullptr); // life's too short to check the task result
				});
			}
		}
	}

	bool CustomMatchmaking::OnUnadvertiseImpl(MatchmakingId* id)
	{
		auto hash = GetIdHash(id);

		// 1) destroying host session
		if (auto it = m_MultiplexedSessions.find(hash); it != m_MultiplexedSessions.end())
		{
			for (auto& session : it->second)
			{
				FiberPool::Push([session]() {
					auto session_copy = session; // the compiler doesn't like it if I use session directly
					BaseHook::Get<Hooks::Matchmaking::MatchmakingUnadvertise, DetourHook<decltype(&Hooks::Matchmaking::MatchmakingUnadvertise)>>()->Original()(0, &session_copy, nullptr);
				});
			}

			return true; // we've destroyed the multiplexed sessions, let the game destroy the main session
		}

		// or 2) game tries to unadvertise multiplexed sessions every few seconds
		for (auto& [_, multiplex] : m_MultiplexedSessions)
		{
			for (auto& session : multiplex)
			{
				if (GetIdHash(&session) == hash)
				{
					return false; // don't let the game destroy our sessions
				}
			}
		}

		return true;
	}

	void CustomMatchmaking::OnSendSessionDetailResponseImpl(rage::rlSessionDetailMsg* message)
	{
		PatchMatchmakingAttrs(&message->m_Detail.m_SessionConfig.m_MatchmakingAttributes);

		if (Features::_SpoofPlayerCount.GetState())
		{
			message->m_Detail.m_PlayerCount = Features::_PlayerCount.GetState();
			message->m_Detail.m_SpectatorCount = 0;
		}
	}
}