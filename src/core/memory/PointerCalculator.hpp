#pragma once
#include <cstdint>
#include <type_traits>

namespace YimMenu
{
	class PointerCalculator final
	{
	private:
		std::uintptr_t m_InternalPtr;

	public:
		inline PointerCalculator(void* ptr = nullptr);
		inline PointerCalculator(std::uintptr_t ptr);
		template<typename T>
		inline PointerCalculator(T* ptr);
		virtual ~PointerCalculator() = default;

		template<typename T>
		std::enable_if_t<std::is_pointer_v<T>, T> As() const;

		template<typename T>
		std::enable_if_t<std::is_lvalue_reference_v<T>, T> As() const;

		template<typename T>
		std::enable_if_t<std::is_same_v<T, std::uintptr_t>, T> As() const;

		template<typename T>
		PointerCalculator Add(T offset) const;

		template<typename T>
		PointerCalculator Sub(T offset) const;

		PointerCalculator Rip() const;

		explicit operator bool() const;
		friend bool operator==(PointerCalculator& a, PointerCalculator& b);
		friend bool operator!=(PointerCalculator& a, PointerCalculator& b);
	};

	inline PointerCalculator::PointerCalculator(void* ptr) :
	    m_InternalPtr(reinterpret_cast<std::uintptr_t>(ptr))
	{
	}

	inline PointerCalculator::PointerCalculator(std::uintptr_t ptr) :
	    m_InternalPtr(ptr)
	{
	}

	template<typename T>
	inline PointerCalculator::PointerCalculator(T* ptr) :
	    m_InternalPtr(reinterpret_cast<std::uintptr_t>(ptr))
	{
	}

	template<typename T>
	inline std::enable_if_t<std::is_pointer_v<T>, T> PointerCalculator::As() const
	{
		return reinterpret_cast<T>(m_InternalPtr);
	}

	template<typename T>
	inline std::enable_if_t<std::is_lvalue_reference_v<T>, T> PointerCalculator::As() const
	{
		return *reinterpret_cast<std::add_pointer_t<std::remove_reference_t<T>>>(m_InternalPtr);
	}

	template<typename T>
	inline std::enable_if_t<std::is_same_v<T, std::uintptr_t>, T> PointerCalculator::As() const
	{
		return m_InternalPtr;
	}

	template<typename T>
	inline PointerCalculator PointerCalculator::Add(T offset) const
	{
		return {m_InternalPtr + offset};
	}

	template<typename T>
	inline PointerCalculator PointerCalculator::Sub(T offset) const
	{
		return {m_InternalPtr - offset};
	}

	inline PointerCalculator PointerCalculator::Rip() const
	{
		return Add(As<std::int32_t&>()).Add(4);
	}

	inline PointerCalculator::operator bool() const
	{
		return m_InternalPtr != 0;
	}

	inline bool operator==(PointerCalculator& a, PointerCalculator& b)
	{
		return a.m_InternalPtr == b.m_InternalPtr;
	}

	inline bool operator!=(PointerCalculator& a, PointerCalculator& b)
	{
		return a.m_InternalPtr != b.m_InternalPtr;
	}
}