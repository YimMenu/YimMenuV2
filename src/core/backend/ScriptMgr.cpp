#include "ScriptMgr.hpp"
#include "core/scripting/LuaManager.hpp"

namespace YimMenu
{
	Script::Script(std::function<void()> callback) :
	    m_Callback(callback),
	    m_Done(false),
	    m_ChildFiber(0),
	    m_MainFiber(0),
	    m_WakeTime(std::nullopt)
	{
		m_ChildFiber = CreateFiber(
		    0,
		    [](void* param) {
			    auto this_script = static_cast<Script*>(param);
			    this_script->m_Callback();
			    this_script->m_Done = true;
			    SwitchToFiber(this_script->m_MainFiber);
		    },
		    this);
	}

	Script::~Script()
	{
		if (m_ChildFiber)
			DeleteFiber(m_ChildFiber);
	}

	void Script::Tick()
	{
		m_MainFiber = GetCurrentFiber();
		if ((!m_WakeTime.has_value() || m_WakeTime.value() <= std::chrono::high_resolution_clock::now()) && !m_Done)
		{
			SwitchToFiber(m_ChildFiber);
		}
	}

	void Script::Yield(std::optional<std::chrono::high_resolution_clock::duration> time)
	{
		if (time.has_value())
			m_WakeTime = std::chrono::high_resolution_clock::now() + time.value();
		else
			m_WakeTime = std::nullopt;

		SwitchToFiber(m_MainFiber);
	}

	void ScriptMgr::InitImpl()
	{
		// none required
	}

	void ScriptMgr::DestroyImpl()
	{
		std::lock_guard lock(m_Mutex);
		m_Scripts.clear();
	}

	void ScriptMgr::TickImpl()
	{
		std::lock_guard lock(m_Mutex);
		static bool ensure_main_fiber = (ConvertThreadToFiber(nullptr), true);

		for (const auto& script : m_Scripts)
			script->Tick();
	}

	void ScriptMgr::YieldImpl(std::optional<std::chrono::high_resolution_clock::duration> time)
	{
		if (auto script = LuaManager::GetRunningCoroutine())
			LuaScript::GetScript(script).Yield(script, time ? std::chrono::duration_cast<std::chrono::milliseconds>(*time).count() : 0);
		else if (auto script = static_cast<Script*>(GetFiberData()))
			script->Yield(time);
	}

	void ScriptMgr::AddScriptImpl(std::unique_ptr<Script> script)
	{
		std::lock_guard lock(m_Mutex);
		m_Scripts.push_back(std::move(script));
	}
}