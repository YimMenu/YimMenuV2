#include "core/hooking/DetourHook.hpp"
#include "game/backend/Players.hpp"
#include "game/frontend/ChatDisplay.hpp"
#include "game/hooks/Hooks.hpp"
#include "types/network/netEvent.hpp"
#include "types/network/netMessage.hpp"
#include "types/rage/datBitBuffer.hpp"
#include "core/frontend/widgets/imgui_colors.h"

namespace YimMenu::Hooks
{
	static std::optional<rage::netMessage::Type> ReadType(rage::datBitBuffer& buffer)
	{
		if (buffer.Read<int>(14) != 0x3246)
			return std::nullopt;

		auto extended = buffer.Read<bool>(1);
		return buffer.Read<rage::netMessage::Type>(extended ? 16 : 8);
	}

	void Network::ReceiveNetMessage(void* a1, rage::netConnectionManager* mgr, rage::netEvent* event)
	{
		if (!g_Running)
			return BaseHook::Get<Network::ReceiveNetMessage, DetourHook<decltype(&Network::ReceiveNetMessage)>>()->Original()(a1, mgr, event);

		if (event->GetEventType() != rage::netEvent::Type::FrameReceived)
			return BaseHook::Get<Network::ReceiveNetMessage, DetourHook<decltype(&Network::ReceiveNetMessage)>>()->Original()(a1, mgr, event);

		// TODO: port security ID stuff from V1
		auto fr_evt = reinterpret_cast<rage::netEventFrameReceived*>(event);
		rage::datBitBuffer buffer(fr_evt->m_Data, fr_evt->m_Length, true);
		
		rage::netMessage::Type type = ReadType(buffer).value_or(rage::netMessage::Type::Invalid);

		switch (type)
		{
		case rage::netMessage::Type::TextMessage:
		{
			auto player = Players::GetByMessageId(fr_evt->m_MsgId);
			if (player)
			{
				char msg[256]{};
				buffer.ReadString(msg, sizeof(msg)); // we don't need the rest
				ChatDisplay::Show(player.GetName(), msg, ImGui::Colors::LightBlue);
			}
			break;
		}
		case rage::netMessage::Type::PackedEvents:
		{
			auto player = Players::GetByMessageId(fr_evt->m_MsgId);

			if (!player)
				break;

			uint32_t count       = buffer.Read<uint32_t>(5);
			uint32_t buffer_size = buffer.Read<uint32_t>(15);

			if (buffer_size > 7296)
				buffer_size = 7296;

			int remaining = buffer_size;

			while (remaining >= 39)
			{
				int bits_read = buffer.m_BitsRead;

				uint16_t event_id           = buffer.Read<uint16_t>(7);
				uint32_t event_index        = buffer.Read<uint32_t>(9);
				uint32_t event_handled_bits = buffer.Read<uint32_t>(8);
				uint32_t event_data_size    = buffer.Read<uint32_t>(15);

				if (buffer.Read<bool>(1))
					buffer.Read<uint32_t>(16);

				char event_data[4096 + 1];
				if (event_data_size)
				{
					buffer.ReadArray(event_data, event_data_size);
				}

				rage::datBitBuffer event_buffer(event_data, sizeof(event_data), true);
				event_buffer.m_MaxBit = event_data_size + 1;

				ReceiveEvent(player, event_id, event_index, event_handled_bits, event_buffer);

				remaining -= (int)buffer.m_BitsRead - bits_read;
			}

			break;
		}
		default: 
			break;
		}

		BaseHook::Get<Network::ReceiveNetMessage, DetourHook<decltype(&Network::ReceiveNetMessage)>>()->Original()(a1, mgr, event);
	}
}