#include "core/commands/BoolCommand.hpp"
#include "core/commands/ColorCommand.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/FloatCommand.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "core/commands/StringCommand.hpp"
#include "core/commands/Vector3Command.hpp"
#include "game/commands/PlayerCommand.hpp"
#include "core/scripting/LuaCommands.hpp"
#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUserInterface.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/util/Joaat.hpp"
#include "game/frontend/items/Items.hpp"
#include "LuaCommandHandle.hpp"

namespace YimMenu::Lua
{
	static std::optional<int> OptionalInt(lua_State* state, int idx)
	{
		if (lua_isnoneornil(state, idx))
			return std::nullopt;
		return static_cast<int>(luaL_checkinteger(state, idx));
	}

	static std::optional<float> OptionalFloat(lua_State* state, int idx)
	{
		if (lua_isnoneornil(state, idx))
			return std::nullopt;
		return static_cast<float>(luaL_checknumber(state, idx));
	}

	static void EnsureNotDuplicate(lua_State* state, std::string_view name)
	{
		if (Commands::GetCommand(Joaat(name)))
			luaL_error(state, "command '%s' already exists", std::string(name).c_str());
	}

	int PushCommandHandle(lua_State* state, joaat_t hash, LuaCommandHandle::Kind kind)
	{
		void* data = lua_newuserdata(state, sizeof(LuaCommandHandle));
		new (data) LuaCommandHandle{hash, kind};
		lua_rawgeti(state, LUA_REGISTRYINDEX, Metatable<LuaCommandHandle>::Get());
		lua_setmetatable(state, -2);
		return 1;
	}

	static int CmdHandleGetName(lua_State* state)
	{
		auto& h   = GetObject<LuaCommandHandle>(state, 1);
		auto* cmd = Commands::GetCommand(h.hash);
		if (!cmd)
		{
			lua_pushnil(state);
			return 1;
		}
		const auto& name = cmd->GetName();
		lua_pushlstring(state, name.data(), name.size());
		return 1;
	}

	static int CmdHandleGetDesc(lua_State* state)
	{
		auto& h   = GetObject<LuaCommandHandle>(state, 1);
		auto* cmd = Commands::GetCommand(h.hash);
		if (!cmd)
		{
			lua_pushnil(state);
			return 1;
		}
		const auto& desc = cmd->GetDescription();
		lua_pushlstring(state, desc.data(), desc.size());
		return 1;
	}

	static int CmdHandleGetValue(lua_State* state)
	{
		auto& h = GetObject<LuaCommandHandle>(state, 1);
		switch (h.kind)
		{
		case LuaCommandHandle::Kind::OneShot:
			lua_pushnil(state);
			return 1;
		case LuaCommandHandle::Kind::Bool:
			if (auto* c = Commands::GetCommand<BoolCommand>(h.hash))
				lua_pushboolean(state, c->GetState());
			else
				lua_pushnil(state);
			return 1;
		case LuaCommandHandle::Kind::Int:
			if (auto* c = Commands::GetCommand<IntCommand>(h.hash))
				lua_pushinteger(state, c->GetState());
			else
				lua_pushnil(state);
			return 1;
		case LuaCommandHandle::Kind::Float:
			if (auto* c = Commands::GetCommand<FloatCommand>(h.hash))
				lua_pushnumber(state, c->GetState());
			else
				lua_pushnil(state);
			return 1;
		case LuaCommandHandle::Kind::List:
			if (auto* c = Commands::GetCommand<ListCommand>(h.hash))
				lua_pushinteger(state, c->GetState());
			else
				lua_pushnil(state);
			return 1;
		}
		lua_pushnil(state);
		return 1;
	}

	static int CmdHandleSetValue(lua_State* state)
	{
		auto& h = GetObject<LuaCommandHandle>(state, 1);
		switch (h.kind)
		{
		case LuaCommandHandle::Kind::OneShot:
			return 0;
		case LuaCommandHandle::Kind::Bool:
			if (auto* c = Commands::GetCommand<BoolCommand>(h.hash))
				c->SetState(CheckBooleanSafe(state, 2));
			return 0;
		case LuaCommandHandle::Kind::Int:
			if (auto* c = Commands::GetCommand<IntCommand>(h.hash))
				c->SetState(static_cast<int>(luaL_checkinteger(state, 2)));
			return 0;
		case LuaCommandHandle::Kind::Float:
			if (auto* c = Commands::GetCommand<FloatCommand>(h.hash))
				c->SetState(static_cast<float>(luaL_checknumber(state, 2)));
			return 0;
		case LuaCommandHandle::Kind::List:
			if (auto* c = Commands::GetCommand<ListCommand>(h.hash))
				c->SetState(static_cast<int>(luaL_checkinteger(state, 2)));
			return 0;
		}
		return 0;
	}

