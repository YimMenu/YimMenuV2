#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class SkipCutscene : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
		}
	};

	static SkipCutscene _SkipCutscene{"SkipCutscene", "SKIP_CUTSCENE", "SKIP_CUTSCENE_DESC"};
}
