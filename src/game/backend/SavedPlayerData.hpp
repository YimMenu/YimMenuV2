#pragma once

namespace YimMenu
{
	struct FetchedPlayerData
	{
		enum class GameState
		{
			INVALID = -1,
			INVITE_ONLY,
			FRIENDS_ONLY,
			CLOSED_CREW,
			OPEN_CREW,
			JOB_SESSION,
			PUBLIC,
			MAX
		};

		enum class MissionType
		{
			NONE = -1,
			MISSION,
			DEATHMATCH,
			RACE,
			SURVIVAL,
			GANG_ATTACK = 6,
			GOLF = 11,
			TENNIS,
			SHOOTING_RANGE
		};

		GameState m_GameState;
		bool m_HostOfSession;
		bool m_Spectating;
		bool m_InTransition;
		bool m_HostOfTransition;
		MissionType m_MissionType;
		std::optional<std::string> m_MissionName;
		std::string m_MissionId;

		static std::string_view GameStateToString(GameState state);
		static std::string_view MissionTypeToString(MissionType type);
	};

	struct SavedPlayerData
	{
		// stored
		std::string m_Name = "";
		bool m_IsModder = false;
		bool m_TrackPlayer = false;

		// not stored
		std::optional<FetchedPlayerData> m_FetchedData = std::nullopt;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(SavedPlayerData, m_Name, m_IsModder, m_TrackPlayer);
	};
}