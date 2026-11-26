#include "Items.hpp"
#include "core/translation/Translation.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/StringCommand.hpp"
#include "imgui.h"

namespace YimMenu
{
	StringCommandItem::StringCommandItem(joaat_t id, std::optional<std::string> label_override) :
	    m_Command(Commands::GetCommand<StringCommand>(id)),
	    m_LabelOverride(Translation::TrOptionalLabel(label_override))
	{
	}

	void StringCommandItem::Draw()
	{
		if (!m_Command)
		{
			ImGui::Text("%s", Translation::Tr("Unknown string command!").c_str());
			return;
		}

		std::string current_value = m_Command->GetString();
		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		memcpy(buffer, current_value.c_str(), current_value.size());

		ImGui::SetNextItemWidth(300.0f);
		if (ImGui::InputText(m_LabelOverride.value_or(m_Command->GetLabel()).c_str(), buffer, sizeof(buffer)))
		{
			m_Command->SetStringValue(buffer);
		}
	}
}
