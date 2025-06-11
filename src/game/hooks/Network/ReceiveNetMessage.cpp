#include "core/hooking/DetourHook.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/backend/Players.hpp"
#include "game/frontend/ChatDisplay.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/gta/Packet.hpp"
#include "game/backend/Self.hpp"
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
			return; // the game doesn't handle that anyway
		}
		case rage::netMessage::Type::PackedEvents:
		{
			auto player = Players::GetByMessageId(fr_evt->m_MsgId);

			if (!player)
				break;

			uint32_t count = buffer.Read<uint32_t>(5);
			uint32_t buffer_size = buffer.Read<uint32_t>(15);

			if (buffer_size > 7296)
				buffer_size = 7296;

			int remaining = buffer_size;

			while (remaining >= 39)
			{
				int bits_read = buffer.m_BitsRead;

				uint16_t event_id = buffer.Read<uint16_t>(7);
				uint32_t event_index = buffer.Read<uint32_t>(9);
				uint32_t event_handled_bits = buffer.Read<uint32_t>(8);
				uint32_t event_data_size = buffer.Read<uint32_t>(15);

				if (buffer.Read<bool>(1))
					buffer.Read<uint32_t>(16);

				char event_data[4096 + 1];
				if (event_data_size)
				{
					buffer.ReadArray(event_data, event_data_size);
				}

				rage::datBitBuffer event_buffer(event_data, sizeof(event_data), true);
				event_buffer.m_MaxBit = event_data_size + 1;

				ReceiveNetGameEvent(player, event_id, event_index, event_handled_bits, event_buffer);

				remaining -= (int)buffer.m_BitsRead - bits_read;
			}

			break;
		}
		case rage::netMessage::Type::PackedReliables:
		{
			auto player = Players::GetByMessageId(fr_evt->m_MsgId);

			auto flags = buffer.Read<int>(4);

			if ((flags & 1) != 0)
			{
				auto timestamp = buffer.Read<std::uint32_t>(32);
				if (auto num_msgs = buffer.Read<int>(5))
					buffer.Seek(buffer.Read<std::uint32_t>(13));
			}

			if ((flags & 2) != 0)
			{
				if (auto num_msgs = buffer.Read<int>(5))
					buffer.Seek(buffer.Read<std::uint32_t>(13));
			}

			if ((flags & 4) != 0)
			{
				if (auto num_msgs = buffer.Read<int>(5))
				{
					auto sz = buffer.Read<std::uint32_t>(13);
					auto pos_now = buffer.m_BitsRead;
					while (pos_now + sz > buffer.m_BitsRead)
					{
						auto id = buffer.Read<std::uint16_t>(13);
						auto token = buffer.Read<int>(5);
						bool reject = false;

						if (Self::GetPed().GetPointer<void*>() && Self::GetPed().GetNetworkObjectId() == id)
						{
							if (player)
								LOGF(WARNING, "Blocked player deletion crash from {}", player.GetName());
							reject = true;
						}

						if (Self::GetVehicle() && Self::GetVehicle().HasControl() && Self::GetVehicle().GetNetworkObjectId() == id)
						{
							if (player)
								LOGF(WARNING, "Blocked vehicle deletion from {}", player.GetName());
							reject = true;
						}

						if (reject)
						{
							rage::datBitBuffer write_buf(fr_evt->m_Data, fr_evt->m_Length);
							write_buf.Seek(buffer.m_BitsRead - 5 - 13);
							write_buf.Write<std::uint16_t>(0xFFFF, 16);
						}
					}
				}
			}

			break;
		}
		case rage::netMessage::Type::KickPlayer:
		{
			if (!AnticheatBypass::IsFSLProvidingBattlEyeBypass())
				return;
			break;
		}
		case rage::netMessage::Type::BattlEyeCmd:
		{
			if (!AnticheatBypass::IsFSLProvidingBattlEyeBypass() && !AnticheatBypass::IsBattlEyeRunning())
			{
				char data[1028]{};
				int size = buffer.Read<int>(11);
				bool from_client = buffer.Read<bool>(1);
				buffer.Seek(4); // normalize before we read
				buffer.ReadArrayBytes(&data, size);

				if (from_client)
					break;

				Packet reply;
				char reply_buf[1028]{};
				int reply_sz = 0;

				auto op = data[0];

				if (op == 0)
				{
					char payload[] = {0x0, 0x5};
					reply_sz = sizeof(payload);
					memcpy(reply_buf, payload, reply_sz);
				}
				else if (op == 2 || op == 4)
				{
					char payload[] = {op, data[1]};
					reply_sz = sizeof(payload);
					memcpy(reply_buf, payload, reply_sz);
				}
				else if (op == 9)
				{
					reply_sz = size;
					memcpy(reply_buf, data, reply_sz);
				}

				reply.WriteMessageHeader(rage::netMessage::Type::BattlEyeCmd);
				reply.GetBuffer().Write<int>(reply_sz, 11);
				reply.GetBuffer().Write<bool>(true, 1);
				reply.GetBuffer().Seek(4);
				reply.GetBuffer().WriteArrayBytes(reply_buf, reply_sz);
				reply.Send(fr_evt->m_MsgId);
				return;
			}
			break;
		}
		default:
			break;
		}

		BaseHook::Get<Network::ReceiveNetMessage, DetourHook<decltype(&Network::ReceiveNetMessage)>>()->Original()(a1, mgr, event);
	}
}