#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "game/gta/Natives.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Lua
{
	class Network : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		// trigger_script_event(2000, -1, "if", 2, 2.5)
		static int TriggerScriptEvent(lua_State* state)
		{
			auto hash = GetHashArgument(state, 1);
			int bits = luaL_checkinteger(state, 2);
			size_t param_length;
			auto param_str = CheckStringSafe(state, 3, &param_length);
			int64_t tse_args[40];
			tse_args[0] = hash;
			tse_args[1] = Self::GetPlayer().GetId();
			tse_args[2] = bits;

			if (param_length >= 37)
				luaL_error(state, "too many arguments");

			for (int i = 0; i < param_length; i++)
			{
				switch (param_str[i])
				{
				case 'i': // integer
				{
					int as_int = luaL_checkinteger(state, 4 + i);
					tse_args[3 + i] = *(int64_t*)&as_int;
					break;
				}
				case 'f': // float
				{
					float as_float = luaL_checknumber(state, 4 + i); 
					tse_args[3 + i] = *(int64_t*)&as_float;
					break;
				}
				case 'l': // long
				{
					tse_args[3 + i] = luaL_checkinteger(state, 4 + i);
					break;
				}
				case 'h': // hash
				{
					std::uint32_t as_uint = GetHashArgument(state, 4 + i);
					tse_args[3 + i] = *(int64_t*)&as_uint;
					break;
				}
				default:
				{
					luaL_error(state, "unknown format specifier: '%c'", param_str[i]);
				}
				// TODO: add text label stuff 
				}
			}

			SCRIPT::_SEND_TU_SCRIPT_EVENT_NEW(1, tse_args, 3 + param_length, bits, hash);
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);
			SetFunction(state, TriggerScriptEvent, "trigger_script_event");
			lua_setglobal(state, "network");
		}
	};

	Network _Network;
}