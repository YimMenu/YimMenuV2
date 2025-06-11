#include "SavedPlayerData.hpp"

namespace YimMenu
{
	std::string_view YimMenu::FetchedPlayerData::GameStateToString(GameState state)
	{
		if (state == GameState::INVALID)
			return "Invalid";

		if (state < GameState::INVALID || state >= GameState::MAX)
			return "Hidden by Modder";

		static constexpr std::array game_states =
		    {
		        "Invite Only",
		        "Friends Only",
		        "Closed Crew",
		        "Crew",
		        "Job",
		        "Public",
		    };

		return game_states[static_cast<int>(state)];
	}

	std::string_view FetchedPlayerData::MissionTypeToString(MissionType type)
	{
		switch (type)
		{
		case MissionType::NONE: return "None";
		case MissionType::MISSION: return "Mission";
		case MissionType::DEATHMATCH: return "Deathmatch";
		case MissionType::RACE: return "Race";
		case MissionType::SURVIVAL: return "Survival";
		case MissionType::GANG_ATTACK: return "Gang Attack";
		case MissionType::GOLF: return "Golf";
		case MissionType::TENNIS: return "Tennis";
		case MissionType::SHOOTING_RANGE: return "Shooting Range";
		}

		return "Unknown";
	}
}