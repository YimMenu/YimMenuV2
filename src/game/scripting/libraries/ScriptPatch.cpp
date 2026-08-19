#include "core/memory/Pattern.hpp"
#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/util/Joaat.hpp"
#include "game/backend/ScriptPatches.hpp"
#include "game/gta/ScriptPointer.hpp"

namespace YimMenu::Lua
{
	class ScriptPatchBinding : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static std::vector<std::uint8_t> ReadPatchBytes(lua_State* state, int idx)
		{
			luaL_checktype(state, idx, LUA_TTABLE);

			std::vector<std::uint8_t> bytes;
			for (lua_Integer i = 1;; ++i)
			{
				lua_rawgeti(state, idx, i);
				if (lua_isnil(state, -1))
				{
					lua_pop(state, 1);
					break;
				}

				lua_Integer value = luaL_checkinteger(state, -1);
				lua_pop(state, 1);

				if (value < 0 || value > 0xFF)
					luaL_error(state, "scr_patch: byte #%d (%d) out of range [0, 255]", static_cast<int>(i), static_cast<int>(value));

				bytes.push_back(static_cast<std::uint8_t>(value));
			}

			if (bytes.empty())
				luaL_argerror(state, idx, "patch byte table is empty");

			return bytes;
		}

		static int New(lua_State* state)
		{
			int base = (lua_type(state, 1) == LUA_TSTRING) ? 0 : 1;

			auto script  = GetHashArgument(state, base + 1);
			auto name    = CheckStringSafe(state, base + 2);
			auto pattern = CheckStringSafe(state, base + 3);
			auto offset  = static_cast<std::int32_t>(luaL_optinteger(state, base + 4, 0));
			auto bytes   = ReadPatchBytes(state, base + 5);

			auto patch = ScriptPatches::AddPatch(script, ScriptPointer(std::string(name), SimplePattern(pattern), offset), std::move(bytes));
			patch->Enable();

			PushObject<ScriptPatch>(state, std::move(patch));
			return 1;
		}

		static int Enable(lua_State* state)
		{
			auto& patch = GetObject<ScriptPatch>(state, 1);
			if (patch)
				patch->Enable();
			return 0;
		}

		static int Disable(lua_State* state)
		{
			auto& patch = GetObject<ScriptPatch>(state, 1);
			if (patch)
				patch->Disable();
			return 0;
		}

		static int Remove(lua_State* state)
		{
			auto& patch = GetObject<ScriptPatch>(state, 1);
			if (patch)
			{
				ScriptPatches::RemovePatch(patch);
				patch.reset();
			}
			return 0;
		}

		static int GC(lua_State* state)
		{
			auto& patch = GetObject<ScriptPatch>(state, 1);
			if (patch)
				ScriptPatches::RemovePatch(patch);
			std::destroy_at(&patch);
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			luaL_newmetatable(state, "ScriptPatch");
			{
				SetFunction(state, GC, "__gc");

				lua_newtable(state);
				{
					SetFunction(state, Enable, "enable");
					SetFunction(state, Disable, "disable");
					SetFunction(state, Remove, "remove");
				}
				lua_setfield(state, -2, "__index");
			}
			Metatable<ScriptPatch>::Register(state);

			lua_newtable(state);
			SetConstructor<New>(state);
			lua_setglobal(state, "ScriptPatch");
		}
	};

	ScriptPatchBinding _ScriptPatchBinding;
}
