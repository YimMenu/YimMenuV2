#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "NativeDefs.hpp"
#include "core/util/Joaat.hpp"

namespace YimMenu::Lua
{
	class Natives : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int LoadNatives(lua_State* state)
		{
			auto& script = LuaScript::GetScript(state);

			if (script.AreNativesLoaded())
				luaL_error(state, "Natives have already been loaded");

			for (int i = 0; i < g_NumLuaNativeDefs; i++)
			{
				auto chunk = g_LuaNativeDefs[i];
				if (luaL_dostring(state, chunk) != LUA_OK)
				{
					std::string err_copy = lua_tostring(state, -1);
					lua_pop(state, 1);
					luaL_error(state, "%s", err_copy.c_str());
				}
			}

			script.SetNativesLoaded();
			return 0;
		}

		static int AreNativesLoaded(lua_State* state)
		{
			auto& script = LuaScript::GetScript(state);
			lua_pushboolean(state, script.AreNativesLoaded());
			return 1;
		}

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);
			SetFunction(state, LoadNatives, "load_natives");
			SetFunction(state, AreNativesLoaded, "are_natives_loaded");
			lua_setglobal(state, "natives");
		}
	};

	Natives _Natives;
}