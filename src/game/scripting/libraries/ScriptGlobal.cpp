#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "types/script/scrVector.hpp"

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

		static int GetString(lua_State* state)
		{
			auto& global = GetObject<YimMenu::ScriptGlobal>(state, 1);
			if (global.CanAccess())
				lua_pushstring(state, global.As<char*>());
			else
				lua_pushnil(state);
			return 1;
		}

		static int GetVector3(lua_State* state)
		{
			auto& global = GetObject<YimMenu::ScriptGlobal>(state, 1);
			rage::scrVector value{};
			if (global.CanAccess())
				value = *global.As<rage::scrVector*>();
			CreateObject<rage::fvector3>(state, value);
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

		static int SetString(lua_State* state)
		{
			auto& global = GetObject<YimMenu::ScriptGlobal>(state, 1);
			if (!global.CanAccess())
				return 0;

			std::size_t len = 0;
			auto str        = CheckStringSafe(state, 2, &len);
			std::size_t cap = lua_isnoneornil(state, 3) ? len + 1 : static_cast<std::size_t>(luaL_checkinteger(state, 3));
			if (cap == 0)
				return 0;

			auto dst        = global.As<char*>();
			std::size_t n   = std::min(len, cap - 1);
			std::memcpy(dst, str, n);
			dst[n] = '\0';
			return 0;
		}

		static int SetVector3(lua_State* state)
		{
			auto& global = GetObject<YimMenu::ScriptGlobal>(state, 1);
			auto& vec = GetObject<rage::fvector3>(state, 2);
			auto script_vec = rage::scrVector(vec);
			if (global.CanAccess())
				*global.As<rage::scrVector*>() = script_vec;
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
					SetFunction(state, GetString, "get_string");
					SetFunction(state, GetVector3, "get_vector3");
					SetFunction(state, SetInt, "set_int");
					SetFunction(state, SetFloat, "set_float");
					SetFunction(state, SetString, "set_string");
					SetFunction(state, SetVector3, "set_vector3");
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