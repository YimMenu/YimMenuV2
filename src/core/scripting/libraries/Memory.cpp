#include "core/memory/ModuleMgr.hpp"
#include "core/memory/Pattern.hpp"
#include "core/memory/PatternScanner.hpp"
#include "core/memory/PointerCalculator.hpp"
#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUserInterface.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/util/Joaat.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu::Lua
{
	class RuntimePattern : public IPattern
	{
		std::string m_Name;
		std::vector<std::optional<std::uint8_t>> m_Bytes;
		PatternHash m_Hash;

	public:
		~RuntimePattern() noexcept override {}

		RuntimePattern(std::string_view name, SimplePattern&& parsed) :
		    m_Name(name),
		    m_Bytes(std::move(parsed.m_Bytes))
		{
			for (const auto& b : m_Bytes)
				m_Hash = m_Hash.Update(b.has_value() ? static_cast<char>(*b) : '?');
			m_Hash = m_Hash.Update(m_Bytes.size());
		}

		const std::string_view Name() const override
		{
			return m_Name;
		}

		std::span<const std::optional<std::uint8_t>> Signature() const override
		{
			return m_Bytes;
		}

		const PatternHash Hash() const override
		{
			return m_Hash;
		}
	};

	class Memory : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int ScanPattern(lua_State* state)
		{
			auto sig    = CheckStringSafe(state, 1);
			auto* gta5  = ModuleMgr.Get("GTA5.exe"_J);
			if (!gta5)
			{
				lua_pushnil(state);
				return 1;
			}

			RuntimePattern pattern("memory.scan_pattern", SimplePattern(sig));

			std::optional<PointerCalculator> found;

			PatternScanner scanner(gta5);
			scanner.Add(pattern, [&](PointerCalculator pc) {
				found.emplace(pc);
			});
			scanner.Scan();

			if (!found)
			{
				lua_pushnil(state);
				return 1;
			}

			PushObject<PointerCalculator>(state, *found);
			return 1;
		}

		static int HandleToPtr(lua_State* state)
		{
			int handle = static_cast<int>(luaL_checkinteger(state, 1));
			void* ptr  = Pointers.HandleToPtr ? Pointers.HandleToPtr(handle) : nullptr;
			PushObject<PointerCalculator>(state, PointerCalculator(ptr));
			return 1;
		}

		static int PtrToHandle(lua_State* state)
		{
			auto& pc = GetObject<PointerCalculator>(state, 1);
			int handle = 0;
			if (Pointers.PtrToHandle)
				handle = Pointers.PtrToHandle(pc.As<void*>());
			lua_pushinteger(state, handle);
			return 1;
		}

		static int Allocate(lua_State* state)
		{
			auto size = static_cast<std::size_t>(luaL_checkinteger(state, 1));
			if (size == 0)
				luaL_argerror(state, 1, "allocation size must be > 0");

			void* block = std::calloc(1, size);
			if (!block)
				luaL_error(state, "memory.allocate: out of memory (requested %zu bytes)", size);

			LuaScript::GetScript(state).GetUserInterface().TrackScriptAllocation(block);
			PushObject<PointerCalculator>(state, PointerCalculator(block));
			return 1;
		}
		
		static int Free(lua_State* state)
		{
			auto& pc    = GetObject<PointerCalculator>(state, 1);
			void* block = pc.As<void*>();
			if (!block)
				return 0;

			auto& iface = LuaScript::GetScript(state).GetUserInterface();
			if (!iface.ReleaseScriptAllocation(block))
				luaL_error(state, "memory.free: pointer was not allocated by this script (or already freed)");

			std::free(block);
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);
			SetFunction(state, ScanPattern, "scan_pattern");
			SetFunction(state, HandleToPtr, "handle_to_ptr");
			SetFunction(state, PtrToHandle, "ptr_to_handle");
			SetFunction(state, Allocate, "allocate");
			SetFunction(state, Free, "free");
			lua_setglobal(state, "memory");
		}
	};

	Memory _Memory;
}
