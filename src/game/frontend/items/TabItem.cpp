#include "Items.hpp"
#include "core/translation/Translation.hpp"

namespace YimMenu
{
	TabItem::TabItem(const std::string& name) :
	    m_Name(name)
	{
	}

	void TabItem::Draw()
	{
		if (ImGui::BeginTabItem(Translation::TrLabel(m_Name).c_str()))
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
