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
		for (auto& session : m_found_sessions)
		{
			session.is_valid = true;
		}

		NetworkGameFilterMatchmakingComponent component{};
		strcpy(component.m_filter_name, "Group");
		component.m_filter_type    = 1;
		component.m_game_mode      = 0;
		component.m_num_parameters = 0;
		component.m_session_type   = 25600;

		/*
		if (g.session_browser.region_filter_enabled)
		{
			component.SetParameter("MMATTR_REGION", 4, g.session_browser.region_filter);
		}
		*/

		if (constraint)
		{
			component.SetParameter("MMATTR_DISCRIMINATOR", 0, constraint.value());
		}

		component.SetParameter("MMATTR_MM_GROUP_2", 2, 30);

		rage::rlTaskStatus state{};
		static rage::rlSessionInfo result_sessions[MAX_SESSIONS_TO_FIND];

		m_active             = true;
		m_num_valid_sessions = 0;

		if (BaseHook::Get<Hooks::Matchmaking::MatchmakingFindSessions, DetourHook<decltype(&Hooks::Matchmaking::MatchmakingFindSessions)>>()->Original()(0, 1, &component, MAX_SESSIONS_TO_FIND, result_sessions, &m_num_sessions_found, &state))
		{
			while (state.m_Status == 1)
				ScriptMgr::Yield();

			if (state.m_Status == 3)
			{
				std::unordered_map<std::uint64_t, session*> stok_map = {};

				for (int i = 0; i < m_num_sessions_found; i++)
				{
					m_found_sessions[i].info = result_sessions[i];

					if (auto it = stok_map.find(m_found_sessions[i].info.m_SessionToken); it != stok_map.end())
					{
						if (/*g.session_browser.filter_multiplexed_sessions*/true)
						{
							it->second->is_valid = false;
						}

						it->second->attributes.multiplex_count++;
						m_found_sessions[i].is_valid = false;
						continue;
					}

					if (enforce_player_limit.has_value() && enforce_player_limit.value()
					    && m_found_sessions[i].attributes.player_count >= 30)
						m_found_sessions[i].is_valid = false;

					/*
					if (g.session_browser.language_filter_enabled
					    && (eGameLanguage)m_found_sessions[i].attributes.language != g.session_browser.language_filter)
						m_found_sessions[i].is_valid = false;

					if (g.session_browser.player_count_filter_enabled
					    && (m_found_sessions[i].attributes.player_count < g.session_browser.player_count_filter_minimum
					        || m_found_sessions[i].attributes.player_count > g.session_browser.player_count_filter_maximum))
					{
						m_found_sessions[i].is_valid = false;
					}

					if (g.session_browser.pool_filter_enabled
					    && ((m_found_sessions[i].attributes.discriminator & (1 << 14)) == (1 << 14))
					        != (bool)g.session_browser.pool_filter)
						m_found_sessions[i].is_valid = false;

					*/

					stok_map.emplace(m_found_sessions[i].info.m_SessionToken, &m_found_sessions[i]);
				}

				if (/*g.session_browser.sort_method*/1 != 0)
				{
					std::qsort(m_found_sessions, m_num_sessions_found, sizeof(session), [](const void* a1, const void* a2) -> int {
						std::strong_ordering result;

						if (/*g.session_browser.sort_method*/1 == 1)
						{
							result = (((session*)(a1))->attributes.player_count <=> ((session*)(a2))->attributes.player_count);
						}

						if (result == 0)
							return 0;

						if (result > 0)
							return /*g.session_browser.sort_direction*/1 ? -1 : 1;

						if (result < 0)
							return /*g.session_browser.sort_direction*/1 ? 1 : -1;


						std::unreachable();
					});
				}

				m_active = false;
				return true;
			}
		}
		else
		{
			m_active = false;
			return false;
		}

		m_active = false;
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
					auto session_copy = session; // the compiler doesn't like it if I use session directly
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