#include "core/commands/BoolCommand.hpp"
#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
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

namespace YimMenu::Hooks
{
	void Features::OpenPauseMenu(uint32_t menuHash, bool pause, uint32_t unk1, bool unk2)
	{
		if (YimMenu::Features::_PauseGame.GetState() && menuHash == 0xBA33ADB3)
			pause = true;

		BaseHook::Get<Features::OpenPauseMenu, DetourHook<decltype(&Features::OpenPauseMenu)>>()->Original()(menuHash, pause, unk1, unk2);
	}
}