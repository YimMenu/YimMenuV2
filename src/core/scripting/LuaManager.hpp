#pragma once
#include "core/filemgr/FileMgr.hpp"
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
		struct LoadRequest
		{
			std::string m_Path;
			bool m_Enable;
		};

		std::vector<std::shared_ptr<LuaScript>> m_LoadedScripts;
		std::vector<UnloadedScript> m_UnloadedScripts;
		std::chrono::system_clock::time_point m_LastRefreshedUnloadedScripts;
		std::vector<LuaLibrary*> m_Libraries;
		std::vector<LuaResourceType*> m_ResourceTypes;
		std::queue<LoadRequest> m_ScriptsToLoad;
		std::vector<std::string> m_ScriptsToDisable;
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
		void DisableScriptImpl(std::string path);
		void RunScriptImpl();
		bool IsRunningInMainThreadImpl();
		void SetRunningCoroutineImpl(lua_State* script);
		void ForAllLoadedScriptsImpl(ForAllLoadedScriptsCallback callback);
		void ForAllUnloadedScriptsImpl(ForAllUnloadedScriptsCallback callback);
		bool DispatchEventImpl(MenuEvent event, const LuaScript::DispatchEventCallback& add_arguments_cb, bool handle_result = false);
		void ForAllResourcesOfTypeImpl(ForAllResourcesOfTypeCallback callback, int type);

		static LuaManager& GetInstance()
		{
			static LuaManager instance;
			return instance;
		}

	public:
		static bool IsIncludeScript(const std::filesystem::path& path, const std::filesystem::path& scripts_folder = FileMgr::GetProjectFolder("./scripts").Path())
		{
			auto root = scripts_folder.lexically_normal();
			auto file = (path.is_absolute() ? path : root / path).lexically_normal();
			auto relative = file.lexically_relative(root);
			if (relative.empty() || relative.has_root_path() || *relative.begin() == "..")
				return false;
			return std::ranges::any_of(relative.parent_path(), [](const std::filesystem::path& folder) {
				return folder.string().contains("include");
			});
		}

		static std::filesystem::path MoveScriptFile(const std::filesystem::path& path, const std::filesystem::path& scripts_folder, bool enable)
		{
			namespace fs = std::filesystem;
			auto root = fs::canonical(scripts_folder);
			auto source = fs::canonical(path);
			auto relative = source.lexically_relative(root);
			if (relative.empty() || relative.has_root_path() || *relative.begin() == ".." || source.extension() != ".lua" || IsIncludeScript(source, root) || !fs::is_regular_file(source))
				throw fs::filesystem_error("script is outside the scripts directory or is an include file", source, std::make_error_code(std::errc::invalid_argument));
			if (*relative.begin() == "disabled")
				relative = relative.lexically_relative("disabled");
			if (enable && std::ranges::any_of(relative.parent_path(), [](const fs::path& component) {
				    return component.string().contains("disabled");
				}))
				relative = source.filename();
			auto destination = (enable ? root : root / "disabled") / relative;
			if (source == destination)
				return source;
			if (fs::weakly_canonical(destination.parent_path()) != destination.parent_path())
				throw fs::filesystem_error("script destination must not be a linked directory", destination, std::make_error_code(std::errc::invalid_argument));
			if (fs::exists(fs::symlink_status(destination)))
				throw fs::filesystem_error("another script already has this name", source, destination, std::make_error_code(std::errc::file_exists));
			fs::create_directories(destination.parent_path());
			fs::rename(source, destination);
			return destination;
		}

		static std::vector<std::filesystem::path> DiscoverScripts(const std::filesystem::path& scripts_folder, bool include_disabled = true)
		{
			namespace fs = std::filesystem;
			std::vector<fs::path> scripts;
			std::error_code ec;
			auto root = fs::canonical(scripts_folder, ec);
			if (ec)
				return scripts;
			auto disabled_folder = [&root](const fs::path& path) {
				auto relative = path.lexically_relative(root);
				return std::ranges::any_of(relative, [](const fs::path& component) {
					return component.string().contains("disabled");
				});
			};

			for (fs::recursive_directory_iterator entry(root, fs::directory_options::skip_permission_denied, ec), end; entry != end; entry.increment(ec))
			{
				if (entry->is_directory(ec))
				{
					auto folder = fs::canonical(entry->path(), ec);
					if (ec || folder != entry->path() || folder.filename().string().contains("include") || (!include_disabled && disabled_folder(folder)))
						entry.disable_recursion_pending();
					continue;
				}
				if (entry->path().extension() != ".lua" || IsIncludeScript(entry->path(), root) || !entry->is_regular_file(ec))
					continue;

				auto file = fs::canonical(entry->path(), ec);
				if (ec || IsIncludeScript(file, root) || (!include_disabled && disabled_folder(file.parent_path())))
					continue;
				auto relative = file.lexically_relative(root);
				if (relative.empty() || relative.has_root_path() || *relative.begin() == "..")
					continue;
				scripts.push_back(std::move(file));
			}
			std::sort(scripts.begin(), scripts.end());
			scripts.erase(std::unique(scripts.begin(), scripts.end()), scripts.end());
			return scripts;
		}

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

		static void DisableScript(std::string file_name)
		{
			GetInstance().DisableScriptImpl(std::move(file_name));
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
		static bool DispatchEvent(MenuEvent event, const LuaScript::DispatchEventCallback& add_arguments_cb, bool handle_result = false)
		{
			return GetInstance().DispatchEventImpl(event, add_arguments_cb, handle_result);
		}
	};
}
