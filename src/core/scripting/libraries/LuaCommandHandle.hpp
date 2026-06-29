#pragma once

#include "core/util/Joaat.hpp"
#include "lua.hpp"

namespace YimMenu::Lua
{
	struct LuaCommandHandle
	{
		enum class Kind
		{
			OneShot,
			Bool, // also used for LoopedCommand (same item, same value type)
			Int,
			Float,
			List,
		};

		joaat_t hash;
		Kind    kind;
	};

	int PushCommandHandle(lua_State* state, joaat_t hash, LuaCommandHandle::Kind kind);
}
