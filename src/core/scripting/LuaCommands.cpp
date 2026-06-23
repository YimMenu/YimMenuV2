#include "LuaCommands.hpp"
#include "LuaScript.hpp"
#include "LuaUserInterface.hpp"
#include "core/commands/Commands.hpp"

namespace YimMenu
{
	static void UnrefIfValid(LuaUserInterface* iface, int ref)
	{
		if (ref == LUA_NOREF || !iface)
			return;
		auto* script = iface->GetScript();
		if (!script)
			return;
		auto* state = script->GetState();
		if (!state)
			return;
		luaL_unref(state, LUA_REGISTRYINDEX, ref);
	}

	LuaCommand::LuaCommand(LuaUserInterface* iface, std::string name, std::string label, std::string description, int on_call) :
	    Command(std::move(name), std::move(label), std::move(description)),
	    m_Interface(iface),
	    m_OnCall(on_call)
	{
	}

	LuaCommand::~LuaCommand()
	{
		Commands::RemoveCommand(this);
		UnrefIfValid(m_Interface, m_OnCall);
	}

	void LuaCommand::OnCall()
	{
		if (m_Interface && m_OnCall != LUA_NOREF)
			m_Interface->QueueCoroutine(m_OnCall, false);
	}

	LuaBoolCommand::LuaBoolCommand(LuaUserInterface* iface, std::string name, std::string label, std::string description, bool default_value, int on_enable, int on_disable) :
	    BoolCommand(std::move(name), std::move(label), std::move(description), default_value),
	    m_Interface(iface),
	    m_OnEnable(on_enable),
	    m_OnDisable(on_disable)
	{
	}

	LuaBoolCommand::~LuaBoolCommand()
	{
		Commands::RemoveCommand(this);
		UnrefIfValid(m_Interface, m_OnEnable);
		UnrefIfValid(m_Interface, m_OnDisable);
	}

	void LuaBoolCommand::OnEnable()
	{
		if (m_Interface && m_OnEnable != LUA_NOREF)
			m_Interface->QueueCoroutine(m_OnEnable, true);
	}

	void LuaBoolCommand::OnDisable()
	{
		if (m_Interface && m_OnDisable != LUA_NOREF)
			m_Interface->QueueCoroutine(m_OnDisable, true);
	}

	LuaLoopedCommand::LuaLoopedCommand(LuaUserInterface* iface, std::string name, std::string label, std::string description, int on_tick, int on_enable, int on_disable) :
	    LoopedCommand(std::move(name), std::move(label), std::move(description)),
	    m_Interface(iface),
	    m_OnTick(on_tick),
	    m_OnEnable(on_enable),
	    m_OnDisable(on_disable)
	{
	}

	LuaLoopedCommand::~LuaLoopedCommand()
	{
		if (m_TickRegistered && m_Interface && m_OnTick != LUA_NOREF)
			m_Interface->RemoveTickFunction(m_OnTick);

		Commands::RemoveCommand(this);

		UnrefIfValid(m_Interface, m_OnTick);
		UnrefIfValid(m_Interface, m_OnEnable);
		UnrefIfValid(m_Interface, m_OnDisable);
	}

	void LuaLoopedCommand::OnEnable()
	{
		if (!m_Interface)
			return;

		if (m_OnTick != LUA_NOREF && !m_TickRegistered)
		{
			m_Interface->AddTickFunction(m_OnTick);
			m_TickRegistered = true;
		}
		if (m_OnEnable != LUA_NOREF)
			m_Interface->QueueCoroutine(m_OnEnable, true);
	}

	void LuaLoopedCommand::OnDisable()
	{
		if (!m_Interface)
			return;

		if (m_TickRegistered)
		{
			m_Interface->RemoveTickFunction(m_OnTick);
			m_TickRegistered = false;
		}
		if (m_OnDisable != LUA_NOREF)
			m_Interface->QueueCoroutine(m_OnDisable, true);
	}

	LuaIntCommand::LuaIntCommand(LuaUserInterface* iface, std::string name, std::string label, std::string description, std::optional<int> min, std::optional<int> max, int default_value, int on_change) :
	    IntCommand(std::move(name), std::move(label), std::move(description), min, max, default_value),
	    m_Interface(iface),
	    m_OnChange(on_change)
	{
	}

	LuaIntCommand::~LuaIntCommand()
	{
		Commands::RemoveCommand(this);
		UnrefIfValid(m_Interface, m_OnChange);
	}

	void LuaIntCommand::OnChange()
	{
		if (m_Interface && m_OnChange != LUA_NOREF)
		{
			CallbackArg arg;
			arg.kind = CallbackArg::Kind::Int;
			arg.i    = GetState();
			m_Interface->QueueCoroutine(m_OnChange, true, arg);
		}
	}

	LuaFloatCommand::LuaFloatCommand(LuaUserInterface* iface, std::string name, std::string label, std::string description, std::optional<float> min, std::optional<float> max, float default_value, int on_change) :
	    FloatCommand(std::move(name), std::move(label), std::move(description), min, max, default_value),
	    m_Interface(iface),
	    m_OnChange(on_change)
	{
	}

	LuaFloatCommand::~LuaFloatCommand()
	{
		Commands::RemoveCommand(this);
		UnrefIfValid(m_Interface, m_OnChange);
	}

	void LuaFloatCommand::OnChange()
	{
		if (m_Interface && m_OnChange != LUA_NOREF)
		{
			CallbackArg arg;
			arg.kind = CallbackArg::Kind::Number;
			arg.n    = GetState();
			m_Interface->QueueCoroutine(m_OnChange, true, arg);
		}
	}

	LuaListCommand::LuaListCommand(LuaUserInterface* iface, std::string name, std::string label, std::string description, std::vector<std::pair<int, std::string>> entries, int default_value, int on_change) :
	    ListCommand(std::move(name), std::move(label), std::move(description), {}, default_value),
	    m_Interface(iface),
	    m_OnChange(on_change)
	{
		m_LabelStorage.reserve(entries.size());

		std::vector<std::pair<int, const char*>> list;
		list.reserve(entries.size());

		for (auto& [k, v] : entries)
		{
			m_LabelStorage.push_back(std::move(v));
			list.emplace_back(k, m_LabelStorage.back().c_str());
		}

		SetList(std::move(list));
	}

	LuaListCommand::~LuaListCommand()
	{
		Commands::RemoveCommand(this);
		UnrefIfValid(m_Interface, m_OnChange);
	}

	void LuaListCommand::OnChange()
	{
		if (m_Interface && m_OnChange != LUA_NOREF)
		{
			CallbackArg arg;
			arg.kind = CallbackArg::Kind::Int;
			arg.i    = GetState();
			m_Interface->QueueCoroutine(m_OnChange, true, arg);
		}
	}
}
