#include "core/commands/BoolCommand.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu::Features
{
	class PauseGame : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			Pointers.AllowPausingInSessionPatch->Apply();
		}

		virtual void OnDisable() override
		{
			Pointers.AllowPausingInSessionPatch->Restore();
		}
	};

	static PauseGame _PauseGame{"pausegame", "Pause Game", "Allows you to pause the game in online (local only)."};
}