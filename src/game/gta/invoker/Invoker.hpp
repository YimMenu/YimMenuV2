#pragma once
#include "Crossmap.hpp"
#include "game/pointers/Pointers.hpp"

#include <script/scrNativeHandler.hpp>
#include <script/types.hpp>

namespace YimMenu
{
	class CustomCallContext : public rage::scrNativeCallContext
	{
	public:
		constexpr CustomCallContext()
		{
			m_return_value = &m_return_stack[0];
			m_args         = &m_arg_stack[0];
		}

	private:
		uint64_t m_return_stack[10];
		uint64_t m_arg_stack[40];
	};

	class NativeInvoker
	{
		static inline rage::scrNativeHandler m_Handlers[g_Crossmap.size()];
		static inline bool m_AreHandlersCached{false};

	public:
		constexpr NativeInvoker(){};

		constexpr void BeginCall()
		{
			m_CallContext.reset();
		}

		template<int index, bool fix_vectors>
		constexpr void EndCall()
		{
			// TODO: try to get rid of this
			if (!m_AreHandlersCached)
				CacheHandlers();

			m_Handlers[index](&m_CallContext);
			if constexpr (fix_vectors)
				Pointers.FixVectors(&m_CallContext);
		}

		template<typename T>
		constexpr void PushArg(T&& value)
		{
			m_CallContext.push_arg(std::forward<T>(value));
		}

		template<typename T>
		constexpr T& GetReturnValue()
		{
			return *m_CallContext.get_return_value<T>();
		}

	public:
		static void CacheHandlers();

		template<int index, typename Ret, typename... Args>
		static constexpr FORCEINLINE Ret Invoke(Args&&... args)
		{
			NativeInvoker invoker{};

			invoker.BeginCall();
			(invoker.PushArg(std::forward<Args>(args)), ...);
			invoker.EndCall<index, std::is_same_v<Ret, Vector3>>();

			if constexpr (!std::is_same_v<Ret, void>)
			{
				return invoker.GetReturnValue<Ret>();
			}
		}

		CustomCallContext m_CallContext{};
	};
}
