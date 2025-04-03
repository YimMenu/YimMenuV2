#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"
#include <game/gta/Natives.hpp>

namespace YimMenu::Features
{
	class skip_cutscene : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
		}
	};

	static skip_cutscene _skip_cutscene{"SkipCutscene", "SKIP_CUTSCENE", "SKIP_CUTSCENE_DESC"}; //static skip_cutscene _skip_cutscene{"SkipCutscene", "SKIP_CUTSCENE", "SKIP_CUTSCENE_DESC", 0};
}