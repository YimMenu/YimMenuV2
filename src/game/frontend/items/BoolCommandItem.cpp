#include "Items.hpp"
#include "core/translation/Translation.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/Command.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "core/frontend/widgets/toggle/imgui_toggle.hpp"

namespace YimMenu
{
	BoolCommandItem::BoolCommandItem(joaat_t id, std::optional<std::string> label_override) :
	    m_Command(Commands::GetCommand<BoolCommand>(id)),
	    m_LabelOverride(Translation::TrOptionalLabel(label_override))
	{
	}

	void BoolCommandItem::Draw()
	{
		if (!m_Command)
		{
			ImGui::Text("%s", Translation::Tr("Unknown!").c_str());
			return;
		}

		bool enabled = m_Command->GetState();
		if (ImGui::Toggle(m_LabelOverride.has_value() ? m_LabelOverride.value().data() : m_Command->GetLabel().data(), &enabled))
			m_Command->SetState(enabled);

		// TODO: refactor this

		auto windowLabel = std::format("{} {}", m_Command->GetLabel(), Translation::Tr("Hotkey"));

		if (ImGui::IsItemHovered())
		{
			ImGui::SetTooltip("%s", m_Command->GetDescription().data());
			if (GetAsyncKeyState(VK_OEM_3) & 0x8000)
				ImGui::OpenPopup(std::format("{} {}", m_Command->GetLabel(), Translation::Tr("Hotkey")).data());
		}

		ImGui::SetNextWindowSize(ImVec2(500, 120));
		if (ImGui::BeginPopupModal(windowLabel.data(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar))
		{
			ImGui::BulletText("%s", Translation::Tr("Hover over the command name to change its hotkey").c_str());
			ImGui::BulletText("%s", Translation::Tr("Press any registered key to remove").c_str());
			ImGui::Separator();


			ImGui::Spacing();
			if (ImGui::Button(Translation::TrLabel("Close").c_str()) || ((!ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered()) && ImGui::IsMouseClicked(ImGuiMouseButton_Left)))
				ImGui::CloseCurrentPopup();

			ImGui::EndPopup();
		}
	}
}