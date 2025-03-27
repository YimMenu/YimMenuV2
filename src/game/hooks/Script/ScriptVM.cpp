#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/backend/ScriptPatches.hpp"

namespace YimMenu::Hooks
{
	int Script::ScriptVM(uint64_t* stack, uint64_t** scr_globals, rage::scrProgram* program, void* ctx)
	{
		if (g_Running)
		{
			ScriptPatches::OnScriptVMEnter(program);
			auto res = BaseHook::Get<Script::ScriptVM, DetourHook<decltype(&Script::ScriptVM)>>()->Original()(stack, scr_globals, program, ctx);
			ScriptPatches::OnScriptVMLeave(program);
			return res;
		}
		return BaseHook::Get<Script::ScriptVM, DetourHook<decltype(&Script::ScriptVM)>>()->Original()(stack, scr_globals, program, ctx);
	}
}