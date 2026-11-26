#include "Items.hpp"
#include "core/translation/Translation.hpp"
#include "core/commands/ColorCommand.hpp"
#include "core/commands/Command.hpp"
#include "core/commands/Commands.hpp"
#include "core/frontend/widgets/toggle/imgui_toggle.hpp"

namespace YimMenu
{
	ColorCommandItem::ColorCommandItem(joaat_t id, std::optional<std::string> labelOverride) :
	    m_Command(Commands::GetCommand<ColorCommand>(id)),
	    m_LabelOverride(Translation::TrOptionalLabel(labelOverride))
	{
	}

	void ColorCommandItem::Draw()
	{
		if (!m_Command)
		{
			ImGui::Text("%s", Translation::Tr("Unknown color picker!").c_str());
			return;
		}

		auto color = m_Command->GetState();
		auto label = m_LabelOverride.has_value() ? m_LabelOverride.value().c_str() : m_Command->GetLabel().c_str();

		ImGui::SameLine();

		ImGui::SetNextItemWidth(150);
		if (ImGui::ColorButton(label, color))
		{
			ImGui::OpenPopup(label);
		}

		if (ImGui::BeginPopup(label))
		{
			if (ImGui::ColorPicker4("##picker", (float*)&color))
			{
				m_Command->SetState(color);
			}
			ImGui::EndPopup();
		}
	}
}