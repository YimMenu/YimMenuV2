#include "Items.hpp"
#include "core/translation/Translation.hpp"
#include "core/commands/Command.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/ListCommand.hpp"
#include "core/frontend/widgets/toggle/imgui_toggle.hpp"

namespace YimMenu
{
	ListCommandItem::ListCommandItem(joaat_t id, std::optional<std::string> label_override) :
	    m_Command(Commands::GetCommand<ListCommand>(id)),
	    m_LabelOverride(Translation::TrOptionalLabel(label_override))
	{
	}

	void ListCommandItem::Draw()
	{
		if (!m_Command)
		{
			ImGui::Text("%s", Translation::Tr("Unknown list!").c_str());
			return;
		}

		int current_val = m_Command->GetState();
		auto& list = m_Command->GetList();
		const char* largest_string = "";
		std::size_t largest_string_len = 0;

		if (!m_SelectedItem.has_value() || !m_ItemWidth.has_value())
		{
			for (auto& item : list)
			{
				if (item.first == current_val)
				{
					m_SelectedItem = item.second;
				}

				int length = strlen(item.second);
				if (length > largest_string_len)
				{
					largest_string = item.second;
					largest_string_len = length;
				}
			}

			if (!m_SelectedItem.has_value())
				m_SelectedItem = "";

			auto size = ImGui::CalcTextSize(Translation::Tr(largest_string).c_str());
			m_ItemWidth = size.x + 40.0f;
		}

		ImGui::SetNextItemWidth(m_ItemWidth.value());
		const auto label = Translation::TrLabel(m_LabelOverride.value_or(m_Command->GetLabel()));
		if (ImGui::BeginCombo(label.c_str(), Translation::Tr(m_SelectedItem.value()).c_str()))
		{
			for (auto& el : list)
			{
				if (ImGui::Selectable(Translation::TrLabel(el.second).c_str(), el.first == current_val))
				{
					current_val = el.first;
					m_Command->SetState(el.first);
				}

				if (el.first == current_val)
				{
					m_SelectedItem = el.second; // just in case
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
	}
}