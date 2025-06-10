#include "Items.hpp"
#include "core/commands/Command.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/FloatCommand.hpp"
#include "core/frontend/widgets/toggle/imgui_toggle.hpp"

namespace YimMenu
{
	FloatCommandItem::FloatCommandItem(joaat_t id, std::optional<std::string> label_override, bool use_slider) :
	    m_useSlider(use_slider),
	    m_Command(Commands::GetCommand<FloatCommand>(id)),
	    m_LabelOverride(label_override)
	{
	}

	void FloatCommandItem::Draw()
	{
		if (!m_Command)
		{
			ImGui::Text("Unknown!");
			return;
		}

		auto value = m_Command->GetState();
		auto label = m_LabelOverride.has_value() ? m_LabelOverride.value().c_str() : m_Command->GetLabel().c_str();
		if (!m_Command->GetMinimum().has_value() || !m_Command->GetMaximum().has_value() || !m_useSlider)
		{
			ImGui::SetNextItemWidth(150);
			if (ImGui::InputFloat(label, &value))
			{
				m_Command->SetState(value);
			}
		}
		else
		{
			ImGui::SetNextItemWidth(150);
			if (ImGui::SliderFloat(label, &value, m_Command->GetMinimum().value(), m_Command->GetMaximum().value()))
			{
				m_Command->SetState(value);
			}
		}
	}
}