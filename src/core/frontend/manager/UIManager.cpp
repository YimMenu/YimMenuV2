#include "UIManager.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/frontend/Menu.hpp"

namespace YimMenu
{
	void UIManager::AddSubmenuImpl(const std::shared_ptr<Submenu>&& submenu)
	{
		if (!m_ActiveSubmenu)
			m_ActiveSubmenu = submenu;

		m_Submenus.push_back(std::move(submenu));
	}

	void UIManager::SetActiveSubmenuImpl(const std::shared_ptr<Submenu> Submenu)
	{
		m_ActiveSubmenu = Submenu;
	}

	void UIManager::DrawImpl()
	{
		ImGuiIO& io = ImGui::GetIO();
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();

		float bubbleSpacing = 75.0f;
		float bubbleSize = 55.0f;
		float bgSize = 70.0f;
		float rounding = 8.0f;
		ImVec2 basePos((*Pointers.ScreenResX / 2.0f) - (bubbleSpacing * m_Submenus.size() / 2.0f), 80.0f);

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(io.DisplaySize);
		ImGui::Begin("##BubbleInputWindow", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);

		for (size_t i = 0; i < m_Submenus.size(); ++i)
		{
			auto& submenu = m_Submenus[i];
			ImVec2 bubblePos(basePos.x + i * bubbleSpacing, basePos.y + 2);
			ImVec2 center(bubblePos.x + bubbleSize / 2.0f, bubblePos.y + bubbleSize / 2.0f);

			ImGui::SetCursorScreenPos(bubblePos);
			ImGui::PushID(static_cast<int>(i));

			ImVec2 bgPos = ImVec2(center.x - bgSize / 2.0f, center.y - bgSize / 2.0f);
			drawList->AddRectFilled(bgPos, ImVec2(bgPos.x + bgSize, bgPos.y + bgSize), IM_COL32(10, 10, 10, 255), rounding);

			drawList->AddRect(bgPos, ImVec2(bgPos.x + bgSize, bgPos.y + bgSize), IM_COL32(192, 192, 192, 32), rounding, ImDrawFlags_None, 1.0f);

			ImU32 bubbleColor = IM_COL32(25, 25, 31, 255);
			ImU32 hoverColor = IM_COL32(46, 46, 51, 255);
			ImGui::InvisibleButton("##Bubble", ImVec2(bubbleSize, bubbleSize));
			bool hovered = ImGui::IsItemHovered();
			bool clicked = ImGui::IsItemClicked();
			drawList->AddRectFilled(bubblePos, ImVec2(bubblePos.x + bubbleSize, bubblePos.y + bubbleSize), hovered ? hoverColor : bubbleColor, rounding);

			drawList->AddRect(bubblePos, ImVec2(bubblePos.x + bubbleSize, bubblePos.y + bubbleSize), IM_COL32(192, 192, 192, 16), rounding, ImDrawFlags_None, 1.0f);

			if (clicked)
			{
				if (submenu == m_ActiveSubmenu)
				{
					m_ShowContentWindow = !m_ShowContentWindow;
				}
				else
				{
					SetActiveSubmenu(submenu);
					m_ShowContentWindow = true;
				}
			}

			ImU32 defaultIconColor = IM_COL32(255, 255, 255, 255);
			ImU32 activeIconColor = IM_COL32(120, 90, 160, 255);
			ImU32 hoveredIconColor = IM_COL32(90, 70, 120, 255);

			ImU32 iconColor = submenu == m_ActiveSubmenu ? activeIconColor : (ImGui::IsItemHovered() ? hoveredIconColor : defaultIconColor);

			ImGui::PushFont(Menu::Font::g_AwesomeFont);
			ImVec2 iconSize = ImGui::CalcTextSize(submenu->m_Icon.c_str());
			ImVec2 iconPos(center.x - iconSize.x / 2, center.y - iconSize.y / 2);
			drawList->AddText(Menu::Font::g_AwesomeFont, 0.0f, iconPos, iconColor, submenu->m_Icon.c_str());
			ImGui::PopFont();

			ImU32 defaultTextColor = IM_COL32(255, 255, 255, 255);
			ImU32 activeTextColor = IM_COL32(120, 90, 160, 255);
			ImU32 hoveredTextColor = IM_COL32(90, 70, 120, 255);

			ImU32 textColor = submenu == m_ActiveSubmenu ? activeTextColor : (ImGui::IsItemHovered() ? hoveredTextColor : defaultTextColor);

			ImVec2 labelSize = ImGui::CalcTextSize(submenu->m_Name.c_str());
			ImVec2 labelPos(center.x - labelSize.x / 2, bubblePos.y + bubbleSize + 15.0f);

			ImVec2 bgMin = labelPos - ImVec2(6, 2);
			ImVec2 bgMax = labelPos + labelSize + ImVec2(6, 2);
			drawList->AddRectFilled(bgMin, bgMax, IM_COL32(26, 26, 31, 120));

			drawList->AddRect(bgMin, bgMax, IM_COL32(192, 192, 192, 16), 4.0f);

			drawList->AddText(labelPos, textColor, submenu->m_Name.c_str());

			ImGui::PopID();
		}

		ImGui::End();

		if (m_ShowContentWindow && m_ActiveSubmenu)
		{
			float windowWidth = *Pointers.ScreenResX / 2.5f;
			float centerX = (*Pointers.ScreenResX - windowWidth) / 2.0f;
			float centerY = *Pointers.ScreenResY / 5.0f;
			ImVec2 windowSize(windowWidth, *Pointers.ScreenResY / 2.5f);

			ImGui::SetNextWindowSize(windowSize, ImGuiCond_Once);
			ImGui::SetNextWindowPos(ImVec2(centerX, centerY), ImGuiCond_Once);
			ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;

			if (ImGui::Begin("##Categories&Content", nullptr, flags))
			{
				if (ImGui::BeginChild("##categorySelectors", ImVec2(0, 60), true))
				{
					m_ActiveSubmenu->DrawCategorySelectors();
				}
				ImGui::EndChild();

				if (ImGui::BeginChild("##options", ImVec2(0, 0), true))
				{
					if (m_OptionsFont)
						ImGui::PushFont(m_OptionsFont);
					m_ActiveSubmenu->Draw();
					if (m_OptionsFont)
						ImGui::PopFont();
				}
				ImGui::EndChild();
			}
			ImGui::End();
		}
	}

	std::shared_ptr<Submenu> UIManager::GetActiveSubmenuImpl()
	{
		if (m_ActiveSubmenu)
		{
			return m_ActiveSubmenu;
		}

		return nullptr;
	}

	std::shared_ptr<Category> UIManager::GetActiveCategoryImpl()
	{
		if (m_ActiveSubmenu)
		{
			return m_ActiveSubmenu->GetActiveCategory();
		}

		return nullptr;
	}
}
