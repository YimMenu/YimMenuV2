#pragma once
#include "core/util/Joaat.hpp"
#include "core/memory/Pattern.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/Scripts.hpp"
#include "types/script/scrThread.hpp"
#include "types/script/scrProgram.hpp"
#include "types/rage/tlsContext.hpp"

namespace YimMenu
{
	class ScriptFunction
	{
		joaat_t m_Script;
		const SimplePattern m_Pattern;
		std::uint32_t m_PC;
		std::string m_Name;

		std::uint32_t GetPC(rage::scrProgram* program);

		template<typename Arg>
		void PushArg(std::uint64_t* stack, std::uint32_t& stackPtr, Arg&& value)
		{
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<Arg>>*>(reinterpret_cast<std::uint64_t*>(stack) + (stackPtr++)) = std::forward<Arg>(value);
		}

	public:
		ScriptFunction(const std::string& name, const joaat_t script, const SimplePattern& pattern);

		template<typename Ret, typename... Args>
		Ret Call(Args... args)
		{
			auto thread  = Scripts::FindScriptThread(m_Script);
			auto program = Scripts::FindScriptProgram(m_Script);

			if (!thread || !program)
				return Ret();

			auto pc = GetPC(program);
			if (!pc)
				return Ret();

			auto tlsCtx                   = rage::tlsContext::Get();
			auto stack                    = (std::uint64_t*)thread->m_Stack;
			auto ogThread                 = tlsCtx->m_CurrentScriptThread;
			tlsCtx->m_CurrentScriptThread = thread;
			tlsCtx->m_ScriptThreadActive  = true;
			rage::scrThread::Context ctx  = thread->m_Context;
			auto topStack                 = ctx.m_StackPointer;

			(PushArg(stack, ctx.m_StackPointer, std::forward<Args>(args)), ...);

			stack[ctx.m_StackPointer++] = 0;
			ctx.m_ProgramCounter        = pc;
			ctx.m_State                 = rage::scrThread::State::IDLE;

			Pointers.ScriptVM(stack, Pointers.ScriptGlobals, program, &ctx);

			tlsCtx->m_CurrentScriptThread = ogThread;
			tlsCtx->m_ScriptThreadActive  = ogThread != nullptr;

			if constexpr (!std::is_same_v<Ret, void>)
			{
				return *reinterpret_cast<Ret*>(stack + topStack);
			}
		}
	};
}