#include "game/backend/Self.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/script/ScriptEvent.hpp"

namespace YimMenu::Hooks
{
	bool Network::HandleScriptedGameEvent(YimMenu::Player& player, int64_t* args, uint32_t args_size)
	{
		SCRIPT_EVENT* script_event = reinterpret_cast<SCRIPT_EVENT*>(args);

		switch (static_cast<ScriptEventIndex>(script_event->GetEventIndex()))
		{
		case ScriptEventIndex::Bounty:
		{
			SCRIPT_EVENT_BOUNTY* bounty = static_cast<SCRIPT_EVENT_BOUNTY*>(script_event);

			if (args_size != SCRIPT_EVENT_BOUNTY::GetSize())
			{
				//player.AddDetection();
				return false;
			}

			if (bounty->Target == Self::GetPed().GetHandle())
			{
				return false;
			}

			break;
		}
		case ScriptEventIndex::SendTextLabelSMS:
		{
			//player.AddDetection();
			return true;
		}
		}

		return true;
	}
}