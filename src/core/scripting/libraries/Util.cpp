#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/util/Joaat.hpp"

#include "game/pointers/Pointers.hpp"

#include <chrono>

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

		static int Time(lua_State* state)
		{
			auto now = std::chrono::system_clock::now();
			auto duration = now.time_since_epoch();
			auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

			lua_pushinteger(state, milliseconds);

			return 1;
		}

		static int GetGameVersion(lua_State* state)
		{
			lua_pushstring(state, Pointers.OnlineVersion);
			lua_pushstring(state, Pointers.GameVersion);
			return 2;
		}

		virtual void Register(lua_State* state) override	
		{
			lua_newtable(state);
			SetFunction(state, Joaat, "joaat");
			SetFunction(state, Time, "time");
			SetFunction(state, GetGameVersion, "get_game_version");
			lua_setglobal(state, "util");
		}
	};

	Util _Util;
}
