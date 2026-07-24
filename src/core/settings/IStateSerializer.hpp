#pragma once

namespace YimMenu
{
	class IStateSerializer
	{
		std::string m_SerComponentName;
		std::atomic_bool m_IsDirty;

	public:
		IStateSerializer(const std::string& name);
		virtual void SaveStateImpl(nlohmann::json& state) = 0;
		virtual void LoadStateImpl(nlohmann::json& state) = 0;

		inline void SaveState(nlohmann::json& state)
		{
			SaveStateImpl(state);
			m_IsDirty.store(false, std::memory_order_release);
		}

		inline void LoadState(nlohmann::json& state)
		{
			LoadStateImpl(state);
			m_IsDirty.store(false, std::memory_order_release);
		}

		inline bool IsStateDirty()
		{
			return m_IsDirty.load(std::memory_order_acquire);
		}

		inline void MarkStateDirty()
		{
			m_IsDirty.store(true, std::memory_order_release);
		}

		inline const std::string& GetSerializerComponentName()
		{
			return m_SerComponentName;
		}
	};
}
