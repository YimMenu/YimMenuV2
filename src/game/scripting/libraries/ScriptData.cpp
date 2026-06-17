#include "core/memory/Pattern.hpp"
#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "game/gta/ScriptData.hpp"
#include "game/gta/Scripts.hpp"
#include "types/script/scrProgram.hpp"

namespace YimMenu::Lua
{
	class ScriptDataBinding : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int New(lua_State* state)
		{
			auto hash = GetHashArgument(state, 1);
			auto* program = Scripts::FindScriptProgram(hash);
			if (!program)
			{
				lua_pushnil(state);
				return 1;
			}

			CreateObject<ScriptData>(state, program);
			return 1;
		}

		static int GetSize(lua_State* state)
		{
			auto& self = GetObject<ScriptData>(state, 1);
			lua_pushinteger(state, self.GetSize());
			return 1;
		}

		static int GetName(lua_State* state)
		{
			auto& self      = GetObject<ScriptData>(state, 1);
			const char* nm  = self.GetName();
			if (nm)
				lua_pushstring(state, nm);
			else
				lua_pushnil(state);
			return 1;
		}

		static int GetCodeLocation(lua_State* state)
		{
			auto& self = GetObject<ScriptData>(state, 1);
			int   idx  = static_cast<int>(luaL_checkinteger(state, 2));
			auto* byte = ScriptData::GetCodeLocation(&self, idx);
			lua_pushinteger(state, reinterpret_cast<std::uintptr_t>(byte));
			return 1;
		}
		
		static int FindPattern(lua_State* state)
		{
			auto& self = GetObject<ScriptData>(state, 1);
			auto  sig  = CheckStringSafe(state, 2);
			auto  loc  = ScriptData::GetCodeLocationByPattern(&self, SimplePattern(sig));
			if (!loc.has_value())
			{
				lua_pushnil(state);
				return 1;
			}
			lua_pushinteger(state, loc.value());
			return 1;
		}

		static int GC(lua_State* state)
		{
			auto& self = GetObject<ScriptData>(state, 1);
			self.~ScriptData();
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			luaL_newmetatable(state, "ScriptData");
			{
				SetFunction(state, GC, "__gc");

				lua_newtable(state);
				{
					SetFunction(state, GetSize, "get_size");
					SetFunction(state, GetName, "get_name");
					SetFunction(state, GetCodeLocation, "get_code_location");
					SetFunction(state, FindPattern, "find_pattern");
				}
				lua_setfield(state, -2, "__index");
			}
			Metatable<ScriptData>::Register(state);

			lua_newtable(state);
			SetConstructor<New>(state);
			lua_setglobal(state, "ScriptData");
		}
	};

	ScriptDataBinding _ScriptDataBinding;
}
