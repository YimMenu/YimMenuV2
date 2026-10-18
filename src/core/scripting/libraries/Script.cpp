#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/util/Joaat.hpp"

#include "game/pointers/Pointers.hpp"

namespace YimMenu::Lua
{
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

			if (!script.IsInsideScriptCallback(state))
			{
				luaL_error(state, "Attempting to yield outside a script callback");
			}

			auto time = lua_gettop(state) >= 1 ? (int)luaL_checkinteger(state, 1) : 0;
			script.Yield(state, time, false);
			return -1;
		}

		static int IsInsideRenderCallback(lua_State* state)
		{
			lua_pushboolean(state, LuaScript::GetScript(state).IsInsideRenderCallback(state));
			return 1;
		}

		static int IsInsideScriptCallback(lua_State* state)
		{
			lua_pushboolean(state, LuaScript::GetScript(state).IsInsideScriptCallback(state));
			return 1;
		}

		static int RequireGameBuild(lua_State* state)
		{
			auto online_ver = CheckStringSafe(state, 1);
			auto game_ver = lua_isnoneornil(state, 2) ? Pointers.GameVersion : CheckStringSafe(state, 2);

			if (strcmp(online_ver, Pointers.OnlineVersion) != 0)
				luaL_error(state, "Incompatible online version! Target version is %s, current version is %s", online_ver, Pointers.OnlineVersion);

			if (strcmp(game_ver, Pointers.GameVersion) != 0)
				luaL_error(state, "Incompatible game build! Target build is %s, current build is %s", game_ver, Pointers.GameVersion);

			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);
			SetFunction(state, RunInCallback, "run_in_callback");
			SetFunction(state, Yield, "yield");
			SetFunction(state, IsInsideRenderCallback, "is_inside_render_callback");
			SetFunction(state, IsInsideScriptCallback, "is_inside_script_callback");
			SetFunction(state, RequireGameBuild, "require_game_build");
			lua_setglobal(state, "script");
		}
	};

	Script _Script;
}
