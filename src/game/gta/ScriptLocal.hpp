#pragma once
#include <cstddef>
#include <type_traits>
#include <types/script/scrThread.hpp>
#include <core/util/Joaat.hpp>
#include <game/gta/Scripts.hpp>

namespace YimMenu
{
	class ScriptLocal
	{
	private:
		std::size_t m_Index;
		void* m_StackPtr;

	public:
		constexpr ScriptLocal(std::size_t index) :
		    m_Index(index),
		    m_StackPtr(nullptr)
		{
		}

		constexpr ScriptLocal(void* stackPtr, std::size_t index) :
		    m_Index(index),
		    m_StackPtr(stackPtr)
		{
		}

		constexpr ScriptLocal(rage::scrThread* thread, std::size_t index) :
		    ScriptLocal(thread->m_Stack, index)
		{
		}

		constexpr ScriptLocal(joaat_t script, std::size_t index) :
		    ScriptLocal(Scripts::FindScriptThread(script)->m_Stack, index)
		{
		}

		constexpr ScriptLocal At(std::ptrdiff_t offset) const
		{
			return {m_StackPtr, m_Index + offset};
		}

		constexpr ScriptLocal At(std::ptrdiff_t offset, std::size_t size) const
		{
			return {m_StackPtr, m_Index + 1 + offset * size};
		}

		constexpr ScriptLocal Set(void* stackPtr)
		{
			return {stackPtr, m_Index};
		}

		// TODO: Uncomment when GTAV-Classes have been added
		// constexpr ScriptLocal Set(rage::scrThread* thread)
		// {
		//     return { thread, m_Index };
		// }

		template<typename T>
		std::enable_if_t<std::is_pointer_v<T>, T> As()
		{
			return static_cast<T>(Get());
		}

		template<typename T>
		std::enable_if_t<std::is_lvalue_reference_v<T>, T> As()
		{
			return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(Get());
		}

		bool CanAccess() const;

	private:
		void* Get() const;
	};
}