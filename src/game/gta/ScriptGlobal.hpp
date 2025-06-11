#pragma once
#include <cstddef>
#include <type_traits>

namespace YimMenu
{
	class ScriptGlobal
	{
	private:
		std::size_t m_Index;

	public:
		constexpr ScriptGlobal(std::size_t idx) :
		    m_Index(idx)
		{
		}

		constexpr ScriptGlobal At(std::ptrdiff_t offset) const
		{
			return m_Index + offset;
		}

		constexpr ScriptGlobal At(std::ptrdiff_t offset, std::size_t size) const
		{
			return m_Index + 1 + offset * size;
		}

		template<typename T>
		inline std::enable_if_t<std::is_pointer_v<T>, T> As() const
		{
			return static_cast<T>(Get());
		}

		template<typename T>
		inline std::enable_if_t<std::is_lvalue_reference_v<T>, T> As() const
		{
			return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(Get());
		}

		constexpr bool operator==(const ScriptGlobal& other)
		{
			return m_Index == other.m_Index;
		}

		bool CanAccess() const;

	private:
		void* Get() const;
	};
}