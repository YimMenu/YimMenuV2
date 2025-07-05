#include "LuaScript.hpp"
#include "LuaManager.hpp"

namespace YimMenu
{
	// https://github.com/brimworks/lua-ev/blob/2d11066b6f96a7501805e8c28d92f70dd2c0ab13/lua_ev.c#L144
	// TODO: may need to check if debug is a real table if ChatGPT is to be trusted
	static int ErrorHandler(lua_State* state)
	{
		auto error_msg = lua_tostring(state, 1);
		if (!error_msg)
			return 1; // return error_msg

		// ok this is the fun part
		// our stack right now: retaddr error_message <
		lua_getglobal(state, "debug");
		lua_getfield(state, -1, "traceback");
		
		lua_pushstring(state, error_msg);
		lua_pushinteger(state, 2);

		lua_call(state, 2, 1); // now the top of stack should have the stacktrace

		return 1;
	}

	bool LuaScript::CallFunction(int n_args, int n_results, lua_State* override_state)
	{
		auto state = override_state;
		if (!state)
			state = m_State;

		if (!LuaManager::IsRunningInMainThread())
		{
			LOGF(FATAL, "LuaScript::CallFunction: {} attempted to call a Lua function outside the main thread. This is not allowed", m_ModuleName);
			lua_pop(state, 1); // pop the function from the stack since we aren't going to call it
			SetMalfunctioning();
			return false;
		}

		lua_pushcfunction(state, &ErrorHandler);
		int handler_index = lua_gettop(state) - n_args - 1;
		lua_insert(state, handler_index); // move it before all the args

		auto result = lua_pcall(state, n_args, n_results, handler_index);

		if (result == LUA_OK)
		{
			// the lua runtime doesn't pop the handler if there's no error
			lua_remove(state, handler_index); // TODO: does this actually work? What happens if your function returns stuff?
			return true;
		}
		else
		{
			auto trace = lua_tostring(state, -1);
			LOGF(FATAL, "{}: {}", m_ModuleName, trace);
			lua_pop(state, 1); // pop the stack trace
			SetMalfunctioning();
			return false;
		}
	}

	int LuaScript::ResumeCoroutine(int n_args, int n_results, lua_State* coro_state)
	{
		if (!LuaManager::IsRunningInMainThread())
		{
			LOGF(FATAL, "LuaScript::ResumeCoroutine: {} attempted to resume a Lua coroutine outside the main thread. This is not allowed", m_ModuleName);
			SetMalfunctioning();
			return LUA_ERRRUN;
		}

		auto result = lua_resume(coro_state, n_args);
		if (result == LUA_OK || result == LUA_YIELD)
		{
			// move returns to the main stack

			auto num_rets = lua_gettop(coro_state);
			if (num_rets != n_results && result == LUA_YIELD)
			{
				LOGF(FATAL, "LuaScript::ResumeCoroutine: {} yielded {} values when code expected {} values to be yielded", m_ModuleName, num_rets, n_results);
				SetMalfunctioning();
				return LUA_ERRRUN;
			}

			if (num_rets)
				lua_xmove(coro_state, m_State, num_rets);
		}
		else
		{
			// there would be an error object on the top of stack
			std::string error_msg = lua_tostring(coro_state, -1);
			lua_pop(coro_state, 1);

			// traceback
			luaL_traceback(coro_state, coro_state, error_msg.c_str(), 1);
			LOGF(FATAL, "{}: {}", m_ModuleName, lua_tostring(coro_state, -1));
			lua_pop(coro_state, 1);
	
			SetMalfunctioning();
		}

		return result;
	}

	void LuaScript::RemoveScriptCallback(ScriptCallback& callback)
	{
		luaL_unref(m_State, LUA_REGISTRYINDEX, callback.m_Coroutine);
		if (callback.m_Fiber)
			DeleteFiber(callback.m_Fiber);
	}

	void LuaScript::DisableResources()
	{
		for (int i = 0; i < m_Resources.size(); i++)
		{
			if (!m_Resources[i].size())
				return;

			auto type = LuaManager::GetResourceType(i);
			type->Lock();

			for (auto& resource : m_Resources[i])
				resource->OnDisable();

			type->Unlock();
		}
	}

