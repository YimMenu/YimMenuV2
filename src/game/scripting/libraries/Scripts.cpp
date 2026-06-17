#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "game/gta/Scripts.hpp"

namespace YimMenu::Lua
{
	class Scripts : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

        static int IsActive(lua_State* state)
        {
            lua_pushboolean(state, YimMenu::Scripts::IsScriptActive(GetHashArgument(state, 1)));
            return 1;
        }

        static int RunAsScript(lua_State* state)
        {
            auto script_hash = GetHashArgument(state, 1);
            luaL_checktype(state, 2, LUA_TFUNCTION);

            auto thread = YimMenu::Scripts::FindScriptThread(script_hash);
            if (!thread)
                return 0;

            lua_pushvalue(state, 2);
            
            YimMenu::Scripts::RunAsScript(thread, [state] {
                auto& script = LuaScript::GetScript(state);
                script.CallFunction(0, 0, state);
            });

			return 0;
        }

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);
			SetFunction(state, IsActive, "is_active");
			SetFunction(state, RunAsScript, "run_as_script");
			lua_setglobal(state, "scripts");
		}
	};

	Scripts _Scripts;
}