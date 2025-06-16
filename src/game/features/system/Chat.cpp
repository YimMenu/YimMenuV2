#include "core/backend/ScriptMgr.hpp"
#include "core/commands/Command.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/frontend/widgets/imgui_colors.h"
#include "game/backend/Players.hpp"
#include "game/backend/Self.hpp"
#include "game/frontend/ChatDisplay.hpp"
#include "game/frontend/GUI.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Packet.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/network/rlGamerHandle.hpp"
#include "types/network/rlGamerInfo.hpp"

namespace
{
	bool ShowTextBox(std::string_view title, char* buf, int max_length)
	{
		int font_flags = 256;
		font_flags |= 64;
		MISC::NEXT_ONSCREEN_KEYBOARD_RESULT_WILL_DISPLAY_USING_THESE_FONTS(font_flags);
		MISC::DISPLAY_ONSCREEN_KEYBOARD(0, title.data(), nullptr, buf, nullptr, nullptr, nullptr, max_length);

		while (true)
		{
			YimMenu::ChatDisplay::MarkAccessed();
			YimMenu::ScriptMgr::Yield();
			int update_res = MISC::UPDATE_ONSCREEN_KEYBOARD();

			if (update_res == 1)
			{
				strncpy(buf, MISC::GET_ONSCREEN_KEYBOARD_RESULT(), max_length);
				return true;
			}
			else if (update_res == 2 || update_res == 3)
			{
				MISC::CANCEL_ONSCREEN_KEYBOARD();
				return false;
			}
		}
	}
}

namespace YimMenu::Features
{
	class Chat : public Command
	{
		using Command::Command;

		std::mutex m_ChatMutex;

		virtual void OnCall() override
		{
			if (*Pointers.IsSessionStarted && MISC::UPDATE_ONSCREEN_KEYBOARD() != 0)
			{
				if (!m_ChatMutex.try_lock())
					return;

				char buffer[256]{};
				if (ShowTextBox("Enter Message", buffer, sizeof(buffer)))
				{
					// well, chat is pretty much dead anyway so hardcoded GUIDs should be fine
					// {A88961C7-B4C8-4A16-A648-AC2D8C9300DB}
					static const GUID guid = {0xa88961c7, 0xb4c8, 0x4a16, {0xa6, 0x48, 0xac, 0x2d, 0x8c, 0x93, 0x0, 0xdb}};
					char guid_str[40];
					std::sprintf(guid_str, "%08lx-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x", guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

					Packet pkt;
					pkt.WriteMessageHeader(rage::netMessage::Type::TextMessage);
					pkt.GetBuffer().WriteString(buffer, sizeof(buffer));
					pkt.GetBuffer().WriteString(guid_str, sizeof(guid_str));
					Self::GetPlayer().GetGamerInfo()->m_GamerHandle.Serialize(pkt);
					pkt.GetBuffer().Write<bool>(false, 1); // is team

					for (auto& player : Players::GetPlayers())
						if (player.second.IsValid() && !player.second.IsLocal())
							pkt.Send(player.second.GetMessageId());

					ChatDisplay::Show(Self::GetPlayer().GetName(), buffer, ImGui::Colors::Green);
				}

				m_ChatMutex.unlock();
			}
		}
	};

	class ClearChat : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			ChatDisplay::Clear();
		}
	};

	static Chat _Chat{"chathelper", "Chat", "Use this to open the chat"};
	static ClearChat _ClearChat{"clearchat", "Clear Chat", "Use this to clear the chat"};
}