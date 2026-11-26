#include "Items.hpp"
#include "core/translation/Translation.hpp"
#include "misc/cpp/imgui_stdlib.h"


namespace YimMenu
{
	InputTextWithHint::InputTextWithHint(std::string label, std::string hint, std::string* buf, int flags, std::function<void()> cb, ImGuiInputTextCallback inputCallback) :
	    m_Id(label),
	    m_Hint(hint),
	    m_Buf(buf),
	    m_Flags(flags),
	    m_Callback(cb),
	    m_ImGuiInputTextCallback(inputCallback)
	{
	}

	void InputTextWithHint::Draw()
	{
		const auto label = Translation::TrLabel(m_Id);
		const auto hint = Translation::Tr(m_Hint);
		if (ImGui::InputTextWithHint(label.c_str(), hint.c_str(), m_Buf, m_Flags, m_ImGuiInputTextCallback))
			;
		{
			if (m_Callback != nullptr)
			{
				m_Callback();
			}
		}
	}
}