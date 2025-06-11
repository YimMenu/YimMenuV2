#include "ChatDisplay.hpp"

#include "Menu.hpp"
#include "core/logger/LogHelper.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/pointers/Pointers.hpp"
#include "core/frontend/widgets/imgui_colors.h"


namespace YimMenu
{
	void ChatDisplay::ShowImpl(std::string sender, std::string message, ImColor color)
	{
		if (sender.empty() || message.empty())
			return;

		Message notification{};
		notification.m_Sender = sender;
		notification.m_Message = message;
		notification.m_Color = color;

		static const bool isBigScreen = *Pointers.ScreenResX > 1600 && *Pointers.ScreenResY > 900;
		static const int maxMessages = isBigScreen ? 17 : 7;

		std::lock_guard<std::mutex> lock(m_Mutex);

		if (m_Messages.size() >= maxMessages)
		{
			m_Messages.erase(m_Messages.begin());
		}

		m_Messages.push_back(notification);
		MarkAccessed();
	}

	void ChatDisplay::DrawImpl()
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		int position = 0;

		static const float y_pos = position * 100 + 200;
		static const float x_pos = *Pointers.ScreenResX - 470;

		if (m_Messages.size() && m_Opacity >= 0.011f)
		{
			ImGui::SetNextWindowSize(ImVec2(*Pointers.ScreenResX - x_pos - 10, *Pointers.ScreenResY - y_pos), ImGuiCond_Always);
			ImGui::SetNextWindowPos(ImVec2(x_pos, y_pos), ImGuiCond_Always);

			if (ImGui::Begin("##chatwin", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoInputs))
			{
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
				ImGui::PushFont(Menu::Font::g_ChatFont);

				for (auto& message : m_Messages)
				{
					auto color = message.m_Color;
					color.Value.w = m_Opacity;
					ImGui::PushStyleColor(ImGuiCol_Text, color.Value);
					ImGui::TextWrapped("%s:", message.m_Sender.data());
					ImGui::PopStyleColor();
					ImGui::SameLine();
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, m_Opacity));
					ImGui::TextWrapped("%s", message.m_Message.data());
					ImGui::PopStyleColor();
				}

				ImGui::PopFont();
				ImGui::PopStyleColor();
			}

			ImGui::End();
		}

		// TODO: unlink fade speed with FPS
		if (std::chrono::system_clock::now() - m_LastAccessTime > 15s && m_Opacity != 0.0f)
		{
			m_Opacity -= 0.01f;
			if (m_Opacity <= 0.011f)
				m_Opacity = 0.0f;
		}
	}

	void ChatDisplay::ClearImpl()
	{
		m_Messages.clear();
	}

	void ChatDisplay::MarkAccessedImpl()
	{
		m_Opacity = 1.0f;
		m_LastAccessTime = std::chrono::system_clock::now();
	}
}