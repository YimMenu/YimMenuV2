#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/frontend/Notifications.hpp"

namespace YimMenu::Lua
{
	class Notify : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int Success(lua_State* state)
		{
			auto title = CheckStringSafe(state, 1);
			auto message = CheckStringSafe(state, 2);
			Notifications::Show(title, message, NotificationType::Success);
			return 0;
		}

		static int Info(lua_State* state)
		{
			auto title = CheckStringSafe(state, 1);
			auto message = CheckStringSafe(state, 2);
			Notifications::Show(title, message, NotificationType::Info);
			return 0;
		}

		static int Warn(lua_State* state)
		{
			auto title = CheckStringSafe(state, 1);
			auto message = CheckStringSafe(state, 2);
			Notifications::Show(title, message, NotificationType::Warning);
			return 0;
		}

		static int Error(lua_State* state)
		{
			auto title = CheckStringSafe(state, 1);
			auto message = CheckStringSafe(state, 2);
			Notifications::Show(title, message, NotificationType::Error);
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);
			SetFunction(state, Success, "success");
			SetFunction(state, Info, "info");
			SetFunction(state, Warn, "warn");
			SetFunction(state, Error, "error");
			lua_setglobal(state, "notify");
		}
	};

	Notify _Notify;
}