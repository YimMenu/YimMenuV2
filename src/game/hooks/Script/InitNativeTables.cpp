#include "core/hooking/DetourHook.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/backend/ScriptPatches.hpp"
#include "game/hooks/Hooks.hpp"

#include "types/script/scrProgram.hpp"

namespace YimMenu::Hooks
{
	void Script::InitNativeTables(rage::scrProgram* program)
	{
		BaseHook::Get<Script::InitNativeTables, DetourHook<decltype(&Script::InitNativeTables)>>()->Original()(program);
		if (g_Running)
		{
			if (program->m_CodeBlocks && program->m_CodeSize)
			{
				NativeHooks::RegisterProgram(program);
				ScriptPatches::RegisterProgram(program);
			}
			else
			{
				// printing name causes crash
				// LOGF(VERBOSE, "InitNativeTables: skipping SHV script {}", program->m_Name);
			}
		}
	}
}