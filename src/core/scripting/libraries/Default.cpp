#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaRequire.hpp"

namespace YimMenu::Lua
{
	class Default : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int UnsupportedOsFunction(lua_State* state)
		{
			return luaL_error(state, "os.%s is not supported", lua_tostring(state, lua_upvalueindex(1)));
		}

		static int OsFileOperation(lua_State* state)
		{
			return luaL_error(state, "os.%s: use FileMgr for file operations", lua_tostring(state, lua_upvalueindex(1)));
		}

		static void SandboxOs(lua_State* state)
		{
			lua_getglobal(state, LUA_OSLIBNAME);
			for (const auto name : std::to_array({"execute", "exit", "getenv", "setlocale", "tmpname"}))
			{
				lua_pushstring(state, name);
				lua_pushcclosure(state, UnsupportedOsFunction, 1);
				lua_setfield(state, -2, name);
			}
			for (const auto name : std::to_array({"rename", "remove"}))
			{
				lua_pushstring(state, name);
				lua_pushcclosure(state, OsFileOperation, 1);
				lua_setfield(state, -2, name);
			}

			lua_getglobal(state, LUA_LOADLIBNAME);
			lua_getfield(state, -1, "loaded");
			lua_pushvalue(state, -3);
			lua_setfield(state, -2, LUA_OSLIBNAME);
			lua_pop(state, 3);
		}

		virtual void Register(lua_State* state) override
		{
			// ensure that only safe libraries are loaded
			static constexpr auto libraries = std::to_array<luaL_Reg>({
			    {"", luaopen_base},
			    {LUA_LOADLIBNAME, luaopen_package},
			    {LUA_TABLIBNAME, luaopen_table},
			    {LUA_STRLIBNAME, luaopen_string},
			    {LUA_MATHLIBNAME, luaopen_math},
			    {LUA_OSLIBNAME, luaopen_os},
			    {LUA_DBLIBNAME, luaopen_debug},
			    {LUA_BITLIBNAME, luaopen_bit},
			    {LUA_JITLIBNAME, luaopen_jit},
			});
			for (const auto& library : libraries)
			{
				lua_pushcfunction(state, library.func);
				lua_pushstring(state, library.name);
				lua_call(state, 1, 0);
			}
			RegisterRequire(state);
			SandboxOs(state);
		}
	};

	Default _Default;
}
