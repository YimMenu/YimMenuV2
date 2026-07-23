#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class HideHud : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();
		}
	};

	static HideHud _HideHud{"hidehud", "Hide HUD", "Hides the HUD and radar (map, health bar, cash, etc.)"};
}
