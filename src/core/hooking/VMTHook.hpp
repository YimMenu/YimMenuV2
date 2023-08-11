#pragma once
#include "BaseHook.hpp"

#include <array>
#include <cstddef>
#include <string_view>

namespace YimMenu
{
	template<std::size_t N>
	class VMTHook : public BaseHook
	{
	private:
		std::string_view m_Name;
		bool m_Enabled;

		std::array<void*, N> m_NewVMT = {nullptr};
		void** m_OriginalVMT;
		void*** m_VMTAddress;

	public:
		template<typename T>
		VMTHook(const std::string_view name, T* vmtAddress);
		~VMTHook();

		virtual bool Enable() override;
		virtual bool Disable() override;

		template<typename T>
		inline T Original(const std::uint32_t idx) const;

		template<typename T>
		void Hook(const std::uint32_t idx, T& detour);
		void UnHook(const std::uint32_t idx);

		inline constexpr std::size_t VMTSize() const
		{
			return N;
		}
	};

	template<std::size_t N>
	template<typename T>
	inline VMTHook<N>::VMTHook(const std::string_view name, T* vmtAddress) :
	    BaseHook(name),
	    m_VMTAddress(reinterpret_cast<void***>(vmtAddress))
	{
		m_OriginalVMT = *m_VMTAddress;
		std::copy_n(m_OriginalVMT, N, m_NewVMT.begin());
	}

	template<std::size_t N>
	inline VMTHook<N>::~VMTHook()
	{
		Disable();
	}

	template<std::size_t N>
	inline bool VMTHook<N>::Enable()
	{
		if (m_Enabled)
			return false;

		m_Enabled     = true;
		*m_VMTAddress = m_NewVMT.data();
		return true;
	}

	template<std::size_t N>
	inline bool VMTHook<N>::Disable()
	{
		if (!m_Enabled)
			return false;

		*m_VMTAddress = m_OriginalVMT;
		m_Enabled     = false;
		return true;
	}

	template<std::size_t N>
	template<typename T>
	inline void VMTHook<N>::Hook(const std::uint32_t idx, T& detour)
	{
		if (std::is_pointer<T>())
			m_NewVMT[idx] = reinterpret_cast<void*>(detour);
		else
			m_NewVMT[idx] = reinterpret_cast<void*>(&detour);
	}

	template<std::size_t N>
	inline void VMTHook<N>::UnHook(const std::uint32_t idx)
	{
		m_NewVMT[idx] = m_OriginalVMT[idx];
	}

	template<std::size_t N>
	template<typename T>
	inline T VMTHook<N>::Original(const std::uint32_t idx) const
	{
		return reinterpret_cast<T>(m_OriginalVMT[idx]);
	}
}