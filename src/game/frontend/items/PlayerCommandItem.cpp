#include "Items.hpp"
#include "game/commands/PlayerCommand.hpp"
#include "core/commands/Commands.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/backend/Players.hpp"

namespace YimMenu
{
	PlayerCommandItem::PlayerCommandItem(joaat_t id, std::optional<std::string> label_override) :
	    m_Command(Commands::GetCommand<PlayerCommand>(id)),
	    m_LabelOverride(label_override)
	{
	}

	void PlayerCommandItem::Draw()
	{
		if (!m_Command)
		{
			ImGui::Text("Unknown!");
			return;
		}

		if (ImGui::Button(m_LabelOverride.has_value() ? m_LabelOverride.value().data() : m_Command->GetLabel().data()))
		{
			FiberPool::Push([this] {
				if (Players::GetSelected().IsValid())
					m_Command->Call(Players::GetSelected());
			});
		}

		if (ImGui::IsItemHovered())
		{
			ImGui::SetTooltip("%s", m_Command->GetDescription().data());
		}
	}
}