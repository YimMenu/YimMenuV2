#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"

namespace YimMenu::Hooks
{
	BOOL Anticheat::GetThreadContext(HANDLE hThread, LPCONTEXT lpContext)
	{
		auto ret = BaseHook::Get<Anticheat::GetThreadContext, DetourHook<decltype(&Anticheat::GetThreadContext)>>()->Original()(hThread, lpContext);
		lpContext->Dr0 = 0;
		lpContext->Dr1 = 0;
		lpContext->Dr2 = 0;
		lpContext->Dr3 = 0;
		return ret;
	}
}