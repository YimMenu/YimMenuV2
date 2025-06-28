#pragma once
#include "lua.hpp"

namespace YimMenu
{
	class LuaLibrary
	{
	public:
		LuaLibrary();

		virtual void Register(lua_State* state) = 0;
	};
}