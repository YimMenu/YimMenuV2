#include "core/commands/LoopedCommand.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu::Features
{
	class SilencePhonecalls : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			constexpr auto is_incoming_call = ScriptGlobal(23010);
			constexpr auto is_phone_call_in_progress = ScriptGlobal(23006);
			constexpr auto phone_call_state = ScriptGlobal(23000);
			constexpr auto calling_character = ScriptGlobal(8779);

			if (*Pointers.IsSessionStarted)
			{
				if (*phone_call_state.As<int*>() != 0 && *phone_call_state.As<int*>() != 5 && *phone_call_state.As<int*>() != 6
				    && *is_phone_call_in_progress.As<bool*>() && *is_incoming_call.As<bool*>())
				{
					LOGF(VERBOSE, "SilencePhoneCalls::OnTick(): Skipped phone call from character {}", *calling_character.As<int*>());
					*phone_call_state.As<int*>() = 6;
				}
			}
		}
	};

	static SilencePhonecalls _SilencePhonecalls{"nocalls", "Silence Phone Calls", "Automatically silences all incoming calls"};
}