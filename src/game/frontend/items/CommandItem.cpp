#include "Items.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/Command.hpp"
#include "core/commands/HotkeySystem.hpp"
#include "core/backend/FiberPool.hpp"
#include "DrawHotkey.hpp"

namespace YimMenu
{
	CommandItem::CommandItem(joaat_t id, std::optional<std::string> label_override) :
	    m_Command(Commands::GetCommand<Command>(id)),
	    m_LabelOverride(label_override)
	{
	}

	void CommandItem::Draw()
	{
		if (!m_Command)
		{
			ImGui::Text("Unknown!");
			return;
		}

		if (ImGui::Button(m_LabelOverride.has_value() ? m_LabelOverride.value().data() : m_Command->GetLabel().data()))
		{
			// Capture the command by value, not 'this'. This item may be drawn from a 
			// Lua command handle's :draw()) and gets destroyed before the FiberPool task runs.
			auto command = m_Command;
			FiberPool::Push([command] {
				command->Call();
			});
		}

		// TODO: refactor this

		auto windowLabel = std::format("{} Hotkey", m_Command->GetLabel());

		if (ImGui::IsItemHovered())
		{
			ImGui::SetTooltip("%s", m_Command->GetDescription().data());
			if (GetAsyncKeyState(VK_CAPITAL) & 0x8000)
				ImGui::OpenPopup(std::format("{} Hotkey", m_Command->GetLabel()).data());
		}

		ImGui::SetNextWindowSize(ImVec2(500, 120));
		if (ImGui::BeginPopupModal(windowLabel.data(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar))
		{
			ImGui::BulletText("Enter a keystroke");

			ImGui::Separator();

			HotkeySystem::SetBeingModifed(true);

			if (auto it = g_HotkeySystem.m_CommandHotkeys.find(m_Command->GetHash()); it != g_HotkeySystem.m_CommandHotkeys.end())
				DrawHotkey(&it->second, m_Command->GetLabel());

			ImGui::Spacing();
			if (ImGui::Button("Close") || ((!ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered()) && ImGui::IsMouseClicked(ImGuiMouseButton_Left)))
			{
				HotkeySystem::SetBeingModifed(false);
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}
}