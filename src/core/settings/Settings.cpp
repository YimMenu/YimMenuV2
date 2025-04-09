#include "Settings.hpp"

#include "IStateSerializer.hpp"
#include "Settings.hpp"


namespace YimMenu
{
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

		std::ifstream file(m_SettingsFile);

		try
		{
			file >> m_Json;
			file.close();
		}
		catch (std::exception&)
		{
			LOG(WARNING) << "Detected corrupt settings, resetting settings...";
			Reset();
			return;
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

			std::ofstream file(m_SettingsFile, std::ios::out | std::ios::trunc);
			file << m_Json.dump(4);
			file.close();
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
		std::ofstream file(m_SettingsFile, std::ios::out | std::ios::trunc);
		file << "{}" << std::endl;
		file.close();
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