	static int CmdHandleDraw(lua_State* state)
	{
		auto& h = GetObject<LuaCommandHandle>(state, 1);
		switch (h.kind)
		{
		case LuaCommandHandle::Kind::OneShot:
			CommandItem(h.hash).Draw();
			break;
		case LuaCommandHandle::Kind::Bool:
			BoolCommandItem(h.hash).Draw();
			break;
		case LuaCommandHandle::Kind::Int:
			IntCommandItem(h.hash).Draw();
			break;
		case LuaCommandHandle::Kind::Float:
			FloatCommandItem(h.hash).Draw();
			break;
		case LuaCommandHandle::Kind::List:
			ListCommandItem(h.hash).Draw();
			break;
		}
		return 0;
	}

	static int CmdAddCommand(lua_State* state)
	{
		auto& iface = LuaScript::GetScript(state).GetUserInterface();
		auto name   = CheckStringSafe(state, 1);
		auto label  = CheckStringSafe(state, 2);
		auto desc   = CheckStringSafe(state, 3);
		int  on_call = CaptureFunction(state, 4, true);

		if (Commands::GetCommand(Joaat(name)))
		{
			luaL_unref(state, LUA_REGISTRYINDEX, on_call);
			luaL_error(state, "command '%s' already exists", std::string(name).c_str());
		}

		auto cmd = std::make_unique<LuaCommand>(&iface, std::string(name), std::string(label), std::string(desc), on_call);
		iface.OwnCommand(std::move(cmd));
		return PushCommandHandle(state, Joaat(name), LuaCommandHandle::Kind::OneShot);
	}

	static int CmdAddBoolCommand(lua_State* state)
	{
		auto& iface = LuaScript::GetScript(state).GetUserInterface();
		auto name   = CheckStringSafe(state, 1);
		auto label  = CheckStringSafe(state, 2);
		auto desc   = CheckStringSafe(state, 3);
		bool def    = lua_isnoneornil(state, 4) ? false : CheckBooleanSafe(state, 4);
		int  on_en  = CaptureFunction(state, 5, false);
		int  on_di  = CaptureFunction(state, 6, false);

		EnsureNotDuplicate(state, name);

		auto cmd = std::make_unique<LuaBoolCommand>(&iface, std::string(name), std::string(label), std::string(desc), def, on_en, on_di);
		iface.OwnCommand(std::move(cmd));
		return PushCommandHandle(state, Joaat(name), LuaCommandHandle::Kind::Bool);
	}

	static int CmdAddLoopedCommand(lua_State* state)
	{
		auto& iface = LuaScript::GetScript(state).GetUserInterface();
		auto name   = CheckStringSafe(state, 1);
		auto label  = CheckStringSafe(state, 2);
		auto desc   = CheckStringSafe(state, 3);
		int  tick   = CaptureFunction(state, 4, true);
		int  on_en  = CaptureFunction(state, 5, false);
		int  on_di  = CaptureFunction(state, 6, false);

		EnsureNotDuplicate(state, name);

		auto cmd = std::make_unique<LuaLoopedCommand>(&iface, std::string(name), std::string(label), std::string(desc), tick, on_en, on_di);
		iface.OwnCommand(std::move(cmd));
		return PushCommandHandle(state, Joaat(name), LuaCommandHandle::Kind::Bool);
	}

	static int CmdAddIntCommand(lua_State* state)
	{
		auto& iface = LuaScript::GetScript(state).GetUserInterface();
		auto name   = CheckStringSafe(state, 1);
		auto label  = CheckStringSafe(state, 2);
		auto desc   = CheckStringSafe(state, 3);
		auto vmin   = OptionalInt(state, 4);
		auto vmax   = OptionalInt(state, 5);
		int  def    = lua_isnoneornil(state, 6) ? 0 : static_cast<int>(luaL_checkinteger(state, 6));
		int  on_ch  = CaptureFunction(state, 7, false);

		EnsureNotDuplicate(state, name);

		auto cmd = std::make_unique<LuaIntCommand>(&iface, std::string(name), std::string(label), std::string(desc), vmin, vmax, def, on_ch);
		iface.OwnCommand(std::move(cmd));
		return PushCommandHandle(state, Joaat(name), LuaCommandHandle::Kind::Int);
	}

	static int CmdAddFloatCommand(lua_State* state)
	{
		auto& iface = LuaScript::GetScript(state).GetUserInterface();
		auto name   = CheckStringSafe(state, 1);
		auto label  = CheckStringSafe(state, 2);
		auto desc   = CheckStringSafe(state, 3);
		auto vmin   = OptionalFloat(state, 4);
		auto vmax   = OptionalFloat(state, 5);
		float def   = lua_isnoneornil(state, 6) ? 0.0f : static_cast<float>(luaL_checknumber(state, 6));
		int   on_ch = CaptureFunction(state, 7, false);

		EnsureNotDuplicate(state, name);

		auto cmd = std::make_unique<LuaFloatCommand>(&iface, std::string(name), std::string(label), std::string(desc), vmin, vmax, def, on_ch);
		iface.OwnCommand(std::move(cmd));
		return PushCommandHandle(state, Joaat(name), LuaCommandHandle::Kind::Float);
	}

