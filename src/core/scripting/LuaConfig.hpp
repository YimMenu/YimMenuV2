#pragma once
#include "core/filemgr/File.hpp"

namespace YimMenu
{
	class LuaConfig
	{
		bool m_Dirty;
		File m_ConfigFile;
		std::mutex m_Mutex;
		
		std::unordered_map<std::uint32_t, nlohmann::json> m_ItemStates;

	public:
		LuaConfig(std::string_view script_name);
		// call when a script is loaded
		void Load();
		// should be called every now and then (10s?) and before unload
		void Update();
		std::optional<nlohmann::json> GetItemState(std::uint32_t hash);
		void SetItemState(std::uint32_t hash, nlohmann::json value);
	};
}