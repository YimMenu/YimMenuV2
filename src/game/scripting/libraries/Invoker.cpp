#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "game/gta/invoker/Invoker.hpp"

namespace YimMenu::Lua
{
	class Invoker : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int GetInteger(lua_State* state, int idx)
		{
			if (lua_type(state, idx) == LUA_TBOOLEAN)
				return static_cast<int>(lua_toboolean(state, idx)); // stand only coerces bools when an option is enabled, but I feel we should do it regardless
			else
				return luaL_checkinteger(state, idx);
		}

		static BOOL GetBoolean(lua_State* state, int idx)
		{
			if (lua_type(state, idx) == LUA_TNUMBER)
				return static_cast<BOOL>(lua_tointeger(state, idx)); // coerce ints
			else if (lua_type(state, idx) == LUA_TBOOLEAN)
				return static_cast<BOOL>(lua_toboolean(state, idx));
			else
				return luaL_argerror(state, idx, "Expected boolean, got something else"); // lua can technically convert anything into a boolean, but it's a good idea to not do that
		}

		static const char* GetString(lua_State* state, int idx)
		{
			if (lua_type(state, idx) == LUA_TNIL || lua_type(state, idx) == LUA_TNONE)
				return nullptr;
			else
				return CheckStringSafe(state, idx);
		}

		// thanks to Stand for the parameter string idea
		// we're assuming that only trusted functions can call this directly (this assumption is incorrect, but would do for now)
		static int InvokeNative(lua_State* state)
		{
			size_t params_len;
			auto index = lua_tointeger(state, 1);
			const char* parameters = lua_tolstring(state, 2, &params_len);
			bool fix_vectors = false;
			NativeInvoker invoker;
			int vector_params = 0;
			rage::fvector3* vectors_to_fix[4];
			char return_type;

			invoker.BeginCall();

			for (int i = 0; i < params_len; i++)
			{
				auto type = parameters[i];
				switch (type)
				{
				case 'i': // integer
					invoker.PushArg<int>(GetInteger(state, 3 + i));
					break;
				case 'f': // float
					invoker.PushArg<float>(luaL_checknumber(state, 3 + i));
					break;
				case 'h': // hash
					invoker.PushArg<std::uint32_t>(GetHashArgument(state, 3 + i));
					break;
				case 'b': // boolean
					invoker.PushArg<std::uint32_t>(GetBoolean(state, 3 + i));
					break;
				case 's': // string
					invoker.PushArg<const char*>(GetString(state, 3 + i));
					break;
				case 'v': // Vector3* (not Vector3)
				{
					fix_vectors = true;
					auto& vec = GetObject<rage::fvector3>(state, 3 + i);
					auto script_vec = rage::scrVector(vec);
					invoker.PushArg<void*>(&script_vec);
					vectors_to_fix[vector_params++] = &vec;
					break;
				}
				case 'p': // Any*
				{
					// idk what to do with this
					luaL_argerror(state, 3 + i, "Pointers are not supported yet");
					break;
				}
				case '=': // done + return
				{
					return_type = parameters[i + 1];
					goto done; // can't break; out of the loop from here
				}
				}
			}
		done:
			invoker.EndCall(index, false);

			if (fix_vectors)
			{
				for (int i = 0; i < vector_params; i++)
				{
					*vectors_to_fix[i] = invoker.m_CallContext.GetSourceVector(i);
				}
			}

			switch (return_type)
			{
			case 'n': // nothing ([v]oid is taken)
				return 0;
			case 'i': // integer
			case 'h': // hash
				lua_pushinteger(state, invoker.GetReturnValue<int>());
				return 1;
			case 'f': // float
				lua_pushnumber(state, invoker.GetReturnValue<float>());
				return 1;
			case 'b': // boolean
				lua_pushboolean(state, invoker.GetReturnValue<bool>());
				return 1;
			case 's': // string
				lua_pushstring(state, invoker.GetReturnValue<const char*>());
				return 1;
			case 'v': // Vector3 (not Vector3*)
				CreateObject<rage::fvector3>(state, invoker.GetReturnValue<rage::scrVector>());
				return 1;
			case 'p': // pointer
				luaL_error(state, "Pointer returns are not supported"); // and probably never will be
			}

			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			lua_pushcfunction(state, InvokeNative);
			lua_setglobal(state, "_I"); // we're trying to keep the auto-generated natives code as short as possible to fit under 65535 characters per namespace
		}
	};

	Invoker _Invoker;
}