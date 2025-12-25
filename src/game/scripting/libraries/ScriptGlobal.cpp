#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "game/gta/ScriptGlobal.hpp"

namespace YimMenu::Lua
{
	// TODO: we need to automate this
	class ScriptGlobal : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int New(lua_State* state)
		{
			CreateObject<YimMenu::ScriptGlobal>(state, luaL_checkinteger(state, 1));
			return 1;
		}

		static int At(lua_State* state)
		{
			auto num_args = lua_gettop(state) - 1; // first argument is self
			auto& global = GetObject<YimMenu::ScriptGlobal>(state, 1);

			auto size = num_args > 1 ? luaL_checkinteger(state, 3) : 0;
			if (size != 0)
				CopyObject<YimMenu::ScriptGlobal>(state, global.At(luaL_checkinteger(state, 2), size));
			else
				CopyObject<YimMenu::ScriptGlobal>(state, global.At(luaL_checkinteger(state, 2)));
	
			return 1;
		}

		static int CanAccess(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::ScriptGlobal>(state, 1).CanAccess());
			return 1;
		}

		static int GetInt(lua_State* state)
		{
			auto& global = GetObject<YimMenu::ScriptGlobal>(state, 1);
			int value = 0;
			if (global.CanAccess())
				value = *global.As<int*>();
			lua_pushinteger(state, value);
			return 1;
		}

		static int GetFloat(lua_State* state)
		{
			auto& global = GetObject<YimMenu::ScriptGlobal>(state, 1);
			float value = 0;
			if (global.CanAccess())
				value = *global.As<float*>();
			lua_pushnumber(state, value);
			return 1;
		}

		static int SetInt(lua_State* state)
		{
			auto& global = GetObject<YimMenu::ScriptGlobal>(state, 1);
			if (global.CanAccess())
				*global.As<int*>() = luaL_checkinteger(state, 2);
			return 0;
		}

		static int SetFloat(lua_State* state)
		{
			auto& global = GetObject<YimMenu::ScriptGlobal>(state, 1);
			if (global.CanAccess())
				*global.As<float*>() = static_cast<float>(luaL_checknumber(state, 2));
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			luaL_newmetatable(state, "ScriptGlobal");
			{
				lua_newtable(state);
				{
					SetFunction(state, At, "at");
					SetFunction(state, CanAccess, "can_access");
					SetFunction(state, GetInt, "get_int");
					SetFunction(state, GetFloat, "get_float");
					SetFunction(state, SetInt, "set_int");
					SetFunction(state, SetFloat, "set_float");
				}
				lua_setfield(state, -2, "__index"); // prototype
			}
			Metatable<YimMenu::ScriptGlobal>::Register(state);

			lua_newtable(state);
			SetConstructor<New>(state);
			lua_setglobal(state, "ScriptGlobal");
		}
	};

	ScriptGlobal _ScriptGlobal;
}