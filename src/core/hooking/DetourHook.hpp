#pragma once
#include "BaseHook.hpp"
#include "core/memory/PointerCalculator.hpp"

#include <MinHook.h>
#include <string_view>

namespace YimMenu
{
	template<typename T = int*>
	class DetourHook : public BaseHook
	{
	private:
		void* m_TargetFunc;
		void* m_DetourFunc;
		void* m_OriginalFunc;

	public:
		DetourHook(const std::string_view name, void* target, T detour);
		virtual ~DetourHook();

		bool Enable();
		bool Disable();

		bool EnableNow();
		bool DisableNow();

		T Original() const;

	private:
		void OptimizeHook();
	};

	template<typename T>
	inline DetourHook<T>::DetourHook(const std::string_view name, void* target, T detour) :
	    BaseHook(name),
	    m_TargetFunc(target),
	    m_DetourFunc(reinterpret_cast<void*>(detour)),
	    m_OriginalFunc(nullptr)
	{
		OptimizeHook();

		if (const auto result = MH_CreateHook(m_TargetFunc, m_DetourFunc, &m_OriginalFunc); result != MH_OK)
		{
			LOGF(FATAL, "Failed to create hook {}", name);
			throw std::runtime_error("Failed to create hook!");
		}
	}

	template<typename T>
	inline DetourHook<T>::~DetourHook()
	{
		DisableNow();
	}

	template<typename T>
	inline bool DetourHook<T>::Enable()
	{
		if (m_Enabled)
			return false;

		if (const auto result = MH_QueueEnableHook(m_TargetFunc); result != MH_OK)
		{
			throw std::runtime_error("Failed to queue hook to be enabled.");

			return false;
		}
		return true;
	}

	template<typename T>
	inline bool DetourHook<T>::Disable()
	{
		if (!m_Enabled)
			return false;

		if (const auto result = MH_QueueDisableHook(m_TargetFunc); result != MH_OK)
		{
			throw std::runtime_error("Failed to queue hook to be disable.");

			return false;
		}
		return true;
	}

	template<typename T>
	inline bool DetourHook<T>::EnableNow()
	{
		if (m_Enabled)
			return false;

		if (const auto result = MH_EnableHook(m_TargetFunc); result != MH_OK)
		{
			throw std::runtime_error("Failed to enable hook right now.");

			return false;
		}
		return true;
	}

	template<typename T>
	inline bool DetourHook<T>::DisableNow()
	{
		if (!m_Enabled)
			return false;

		if (const auto result = MH_DisableHook(m_TargetFunc); result != MH_OK)
		{
			throw std::runtime_error("Failed to disable hook right now.");

			return false;
		}
		return true;
	}

	template<typename T>
	inline T DetourHook<T>::Original() const
	{
		return reinterpret_cast<T>(m_OriginalFunc);
	}

	template<typename T>
	inline void DetourHook<T>::OptimizeHook()
	{
		auto ptr = PointerCalculator(m_TargetFunc);
		while (ptr.As<std::uint8_t&>() == 0xE9)
		{
			ptr = ptr.Add(1).Rip();
		}
		m_TargetFunc = ptr.As<void*>();
	}
}