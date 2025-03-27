#include "core/hooking/DetourHook.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/backend/ScriptPatches.hpp"
#include "game/hooks/Hooks.hpp"

namespace YimMenu::Hooks
{
	void Script::InitNativeTables(rage::scrProgram* program)
	{
		BaseHook::Get<Script::InitNativeTables, DetourHook<decltype(&Script::InitNativeTables)>>()->Original()(program);
		if (g_Running)
		{
			NativeHooks::RegisterProgram(program);
			ScriptPatches::RegisterProgram(program);
		}
	}
}