	void LuaScript::EnableResources()
	{
		for (int i = 0; i < m_Resources.size(); i++)
		{
			if (!m_Resources[i].size())
				return;

			auto type = LuaManager::GetResourceType(i);
			type->Lock();

			for (auto& resource : m_Resources[i])
				resource->OnEnable();

			type->Unlock();
		}
	}

	LuaScript::LuaScript(std::string_view file_name) :
	    m_FileName(file_name),
	    m_ModuleName(std::filesystem::path(file_name).filename().string()),
	    m_Config(std::filesystem::path(file_name).stem().string())
	{
		m_Resources.resize(LuaManager::GetNumResourceTypes());
		m_State = luaL_newstate();
		
		lua_pushlightuserdata(m_State, (void*)this);  
		lua_setfield(m_State, LUA_REGISTRYINDEX, "context");

		LuaManager::LoadLibraries(m_State);
		
		auto result = luaL_loadfilex(m_State, file_name.data(), "t");
		if (result != LUA_OK) // don't load binary chunks
		{
			auto error = lua_tostring(m_State, -1);
			LOGF(FATAL, "{}: {}", m_ModuleName, error);
			SetMalfunctioning();
			return;
		}

		// we should have a function in the top of stack
		CallFunction(0, 0);
		m_LoadState = LoadState::RUNNING;
	}

	LuaScript::~LuaScript()
	{
		if (m_State)
		{
			lua_close(m_State);
			m_State = nullptr;
		}
	}

	void LuaScript::Pause()
	{
		if (m_LoadState == LoadState::RUNNING)
		{
			DisableResources();
			m_LoadState = LoadState::PAUSED;
		}
	}

	void LuaScript::Resume()
	{
		if (m_LoadState == LoadState::PAUSED)
		{
			EnableResources();
			m_LoadState = LoadState::RUNNING;
		}
	}

	void LuaScript::MarkUnloaded()
	{
		DisableResources();
		m_LoadState = LoadState::UNLOADED;
	}

	bool LuaScript::SafeToUnload()
	{
		for (auto& callback : m_ScriptCallbacks)
			if (callback.m_LastYieldFromCode)
				return false; // don't unload if we're calling a latent function

		return true;
	}

	LuaScript& LuaScript::GetScript(lua_State* state)
	{
		lua_getfield(state, LUA_REGISTRYINDEX, "context");
		auto script = static_cast<LuaScript*>(lua_touserdata(state, -1));
		lua_pop(state, 1);
		return *script;
	}

	void LuaScript::AddScriptCallback(int func_handle)
	{
		lua_rawgeti(m_State, LUA_REGISTRYINDEX, func_handle);

		lua_State* coro_state = lua_newthread(m_State);
		lua_pushvalue(m_State, 1); // xmove can only move from top of stack, so we have to push the function again even if it's already in the stack
		lua_xmove(m_State, coro_state, 1);

		auto coro_handle = luaL_ref(m_State, LUA_REGISTRYINDEX);

		ScriptCallback callback;
		callback.m_Coroutine = coro_handle;
		callback.m_LastYieldFromCode = false;
		callback.m_TimeToResume = std::nullopt;
		callback.m_Fiber = nullptr;
		callback.m_ParentFiber = nullptr;
		callback.m_LatentTarget = nullptr;
		callback.m_CoroState = nullptr;
		callback.m_LastReturnValue = -1;

		// we don't want to push any additional callbacks to the main array when we're in the middle of running, and potentially deleting, them
		if (m_RunningScriptCallbacks)
			m_QueuedScriptCallbacks.push_back(callback);
		else
			m_ScriptCallbacks.push_back(callback);
	}

	void LuaScript::Yield(lua_State* state, int millis, bool from_code)
	{
		lua_pushinteger(state, millis);
		lua_pushboolean(state, from_code);
		if (from_code)
		{
			if (lua_isyieldable(state) && lua_status(state) != LUA_YIELD) // only yield for the first time, since after that we're not yielding for real
				lua_yield(state, 2);
			GetScript(state).m_CurrentlyExecutingCallback->m_LastReturnValue = -1;
			SwitchToFiber(GetScript(state).m_CurrentlyExecutingCallback->m_ParentFiber);
		}
		else
		{
			lua_yield(state, 2);
			// function must return -1 immediately after this
		}
	}

