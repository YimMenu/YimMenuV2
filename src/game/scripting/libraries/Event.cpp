#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/util/Joaat.hpp"

namespace YimMenu::Lua
{
	class Event : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int RegisterEventHandler(lua_State* state)
		{
			auto event_name = (MenuEvent)luaL_checkinteger(state, 1);
			luaL_checktype(state, 2, LUA_TFUNCTION);      
			lua_pushvalue(state, 2);                    
			int handler = luaL_ref(state, LUA_REGISTRYINDEX); 

			LuaScript::GetScript(state).AddEventHandler(event_name, handler);
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);
			SetFunction(state, RegisterEventHandler, "register_handler");
			lua_setglobal(state, "event");

            static const EnumEntry menu_events[] = {
				{"PlayerLeave", static_cast<int>(MenuEvent::PlayerLeave)},
				{"PlayerJoin", static_cast<int>(MenuEvent::PlayerJoin)},
				{"ScriptedGameEventReceived", static_cast<int>(MenuEvent::ScriptedGameEventReceived)},
				{"ChatMessageReceived", static_cast<int>(MenuEvent::ChatMessageReceived)},
				{"Unload", static_cast<int>(MenuEvent::Unload)},
			};
			RegisterEnum(state, "menu_event", menu_events, std::size(menu_events));
		}
	};

	Event _Event;
}