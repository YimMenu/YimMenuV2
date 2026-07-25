#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class DisableTextSounds : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			HUD::DISABLE_FRONTEND_THIS_FRAME();
		}
	};

	static DisableTextSounds _DisableTextSounds{"disabletextsounds", "Disable Text Sounds", "Mutes frontend/UI sound effects such as text and prompt beeps"};
}
