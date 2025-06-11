#pragma once
#include "BaseHook.hpp"

#include <array>
#include <cstddef>
#include <string_view>

namespace YimMenu
{
	class VMTHook
	{
	private:
		std::string_view m_Name;
		bool m_Enabled;

		int m_NumEntries;
		void** m_NewVMT{};
		void** m_OriginalVMT{};
		void*** m_VMTAddress;

	public:
		template<typename T>
		VMTHook(const std::string_view name, T* vmtAddress, int numEntries);
		~VMTHook();

		VMTHook(VMTHook&& that) = delete;
		VMTHook& operator=(VMTHook&& that) = delete;
		VMTHook(VMTHook const&) = delete;
		VMTHook& operator=(VMTHook const&) = delete;

		virtual void Enable();
		virtual void Disable();

		template<typename T>
		inline T Original(const std::uint32_t idx) const;

		void Hook(const std::uint32_t idx, void* detour);
		void UnHook(const std::uint32_t idx);

		inline constexpr std::size_t VMTSize() const
		{
			return m_NumEntries;
		}
	};


	template<typename T>
	inline VMTHook::VMTHook(const std::string_view name, T* vmtAddress, int numEntries) :
	    m_Name(name),
	    m_VMTAddress(reinterpret_cast<void***>(vmtAddress)),
	    m_NumEntries(numEntries),
	    m_NewVMT(new void*[m_NumEntries]),
	    m_Enabled(false)
	{
		m_OriginalVMT = *m_VMTAddress;
		memcpy(m_NewVMT, m_OriginalVMT, sizeof(void*) * m_NumEntries);
	}

	inline VMTHook::~VMTHook()
	{
		Disable();
		delete[] m_NewVMT;
	}


	inline void VMTHook::Enable()
	{
		if (m_Enabled)
			return;

		m_Enabled = true;
		*m_VMTAddress = m_NewVMT;
		return;
	}


	inline void VMTHook::Disable()
	{
		if (!m_Enabled)
			return;

		*m_VMTAddress = m_OriginalVMT;
		m_Enabled = false;
		return;
	}

	inline void VMTHook::Hook(const std::uint32_t idx, void* detour)
	{
		m_NewVMT[idx] = reinterpret_cast<void*>(detour);
	}


	inline void VMTHook::UnHook(const std::uint32_t idx)
	{
		m_NewVMT[idx] = m_OriginalVMT[idx];
	}


	template<typename T>
	inline T VMTHook::Original(const std::uint32_t idx) const
	{
		return reinterpret_cast<T>(m_OriginalVMT[idx]);
	}
}