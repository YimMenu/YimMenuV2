#include "core/memory/BytePatches.hpp"
#include "core/memory/PointerCalculator.hpp"
#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"

namespace YimMenu::Lua
{
	struct LuaPatch
	{
		BytePatch patch;
	};

	class PointerBinding : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static PointerCalculator& Self(lua_State* state)
		{
			return GetObject<PointerCalculator>(state, 1);
		}

		static void GuardNull(lua_State* state, const PointerCalculator& pc)
		{
			if (!pc)
				luaL_error(state, "attempt to access a null pointer");
		}

		static int New(lua_State* state)
		{
			int idx   = lua_istable(state, 1) ? 2 : 1;
			auto addr = static_cast<std::uintptr_t>(luaL_checkinteger(state, idx));
			PushObject<PointerCalculator>(state, PointerCalculator(addr));
			return 1;
		}

		static int GetAddress(lua_State* state)
		{
			lua_pushinteger(state, static_cast<lua_Integer>(Self(state).As<std::uintptr_t>()));
			return 1;
		}

		static int SetAddress(lua_State* state)
		{
			auto& pc  = Self(state);
			auto addr = static_cast<std::uintptr_t>(luaL_checkinteger(state, 2));
			pc.~PointerCalculator();
			new (&pc) PointerCalculator(addr);
			return 0;
		}

		static int IsNull(lua_State* state)
		{
			lua_pushboolean(state, !static_cast<bool>(Self(state)));
			return 1;
		}

		static int IsValid(lua_State* state)
		{
			lua_pushboolean(state, static_cast<bool>(Self(state)));
			return 1;
		}

		static int Add(lua_State* state)
		{
			auto& pc   = Self(state);
			auto offset = static_cast<std::ptrdiff_t>(luaL_checkinteger(state, 2));
			PushObject<PointerCalculator>(state, pc.Add(offset));
			return 1;
		}

		static int Sub(lua_State* state)
		{
			auto& pc   = Self(state);
			auto offset = static_cast<std::ptrdiff_t>(luaL_checkinteger(state, 2));
			PushObject<PointerCalculator>(state, pc.Sub(offset));
			return 1;
		}

		static int Rip(lua_State* state)
		{
			auto& pc   = Self(state);
			GuardNull(state, pc);
			auto offset = static_cast<std::ptrdiff_t>(luaL_optinteger(state, 2, 0));
			PushObject<PointerCalculator>(state, pc.Rip().Add(offset));
			return 1;
		}

		static int Deref(lua_State* state)
		{
			auto& pc = Self(state);
			GuardNull(state, pc);
			PushObject<PointerCalculator>(state, PointerCalculator(pc.As<std::uintptr_t&>()));
			return 1;
		}

		template<typename T>
		static int GetInt(lua_State* state)
		{
			auto& pc = Self(state);
			GuardNull(state, pc);
			lua_pushinteger(state, static_cast<lua_Integer>(pc.As<T&>()));
			return 1;
		}

		template<typename T>
		static int SetInt(lua_State* state)
		{
			auto& pc = Self(state);
			GuardNull(state, pc);
			pc.As<T&>() = static_cast<T>(luaL_checkinteger(state, 2));
			return 0;
		}

		static int GetFloat(lua_State* state)
		{
			auto& pc = Self(state);
			GuardNull(state, pc);
			lua_pushnumber(state, pc.As<float&>());
			return 1;
		}

		static int SetFloat(lua_State* state)
		{
			auto& pc = Self(state);
			GuardNull(state, pc);
			pc.As<float&>() = static_cast<float>(luaL_checknumber(state, 2));
			return 0;
		}

		static int GetString(lua_State* state)
		{
			auto& pc = Self(state);
			GuardNull(state, pc);
			lua_pushstring(state, pc.As<char*>());
			return 1;
		}

		static int SetString(lua_State* state)
		{
			auto& pc = Self(state);
			GuardNull(state, pc);
			std::size_t len = 0;
			auto src = CheckStringSafe(state, 2, &len);
			std::memcpy(pc.As<char*>(), src, len + 1);
			return 0;
		}

		template<typename T>
		static int Patch(lua_State* state)
		{
			auto& pc = Self(state);
			GuardNull(state, pc);
			T value   = static_cast<T>(luaL_checkinteger(state, 2));
			auto patch = BytePatches::Add(pc.As<T*>(), value);
			PushObject<LuaPatch>(state, LuaPatch{std::move(patch)});
			return 1;
		}

		static int GC(lua_State* state)
		{
			Self(state).~PointerCalculator();
			return 0;
		}

		static int PatchApply(lua_State* state)
		{
			GetObject<LuaPatch>(state, 1).patch->Apply();
			return 0;
		}

		static int PatchRestore(lua_State* state)
		{
			GetObject<LuaPatch>(state, 1).patch->Restore();
			return 0;
		}

		static int PatchGC(lua_State* state)
		{
			GetObject<LuaPatch>(state, 1).~LuaPatch();
			return 0;
		}

		void RegisterPatchType(lua_State* state)
		{
			luaL_newmetatable(state, "lua_patch");
			{
				SetFunction(state, PatchGC, "__gc");

				lua_newtable(state);
				{
					SetFunction(state, PatchApply, "apply");
					SetFunction(state, PatchRestore, "restore");
				}
				lua_setfield(state, -2, "__index");
			}
			Metatable<LuaPatch>::Register(state);
		}

		virtual void Register(lua_State* state) override
		{
			RegisterPatchType(state);

			luaL_newmetatable(state, "pointer");
			{
				SetFunction(state, GC, "__gc");

				lua_newtable(state);
				{
					SetFunction(state, Add, "add");
					SetFunction(state, Sub, "sub");
					SetFunction(state, Rip, "rip");
					SetFunction(state, Deref, "deref");

					SetFunction(state, GetInt<std::uint8_t>, "get_byte");
					SetFunction(state, GetInt<std::uint16_t>, "get_word");
					SetFunction(state, GetInt<std::int32_t>, "get_int");
					SetFunction(state, GetInt<std::uint32_t>, "get_dword");
					SetFunction(state, GetFloat, "get_float");
					SetFunction(state, GetInt<std::uint64_t>, "get_qword");

					SetFunction(state, SetInt<std::uint8_t>, "set_byte");
					SetFunction(state, SetInt<std::uint16_t>, "set_word");
					SetFunction(state, SetInt<std::int32_t>, "set_int");
					SetFunction(state, SetInt<std::uint32_t>, "set_dword");
					SetFunction(state, SetFloat, "set_float");
					SetFunction(state, SetInt<std::uint64_t>, "set_qword");

					SetFunction(state, GetString, "get_string");
					SetFunction(state, SetString, "set_string");

					SetFunction(state, Patch<std::uint8_t>, "patch_byte");
					SetFunction(state, Patch<std::uint16_t>, "patch_word");
					SetFunction(state, Patch<std::uint32_t>, "patch_dword");
					SetFunction(state, Patch<std::uint64_t>, "patch_qword");

					SetFunction(state, IsNull, "is_null");
					SetFunction(state, IsValid, "is_valid");
					SetFunction(state, GetAddress, "get_address");
					SetFunction(state, SetAddress, "set_address");
				}
				lua_setfield(state, -2, "__index");
			}
			Metatable<PointerCalculator>::Register(state);

			lua_newtable(state);
			SetConstructor<New>(state);
			lua_setglobal(state, "pointer");
		}
	};

	PointerBinding _PointerBinding;
}
