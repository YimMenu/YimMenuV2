#include "game/backend/Self.hpp"
#include "game/backend/ProtectionTelemetry.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/network/netGameEvent.hpp"
#include "types/script/globals/GPBD_FM_3.hpp"
#include "types/script/globals/GlobalPlayerBD.hpp"
#include "types/script/ScriptEvent.hpp"
#include "core/scripting/LuaManager.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/util/Joaat.hpp"

namespace YimMenu::Hooks
{
	static bool CheckLuaScripts(Player player, CScriptedGameEvent& event)
	{
		return LuaManager::DispatchEvent(MenuEvent::ScriptedGameEventReceived, [player, &event](lua_State* state)
		{
			Lua::CreateObject<YimMenu::Player>(state, player);

			lua_newtable(state);
			auto length = event.m_ArgsSize / 8;
			for (int i = 0; i < length; i++)
			{
				lua_pushinteger(state, i == 0 ? (ptrdiff_t)(int)event.m_Args[i] : event.m_Args[i]);
				lua_rawseti(state, -2, i + 1);
			}

			return 2;
		}, true);
	}

	bool Network::HandleScriptedGameEvent(Player player, CScriptedGameEvent& event)
	{
		if (event.m_ArgsSize < sizeof(std::int64_t) || event.m_ArgsSize > sizeof(event.m_Args) || event.m_ArgsSize % sizeof(std::int64_t) != 0)
		{
			ProtectionTelemetry::Increment(ProtectionTelemetry::Event::MalformedScriptEvent);
			return false;
		}

		if (!CheckLuaScripts(player, event))
			return false;

		SCRIPT_EVENT* script_event = reinterpret_cast<SCRIPT_EVENT*>(event.m_Args);

		switch (static_cast<ScriptEventIndex>(script_event->GetEventIndex()))
		{
		case ScriptEventIndex::Bounty:
		{
			SCRIPT_EVENT_BOUNTY* bounty = static_cast<SCRIPT_EVENT_BOUNTY*>(script_event);

			if (event.m_ArgsSize != SCRIPT_EVENT_BOUNTY::GetSize())
			{
				ProtectionTelemetry::Increment(ProtectionTelemetry::Event::MalformedScriptEvent);
				return false;
			}

			if (bounty->Target == Self::GetPlayer().GetId())
			{
				ProtectionTelemetry::Increment(ProtectionTelemetry::Event::BlockedBounty);
				return false;
			}

			break;
		}
		case ScriptEventIndex::SendTextLabelSMS:
		{
			ProtectionTelemetry::Increment(ProtectionTelemetry::Event::BlockedTextLabelSms);
			return false;
		}
		case ScriptEventIndex::CeoKick:
		{
			const auto local_id = Self::GetPlayer().GetId();
			if (local_id < 0 || local_id >= 32 || player.GetId() < 0 || player.GetId() >= 32)
			{
				ProtectionTelemetry::Increment(ProtectionTelemetry::Event::MalformedScriptEvent);
				return false;
			}

			if (player.GetId() != GPBD_FM_3::Get()->Entries[local_id].BossGoon.Boss)
			{
				ProtectionTelemetry::Increment(ProtectionTelemetry::Event::BlockedCeoKick);
				return false;
			}

			break;
		}
		case ScriptEventIndex::InteriorControl:
		{
			SCRIPT_EVENT_SEND_TO_INTERIOR* interior_control = static_cast<SCRIPT_EVENT_SEND_TO_INTERIOR*>(script_event);

			if (interior_control->Interior < 0 || interior_control->Interior >= static_cast<int>(eSimpleInteriorIndex::SIMPLE_INTERIOR_MAX)) // the upper bound will change after an update
			{
				ProtectionTelemetry::Increment(ProtectionTelemetry::Event::BlockedInteriorControl);
				return false;
			}

			if (!interior_control->GoonsOnly)
			{
				ProtectionTelemetry::Increment(ProtectionTelemetry::Event::BlockedInteriorControl);
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
