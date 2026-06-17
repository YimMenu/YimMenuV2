#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "types/script/scrVector.hpp"

namespace YimMenu::Lua
{
	class ScriptLocal : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;
		
		static int New(lua_State* state)
		{
			auto script_hash = GetHashArgument(state, 1);
			auto index = luaL_checkinteger(state, 2);

			auto thread = Scripts::FindScriptThread(script_hash);
			if (!thread || !thread->m_Stack)
			{
				lua_pushnil(state);
				return 1;
			}

			CreateObject<YimMenu::ScriptLocal>(state, thread->m_Stack, index);
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

		static int GetInt(lua_State* state)
		{
			auto& local = GetObject<YimMenu::ScriptLocal>(state, 1);
			int value = *local.As<int*>();
			lua_pushinteger(state, value);
			return 1;
		}

		static int GetFloat(lua_State* state)
		{
			auto& local = GetObject<YimMenu::ScriptLocal>(state, 1);
			float value = *local.As<float*>();
			lua_pushnumber(state, value);
			return 1;
		}

		static int GetVector3(lua_State* state)
		{
			auto& local = GetObject<YimMenu::ScriptLocal>(state, 1);
			rage::scrVector value{};
			value = *local.As<rage::scrVector*>();
			CreateObject<rage::fvector3>(state, value);
			return 1;
		}

		static int SetInt(lua_State* state)
		{
			auto& local = GetObject<YimMenu::ScriptLocal>(state, 1);
			*local.As<int*>() = luaL_checkinteger(state, 2);
			return 0;
		}

		static int SetFloat(lua_State* state)
		{
			auto& local = GetObject<YimMenu::ScriptLocal>(state, 1);
			*local.As<float*>() = static_cast<float>(luaL_checknumber(state, 2));
			return 0;
		}

		static int SetVector3(lua_State* state)
		{
			auto& local = GetObject<YimMenu::ScriptLocal>(state, 1);
			auto& vec = GetObject<rage::fvector3>(state, 2);
			auto script_vec = rage::scrVector(vec);
			*local.As<rage::scrVector*>() = script_vec;
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			luaL_newmetatable(state, "ScriptLocal");
			{
				lua_newtable(state);
				{
					SetFunction(state, At, "at");
					SetFunction(state, GetInt, "get_int");
					SetFunction(state, GetFloat, "get_float");
					SetFunction(state, GetVector3, "get_vector3");
					SetFunction(state, SetInt, "set_int");
					SetFunction(state, SetFloat, "set_float");
					SetFunction(state, SetVector3, "set_vector3");
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