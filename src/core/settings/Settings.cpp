#include "Settings.hpp"

#include "IStateSerializer.hpp"
#include "Settings.hpp"


namespace YimMenu
{
	namespace
	{
		bool ReadJson(const std::filesystem::path& path, nlohmann::json& output)
		{
			std::ifstream file(path);
			if (!file)
				return false;

			try
			{
				file >> output;
				return output.is_object();
			}
			catch (const std::exception&)
			{
				return false;
			}
		}

		bool WriteAtomically(const std::filesystem::path& destination, std::string_view contents)
		{
			auto temporary = destination;
			temporary += ".tmp";
			auto backup = destination;
			backup += ".bak";

			{
				std::ofstream file(temporary, std::ios::binary | std::ios::trunc);
				if (!file)
					return false;
				file.write(contents.data(), static_cast<std::streamsize>(contents.size()));
				file.flush();
				if (!file)
					return false;
			}

			const bool replaced = std::filesystem::exists(destination)
				? ReplaceFileW(destination.c_str(), temporary.c_str(), backup.c_str(), REPLACEFILE_WRITE_THROUGH, nullptr, nullptr)
				: MoveFileExW(temporary.c_str(), destination.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);

			if (!replaced)
			{
				std::error_code ec;
				std::filesystem::remove(temporary, ec);
			}
			return replaced;
		}
	}

	Settings::Settings() :
	    m_SettingsFile(),
	    m_StateSerializers(),
	    m_InitialLoadDone(false)
	{
	}

	void Settings::InitializeImpl(File settingsFile)
	{
		m_SettingsFile = settingsFile;

		if (!settingsFile.Exists())
		{
			Reset();
			return;
		}

		if (!ReadJson(m_SettingsFile, m_Json))
		{
			auto backup = m_SettingsFile;
			backup += ".bak";
			if (ReadJson(backup, m_Json))
			{
				LOG(WARNING) << "Detected corrupt settings, recovered the previous backup";
				std::error_code ec;
				std::filesystem::copy_file(backup, m_SettingsFile, std::filesystem::copy_options::overwrite_existing, ec);
				if (ec)
					LOGF(FATAL, "Recovered settings in memory but could not restore the file: {}", ec.message());
			}
			else
			{
				LOG(WARNING) << "Detected corrupt settings without a valid backup, resetting settings...";
				Reset();
				return;
			}
		}

		for (auto& serializer : m_StateSerializers)
			LoadComponentImpl(serializer);

		LOG(VERBOSE) << "All settings loaded";
		m_InitialLoadDone = true;
	}

	void Settings::TickImpl()
	{
		std::lock_guard lock(m_Mutex);
		while (!m_LateLoaders.empty())
		{
			if (auto component = std::move(m_LateLoaders.front()))
			{
				LoadComponent(component);
			}

			m_LateLoaders.pop();
		}

		if (m_InitialLoadDone && ShouldSave())
		{
			for (auto& serializer : m_StateSerializers)
				if (serializer->IsStateDirty())
					SaveComponentImpl(serializer);

			if (!WriteAtomically(m_SettingsFile, m_Json.dump(4)))
				LOGF(FATAL, "Failed to save settings atomically: error {}", GetLastError());
		}
	}

	void Settings::AddComponentImpl(IStateSerializer* serializer)
	{
		std::lock_guard lock(m_Mutex);
		m_StateSerializers.push_back(serializer);
		if (m_InitialLoadDone)
			m_LateLoaders.push(serializer);
	}

	void Settings::LoadComponentImpl(IStateSerializer* serializer)
	{
		if (!m_Json.contains(serializer->GetSerializerComponentName()) || !m_Json[serializer->GetSerializerComponentName()].is_object())
			m_Json[serializer->GetSerializerComponentName()] = nlohmann::json::object();

		try
		{
			serializer->LoadState(m_Json[serializer->GetSerializerComponentName()]);
		}
		catch (const std::exception& e)
		{
			LOGF(FATAL, "Failed to load component {}: {}", serializer->GetSerializerComponentName(), e.what());
		}
	}

	void Settings::SaveComponentImpl(IStateSerializer* serializer)
	{
		try
		{
			serializer->SaveState(m_Json[serializer->GetSerializerComponentName()]);
		}
		catch (const std::exception& e)
		{
			LOGF(FATAL, "Failed to save component {}: {}", serializer->GetSerializerComponentName(), e.what());
		}
	}

	void Settings::Reset()
	{
		if (!WriteAtomically(m_SettingsFile, "{}\n"))
			LOGF(FATAL, "Failed to reset settings atomically: error {}", GetLastError());
		m_Json.clear();
		m_InitialLoadDone = true;
	}

	bool Settings::ShouldSave()
	{
		for (auto& serializer : m_StateSerializers)
			if (serializer->IsStateDirty())
				return true;

		return false;
	}
}
