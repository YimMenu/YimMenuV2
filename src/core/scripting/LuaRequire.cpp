#include "LuaRequire.hpp"
#include "core/filemgr/FileMgr.hpp"

#include <set>

namespace YimMenu::Lua
{
	namespace fs = std::filesystem;

	static fs::path NormalizePath(const fs::path& path)
	{
		auto name = path.native();
		if (name.starts_with(L"\\\\?\\UNC\\"))
			name = L"\\\\" + name.substr(8);
		else if (name.starts_with(L"\\\\?\\"))
			name.erase(0, 4);
		return fs::path(name).lexically_normal();
	}

	static fs::path ScriptsRoot()
	{
		return NormalizePath(fs::canonical(FileMgr::GetProjectFolder("./scripts").Path()));
	}

	static bool IsDescendant(const fs::path& path, const fs::path& root)
	{
		auto relative = path.lexically_relative(root);
		return !relative.empty() && relative != "." && !relative.has_root_path() && *relative.begin() != "..";
	}

	static bool IsScriptFile(const fs::path& path, const fs::path& root)
	{
		return IsDescendant(path, root) && path.extension() == ".lua" && !path.lexically_relative(root).parent_path().native().contains(L"disabled");
	}

	static bool PushSearchPath(lua_State* state)
	{
		try
		{
			auto root = ScriptsRoot();
			std::set<fs::path> folders;
			for (fs::recursive_directory_iterator entry(root, fs::directory_options::skip_permission_denied), end; entry != end; ++entry)
			{
				if (!entry->is_directory())
					continue;
				if (entry->path().lexically_relative(root).native().contains(L"disabled"))
				{
					entry.disable_recursion_pending();
					continue;
				}
				auto folder = NormalizePath(fs::canonical(entry->path()));
				if (!IsDescendant(folder, root) || folder.lexically_relative(root).native().contains(L"disabled"))
				{
					entry.disable_recursion_pending();
					continue;
				}
				folders.insert(folder);
				if (GetFileAttributesW(entry->path().c_str()) & FILE_ATTRIBUTE_REPARSE_POINT)
					entry.disable_recursion_pending();
			}

			std::string search_path;
			auto add_folder = [&search_path](const fs::path& folder) {
				auto name = folder.string();
				search_path += name + "/?.lua;" + name + "/?/init.lua;";
			};
			add_folder(root);
			for (const auto& folder : folders)
				add_folder(folder);
			search_path.pop_back();
			lua_pushlstring(state, search_path.data(), search_path.size());
			return true;
		}
		catch (const std::exception& error)
		{
			lua_pushstring(state, error.what());
			return false;
		}
	}

	static bool PushModuleName(lua_State* state, std::string_view module_name)
	{
		try
		{
			if (module_name.empty() || module_name.find('\0') != std::string_view::npos || module_name.find(':') != std::string_view::npos)
			{
				lua_pushliteral(state, "invalid module name");
				return false;
			}

			std::string name(module_name);
			std::replace(name.begin(), name.end(), '\\', '/');
			bool explicit_file = name.ends_with(".lua");
			if (explicit_file)
				name.resize(name.size() - 4);
			if (name.empty())
			{
				lua_pushliteral(state, "invalid module name");
				return false;
			}
			if (!explicit_file && name.find('/') == std::string::npos)
			{
				if (name.front() == '.' || name.back() == '.' || name.contains(".."))
				{
					lua_pushliteral(state, "invalid module name");
					return false;
				}
				std::replace(name.begin(), name.end(), '.', '/');
			}

			auto relative = fs::path(name);
			if (relative.has_root_path())
			{
				lua_pushliteral(state, "module paths must be relative to the scripts directory");
				return false;
			}
			for (const auto& component : relative)
			{
				if (component.empty() || component == "." || component == "..")
				{
					lua_pushliteral(state, "module path traversal is not allowed");
					return false;
				}
			}
			if (relative.parent_path().native().contains(L"disabled"))
			{
				lua_pushliteral(state, "module paths through disabled folders are not allowed");
				return false;
			}

			lua_pushlstring(state, name.data(), name.size());
			return true;
		}
		catch (const std::exception& error)
		{
			lua_pushstring(state, error.what());
		}
		return false;
	}

	static bool PushModuleChunk(lua_State* state, const char* filename)
	{
		try
		{
			auto path = fs::path(filename);
			auto handle = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
			if (handle == INVALID_HANDLE_VALUE)
			{
				lua_pushfstring(state, "cannot open module '%s'", filename);
				return false;
			}
			std::unique_ptr<void, decltype(&CloseHandle)> file(handle, &CloseHandle);

			// Validate the opened file as well, so replacing a link after resolution cannot escape the sandbox.
			auto length = GetFinalPathNameByHandleW(handle, nullptr, 0, FILE_NAME_NORMALIZED | VOLUME_NAME_DOS);
			std::wstring final_name(length, L'\0');
			auto written = length ? GetFinalPathNameByHandleW(handle, final_name.data(), length, FILE_NAME_NORMALIZED | VOLUME_NAME_DOS) : 0;
			if (!written || written >= length)
			{
				lua_pushliteral(state, "cannot resolve the opened module path");
				return false;
			}
			final_name.resize(written);
			auto resolved = NormalizePath(fs::path(final_name));
			if (!IsScriptFile(resolved, ScriptsRoot()))
			{
				lua_pushliteral(state, "opened module is outside the scripts directory, in a disabled folder, or is not a Lua file");
				return false;
			}

			std::string source;
			std::array<char, 4096> buffer;
			DWORD bytes_read;
			while (true)
			{
				if (!ReadFile(handle, buffer.data(), static_cast<DWORD>(buffer.size()), &bytes_read, nullptr))
				{
					lua_pushfstring(state, "cannot read module '%s'", filename);
					return false;
				}
				if (!bytes_read)
					break;
				source.append(buffer.data(), bytes_read);
			}
			auto chunk_name = "@" + resolved.string();
			return luaL_loadbufferx(state, source.data(), source.size(), chunk_name.c_str(), "t") == LUA_OK;
		}
		catch (const std::exception& error)
		{
			lua_pushstring(state, error.what());
			return false;
		}
	}

