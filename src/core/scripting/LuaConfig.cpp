#include "LuaConfig.hpp"
#include "core/filemgr/FileMgr.hpp"

namespace YimMenu
{
	LuaConfig::LuaConfig(std::string_view script_name) :
	    m_ConfigFile(FileMgr::GetProjectFile(std::string("./scripts/config/") + script_name.data() + ".json")),
	    m_Dirty(false)
	{
	}

	void LuaConfig::Load()
	{
		if (m_ConfigFile.Exists())
		{
			try
			{
				std::ifstream stream(m_ConfigFile.Path());

				nlohmann::json json;
				stream >> json;
				stream.close();

				for (auto& [key, value] : json["item_states"].items())
				{
					auto as_uint = std::stol(key.c_str());
					m_ItemStates.emplace(as_uint, value);
				}
			}
			catch (const std::exception& e)
			{
				LOGF(FATAL, "Error loading config file {}: {}", m_ConfigFile.Path().filename().string(), e.what());
				std::filesystem::remove(m_ConfigFile.Path()); // TODO: this is probably a bad idea
			}
		}
	}

	void LuaConfig::Update()
	{
		if (!m_Dirty)
			return;

		try
		{
			std::lock_guard lock(m_Mutex);

			nlohmann::json json;

			json["item_states"] = nlohmann::json::object();

			for (auto& [key, value] : m_ItemStates)
			{
				json[std::to_string(key)] = value;
			}

			std::ofstream stream(m_ConfigFile.Path());
			stream << json;
			stream.close();
		}
		catch (const std::exception& e)
		{
			LOGF(FATAL, "Error saving config file {}: {}", m_ConfigFile.Path().filename().string(), e.what());
		}
	}

	std::optional<nlohmann::json> LuaConfig::GetItemState(std::uint32_t hash)
	{
		// no need to lock when we're just reading from the array

		if (auto it = m_ItemStates.find(hash); it != m_ItemStates.end())
			return it->second;
		else
			return std::nullopt;
	}

	void LuaConfig::SetItemState(std::uint32_t hash, nlohmann::json value)
	{
		std::lock_guard lock(m_Mutex);

		if (auto it = m_ItemStates.find(hash); it != m_ItemStates.end())
			it->second = value;
		else
			m_ItemStates.emplace(hash, value);
	}
}