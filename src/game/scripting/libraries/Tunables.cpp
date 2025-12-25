#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "game/backend/Tunables.hpp"

namespace YimMenu::Lua
{
	class Tunables : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int SetInt(lua_State* state)
		{
			Tunable tune(GetHashArgument(state, 1));
			if (tune.IsReady())
				tune.Set<int>(luaL_checkinteger(state, 2));
			return 0;
		}

		static int SetBool(lua_State* state)
		{
			Tunable tune(GetHashArgument(state, 1));
			if (tune.IsReady())
				tune.Set<BOOL>(CheckBooleanSafe(state, 2));
			return 0;
		}

		static int SetFloat(lua_State* state)
		{
			Tunable tune(GetHashArgument(state, 1));
			if (tune.IsReady())
				tune.Set<float>(luaL_checknumber(state, 2));
			return 0;
		}

		static int GetInt(lua_State* state)
		{
			int value = 0;
			Tunable tune(GetHashArgument(state, 1));
			if (tune.IsReady())
				value = tune.Get<int>();
			lua_pushinteger(state, value);
			return 1;
		}

		static int GetBool(lua_State* state)
		{
			bool value = 0;
			Tunable tune(GetHashArgument(state, 1));
			if (tune.IsReady())
				value = tune.Get<bool>();
			lua_pushboolean(state, value);
			return 1;
		}

		static int GetFloat(lua_State* state)
		{
			float value = 0;
			Tunable tune(GetHashArgument(state, 1));
			if (tune.IsReady())
				value = tune.Get<float>();
			lua_pushnumber(state, value);
			return 1;
		}

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);
			SetFunction(state, SetInt, "set_int");
			SetFunction(state, SetBool, "set_bool");
			SetFunction(state, SetFloat, "set_float");
			SetFunction(state, GetInt, "get_int");
			SetFunction(state, GetBool, "get_bool");
			SetFunction(state, GetFloat, "get_float");
			lua_setglobal(state, "tunables");
		}
	};

	Tunables _Tunables;
}