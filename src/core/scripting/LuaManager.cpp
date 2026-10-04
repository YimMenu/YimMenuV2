#include "LuaManager.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "types/script/scrThread.hpp"
#include "core/util/Joaat.hpp"

namespace YimMenu
{
	void LuaManager::AddUnloadedScript(std::string_view name, std::string_view path)
	{
		if (IsIncludeScript(std::filesystem::path(path)))
			return;
		m_UnloadedScripts.push_back({std::string(name), std::string(path)});
	}

	void LuaManager::RegisterLibraryImpl(LuaLibrary* library)
	{
		m_Libraries.push_back(library);
	}

	int LuaManager::RegisterResourceTypeImpl(LuaResourceType* res_type)
	{
		m_ResourceTypes.push_back(res_type);
		return m_ResourceTypes.size() - 1;
	}

	int LuaManager::GetNumResourceTypesImpl()
	{
		return m_ResourceTypes.size();
	}

	LuaResourceType* LuaManager::GetResourceTypeImpl(int index)
	{
		return m_ResourceTypes[index];
	}

	void LuaManager::LoadLibrariesImpl(lua_State* state)
	{
		for (auto library : m_Libraries)
			library->Register(state);
	}

	void LuaManager::LoadScriptImpl(std::string path)
	{
		if (std::filesystem::path(path).extension() != ".lua" || IsIncludeScript(std::filesystem::path(path)))
			return;
		std::lock_guard lock(m_LoadMutex);
		m_ScriptsToLoad.push({std::move(path), true});
	}

	void LuaManager::DisableScriptImpl(std::string path)
	{
		std::lock_guard lock(m_LoadMutex);
		if (std::find(m_ScriptsToDisable.begin(), m_ScriptsToDisable.end(), path) == m_ScriptsToDisable.end())
			m_ScriptsToDisable.push_back(std::move(path));
	}

	void LuaManager::RunScriptImpl()
	{
		m_MainThreadId = GetCurrentThreadId();

		auto scripts_dir = FileMgr::GetProjectFolder("./scripts");
		for (const auto& script : DiscoverScripts(scripts_dir.Path(), false))
			m_ScriptsToLoad.push({script.string(), false});

		while (g_Running)
		{
			{
				// 1) process new load requests
				std::lock_guard lock(m_LoadMutex);
				while (!m_ScriptsToLoad.empty())
				{
					auto request = std::move(m_ScriptsToLoad.front());
					m_ScriptsToLoad.pop();
					auto path = request.m_Path;
					if (IsIncludeScript(std::filesystem::path(path)))
						continue;
					if (std::ranges::any_of(m_LoadedScripts, [&path](const auto& script) {
						    std::error_code ec;
						    return std::filesystem::equivalent(path, script->GetPath(), ec);
					    }))
						continue;
					if (request.m_Enable)
					{
						try
						{
							path = MoveScriptFile(path, scripts_dir.Path(), true).string();
						}
						catch (const std::filesystem::filesystem_error& error)
						{
							Notifications::Show("Lua Scripts", error.what(), NotificationType::Error);
							continue;
						}
					}
					std::erase_if(m_UnloadedScripts, [&path, &request](auto& script) {
						std::error_code ec;
						return script.m_Path == request.m_Path || std::filesystem::equivalent(path, script.m_Path, ec);
					});
					m_LoadedScripts.push_back(std::make_shared<LuaScript>(path));
				}

				std::erase_if(m_ScriptsToDisable, [this, &scripts_dir](const std::string& path) {
					auto found = std::ranges::find_if(m_LoadedScripts, [&path](const auto& script) {
						return script->GetPath() == path;
					});
					if (found == m_LoadedScripts.end())
						return true;
					auto& script = *found;
					if (!script->IsRunning())
						return true;
					if (!script->SafeToUnload())
						return false;
					try
					{
						auto destination = MoveScriptFile(std::filesystem::path(path), scripts_dir.Path(), false);
						script->SetPath(destination.string());
						script->Unload();
					}
					catch (const std::filesystem::filesystem_error& error)
					{
						Notifications::Show("Lua Scripts", error.what(), NotificationType::Error);
					}
					return true;
				});

				// 2) remove scripts if needed
				std::erase_if(m_LoadedScripts, [this](auto& script) {
					if (!script->SafeToUnload())
						return false;

					bool unload = false;

					if (script->IsMalfunctioning())
					{
						Notifications::Show("Lua Scripting", std::format("Script {} has been unloaded due to a malfunction. Check the console for more details", script->GetName()), NotificationType::Warning);
						unload = true;
					}
					else if (script->GetLoadState() == LuaScript::LoadState::WANT_UNLOAD)
					{
						unload = true;
					}
					else if (script->GetLoadState() == LuaScript::LoadState::WANT_RELOAD)
					{
						m_ScriptsToLoad.push({std::string(script->GetPath()), false}); // will be reloaded next tick
						unload = true;
					}

					if (unload)
					{
						script->MarkUnloaded();
						AddUnloadedScript(script->GetName(), script->GetPath());
					}

					return unload;
				});

				// 3) refresh unloaded scripts (every 10 seconds)
				if (m_LastRefreshedUnloadedScripts + 10s < std::chrono::system_clock::now())
				{
					m_UnloadedScripts.clear();
					for (const auto& path : DiscoverScripts(scripts_dir.Path()))
					{
						if (std::ranges::any_of(m_LoadedScripts, [&path](const auto& script) {
							    std::error_code ec;
							    return std::filesystem::equivalent(script->GetPath(), path, ec);
						    }))
							continue;
						AddUnloadedScript(path.filename().string(), path.string());
					}
					m_LastRefreshedUnloadedScripts = std::chrono::system_clock::now();
				}
			}

			// don't run stuff while we're starting up
			if (rage::scrThread::GetRunningThread()->m_ScriptHash != "startup"_J)
			{
				// 4) run tick coroutines
				for (auto& script : m_LoadedScripts)
					if (script->IsRunning())
						script->Tick();
			}

			ScriptMgr::Yield();
		}
	}

