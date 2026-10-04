#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Network.hpp"
#include "game/gta/Scripts.hpp"

namespace YimMenu::Lua
{
	class LuaNetwork : LuaLibrary
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

		static int ForceScriptHost(lua_State* state)
        {
            auto script_hash = GetHashArgument(state, 1);

            auto thread = YimMenu::Scripts::FindScriptThread(script_hash);
            if (!thread)
                return 0;

            YimMenu::Scripts::ForceScriptHost(thread);

			return 0;
        }

		static int ForceScriptOnPlayer(lua_State* state)
		{
			auto script_hash = GetHashArgument(state, 1);
			auto bits = luaL_checkinteger(state, 2);

			YimMenu::Scripts::ForceScriptOnPlayer(script_hash, bits);

			return 0;
		}

		static int IsSessionStarted(lua_State* state)
		{
			lua_pushboolean(state, *Pointers.IsSessionStarted);
			return 1;
		}

		static int JoinSession(lua_State* state)
		{
			auto session_type = (Network::JoinType)luaL_checkinteger(state, 1);

			Network::LaunchJoinType(session_type);
			
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);
			SetFunction(state, TriggerScriptEvent, "trigger_script_event");
			SetFunction(state, ForceScriptHost, "force_script_host");
			SetFunction(state, ForceScriptOnPlayer, "force_script_on_player");
			SetFunction(state, IsSessionStarted, "is_session_started");
			SetFunction(state, JoinSession, "join_session");
			lua_setglobal(state, "network");

			static constexpr auto session_types = std::to_array<EnumEntry>({
				{"public", static_cast<int>(Network::JoinType::JOIN_PUBLIC)},
				{"solo_public", static_cast<int>(Network::JoinType::NEW_PUBLIC)},
				{"sctv", static_cast<int>(Network::JoinType::SC_TV)},
				{"crew", static_cast<int>(Network::JoinType::CREW)},
				{"join_crew", static_cast<int>(Network::JoinType::JOIN_CREW)},
				{"closed_crew", static_cast<int>(Network::JoinType::CLOSED_CREW)},
				{"closed_friend", static_cast<int>(Network::JoinType::CLOSED_FRIENDS)},
				{"find_friend", static_cast<int>(Network::JoinType::FIND_FRIEND)},
				{"invite_only", static_cast<int>(Network::JoinType::INVITE_ONLY)},
				{"solo", static_cast<int>(Network::JoinType::SOLO)},
			});
			RegisterEnum(state, "session_types", session_types.data(), session_types.size());
		}
	};

	LuaNetwork _Network;
}