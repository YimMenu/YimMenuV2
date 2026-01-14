#include "game/hooks/Hooks.hpp"
#include "core/hooking/DetourHook.hpp"
#include "game/backend/CustomMatchmaking.hpp"
#include "types/network/NetworkGameFilterMatchmakingComponent.hpp"

namespace rage
{
	class JSONNode
	{
	public:
		char* m_key;                    //0x0000
		char pad_0008[40];              //0x0008
		class rage::JSONNode* m_sibling;//0x0030
		class rage::JSONNode* m_child;  //0x0038
		char* m_value;                  //0x0040
		char pad_0040[8];               //0x0048

		inline JSONNode* get_child_node(const char* name)
		{
			for (auto node = m_child; node; node = node->m_sibling)
			{
				if (strcmp(name, node->m_key) == 0)
					return node;
			}

			return nullptr;
		}
	};//Size: 0x0048
	static_assert(sizeof(rage::JSONNode) == 0x50);
}

namespace
{
	// https://stackoverflow.com/a/5167641
	static std::vector<std::string> split(const std::string& s, char seperator)
	{
		std::vector<std::string> output;

		std::string::size_type prev_pos = 0, pos = 0;

		while ((pos = s.find(seperator, pos)) != std::string::npos)
		{
			std::string substring(s.substr(prev_pos, pos - prev_pos));

			output.push_back(substring);

			prev_pos = ++pos;
		}

		output.push_back(s.substr(prev_pos, pos - prev_pos));// Last word

		return output;
	}
}

namespace YimMenu::Hooks
{
	bool Matchmaking::MatchmakingFindSessions(int profile_index, int available_slots, NetworkGameFilterMatchmakingComponent* m_filter, unsigned int max_sessions, rage::rlSessionInfo* result_sessions, int* result_session_count, rage::rlTaskStatus* state)
	{
		LOGF(VERBOSE, "MatchmakingFindSessions({}, {}, {}, {}, {}, {}, {})", profile_index, available_slots, (void*)m_filter, max_sessions, (void*)result_sessions, (void*)result_session_count, (void*)state);

		LOG(VERBOSE) << "m_filter_type " << m_filter->m_filter_type;
		LOG(VERBOSE) << "m_filter_name " << m_filter->m_filter_name;
		LOG(VERBOSE) << "m_game_mode " << m_filter->m_game_mode;
		LOG(VERBOSE) << "m_session_type " << m_filter->m_session_type;
		LOG(VERBOSE) << "m_enabled_params_bitset " << m_filter->m_enabled_params_bitset;

		for (uint32_t i = 0; i < 8; i++)
		{
			bool active_param = (m_filter->m_enabled_params_bitset & (1 << i)) != 0;
			if (active_param)
			{
				LOG(VERBOSE) << m_filter->m_param_names[i] << "(" << i << ") = " << m_filter->m_param_values[i];
			}
		}

		return BaseHook::Get<Matchmaking::MatchmakingFindSessions, DetourHook<decltype(&Matchmaking::MatchmakingFindSessions)>>()->Original()(profile_index, available_slots, m_filter, max_sessions, result_sessions, result_session_count, state);
	}

	bool Matchmaking::MatchmakingFindSessionsResponse(void* _this, void* unused, rage::JSONNode* node, int* unk)
	{
		bool ret = BaseHook::Get<Matchmaking::MatchmakingFindSessionsResponse, DetourHook<decltype(&Matchmaking::MatchmakingFindSessionsResponse)>>()->Original()(_this, unused, node, unk);

		if (CustomMatchmaking::IsActive())
		{
			int i = 0;
			for (auto result = node->get_child_node("Results")->m_child; result; result = result->m_sibling)
			{
				const auto& attributes = result->get_child_node("Attributes")->m_value;
				LOG(VERBOSE) << "Session " << attributes;
				const auto& values = split(attributes, ',');
				CustomMatchmaking::GetFoundSessions()[i].attributes.discriminator = std::stoi(values[2]);
				CustomMatchmaking::GetFoundSessions()[i].attributes.player_count  = std::stoi(values[4]);
				CustomMatchmaking::GetFoundSessions()[i].attributes.language      = std::stoi(values[5]);
				CustomMatchmaking::GetFoundSessions()[i].attributes.region        = std::stoi(values[6]);
				i++;
			}
		}

		return ret;
	}
}
