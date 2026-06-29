#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "game/gta/Pools.hpp"

namespace YimMenu::Lua
{
	class Entities : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		template<typename PoolView>
		static int PushHandlesFromPool(lua_State* state, PoolView pool)
		{
			lua_newtable(state);
			int idx = 1;
			for (auto entity : pool)
			{
				if (!entity)
					continue;
				lua_pushinteger(state, entity.GetHandle());
				lua_rawseti(state, -2, idx++);
			}
			return 1;
		}
		
		static int GetAllVehiclesAsHandles(lua_State* state)
		{
			if (!GetVehiclePool())
			{
				lua_newtable(state);
				return 1;
			}
			return PushHandlesFromPool(state, Pools::GetVehicles());
		}

		static int GetAllPedsAsHandles(lua_State* state)
		{
			if (!GetPedPool())
			{
				lua_newtable(state);
				return 1;
			}
			return PushHandlesFromPool(state, Pools::GetPeds());
		}

		static int GetAllObjectsAsHandles(lua_State* state)
		{
			if (!GetObjectPool())
			{
				lua_newtable(state);
				return 1;
			}
			return PushHandlesFromPool(state, Pools::GetObjects());
		}

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);
			SetFunction(state, GetAllVehiclesAsHandles, "get_all_vehicles_as_handles");
			SetFunction(state, GetAllPedsAsHandles, "get_all_peds_as_handles");
			SetFunction(state, GetAllObjectsAsHandles, "get_all_objects_as_handles");
			lua_setglobal(state, "entities");
		}
	};

	Entities _Entities;
}
