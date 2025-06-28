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

		virtual void Register(lua_State* state) override
		{
			luaL_newmetatable(state, "Vector3");
			{
				lua_newtable(state);
				{
					// TODO?
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