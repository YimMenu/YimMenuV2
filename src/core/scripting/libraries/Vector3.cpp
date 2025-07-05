#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "types/rage/vector.hpp"

namespace YimMenu::Lua
{
	class Vector3 : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int New(lua_State* state)
		{
			auto args = lua_gettop(state);
			if (args == 0)
				CreateObject<rage::fvector3>(state);
			else if (args == 3)
				CreateObject<rage::fvector3>(state, luaL_checknumber(state, 1), luaL_checknumber(state, 2), luaL_checknumber(state, 3));
			else
				luaL_error(state, "Invalid amount of arguments passed to Vector3::New");
			return 1;
		}

		// returns three values
		static int GetCoords(lua_State* state)
		{
			lua_pushnumber(state, GetObject<rage::fvector3>(state, 1).x);
			lua_pushnumber(state, GetObject<rage::fvector3>(state, 1).y);
			lua_pushnumber(state, GetObject<rage::fvector3>(state, 1).z);
			return 3;
		}

		static int GetX(lua_State* state)
		{
			lua_pushnumber(state, GetObject<rage::fvector3>(state, 1).x);
			return 1;
		}

		static int GetY(lua_State* state)
		{
			lua_pushnumber(state, GetObject<rage::fvector3>(state, 1).y);
			return 1;
		}

		static int GetZ(lua_State* state)
		{
			lua_pushnumber(state, GetObject<rage::fvector3>(state, 1).z);
			return 1;
		}

		static int SetX(lua_State* state)
		{
			GetObject<rage::fvector3>(state, 1).x = luaL_checknumber(state, 2);
			return 1;
		}

		static int SetY(lua_State* state)
		{
			GetObject<rage::fvector3>(state, 1).y = luaL_checknumber(state, 2);
			return 1;
		}

		static int SetZ(lua_State* state)
		{
			GetObject<rage::fvector3>(state, 1).z = luaL_checknumber(state, 2);
			return 1;
		}

		static int GetDistance(lua_State* state)
		{
			lua_pushnumber(state, GetObject<rage::fvector3>(state, 1).GetDistance(GetObject<rage::fvector3>(state, 2)));
			return 1;
		}

		virtual void Register(lua_State* state) override
		{
			luaL_newmetatable(state, "Vector3");
			{
				lua_newtable(state);
				{
					SetFunction(state, GetCoords, "get_coords");
					SetFunction(state, GetX, "get_x");
					SetFunction(state, GetY, "get_y");
					SetFunction(state, GetZ, "get_z");
					SetFunction(state, SetX, "set_x");
					SetFunction(state, SetY, "set_y");
					SetFunction(state, SetZ, "set_z");
					SetFunction(state, SetZ, "set_z");
					SetFunction(state, GetDistance, "get_distance");
				}
				lua_setfield(state, -2, "__index"); // prototype
			}
			Metatable<rage::fvector3>::Register(state);

			lua_newtable(state);
			SetConstructor<New>(state);
			lua_setglobal(state, "Vector3");
		}
	};

	Vector3 _Vector3;
}