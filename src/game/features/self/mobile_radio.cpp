#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class MobileRadio : public LoopedCommand
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

	static MobileRadio _MobileRadio{"mobileradio", "MOBILE_RADIO", "Play GTA V Radio without vehicle Press Q the choose your Radio the hear"};
}
