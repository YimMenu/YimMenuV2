#include "Items.hpp"

namespace YimMenu
{
	TabItem::TabItem(const std::string& name) :
	    m_Name(name)
	{
	}

	void TabItem::Draw()
	{
		if (ImGui::BeginTabItem(m_Name.c_str()))
		{
			for (auto& item : m_Items)
			{
				if (item->CanDraw())
					item->Draw();
			}
			ImGui::EndTabItem();
		}
	}
}
