#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"

namespace YimMenu::Lua
{
	class Default : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		virtual void Register(lua_State* state) override
		{
			// ensure that only safe libraries are loaded
			static const luaL_Reg lj_lib_load[] = {
			    {"", luaopen_base},
		  //    {LUA_LOADLIBNAME, luaopen_package},
			    {LUA_TABLIBNAME, luaopen_table},
		  //    {LUA_IOLIBNAME, luaopen_io},
	      //    {LUA_OSLIBNAME, luaopen_os},
			    {LUA_STRLIBNAME, luaopen_string},
			    {LUA_MATHLIBNAME, luaopen_math},
			    {LUA_DBLIBNAME, luaopen_debug},
			    {LUA_BITLIBNAME, luaopen_bit},
			    {LUA_JITLIBNAME, luaopen_jit},
			    {NULL, NULL}};

			static const luaL_Reg lj_lib_preload[] = {
		//	    {LUA_FFILIBNAME, luaopen_ffi},
			    {NULL, NULL}};


			const luaL_Reg* lib;
			for (lib = lj_lib_load; lib->func; lib++)
			{
				lua_pushcfunction(state, lib->func);
				lua_pushstring(state, lib->name);
				lua_call(state, 1, 0);
			}
			luaL_findtable(state, LUA_REGISTRYINDEX, "_PRELOAD", sizeof(lj_lib_preload) / sizeof(lj_lib_preload[0]) - 1);
			for (lib = lj_lib_preload; lib->func; lib++)
			{
				lua_pushcfunction(state, lib->func);
				lua_setfield(state, -2, lib->name);
			}
			lua_pop(state, 1);
		}
	};

	Default _Default;
}