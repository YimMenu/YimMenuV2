#pragma once

namespace rage
{
	class rlSessionInfo;
}

namespace YimMenu::Network
{
	enum class JoinType
	{
		JOIN_PUBLIC,
		NEW_PUBLIC,
		CLOSED_CREW,
		CREW,
		CLOSED_FRIENDS = 6,
		FIND_FRIEND = 9,
		SOLO,
		INVITE_ONLY,
		JOIN_CREW,
		SC_TV,
		LEAVE_ONLINE = -1
	};

	void LaunchJoinType(JoinType to_launch);
	void JoinSessionInfo(rage::rlSessionInfo* info);
	void JoinRockstarId(std::uint64_t id);
	std::optional<std::uint64_t> ResolveRockstarId(std::string_view name);
}