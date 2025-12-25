#pragma once
#include "LuaScript.hpp"
#include "LuaLibrary.hpp"
#include "LuaResource.hpp"

namespace YimMenu
{
	// note to future self: Lua is a horrible language and should never be used
	class LuaManager
	{
	public:
		struct UnloadedScript
		{
			std::string m_Name;
			std::string m_Path;
		};

		using ForAllLoadedScriptsCallback = void(*)(std::shared_ptr<LuaScript>& script);
		using ForAllUnloadedScriptsCallback = void(*)(UnloadedScript& script);
		using ForAllResourcesOfTypeCallback = void(*)(LuaResource* resource);

	private:
		std::vector<std::shared_ptr<LuaScript>> m_LoadedScripts;
		std::vector<UnloadedScript> m_UnloadedScripts;
		std::chrono::system_clock::time_point m_LastRefreshedUnloadedScripts;
		std::vector<LuaLibrary*> m_Libraries;
		std::vector<LuaResourceType*> m_ResourceTypes;
		std::queue<std::string> m_ScriptsToLoad;
		std::mutex m_LoadMutex;
		std::uint32_t m_MainThreadId;
		lua_State* m_RunningCoroutine = nullptr;

		// m_LoadMutex MUST be locked when calling this function
		void AddUnloadedScript(std::string_view name, std::string_view path);

		void RegisterLibraryImpl(LuaLibrary* library);
		int RegisterResourceTypeImpl(LuaResourceType* res_type); // returns resource index
		int GetNumResourceTypesImpl();
		LuaResourceType* GetResourceTypeImpl(int index);
		void LoadLibrariesImpl(lua_State* state);
		void LoadScriptImpl(std::string path);
		void RunScriptImpl();
		bool IsRunningInMainThreadImpl();
		void SetRunningCoroutineImpl(lua_State* script);
		void ForAllLoadedScriptsImpl(ForAllLoadedScriptsCallback callback);
		void ForAllUnloadedScriptsImpl(ForAllUnloadedScriptsCallback callback);
		bool DispatchEventImpl(std::uint32_t event, const LuaScript::DispatchEventCallback& add_arguments_cb, bool handle_result = false);
		void ForAllResourcesOfTypeImpl(ForAllResourcesOfTypeCallback callback, int type);

		static LuaManager& GetInstance()
		{
			static LuaManager instance;
			return instance;
		}

	public:
		static void RegisterLibrary(LuaLibrary* library)
		{
			GetInstance().RegisterLibraryImpl(library);
		}

		static int RegisterResourceType(LuaResourceType* res_type)
		{
			return GetInstance().RegisterResourceTypeImpl(res_type);
		}

		static int GetNumResourceTypes()
		{
			return GetInstance().GetNumResourceTypesImpl();
		}

		static LuaResourceType* GetResourceType(int index)
		{
			return GetInstance().GetResourceTypeImpl(index);
		}

		static void LoadLibraries(lua_State* state)
		{
			GetInstance().LoadLibrariesImpl(state);
		}

		static void LoadScript(std::string file_name)
		{
			GetInstance().LoadScriptImpl(file_name);
		}

		static void RunScript()
		{
			GetInstance().RunScriptImpl();
		}

		static bool IsRunningInMainThread()
		{
			return GetInstance().IsRunningInMainThreadImpl();
		}

		static void SetRunningCoroutine(lua_State* script)
		{
			GetInstance().SetRunningCoroutineImpl(script);
		}

		static lua_State* GetRunningCoroutine()
		{
			return GetInstance().m_RunningCoroutine;
		}

		// these can be safely called from the DX thread
		static void ForAllLoadedScripts(ForAllLoadedScriptsCallback callback)
		{
			GetInstance().ForAllLoadedScriptsImpl(callback);
		}

		static void ForAllUnloadedScripts(ForAllUnloadedScriptsCallback callback)
		{
			GetInstance().ForAllUnloadedScriptsImpl(callback);
		}

		// if handle_result is true, the event will be blocked when a callback returns false
		// events MUST be dispatched from the main thread
		static bool DispatchEvent(std::uint32_t event, const LuaScript::DispatchEventCallback& add_arguments_cb, bool handle_result = false)
		{
			return GetInstance().DispatchEventImpl(event, add_arguments_cb, handle_result);
		}
	};
}