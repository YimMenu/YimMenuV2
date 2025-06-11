#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Players.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class Spectate : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		Player m_SpectatingPlayer{nullptr};

		virtual void OnTick() override
		{
			auto selected = Players::GetSelected();
			if (selected != m_SpectatingPlayer)
			{
				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, 0);
				HUD::SET_MINIMAP_IN_SPECTATOR_MODE(false, 0);

				m_SpectatingPlayer = selected;
			}

			if (m_SpectatingPlayer)
			{
				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, m_SpectatingPlayer.GetPed().GetHandle());
				HUD::SET_MINIMAP_IN_SPECTATOR_MODE(true, m_SpectatingPlayer.GetPed().GetHandle());
			}
		}

		virtual void OnDisable() override
		{
			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, 0);
			HUD::SET_MINIMAP_IN_SPECTATOR_MODE(false, 0);
		}
	};

	static Spectate _Spectate{"spectate", "Spectate", "Spectates the selected player"};
}