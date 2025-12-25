#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/util/Joaat.hpp"

namespace YimMenu::Lua
{
	static bool IsCoroutine(lua_State* state)
	{
		bool result = lua_pushthread(state);
		lua_pop(state, 1); 
		return !result; // this is dumb af. Why do you need to push a value to the stack to figure out if you're in the main thread?
	}

	class Script : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int RunInCallback(lua_State* state)
		{
			auto& script = LuaScript::GetScript(state);

			luaL_checktype(state, 1, LUA_TFUNCTION); // will throw error if a1 isn't a function. not sure what happens if you don't pass any parameters

			auto func_handle = luaL_ref(state, LUA_REGISTRYINDEX);
			script.AddScriptCallback(func_handle);
			luaL_unref(state, LUA_REGISTRYINDEX, func_handle);

			return 0;
		}

		static int Yield(lua_State* state)
		{
			auto& script = LuaScript::GetScript(state);

			if (!IsCoroutine(state))
			{
				luaL_error(state, "Attempting to yield outside a script callback");
			}

			auto time = lua_gettop(state) >= 1 ? (int)luaL_checkinteger(state, 1) : 0;
			script.Yield(state, time, false);
			return -1;
		}

		static int IsInsideCallback(lua_State* state)
		{
			lua_pushboolean(state, IsCoroutine(state));
			return 1;
		}

		static int RegisterEventHandler(lua_State* state)
		{
			auto event_name = GetHashArgument(state, 1);
			luaL_checktype(state, 2, LUA_TFUNCTION);      
			lua_pushvalue(state, 2);                    
			int handler = luaL_ref(state, LUA_REGISTRYINDEX); 

			LuaScript::GetScript(state).AddEventHandler(event_name, handler);
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);
			SetFunction(state, RunInCallback, "run_in_callback");
			SetFunction(state, Yield, "yield");
			SetFunction(state, IsInsideCallback, "is_inside_callback");
			SetFunction(state, RegisterEventHandler, "register_event_handler");
			lua_setglobal(state, "script");
		}
	};

	Script _Script;
}