	static std::vector<std::pair<int, std::string>> ReadListEntries(lua_State* state, int idx)
	{
		luaL_checktype(state, idx, LUA_TTABLE);

		std::vector<std::pair<int, std::string>> out;

		for (lua_Integer i = 1;; ++i)
		{
			lua_rawgeti(state, idx, i);
			if (lua_isnil(state, -1))
			{
				lua_pop(state, 1);
				break;
			}
			if (lua_type(state, -1) != LUA_TTABLE)
			{
				lua_pop(state, 1);
				luaL_error(state, "list entry #%d must be a { key, label } table", static_cast<int>(i));
			}

			lua_rawgeti(state, -1, 1);
			int key = static_cast<int>(luaL_checkinteger(state, -1));
			lua_pop(state, 1);

			lua_rawgeti(state, -1, 2);
			std::size_t len   = 0;
			const char* label = luaL_checklstring(state, -1, &len);
			out.emplace_back(key, std::string(label, len));

			lua_pop(state, 2);
		}

		return out;
	}

	static int CmdGetCommand(lua_State* state)
	{
		auto hash = GetHashArgument(state, 1);
		auto* cmd = Commands::GetCommand(hash);
		if (!cmd)
		{
			lua_pushnil(state);
			return 1;
		}
		
		if (dynamic_cast<PlayerCommand*>(cmd) || dynamic_cast<ColorCommand*>(cmd)
		    || dynamic_cast<StringCommand*>(cmd) || dynamic_cast<Vector3Command*>(cmd))
		{
			lua_pushnil(state);
			return 1;
		}

		LuaCommandHandle::Kind kind;
		if (dynamic_cast<ListCommand*>(cmd))
			kind = LuaCommandHandle::Kind::List;
		else if (dynamic_cast<IntCommand*>(cmd))
			kind = LuaCommandHandle::Kind::Int;
		else if (dynamic_cast<FloatCommand*>(cmd))
			kind = LuaCommandHandle::Kind::Float;
		else if (dynamic_cast<BoolCommand*>(cmd))
			kind = LuaCommandHandle::Kind::Bool; // covers LoopedCommand too
		else
			kind = LuaCommandHandle::Kind::OneShot;

		return PushCommandHandle(state, hash, kind);
	}

	static int CmdAddListCommand(lua_State* state)
	{
		auto& iface  = LuaScript::GetScript(state).GetUserInterface();
		auto name    = CheckStringSafe(state, 1);
		auto label   = CheckStringSafe(state, 2);
		auto desc    = CheckStringSafe(state, 3);
		auto entries = ReadListEntries(state, 4);
		int  def     = lua_isnoneornil(state, 5) ? 0 : static_cast<int>(luaL_checkinteger(state, 5));
		int  on_ch   = CaptureFunction(state, 6, false);

		EnsureNotDuplicate(state, name);

		auto cmd = std::make_unique<LuaListCommand>(&iface, std::string(name), std::string(label), std::string(desc), std::move(entries), def, on_ch);
		iface.OwnCommand(std::move(cmd));
		return PushCommandHandle(state, Joaat(name), LuaCommandHandle::Kind::List);
	}

	class CommandMgr : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);
			SetFunction(state, CmdHandleDraw, "draw");
			SetFunction(state, CmdHandleGetValue, "get_value");
			SetFunction(state, CmdHandleSetValue, "set_value");
			SetFunction(state, CmdHandleGetName, "get_name");
			SetFunction(state, CmdHandleGetDesc, "get_desc");

			lua_newtable(state);
			lua_pushvalue(state, -2);
			lua_setfield(state, -2, "__index");
			lua_remove(state, -2);
			Metatable<LuaCommandHandle>::Register(state);

			lua_newtable(state);
			SetFunction(state, CmdAddCommand, "add_command");
			SetFunction(state, CmdAddBoolCommand, "add_bool_command");
			SetFunction(state, CmdAddLoopedCommand, "add_looped_command");
			SetFunction(state, CmdAddIntCommand, "add_int_command");
			SetFunction(state, CmdAddFloatCommand, "add_float_command");
			SetFunction(state, CmdAddListCommand, "add_list_command");
			SetFunction(state, CmdGetCommand, "get_command");
			lua_setglobal(state, "commandmgr");
		}
	};

	CommandMgr _CommandMgr;
}
