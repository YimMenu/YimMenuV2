#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LatentFunction.hpp"
#include "game/gta/Vehicle.hpp"
#include "game/backend/Self.hpp"
#include "core/util/Joaat.hpp"

namespace YimMenu::Lua
{
	// only use for internal testing
	class Internal : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int SpawnVehicle(lua_State* state)
		{
			const char* model = luaL_checkstring(state, 1);
			Vehicle::Create(Joaat(model), Self::GetPed().GetPosition());
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);

			lua_pushcfunction(state, LatentFunction<SpawnVehicle>);
			lua_setfield(state, -2, "spawn_vehicle");

			lua_setglobal(state, "internal");
		}
	};

	Internal _Internal;
}