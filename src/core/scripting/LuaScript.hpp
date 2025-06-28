#pragma once
#include "lua.hpp"

namespace YimMenu
{
	class LuaScript
	{
	public:
		enum class LoadState
		{
			EMPTY,
			RUNNING,
			PAUSED,
			WANT_UNLOAD,
			WANT_RELOAD,
			UNLOADED
		};

		struct ScriptCallback
		{
			int m_Coroutine;
			std::optional<std::chrono::high_resolution_clock::time_point> m_TimeToResume;
			bool m_LastYieldFromCode;
			PVOID m_Fiber;
			PVOID m_ParentFiber;
			lua_CFunction m_LatentTarget;
			lua_State* m_CoroState;
			int m_LastReturnValue;

			void SetTimeToResume(int millis);
		};

		using DispatchEventCallback = std::function<int(lua_State* state)>;

	private:
		LoadState m_LoadState = LoadState::EMPTY;
		lua_State* m_State = nullptr;
		std::string m_FileName;
		std::string m_ModuleName;
		bool m_IsMalfunctioning = false; // when this is set to true, the script will be unloaded next tick
		std::vector<ScriptCallback> m_ScriptCallbacks;
		std::vector<ScriptCallback> m_QueuedScriptCallbacks;
		bool m_RunningScriptCallbacks = false;
		ScriptCallback* m_CurrentlyExecutingCallback = nullptr;
		std::unordered_map<std::uint32_t, std::vector<int>> m_EventHandlers;
		bool m_NativesLoaded = false; // TODO: move this to a LuaResource

		// Calls the function at the top of stack. If this returns false the stack would have nothing on it
		bool CallFunction(int n_args, int n_results, lua_State* override_state = nullptr);
		int ResumeCoroutine(int n_args, int n_results, lua_State* coro_state);
		void RemoveScriptCallback(ScriptCallback& callback);

	public:
		LuaScript(std::string_view file_name);
		~LuaScript();

		bool IsMalfunctioning() const
		{
			return m_IsMalfunctioning;
		}

		bool IsValid() const
		{
			return m_LoadState == LoadState::RUNNING;
		}

		LoadState GetLoadState() const
		{
			return m_LoadState;
		}

		void SetMalfunctioning()
		{
			m_IsMalfunctioning = true;
		}

		void Unload()
		{
			if (m_LoadState == LoadState::RUNNING)
				m_LoadState = LoadState::WANT_UNLOAD;
		}

		void Reload()
		{
			if (m_LoadState == LoadState::RUNNING)
				m_LoadState = LoadState::WANT_RELOAD;
		}
		
		void Pause()
		{
			if (m_LoadState == LoadState::RUNNING)
				m_LoadState = LoadState::PAUSED;
		}

		void Resume()
		{
			if (m_LoadState == LoadState::PAUSED)
				m_LoadState = LoadState::RUNNING;
		}

		// Should only be called by LuaManager::RunScriptImpl
		void MarkUnloaded()
		{
			m_LoadState = LoadState::UNLOADED;
		}

		bool SafeToUnload();

		std::string_view GetName()
		{
			return m_ModuleName;
		}

		std::string_view GetPath()
		{
			return m_FileName;
		}

		// we're guaranteed to have a LuaScript for each lua_State, so we can return it as a reference
		static LuaScript& GetScript(lua_State* state);


		void AddScriptCallback(int coro_handle);

		// must be called from a coroutine
		void Yield(lua_State* state, int millis = 0, bool from_code = true);

		void Tick();

		ScriptCallback* GetRunningCallback()
		{
			return m_CurrentlyExecutingCallback;
		}

		void AddEventHandler(std::uint32_t event, int handler);
		bool DispatchEvent(std::uint32_t event, const DispatchEventCallback& add_arguments_cb, bool handle_result = false);

		// ------- TODO: move these into a resource

		bool AreNativesLoaded() const
		{
			return m_NativesLoaded;
		}

		void SetNativesLoaded()
		{
			m_NativesLoaded = true;
		}

		// --------------
	};
}