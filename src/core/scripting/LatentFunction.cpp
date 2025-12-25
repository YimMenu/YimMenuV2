#include "LatentFunction.hpp"

namespace YimMenu::Lua
{
	static void LatentFiber(LPVOID parameter)
	{
		auto callback = reinterpret_cast<LuaScript::ScriptCallback*>(parameter);
		callback->m_LastReturnValue = callback->m_LatentTarget(callback->m_CoroState);
		SwitchToFiber(callback->m_ParentFiber);
	}

	int LatentFunctionInternal(lua_State* state, lua_CFunction func)
	{
		auto& script = LuaScript::GetScript(state);
		auto callback = script.GetRunningCallback();

		if (!callback)
			luaL_error(state, "Attempted to call a latent function outside a script callback");

		// destroy remnants from a previous latent function call
		if (callback->m_Fiber)
		{
			DeleteFiber(callback->m_Fiber);
			callback->m_Fiber = nullptr;
		}

		callback->m_Fiber = CreateFiber(0, &LatentFiber, callback); // TODO: maybe create a latent function fiber pool?
		callback->m_ParentFiber = GetCurrentFiber(); // the scripting system has already turned the main thread into a fiber
		callback->m_LatentTarget = func;
		callback->m_CoroState = state;
		callback->m_LastReturnValue = -1;

		SwitchToFiber(callback->m_Fiber); // switch to the new fiber
		// we'll be back eventually

		return script.GetRunningCallback()->m_LastReturnValue;
	}
}