	bool LuaManager::IsRunningInMainThreadImpl()
	{
		return GetCurrentThreadId() == m_MainThreadId;
	}

	void LuaManager::SetRunningCoroutineImpl(lua_State* script)
	{
		if (!m_RunningCoroutine || !script)
		{
			m_RunningCoroutine = script;
		}
		else
		{
			LOGF(FATAL, "LuaManager::SetRunningCoroutineImpl: {} attempted to enter a coroutine when a coroutine from {} is already running", LuaScript::GetScript(script).GetName(), LuaScript::GetScript(m_RunningCoroutine).GetName());
			LuaScript::GetScript(script).SetMalfunctioning();
		}
	}

	void LuaManager::ForAllLoadedScriptsImpl(ForAllLoadedScriptsCallback callback)
	{
		std::lock_guard lock(m_LoadMutex);
		for (auto& script : m_LoadedScripts)
			callback(script);
	}

	void LuaManager::ForAllUnloadedScriptsImpl(ForAllUnloadedScriptsCallback callback)
	{
		std::lock_guard lock(m_LoadMutex);
		for (auto& script : m_UnloadedScripts)
			callback(script);
	}

	bool LuaManager::DispatchEventImpl(MenuEvent event, const LuaScript::DispatchEventCallback& add_arguments_cb, bool handle_result)
	{
		auto result = true;

		for (auto& script : m_LoadedScripts)
		{
			if (script->IsRunning())
			{
				result = (bool)(((int)result) & ((int)script->DispatchEvent(event, add_arguments_cb, handle_result)));
				if (!result && handle_result)
					return false;
			}
		}

		return result;
	}

	void LuaManager::ForAllResourcesOfTypeImpl(ForAllResourcesOfTypeCallback callback, int type)
	{
		auto _type = GetResourceType(type);
		bool locked = false;
		for (auto& script : m_LoadedScripts)
		{
			if (script->IsRunning())
			{
				auto& resources = script->GetAllResourcesOfType(type);
				if (resources.size() > 0)
				{
					if (!locked)
					{
						_type->Lock();
						locked = true;
					}

					for (auto& resource : resources)
					{
						callback(resource.get());
					}
				}
			}
		}
		if (locked)
			_type->Unlock();
	}
}
