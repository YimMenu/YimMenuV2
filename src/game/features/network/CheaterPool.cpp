#include "core/commands/BoolCommand.hpp"
#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu::Features
{
	class CheaterPool : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			Pointers.SetJoinRequestPoolTypePatch->Apply();
			Pointers.HandleJoinRequestIgnorePoolPatch->Apply();
		}

		virtual void OnDisable() override
		{
			Pointers.SetJoinRequestPoolTypePatch->Restore();
			Pointers.HandleJoinRequestIgnorePoolPatch->Restore();
		}
	};

	static CheaterPool _CheaterPool{"cheaterpool", "Cheater Pool", "Matchmaking will put you into sessions with other YimMenu users.", true};
}

namespace YimMenu::Hooks
{
	int Network::GetPoolType()
	{
		if (YimMenu::Features::_CheaterPool.GetState())
			return 1;

		return BaseHook::Get<Network::GetPoolType, DetourHook<decltype(&Network::GetPoolType)>>()->Original()();
	}
}