#include "game/pointers/Pointers.hpp"
#include "game/frontend/Menu.hpp"
#include "core/frontend/manager/UIManager.hpp"
#include "game/frontend/submenus/Settings/GUISettings.hpp"

namespace YimMenu
{
	void RenderModernTheme()
	{
		YimMenu::SyncColorCommandsToStyle();

		ImGuiIO& io = ImGui::GetIO();
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		float bubbleSpacing = 75.0f;
		float bubbleSize = 55.0f;
		float bgSize = 70.0f;
		float rounding = 8.0f;

		static ImVec2 basePosOffset = ImVec2(0, 0);
		static bool dragging = false;
		static ImVec2 dragStart = ImVec2(0, 0);

		ImVec2 defaultBasePos((*YimMenu::Pointers.ScreenResX / 2.0f) - (bubbleSpacing * YimMenu::UIManager::GetSubmenus().size() / 2.0f), 80.0f);
		ImVec2 basePos = defaultBasePos + basePosOffset;

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(io.DisplaySize);
		ImGui::Begin("##BubbleInputWindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);

		const auto& submenus = YimMenu::UIManager::GetSubmenus();
		auto activeSubmenu = YimMenu::UIManager::GetActiveSubmenu();

		for (size_t i = 0; i < submenus.size(); ++i)
		{
			auto& submenu = submenus[i];
			ImVec2 bubblePos(basePos.x + i * bubbleSpacing, basePos.y + 2);
			ImVec2 center(bubblePos.x + bubbleSize / 2.0f, bubblePos.y + bubbleSize / 2.0f);

			ImGui::SetCursorScreenPos(bubblePos);
			ImGui::PushID(static_cast<int>(i));

			ImGui::InvisibleButton("##Bubble", ImVec2(bubbleSize, bubbleSize));
			bool hovered = ImGui::IsItemHovered();
			bool clicked = ImGui::IsItemClicked();

			if (clicked)
			{
				if (submenu == activeSubmenu)
					YimMenu::UIManager::SetShowContentWindow(!YimMenu::UIManager::ShowingContentWindow());
				else
				{
					YimMenu::UIManager::SetActiveSubmenu(submenu);
					YimMenu::UIManager::SetShowContentWindow(true);
				}
			}

			// Colors
			ImU32 buttonColor = ImGui::GetColorU32(ImGuiCol_Button);
			ImU32 hoverColor = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
			ImU32 activeColor = ImGui::GetColorU32(ImGuiCol_ButtonActive);
			ImU32 borderColor = ImGui::GetColorU32(ImGuiCol_Border);
			ImU32 iconColor = ImGui::GetColorU32(ImGuiCol_Text);

			ImU32 fillColor = (submenu == activeSubmenu) ? activeColor : (hovered ? hoverColor : buttonColor);

			// Bubble background and border
			drawList->AddRectFilled(bubblePos, bubblePos + ImVec2(bubbleSize, bubbleSize), fillColor, rounding);
			drawList->AddRect(bubblePos, bubblePos + ImVec2(bubbleSize, bubbleSize), borderColor, rounding);

			// Icon (text color only)
			ImGui::PushFont(YimMenu::Menu::Font::g_AwesomeFont);
			ImVec2 iconSize = ImGui::CalcTextSize(submenu->m_Icon.c_str());
			ImVec2 iconPos(center.x - iconSize.x / 2, center.y - iconSize.y / 2);
			drawList->AddText(YimMenu::Menu::Font::g_AwesomeFont, 0.0f, iconPos, iconColor, submenu->m_Icon.c_str());
			ImGui::PopFont();

			// Label
			ImVec2 labelSize = ImGui::CalcTextSize(submenu->m_Name.c_str());
			ImVec2 labelPos(center.x - labelSize.x / 2, bubblePos.y + bubbleSize + 15.0f);
			ImVec2 bgMin = labelPos - ImVec2(6, 2);
			ImVec2 bgMax = labelPos + labelSize + ImVec2(6, 2);
			drawList->AddRectFilled(bgMin, bgMax, ImGui::GetColorU32(ImGuiCol_ChildBg));
			drawList->AddRect(bgMin, bgMax, borderColor, 4.0f);
			drawList->AddText(labelPos, iconColor, submenu->m_Name.c_str());

			ImGui::PopID();
		}

		// Drag zone
		ImVec2 dragZoneMin = ImVec2(basePos.x, basePos.y - 20);
		ImVec2 dragZoneMax = ImVec2(basePos.x + bubbleSpacing * submenus.size(), basePos.y + bubbleSize);
		ImGui::SetCursorScreenPos(dragZoneMin);
		ImGui::InvisibleButton("##BubbleDragZone", dragZoneMax - dragZoneMin);

		if (ImGui::IsItemActive())
		{
			if (!dragging)
			{
				dragging = true;
				dragStart = io.MousePos;
			}
			else
			{
				ImVec2 delta = io.MousePos - dragStart;
				basePosOffset += delta;
				dragStart = io.MousePos;
			}
		}
		else
		{
			dragging = false;
		}

		ImGui::End(); // ##BubbleInputWindow

		// Content window
		if (YimMenu::UIManager::ShowingContentWindow() && activeSubmenu)
		{
			float windowWidth = *YimMenu::Pointers.ScreenResX / 2.5f;
			float centerX = (*YimMenu::Pointers.ScreenResX - windowWidth) / 2.0f;
			float centerY = *YimMenu::Pointers.ScreenResY / 5.0f;
			ImVec2 windowSize(windowWidth, *YimMenu::Pointers.ScreenResY / 2.5f);

			ImGui::SetNextWindowSize(windowSize, ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowPos(ImVec2(centerX, centerY), ImGuiCond_FirstUseEver);

			ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;

			if (ImGui::Begin("##Categories&Content", nullptr, flags))
			{
				if (ImGui::BeginChild("##categorySelectors", ImVec2(0, 60), true))
					activeSubmenu->DrawCategorySelectors();
				ImGui::EndChild();

				if (ImGui::BeginChild("##options", ImVec2(0, 0), true))
				{
					ImFont* optionsFont = YimMenu::UIManager::GetOptionsFont();
					if (optionsFont)
						ImGui::PushFont(optionsFont);

					activeSubmenu->Draw();

					if (optionsFont)
						ImGui::PopFont();
				}
				ImGui::EndChild();
			}
			ImGui::End();
		}
	}
}
