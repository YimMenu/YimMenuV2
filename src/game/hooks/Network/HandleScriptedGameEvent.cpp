#include "game/backend/Self.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/network/netGameEvent.hpp"
#include "types/script/globals/GPBD_FM_3.hpp"
#include "types/script/globals/GlobalPlayerBD.hpp"
#include "types/script/ScriptEvent.hpp"

namespace YimMenu::Hooks
{
	bool Network::HandleScriptedGameEvent(Player player, CScriptedGameEvent& event)
	{
		SCRIPT_EVENT* script_event = reinterpret_cast<SCRIPT_EVENT*>(event.m_Args);

		switch (static_cast<ScriptEventIndex>(script_event->GetEventIndex()))
		{
		case ScriptEventIndex::Bounty:
		{
			SCRIPT_EVENT_BOUNTY* bounty = static_cast<SCRIPT_EVENT_BOUNTY*>(script_event);

			if (event.m_ArgsSize != SCRIPT_EVENT_BOUNTY::GetSize())
			{
				//player.AddDetection();
				return false;
			}

			if (bounty->Target == Self::GetPlayer().GetId())
			{
				return false;
			}

			break;
		}
		case ScriptEventIndex::SendTextLabelSMS:
		{
			//player.AddDetection();
			return false;
		}
		case ScriptEventIndex::CeoKick:
		{
			if (player.GetId() != GPBD_FM_3::Get()->Entries[Self::GetPlayer().GetId()].BossGoon.Boss)
			{
				return false;
			}

			break;
		}
		case ScriptEventIndex::InteriorControl:
		{
			SCRIPT_EVENT_SEND_TO_INTERIOR* interior_control = static_cast<SCRIPT_EVENT_SEND_TO_INTERIOR*>(script_event);

			if (interior_control->Interior < 0 || interior_control->Interior >= static_cast<int>(eSimpleInteriorIndex::SIMPLE_INTERIOR_MAX)) // the upper bound will change after an update
			{
				// null function kick
				return false;
			}

			if (!interior_control->GoonsOnly)
			{
				// send to interior
				return false;
			}

			break;
		}
		default:
			break;
		}

		return true;
	}
}