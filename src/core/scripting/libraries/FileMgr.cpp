#include "core/filemgr/FileMgr.hpp"
#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"

#undef DeleteFile

namespace YimMenu::Lua
{
	namespace fs = std::filesystem;

	static const fs::path& ScriptsRoot()
	{
		static const fs::path root = [] {
			std::error_code ec;
			auto p = fs::weakly_canonical(YimMenu::FileMgr::GetProjectFolder("./scripts").Path(), ec);
			return ec ? YimMenu::FileMgr::GetProjectFolder("./scripts").Path() : p;
		}();
		return root;
	}

	static bool ResolveInSandbox(std::string_view input, fs::path& out)
	{
		if (input.empty() || input.find('\0') != std::string_view::npos || input.find(':') != std::string_view::npos)
			return false;

		fs::path p(std::string{input});
		if (p.has_root_path())
			return false;
		std::error_code ec;
		auto canon = fs::weakly_canonical(ScriptsRoot() / p, ec);
		if (ec)
			return false;

		auto rel = canon.lexically_relative(ScriptsRoot());
		if (rel.empty() || rel.has_root_path() || *rel.begin() == "..")
			return false;

		out = canon;
		return true;
	}

	static fs::path CheckSandboxedPath(lua_State* state, int idx)
	{
		std::size_t length = 0;
		auto raw = CheckStringSafe(state, idx, &length);
		fs::path out;
		if (!ResolveInSandbox(std::string_view(raw, length), out))
		{
			luaL_argerror(state, idx, "expected a relative path inside the scripts directory");
			return {};
		}
		return out;
	}

	class FileMgr : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int CreateDir(lua_State* state)
		{
			auto path = CheckSandboxedPath(state, 1);
			std::error_code ec;
			fs::create_directories(path, ec);
			lua_pushboolean(state, fs::is_directory(path, ec));
			return 1;
		}

		static int DeleteFile(lua_State* state)
		{
			auto path = CheckSandboxedPath(state, 1);
			if (path == ScriptsRoot())
				return 0;
			std::error_code ec;
			fs::remove(path, ec);
			return 0;
		}

		static int RenameFile(lua_State* state)
		{
			auto source = CheckSandboxedPath(state, 1);
			auto destination = CheckSandboxedPath(state, 2);
			std::error_code ec;
			bool success = fs::is_regular_file(source, ec) && !ec;
			if (success && source != destination)
				success = MoveFileW(source.c_str(), destination.c_str()) != FALSE;
			lua_pushboolean(state, success);
			return 1;
		}

		static int DoesFileExist(lua_State* state)
		{
			auto path = CheckSandboxedPath(state, 1);
			std::error_code ec;
			lua_pushboolean(state, fs::exists(path, ec));
			return 1;
		}

		static int FindFiles(lua_State* state)
		{
			auto path      = CheckSandboxedPath(state, 1);
			auto ext_raw   = std::string{CheckStringSafe(state, 2)};
			bool recursive = lua_isnoneornil(state, 3) ? false : CheckBooleanSafe(state, 3);

			std::string ext;
			if (!ext_raw.empty())
				ext = ext_raw.front() == '.' ? ext_raw : "." + ext_raw;

			lua_newtable(state);
			std::error_code ec;
			if (!fs::is_directory(path, ec))
				return 1;

			int idx = 1;
			auto emit = [&](const fs::directory_entry& entry) {
				if (!entry.is_regular_file(ec))
					return;
				if (!ext.empty() && entry.path().extension() != ext)
					return;
				auto relative = entry.path().lexically_relative(ScriptsRoot()).generic_string();
				fs::path resolved;
				if (!ResolveInSandbox(relative, resolved))
					return;
				lua_pushlstring(state, relative.data(), relative.size());
				lua_rawseti(state, -2, idx++);
			};

			if (recursive)
			{
				for (fs::recursive_directory_iterator entry(path, fs::directory_options::skip_permission_denied, ec), end; entry != end; entry.increment(ec))
				{
					if (entry->is_directory(ec))
					{
						auto directory = fs::canonical(entry->path(), ec);
						if (ec || directory != entry->path())
							entry.disable_recursion_pending();
					}
					else
					{
						emit(*entry);
					}
				}
			}
			else
				for (fs::directory_iterator entry(path, fs::directory_options::skip_permission_denied, ec), end; entry != end; entry.increment(ec))
					emit(*entry);

			return 1;
		}

		static int ReadFileContent(lua_State* state)
		{
			auto path = CheckSandboxedPath(state, 1);

			std::ifstream in(path, std::ios::binary);
			if (!in.is_open())
			{
				lua_pushlstring(state, "", 0);
				return 1;
			}

			std::string content((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
			lua_pushlstring(state, content.data(), content.size());
			return 1;
		}

		static int WriteFileContent(lua_State* state)
		{
			auto path = CheckSandboxedPath(state, 1);

			std::size_t len = 0;
			auto body       = CheckStringSafe(state, 2, &len);
			bool append     = lua_isnoneornil(state, 3) ? false : CheckBooleanSafe(state, 3);

			auto mode = std::ios::binary | (append ? std::ios::app : std::ios::trunc);
			std::ofstream out(path, mode);
			if (!out.is_open())
			{
				lua_pushboolean(state, false);
				return 1;
			}

			out.write(body, static_cast<std::streamsize>(len));
			lua_pushboolean(state, static_cast<bool>(out));
			return 1;
		}

		virtual void Register(lua_State* state) override
		{
			lua_newtable(state);
			SetFunction(state, CreateDir, "CreateDir");
			SetFunction(state, DeleteFile, "DeleteFile");
			SetFunction(state, RenameFile, "RenameFile");
			SetFunction(state, DoesFileExist, "DoesFileExist");
			SetFunction(state, FindFiles, "FindFiles");
			SetFunction(state, ReadFileContent, "ReadFileContent");
			SetFunction(state, WriteFileContent, "WriteFileContent");
			lua_setglobal(state, "FileMgr");
		}
	};

	FileMgr _FileMgr;
}
