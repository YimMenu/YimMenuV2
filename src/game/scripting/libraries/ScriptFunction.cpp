#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "game/gta/ScriptFunction.hpp"
#include "game/gta/ScriptPointer.hpp"

namespace YimMenu::Lua
{
	class ScriptFunctionBinding : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int New(lua_State* state)
		{
			auto script = GetHashArgument(state, 1);
			auto& ptr   = GetObject<ScriptPointer>(state, 2);
			CreateObject<ScriptFunction>(state, script, ptr);
			return 1;
		}

		static int GC(lua_State* state)
		{
			auto& self = GetObject<ScriptFunction>(state, 1);
			self.~ScriptFunction();
			return 0;
		}

		static int GetInteger(lua_State* state, int idx)
		{
			if (lua_type(state, idx) == LUA_TBOOLEAN)
				return static_cast<int>(lua_toboolean(state, idx));
			return static_cast<int>(luaL_checkinteger(state, idx));
		}

		static std::uint32_t GetBool(lua_State* state, int idx)
		{
			auto t = lua_type(state, idx);
			if (t == LUA_TBOOLEAN)
				return lua_toboolean(state, idx) ? 1u : 0u;
			if (t == LUA_TNUMBER)
				return lua_tointeger(state, idx) ? 1u : 0u;
			luaL_argerror(state, idx, "expected boolean or number");
			return 0u;
		}

		template<typename T>
		static std::uint64_t PackSlot(T value)
		{
			std::uint64_t slot = 0;
			std::memcpy(&slot, &value, sizeof(value));
			return slot;
		}

		// params follows the Invoker convention:
		static int Call(lua_State* state)
		{
			auto& self    = GetObject<ScriptFunction>(state, 1);
			auto  params  = CheckStringSafe(state, 2);

			std::vector<std::uint64_t> args;
			char return_type = 'n';

			int lua_arg = 3;
			for (const char* p = params; *p; ++p)
			{
				if (*p == '=')
				{
					return_type = *(p + 1);
					break;
				}

				std::uint64_t slot = 0;
				switch (*p)
				{
				case 'i':
					slot = PackSlot<std::int32_t>(GetInteger(state, lua_arg++));
					break;
				case 'f':
					slot = PackSlot<float>(static_cast<float>(luaL_checknumber(state, lua_arg++)));
					break;
				case 'h':
					slot = PackSlot<std::uint32_t>(GetHashArgument(state, lua_arg++));
					break;
				case 'b':
					slot = PackSlot<std::uint32_t>(GetBool(state, lua_arg++));
					break;
				default:
					luaL_error(state, "unknown ScriptFunction param type '%c'", *p);
					return 0;
				}
				args.push_back(slot);
			}

			switch (return_type)
			{
			case 'n':
				self.Invoke(args);
				return 0;
			case 'i':
			{
				std::int32_t ret = 0;
				self.Invoke(args, &ret, sizeof(ret));
				lua_pushinteger(state, ret);
				return 1;
			}
			case 'h':
			{
				std::uint32_t ret = 0;
				self.Invoke(args, &ret, sizeof(ret));
				lua_pushinteger(state, ret);
				return 1;
			}
			case 'f':
			{
				float ret = 0.0f;
				self.Invoke(args, &ret, sizeof(ret));
				lua_pushnumber(state, ret);
				return 1;
			}
			case 'b':
			{
				std::uint32_t ret = 0;
				self.Invoke(args, &ret, sizeof(ret));
				lua_pushboolean(state, ret != 0);
				return 1;
			}
			default:
				luaL_error(state, "unknown ScriptFunction return type '%c'", return_type);
				return 0;
			}
		}

		virtual void Register(lua_State* state) override
		{
			luaL_newmetatable(state, "ScriptFunction");
			{
				SetFunction(state, GC, "__gc");

				lua_newtable(state);
				{
					SetFunction(state, Call, "call");
				}
				lua_setfield(state, -2, "__index");
			}
			Metatable<ScriptFunction>::Register(state);

			lua_newtable(state);
			SetConstructor<New>(state);
			lua_setglobal(state, "ScriptFunction");
		}
	};

	ScriptFunctionBinding _ScriptFunctionBinding;
}
