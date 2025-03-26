#include "core/util/Joaat.hpp"
#include "game/backend/Self.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/network/CNetGamePlayer.hpp"
#include "types/network/NetEventType.hpp"
#include "types/rage/datBitBuffer.hpp"

namespace YimMenu::Hooks
{
	static void SendEventAck(rage::netEventMgr* event_mgr, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint32_t event_index, uint32_t event_handled_bits)
	{
		if (source_player->m_PlayerIndex != 255 && !Pointers.EventAck(0x778LL * source_player->m_PlayerIndex + (intptr_t)event_mgr + 0x2C408, target_player, event_index, event_handled_bits))
		{
			Pointers.SendEventAck(event_mgr, source_player);
			Pointers.EventAck((intptr_t)event_mgr + 0x2C408 + 0x778LL * source_player->m_PlayerIndex, target_player, event_index, event_handled_bits);
		}

		*reinterpret_cast<std::uint32_t*>(0x118LL * event_index + (uint64_t)event_mgr + 4 * source_player->m_PlayerIndex + 0x458) = event_handled_bits;
	}

	static bool HandleNetGameEvent(Player& player, uint16_t event_id, rage::datBitBuffer& buffer)
	{
		switch (static_cast<NetEventType>(event_id))
		{
		case NetEventType::WEAPON_DAMAGE_EVENT:
		{
			uint8_t damage_type  = buffer.Read<uint8_t>(2);
			uint32_t weapon_type = buffer.Read<uint32_t>(32);

			if (weapon_type == "WEAPON_TRANQUILIZER"_J)
			{
				LOG(INFO) << "blocked this thing from " << player.GetName();
				//player.AddDetection();
				return false;
			}

			break;
		}
		case NetEventType::SCRIPTED_GAME_EVENT:
		{
			int64_t args[54]{};
			uint32_t args_size = buffer.Read<uint32_t>(32);

			if (args_size > sizeof(args))
				return false;

			buffer.ReadArray(args, 8 * args_size);

			if (!Network::HandleScriptedGameEvent(player, args, args_size))
				return false;

			break;
		}
		default:
			break;
		}

		return true;
	}

	void Network::ReceiveEvent(Player& player, uint16_t event_id, uint32_t event_index, uint32_t event_handled_bits, rage::datBitBuffer& buffer)
	{
		if (!HandleNetGameEvent(player, event_id, buffer))
			SendEventAck(*Pointers.NetEventMgr, player.GetHandle(), Self::GetPlayer().GetHandle(), event_index, event_handled_bits);
	}
}