	void LuaScript::Tick()
	{
		m_RunningScriptCallbacks = true;
		std::erase_if(m_ScriptCallbacks, [this](ScriptCallback& callback) {
			if (callback.m_TimeToResume && *callback.m_TimeToResume > std::chrono::high_resolution_clock::now())
				return false;

			lua_rawgeti(m_State, LUA_REGISTRYINDEX, callback.m_Coroutine);
			lua_State* coro_state = lua_tothread(m_State, -1);
			lua_pop(m_State, 1);

			int num_args = 0;

			if (callback.m_LastYieldFromCode)
			{
				// we need to pretend we're running in a coroutine
				LuaManager::SetRunningCoroutine(coro_state);
				m_CurrentlyExecutingCallback = &callback;
				SwitchToFiber(callback.m_Fiber);
				m_CurrentlyExecutingCallback = nullptr;
				LuaManager::SetRunningCoroutine(nullptr);

				if (callback.m_LastReturnValue < 0)
				{
					// yielded again into a latent function
					auto time = lua_tointeger(m_State, -2);
					lua_pop(m_State, 2);

					callback.SetTimeToResume(time);
					return false;
				}
				else
				{
					// done with this one
					callback.m_LastYieldFromCode = false;
					num_args = callback.m_LastReturnValue;
				}
			}

			LuaManager::SetRunningCoroutine(coro_state);
			m_CurrentlyExecutingCallback = &callback;

			auto state = ResumeCoroutine(num_args, 2, coro_state);

			m_CurrentlyExecutingCallback = nullptr;
			LuaManager::SetRunningCoroutine(nullptr);

			if (state != LUA_YIELD)
			{
				RemoveScriptCallback(callback);
				return true;
			}

			auto time = lua_tointeger(m_State, -2);
			auto from_code = lua_toboolean(m_State, -1);
			lua_pop(m_State, 2);

			callback.SetTimeToResume(time);
			callback.m_LastYieldFromCode = from_code;

			return false;
		});
		m_RunningScriptCallbacks = false;
		
		std::ranges::move(m_QueuedScriptCallbacks, std::back_inserter(m_ScriptCallbacks));
		m_QueuedScriptCallbacks.clear();
	}

	void LuaScript::AddEventHandler(std::uint32_t event, int handler)
	{
		if (auto it = m_EventHandlers.find(event); it != m_EventHandlers.end())
			it->second.push_back(handler);
		else
			m_EventHandlers.emplace(event, std::vector{handler});
	}

	bool LuaScript::DispatchEvent(std::uint32_t event, const DispatchEventCallback& add_arguments_cb, bool handle_result)
	{
		bool result = true;

		if (auto it = m_EventHandlers.find(event); it != m_EventHandlers.end())
		{
			for (auto& handler : it->second)
			{
				lua_rawgeti(m_State, LUA_REGISTRYINDEX, handler);
				auto num_args = add_arguments_cb(m_State);

				if (CallFunction(num_args, 1))
				{
					if (!lua_isnoneornil(m_State, -1))
					{
						if (lua_toboolean(m_State, -1) == false)
						{
							result = false;
						}
					}

					lua_pop(m_State, 1);
				}
				
				if (!result && handle_result)
					return false;
			}
		}

		return result;
	}

	void LuaScript::AddResource(std::shared_ptr<LuaResource>&& resource, int idx)
	{
		resource->SetType(idx); // TODO: this is a bad idea
		auto type = LuaManager::GetResourceType(idx);
		type->Lock();
		m_Resources[resource->GetType()].push_back(std::move(resource));
		type->Unlock();
	}

	int LuaScript::GetNumResourcesOfType(int type)
	{
		return m_Resources[type].size();
	}

	std::vector<std::shared_ptr<LuaResource>>& LuaScript::GetAllResourcesOfType(int idx)
	{
		return m_Resources[idx];
	}
	
	void LuaScript::ScriptCallback::SetTimeToResume(int millis)
	{
		if (millis == 0)
		{
			m_TimeToResume = std::nullopt;
		}
		else
		{
			m_TimeToResume = std::chrono::high_resolution_clock::now() + std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(std::chrono::milliseconds(static_cast<std::uint64_t>(millis)));
		}
	}
}