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

		static int IsZero(lua_State* state)
		{
			auto& v = GetObject<rage::fvector3>(state, 1);
			lua_pushboolean(state, v.x == 0.0f && v.y == 0.0f && v.z == 0.0f);
			return 1;
		}

		//having to write :get_x() instead of .x is a bit annoying, so we can use __index and __newindex to allow for that
		static int Index(lua_State* state)
		{
			if (lua_type(state, 2) == LUA_TSTRING)
			{
				std::size_t len = 0;
				const char* key = lua_tolstring(state, 2, &len);
				if (len == 1)
				{
					auto& v = GetObject<rage::fvector3>(state, 1);
					switch (key[0])
					{
					case 'x': lua_pushnumber(state, v.x); return 1;
					case 'y': lua_pushnumber(state, v.y); return 1;
					case 'z': lua_pushnumber(state, v.z); return 1;
					}
				}
			}

			lua_pushvalue(state, 2);
			lua_rawget(state, lua_upvalueindex(1));
			return 1;
		}

		static int NewIndex(lua_State* state)
		{
			if (lua_type(state, 2) == LUA_TSTRING)
			{
				std::size_t len = 0;
				const char* key = lua_tolstring(state, 2, &len);
				if (len == 1)
				{
					auto& v = GetObject<rage::fvector3>(state, 1);
					switch (key[0])
					{
					case 'x': v.x = static_cast<float>(luaL_checknumber(state, 3)); return 0;
					case 'y': v.y = static_cast<float>(luaL_checknumber(state, 3)); return 0;
					case 'z': v.z = static_cast<float>(luaL_checknumber(state, 3)); return 0;
					}
				}
			}

			if (lua_type(state, 2) == LUA_TSTRING)
				return luaL_error(state, "cannot assign field '%s' on Vector3 (only x/y/z)", lua_tostring(state, 2));
			return luaL_error(state, "cannot assign %s key on Vector3 (only x/y/z)", luaL_typename(state, 2));
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
					SetFunction(state, GetDistance, "get_distance");
					SetFunction(state, IsZero, "is_zero");
				}
				lua_pushcclosure(state, Index, 1);
				lua_setfield(state, -2, "__index");

				SetFunction(state, NewIndex, "__newindex");
			}
			Metatable<rage::fvector3>::Register(state);

			lua_newtable(state);
			SetConstructor<New>(state);
			lua_setglobal(state, "Vector3");
		}
	};

	Vector3 _Vector3;
}