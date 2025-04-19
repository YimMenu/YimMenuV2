#include "ScriptFunction.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/pointers/ScriptPointers.hpp"
#include "game/gta/Scripts.hpp"
#include "types/script/scrThread.hpp"
#include "types/script/scrProgram.hpp"
#include "types/rage/tlsContext.hpp"

namespace YimMenu
{
	ScriptFunction::ScriptFunction(const joaat_t nameHash, const joaat_t script) :
	    m_NameHash(nameHash),
	    m_Script(script)
	{
	}

	ScriptFunction::ScriptFunction(const joaat_t script) :
	    m_NameHash(0),
	    m_Script(script)
	{
	}

	void ScriptFunction::CallImpl(const std::vector<uint64_t>& args, void* returnValue, std::uint32_t returnSize)
	{
		auto thread  = Scripts::FindScriptThread(m_Script);
		auto program = Scripts::FindScriptProgram(m_Script);
		auto pc      = ScriptPointers::GetPointer(m_NameHash);

		if (!thread || !program || !pc)
			return;

		auto tlsCtx                   = rage::tlsContext::Get();
		auto stack                    = (std::uint64_t*)thread->m_Stack;
		auto ogThread                 = tlsCtx->m_CurrentScriptThread;
		tlsCtx->m_CurrentScriptThread = thread;
		tlsCtx->m_ScriptThreadActive  = true;
		rage::scrThread::Context ctx  = thread->m_Context;
		auto topStack                 = ctx.m_StackPointer;

		for (auto& arg : args)
			stack[ctx.m_StackPointer++] = arg;

		stack[ctx.m_StackPointer++] = 0;
		ctx.m_ProgramCounter        = pc;
		ctx.m_State                 = rage::scrThread::State::IDLE;

		Pointers.ScriptVM(stack, Pointers.ScriptGlobals, program, &ctx);

		tlsCtx->m_CurrentScriptThread = ogThread;
		tlsCtx->m_ScriptThreadActive  = ogThread != nullptr;

		if (returnValue)
			std::memcpy(returnValue, stack + topStack, returnSize);
	}

	void ScriptFunction::CallImpl(std::uint32_t pc, const std::vector<uint64_t>& args, void* returnValue, std::uint32_t returnSize)
	{
		auto thread  = Scripts::FindScriptThread(m_Script);
		auto program = Scripts::FindScriptProgram(m_Script);

		if (!thread || !program)
			return;

		auto tlsCtx                   = rage::tlsContext::Get();
		auto stack                    = (std::uint64_t*)thread->m_Stack;
		auto ogThread                 = tlsCtx->m_CurrentScriptThread;
		tlsCtx->m_CurrentScriptThread = thread;
		tlsCtx->m_ScriptThreadActive  = true;
		rage::scrThread::Context ctx  = thread->m_Context;
		auto topStack                 = ctx.m_StackPointer;

		for (auto& arg : args)
			stack[ctx.m_StackPointer++] = arg;

		stack[ctx.m_StackPointer++] = 0;
		ctx.m_ProgramCounter        = pc;
		ctx.m_State                 = rage::scrThread::State::IDLE;

		Pointers.ScriptVM(stack, Pointers.ScriptGlobals, program, &ctx);

		tlsCtx->m_CurrentScriptThread = ogThread;
		tlsCtx->m_ScriptThreadActive  = ogThread != nullptr;

		if (returnValue)
			std::memcpy(returnValue, stack + topStack, returnSize);
	}
}