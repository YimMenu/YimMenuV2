#pragma once
#include "lua.hpp"
#include "LuaResource.hpp"
#include "LuaConfig.hpp"
#include "LuaUserInterface.hpp"

namespace YimMenu
{
	enum class MenuEvent
	{
		PlayerLeave,
		PlayerJoin,
		ScriptedGameEventReceived,
		ChatMessageReceived,
		Unload
	};

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
			int m_InitialArgs = 0;

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
		std::unordered_map<MenuEvent, std::vector<int>> m_EventHandlers;
		std::vector<std::vector<std::shared_ptr<LuaResource>>> m_Resources; // yes, it's a shared pointer stored in a vector of resources stored in a vector of resource types TODO: can we just use raw pointers or even store the resource directly in that array?
		LuaConfig m_Config;
		LuaUserInterface m_Interface;
		
		std::recursive_mutex m_ExecutionLock;

		int ResumeCoroutine(int n_args, int n_results, lua_State* coro_state);
		void RemoveScriptCallback(ScriptCallback& callback);
		void DisableResources();
		void EnableResources();

	public:
		LuaScript(std::string_view file_name);
		~LuaScript();

		bool IsMalfunctioning() const
		{
			return m_IsMalfunctioning;
		}

		bool IsRunning() const
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

		void Unload();
		void Reload();
		void Pause();
		void Resume();

		// Should only be called by LuaManager::RunScriptImpl
		void MarkUnloaded();

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

		void AddScriptCallback(int func_handle, CallbackArg arg = {});

		// must be called from a coroutine
		void Yield(lua_State* state, int millis = 0, bool from_code = true);

		void Tick();

		ScriptCallback* GetRunningCallback()
		{
			return m_CurrentlyExecutingCallback;
		}
		
		bool CallFunction(int n_args, int n_results, lua_State* override_state = nullptr);
		void AddEventHandler(MenuEvent event, int handler);
		bool DispatchEvent(MenuEvent event, const DispatchEventCallback& add_arguments_cb, bool handle_result = false);

		// TODO: add RemoveResource
		void AddResource(std::shared_ptr<LuaResource>&& resource, int idx);
		int GetNumResourcesOfType(int type);
		std::vector<std::shared_ptr<LuaResource>>& GetAllResourcesOfType(int idx);

		LuaUserInterface& GetUserInterface()
		{
			return m_Interface;
		}

		lua_State* GetState() const
		{
			return m_State;
		}

		std::recursive_mutex& GetExecutionLock()
		{
			return m_ExecutionLock;
		}

		// Invokes a registered function ref from a non-script thread (the DX
		// render thread, for ImGui draw callbacks). Acquires m_ExecutionLock
		// for mutual exclusion with Tick(). The callback must not yield.
		void RunRenderCallback(int func_ref);
	};
}