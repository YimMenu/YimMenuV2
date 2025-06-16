#include "core/commands/Command.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/gta/Network.hpp"

namespace YimMenu::Features
{
	static std::vector<std::pair<int, const char*>> g_JoinTypes = {
	    {static_cast<int>(Network::JoinType::JOIN_PUBLIC), "Public"},
	    {static_cast<int>(Network::JoinType::NEW_PUBLIC), "Solo Public"},
	    {static_cast<int>(Network::JoinType::SC_TV), "SCTV"},
	    {static_cast<int>(Network::JoinType::CREW), "Crew"},
	    {static_cast<int>(Network::JoinType::JOIN_CREW), "Join Crew"},
	    {static_cast<int>(Network::JoinType::CLOSED_CREW), "Closed Crew"},
	    {static_cast<int>(Network::JoinType::CLOSED_FRIENDS), "Closed Friend"},
	    {static_cast<int>(Network::JoinType::FIND_FRIEND), "Find Friend"},
	    {static_cast<int>(Network::JoinType::INVITE_ONLY), "Invite Only"},
	    {static_cast<int>(Network::JoinType::SOLO), "Solo"},
	};

	static ListCommand _JoinType{"joinsessiontype", "Join Session Type", "The session type to join", g_JoinTypes, static_cast<int>(Network::JoinType::JOIN_PUBLIC)};

	class JoinSession : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Network::LaunchJoinType(static_cast<Network::JoinType>(_JoinType.GetState()));
		}
	};
	static JoinSession _JoinSession{"joinsession", "Join Session", "Joins the specified session type"};


}