	static bool PushResolvedModulePath(lua_State* state, const char* filename)
	{
		try
		{
			auto root = ScriptsRoot();
			auto requested = NormalizePath(fs::absolute(fs::path(filename)));
			auto resolved = NormalizePath(fs::canonical(requested));
			bool disabled_path = IsDescendant(requested, root) && requested.lexically_relative(root).parent_path().native().contains(L"disabled");
			if (disabled_path || !IsScriptFile(resolved, root) || !fs::is_regular_file(resolved))
			{
				lua_pushliteral(state, "module must be a Lua file inside the scripts directory and outside disabled folders");
				return false;
			}
			auto name = resolved.string();
			lua_pushlstring(state, name.data(), name.size());
			return true;
		}
		catch (const std::exception& error)
		{
			lua_pushstring(state, error.what());
			return false;
		}
	}

	static bool PushModulePath(lua_State* state, std::string_view name, std::string_view search_path)
	{
		try
		{
			while (!search_path.empty())
			{
				auto separator = search_path.find(';');
				std::string filename(search_path.substr(0, separator));
				if (separator == std::string_view::npos)
					search_path = {};
				else
					search_path.remove_prefix(separator + 1);
				if (filename.empty())
					continue;
				for (std::size_t mark = filename.find('?'); mark != std::string::npos; mark = filename.find('?', mark + name.size()))
					filename.replace(mark, 1, name);
				std::error_code ec;
				if (!fs::is_regular_file(fs::path(filename), ec))
					continue;
				lua_pushlstring(state, filename.data(), filename.size());
				return true;
			}
			lua_pushfstring(state, "\n\tno Lua file for module '%s' in package.path", name.data());
		}
		catch (const std::exception& error)
		{
			lua_pushstring(state, error.what());
		}
		return false;
	}

	static int LuaFileSearcher(lua_State* state)
	{
		luaL_checktype(state, 1, LUA_TSTRING);
		std::size_t length;
		auto name = lua_tolstring(state, 1, &length);
		lua_settop(state, 1);
		if (!PushModuleName(state, std::string_view(name, length)))
			return lua_error(state);

		lua_getfield(state, lua_upvalueindex(1), "path");
		luaL_checktype(state, -1, LUA_TSTRING);
		std::size_t path_length;
		auto search_path = lua_tolstring(state, -1, &path_length);
		std::size_t name_length;
		auto normalized_name = lua_tolstring(state, 2, &name_length);
		if (!PushModulePath(state, std::string_view(normalized_name, name_length), std::string_view(search_path, path_length)))
			return 1;
		if (!PushResolvedModulePath(state, lua_tostring(state, -1)))
			return lua_error(state);
		if (!PushModuleChunk(state, lua_tostring(state, -1)))
			return lua_error(state);
		return 1;
	}

	static int CheckedRequire(lua_State* state)
	{
		luaL_checktype(state, 1, LUA_TSTRING);
		std::size_t length;
		auto name = lua_tolstring(state, 1, &length);
		if (!PushModuleName(state, std::string_view(name, length)))
			return lua_error(state);
		lua_pop(state, 1);
		lua_pushvalue(state, lua_upvalueindex(1));
		lua_pushvalue(state, 1);
		lua_call(state, 1, 1);
		return 1;
	}

	static int NotSupported(lua_State* state)
	{
		return luaL_error(state, "%s is not supported", lua_tostring(state, lua_upvalueindex(1)));
	}

	void RegisterRequire(lua_State* state)
	{
		lua_getglobal(state, "package");
		if (!PushSearchPath(state))
			lua_error(state);
		lua_setfield(state, -2, "path");
		lua_pushliteral(state, "");
		lua_setfield(state, -2, "cpath");
		lua_pushliteral(state, "package.loadlib");
		lua_pushcclosure(state, NotSupported, 1);
		lua_setfield(state, -2, "loadlib");

		lua_newtable(state);
		lua_pushvalue(state, -1);
		lua_setfield(state, LUA_REGISTRYINDEX, "_LOADED");
		lua_setfield(state, -2, "loaded");
		lua_newtable(state);
		lua_pushvalue(state, -1);
		lua_setfield(state, LUA_REGISTRYINDEX, "_PRELOAD");
		lua_setfield(state, -2, "preload");

		lua_newtable(state);
		lua_pushvalue(state, -2);
		lua_pushcclosure(state, LuaFileSearcher, 1);
		lua_rawseti(state, -2, 1);
		lua_pushvalue(state, -1);
		lua_setfield(state, -3, "loaders");
		lua_setfield(state, -2, "searchers");
		lua_pop(state, 1);

		for (const auto name : std::to_array({"load", "loadstring", "loadfile", "dofile"}))
		{
			lua_pushstring(state, name);
			lua_pushcclosure(state, NotSupported, 1);
			lua_setglobal(state, name);
		}
		lua_getglobal(state, "require");
		lua_pushcclosure(state, CheckedRequire, 1);
		lua_setglobal(state, "require");
	}
}
