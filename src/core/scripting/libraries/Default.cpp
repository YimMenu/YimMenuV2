#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaRequire.hpp"

namespace YimMenu::Lua
{
	class Default : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		virtual void Register(lua_State* state) override
		{
			// ensure that only safe libraries are loaded
			static constexpr auto libraries = std::to_array<luaL_Reg>({
			    {"", luaopen_base},
			    {LUA_LOADLIBNAME, luaopen_package},
			    {LUA_TABLIBNAME, luaopen_table},
			    {LUA_STRLIBNAME, luaopen_string},
			    {LUA_MATHLIBNAME, luaopen_math},
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
		}
	};

	Default _Default;
}
