#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class mobile_radio : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;


		virtual void OnTick() override
		{
			AUDIO::SET_MOBILE_PHONE_RADIO_STATE(true);
			AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(true);
		}

		virtual void OnDisable() override
			{
			    AUDIO::SET_MOBILE_PHONE_RADIO_STATE(false);
			    AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(false);		
		    }
	};

	static mobile_radio _mobile_radio{"mobileradio", "MOBILE_RADIO", "Play GTA V Radio without vehicle Press Q the choose your Radio the hear"};
}
