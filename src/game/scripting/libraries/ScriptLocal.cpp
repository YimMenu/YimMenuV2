#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/gta/Scripts.hpp"
#include "core/util/Joaat.hpp"

namespace YimMenu::Lua
{
	// TODO: we need to automate this
	class ScriptLocal : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int New(lua_State* state)
		{
			// ScriptLocal.new(script_name_or_hash, local_index)
			// script_name_or_hash can be a string (script name) or integer (script hash)
			// local_index is the local variable index in the script
			auto script_hash = GetHashArgument(state, 1);
			auto local_index = luaL_checkinteger(state, 2);

			// Find the script thread
			auto thread = Scripts::FindScriptThread(script_hash);
			if (!thread)
			{
				luaL_error(state, "Script with hash 0x%X not found or not running", script_hash);
				return 0;
			}

			// Create ScriptLocal with thread and local index
			CreateObject<YimMenu::ScriptLocal>(state, thread, static_cast<std::size_t>(local_index));
			return 1;
		}

		static int At(lua_State* state)
		{
			auto num_args = lua_gettop(state) - 1; // first argument is self
			auto& local = GetObject<YimMenu::ScriptLocal>(state, 1);

			auto size = num_args > 1 ? luaL_checkinteger(state, 3) : 0;
			if (size != 0)
				CopyObject<YimMenu::ScriptLocal>(state, local.At(luaL_checkinteger(state, 2), size));
			else
				CopyObject<YimMenu::ScriptLocal>(state, local.At(luaL_checkinteger(state, 2)));

			return 1;
		}

		static int CanAccess(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::ScriptLocal>(state, 1).CanAccess());
			return 1;
		}

		static int GetInt(lua_State* state)
		{
			auto& local = GetObject<YimMenu::ScriptLocal>(state, 1);
			int value = 0;
			if (local.CanAccess())
				value = *local.As<int*>();
			lua_pushinteger(state, value);
			return 1;
		}

		static int GetFloat(lua_State* state)
		{
			auto& local = GetObject<YimMenu::ScriptLocal>(state, 1);
			float value = 0;
			if (local.CanAccess())
				value = *local.As<float*>();
			lua_pushnumber(state, value);
			return 1;
		}

		static int SetInt(lua_State* state)
		{
			auto& local = GetObject<YimMenu::ScriptLocal>(state, 1);
			if (local.CanAccess())
				*local.As<int*>() = luaL_checkinteger(state, 2);
			return 0;
		}

		static int SetFloat(lua_State* state)
		{
			auto& local = GetObject<YimMenu::ScriptLocal>(state, 1);
			if (local.CanAccess())
				*local.As<float*>() = static_cast<float>(luaL_checknumber(state, 2));
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			luaL_newmetatable(state, "ScriptLocal");
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
			Metatable<YimMenu::ScriptLocal>::Register(state);

			lua_newtable(state);
			SetConstructor<New>(state);
			lua_setglobal(state, "ScriptLocal");
		}
	};

	ScriptLocal _ScriptLocal;
}

