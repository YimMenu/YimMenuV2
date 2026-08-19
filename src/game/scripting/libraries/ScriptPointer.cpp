#include "core/memory/Pattern.hpp"
#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "game/gta/ScriptPointer.hpp"
#include "game/gta/Scripts.hpp"
#include "types/script/scrProgram.hpp"

namespace YimMenu::Lua
{
	class ScriptPointerBinding : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int New(lua_State* state)
		{
			auto name    = CheckStringSafe(state, 1);
			auto pattern = CheckStringSafe(state, 2);
			auto offset  = static_cast<std::int32_t>(luaL_optinteger(state, 3, 0));
			bool rip     = lua_isnoneornil(state, 4) ? false : lua_toboolean(state, 4);
			auto address = static_cast<std::uint32_t>(luaL_optinteger(state, 5, 0));

			CreateObject<ScriptPointer>(state, std::string(name), SimplePattern(pattern), offset, rip, address);
			return 1;
		}

		static int Add(lua_State* state)
		{
			auto& self = GetObject<ScriptPointer>(state, 1);
			auto offset = static_cast<std::uint32_t>(luaL_checkinteger(state, 2));
			PushObject<ScriptPointer>(state, self.Add(offset));
			return 1;
		}

		static int Sub(lua_State* state)
		{
			auto& self = GetObject<ScriptPointer>(state, 1);
			auto offset = static_cast<std::uint32_t>(luaL_checkinteger(state, 2));
			PushObject<ScriptPointer>(state, self.Sub(offset));
			return 1;
		}

		static int Rip(lua_State* state)
		{
			auto& self = GetObject<ScriptPointer>(state, 1);
			PushObject<ScriptPointer>(state, self.Rip());
			return 1;
		}
		
		static int Scan(lua_State* state)
		{
			auto& self = GetObject<ScriptPointer>(state, 1);
			auto hash = GetHashArgument(state, 2);
			auto* program = Scripts::FindScriptProgram(hash);
			
			if (!program)
			{
				lua_pushnil(state);
				return 1;
			}

			PushObject<ScriptPointer>(state, self.Scan(program));
			return 1;
		}

		static int GetAddress(lua_State* state)
		{
			auto& self = GetObject<ScriptPointer>(state, 1);
			lua_pushinteger(state, self.As<std::uint32_t>());
			return 1;
		}

		static int GetName(lua_State* state)
		{
			auto& self = GetObject<ScriptPointer>(state, 1);
			auto name  = self.GetName();
			lua_pushlstring(state, name.data(), name.size());
			return 1;
		}

		static int GC(lua_State* state)
		{
			auto& self = GetObject<ScriptPointer>(state, 1);
			self.~ScriptPointer();
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			luaL_newmetatable(state, "ScriptPointer");
			{
				SetFunction(state, GC, "__gc");

				lua_newtable(state);
				{
					SetFunction(state, Add, "add");
					SetFunction(state, Sub, "sub");
					SetFunction(state, Rip, "rip");
					SetFunction(state, Scan, "scan");
					SetFunction(state, GetAddress, "get_address");
					SetFunction(state, GetName, "get_name");
				}
				lua_setfield(state, -2, "__index");
			}
			Metatable<ScriptPointer>::Register(state);

			lua_newtable(state);
			SetConstructor<New>(state);
			lua_setglobal(state, "ScriptPointer");
		}
	};

	ScriptPointerBinding _ScriptPointerBinding;
}
