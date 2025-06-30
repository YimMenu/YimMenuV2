#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/util/Joaat.hpp"

namespace YimMenu::Lua
{
	class Util : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int Joaat(lua_State* state)
		{
			const char* string = CheckStringSafe(state, 1);
			lua_pushinteger(state, (int)YimMenu::Joaat(string));
			return 1;
		}

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);
			SetFunction(state, Joaat, "joaat");
			lua_setglobal(state, "util");
		}
	};

	Util _Util;
}