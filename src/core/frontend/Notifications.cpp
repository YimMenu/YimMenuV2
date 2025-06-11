#include "Notifications.hpp"

#include "core/logger/LogHelper.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/util/Joaat.hpp"

#include <mutex>

namespace YimMenu
{

	Notification Notifications::ShowImpl(std::string title, std::string message, NotificationType type, int duration, std::function<void()> context_function, std::string context_function_name)
	{
		if (title.empty() || message.empty())
			return {};

		auto message_id = Joaat(title + message);

		auto exists = std::find_if(m_Notifications.begin(), m_Notifications.end(), [&](auto& notification) {
			return notification.second.m_Identifier == message_id;
		});

		if (exists != m_Notifications.end())
		{
			exists->second.m_CreatedOn = std::chrono::system_clock::now();
			return {};
		}

		Notification notification{};
		notification.m_Title = title;
		notification.m_Message = message;
		notification.m_Type = type;
		notification.m_CreatedOn = std::chrono::system_clock::now();
		notification.m_Duration = duration;
		notification.m_Identifier = message_id;

		if (context_function)
		{
			notification.m_ContextFunc = context_function;
			notification.m_ContextFuncName = context_function_name.empty() ? "Context Function" : context_function_name;
		}

		std::lock_guard<std::mutex> lock(m_mutex);
		auto result = m_Notifications.insert(std::make_pair(title + message, notification));

		return notification;
	}

	bool Notifications::EraseImpl(Notification notification)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		for (auto& [id, n] : m_Notifications)
		{
			if (n.m_Identifier == notification.m_Identifier)
			{
				n.m_Erasing = true;
				return true;
			}
		}

		return false;
	}

	static void DrawNotification(Notification& notification, int position)
	{
		float y_pos = position * 100;
		float x_pos = 10;
		ImVec2 cardSize(m_CardSizeX, m_CardSizeY);

		ImGui::SetNextWindowSize(cardSize, ImGuiCond_Always);
		ImGui::SetNextWindowPos(ImVec2(x_pos + notification.m_AnimationOffset, y_pos + 10), ImGuiCond_Always);

		std::string windowTitle = std::to_string(position);
		ImGui::Begin(windowTitle.c_str(), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoFocusOnAppearing);

		auto timeElapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - notification.m_CreatedOn).count();

		auto depletionProgress = 1.0f - (timeElapsed / (float)notification.m_Duration);

		ImGui::ProgressBar(depletionProgress, ImVec2(-1, 3.5f), "");

		// TODO: Add icon for type instead of colored text
		if (notification.m_Type == NotificationType::Info)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
			ImGui::Text("%s", notification.m_Title.c_str());
		}
		else if (notification.m_Type == NotificationType::Success)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
			ImGui::Text("%s", notification.m_Title.c_str());
		}
		else if (notification.m_Type == NotificationType::Warning)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.5f, 0.0f, 1.0f));
			ImGui::Text("%s", notification.m_Title.c_str());
		}
		else if (notification.m_Type == NotificationType::Error)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
			ImGui::Text("%s", notification.m_Title.c_str());
		}

		ImGui::PopStyleColor();

		ImGui::Separator();

		ImGui::TextWrapped("%s", notification.m_Message.c_str());

		if (notification.m_ContextFunc)
		{
			ImGui::Spacing();
			if (ImGui::Selectable(notification.m_ContextFuncName.c_str()))
				FiberPool::Push([notification] {
					notification.m_ContextFunc();
				});
		}

		ImGui::End();
	}

	void Notifications::DrawImpl()
	{
		std::vector<std::string> keys_to_erase;
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			int position = 0;

			for (auto& [id, notification] : m_Notifications)
			{
				DrawNotification(notification, position);

				if (!notification.m_Erasing)
				{
					if (notification.m_AnimationOffset < 0)
						notification.m_AnimationOffset += m_CardAnimationSpeed;

					//Need this to account for changes in card size (x dimension), custom increments might result in odd numbers
					if (notification.m_AnimationOffset > 0)
						notification.m_AnimationOffset = 0.f;
				}
				else
				{
					notification.m_AnimationOffset -= m_CardAnimationSpeed;
					if (notification.m_AnimationOffset <= -m_CardSizeX)
						keys_to_erase.push_back(id);
				}


				if ((float)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - notification.m_CreatedOn).count() >= notification.m_Duration)
					keys_to_erase.push_back(id);

				position++;
			}
		}
		std::lock_guard<std::mutex> lock(m_mutex);
		for (const auto& key : keys_to_erase)
		{
			m_Notifications.erase(key);
		}
	}
}
