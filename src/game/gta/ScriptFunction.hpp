#pragma once
#include "core/util/Joaat.hpp"
#include "game/gta/ScriptPointer.hpp"

namespace YimMenu
{
	class ScriptFunction
	{
		joaat_t m_Script;
		ScriptPointer m_Pointer;
		std::uint32_t m_Pc;

		template<typename Arg>
		static void PushArg(std::uint64_t* stack, std::uint32_t& stackPtr, Arg&& value)
		{
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<Arg>>*>(reinterpret_cast<std::uint64_t*>(stack) + (stackPtr++)) = std::forward<Arg>(value);
		}

		void CallImpl(const std::vector<uint64_t>& args, void* returnValue = 0, std::uint32_t returnSize = 0);

	public:
		ScriptFunction(const joaat_t script, ScriptPointer ptr);

		template<typename Ret, typename... Args>
		Ret Call(Args... args)
		{
			std::uint32_t index{};
			std::vector<std::uint64_t> params(sizeof...(Args));
			(PushArg(params.data(), index, std::forward<Args>(args)), ...);
			if constexpr (!std::is_same_v<Ret, void>)
			{
				Ret returnValue;
				CallImpl(params, &returnValue, sizeof(returnValue));
				return returnValue;
			}
			else
			{
				CallImpl(params);
			}
		}
	};
}