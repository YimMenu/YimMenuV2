#include "game/pointers/Pointers.hpp"
#include "game/frontend/Menu.hpp"
#include "core/frontend/manager/UIManager.hpp"

namespace YimMenu
{
	void RenderModernTheme()
	{
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
		for (size_t i = 0; i < submenus.size(); ++i)
		{
			auto& submenu = submenus[i];
			ImVec2 bubblePos(basePos.x + i * bubbleSpacing, basePos.y + 2);
			ImVec2 center(bubblePos.x + bubbleSize / 2.0f, bubblePos.y + bubbleSize / 2.0f);

			ImGui::SetCursorScreenPos(bubblePos);
			ImGui::PushID(static_cast<int>(i));

			ImVec2 bgPos(center.x - bgSize / 2.0f, center.y - bgSize / 2.0f);
			drawList->AddRectFilled(bgPos, ImVec2(bgPos.x + bgSize, bgPos.y + bgSize), IM_COL32(10, 10, 10, 255), rounding);
			drawList->AddRect(bgPos, ImVec2(bgPos.x + bgSize, bgPos.y + bgSize), IM_COL32(192, 192, 192, 32), rounding, ImDrawFlags_None, 1.0f);

			ImU32 bubbleColor = IM_COL32(25, 25, 31, 255);
			ImU32 hoverColor = IM_COL32(46, 46, 51, 255);
			ImGui::InvisibleButton("##Bubble", ImVec2(bubbleSize, bubbleSize));
			bool hovered = ImGui::IsItemHovered();
			bool clicked = ImGui::IsItemClicked();

			drawList->AddRectFilled(bubblePos, ImVec2(bubblePos.x + bubbleSize, bubblePos.y + bubbleSize), hovered ? hoverColor : bubbleColor, rounding);
			drawList->AddRect(bubblePos, ImVec2(bubblePos.x + bubbleSize, bubblePos.y + bubbleSize), IM_COL32(192, 192, 192, 16), rounding, ImDrawFlags_None, 1.0f);

			auto activeSubmenu = YimMenu::UIManager::GetActiveSubmenu();

			if (clicked)
			{
				if (submenu == activeSubmenu)
				{
					YimMenu::UIManager::SetShowContentWindow(!YimMenu::UIManager::ShowingContentWindow());
				}
				else
				{
					YimMenu::UIManager::SetActiveSubmenu(submenu);
					YimMenu::UIManager::SetShowContentWindow(true);
				}
			}

			ImU32 defaultIconColor = IM_COL32(255, 255, 255, 255);
			ImU32 activeIconColor = IM_COL32(46, 204, 113, 255);
			ImU32 hoveredIconColor = IM_COL32(36, 174, 93, 255);
			ImU32 iconColor = submenu == activeSubmenu ? activeIconColor : (hovered ? hoveredIconColor : defaultIconColor);

			ImGui::PushFont(YimMenu::Menu::Font::g_AwesomeFont);
			ImVec2 iconSize = ImGui::CalcTextSize(submenu->m_Icon.c_str());
			ImVec2 iconPos(center.x - iconSize.x / 2, center.y - iconSize.y / 2);
			drawList->AddText(YimMenu::Menu::Font::g_AwesomeFont, 0.0f, iconPos, iconColor, submenu->m_Icon.c_str());
			ImGui::PopFont();

			ImU32 defaultTextColor = IM_COL32(255, 255, 255, 255);
			ImU32 activeTextColor = IM_COL32(46, 204, 113, 255);
			ImU32 hoveredTextColor = IM_COL32(36, 174, 93, 255);
			ImU32 textColor = submenu == activeSubmenu ? activeTextColor : (hovered ? hoveredTextColor : defaultTextColor);

			ImVec2 labelSize = ImGui::CalcTextSize(submenu->m_Name.c_str());
			ImVec2 labelPos(center.x - labelSize.x / 2, bubblePos.y + bubbleSize + 15.0f);
			ImVec2 bgMin = labelPos - ImVec2(6, 2);
			ImVec2 bgMax = labelPos + labelSize + ImVec2(6, 2);

			drawList->AddRectFilled(bgMin, bgMax, IM_COL32(26, 26, 31, 120));
			drawList->AddRect(bgMin, bgMax, IM_COL32(192, 192, 192, 16), 4.0f);
			drawList->AddText(labelPos, textColor, submenu->m_Name.c_str());

			ImGui::PopID();
		}

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
				basePosOffset.x += delta.x;
				basePosOffset.y += delta.y;
				dragStart = io.MousePos;
			}
		}
		else
		{
			dragging = false;
		}

		ImGui::End();

		auto activeSubmenu = YimMenu::UIManager::GetActiveSubmenu();

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
				{
					activeSubmenu->DrawCategorySelectors();
				}
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
