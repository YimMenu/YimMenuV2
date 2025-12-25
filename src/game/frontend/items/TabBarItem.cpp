#include "Items.hpp"

namespace YimMenu
{
	TabBarItem::TabBarItem(const std::string& id) :
		m_Id(id)
	{
	}

	void TabBarItem::Draw()
	{
		if (ImGui::BeginTabBar(m_Id.c_str()))
		{
			for (const auto& tab : m_Tabs)
			{
				if (tab->CanDraw())
					tab->Draw();
			}
			ImGui::EndTabBar();
		}
	}
}