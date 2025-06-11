#pragma once
#include "core/hooking/VMTHook.hpp"
#include "core/util/Joaat.hpp"
#include "types/script/scrNativeHandler.hpp"

enum class NativeIndex;

namespace rage
{
	class scrProgram;
}

namespace YimMenu
{
	class NativeHooks
	{
		struct Hook
		{
			NativeIndex m_Index;
			rage::scrNativeHandler m_Replacement;
		};

		class Program final
		{
			rage::scrProgram* m_Program = nullptr;
			std::unique_ptr<VMTHook> m_Hook = nullptr;
			rage::scrNativeHandler* m_OrigHandlers = nullptr;

		public:
			Program(rage::scrProgram* program);
			void Apply(Hook hook);
			void Cleanup();
			static void ScrProgram_Dtor(rage::scrProgram* _this, bool free_mem);
		};

		std::unordered_map<rage::scrProgram*, std::unique_ptr<Program>> m_RegisteredPrograms;
		std::unordered_map<joaat_t, std::vector<Hook>> m_RegisteredHooks;

	public:
		static void RunScript()
		{
			GetInstance().RunScriptImpl();
		}

		static constexpr auto ALL_SCRIPTS = "ALL_SCRIPTS"_J;
		static void AddHook(joaat_t script, NativeIndex index, rage::scrNativeHandler hook)
		{
			GetInstance().AddHookImpl(script, index, hook);
		}

		static void RegisterProgram(rage::scrProgram* program)
		{
			GetInstance().RegisterProgramImpl(program);
		}

		static void UnregisterProgram(rage::scrProgram* program)
		{
			GetInstance().UnregisterProgramImpl(program);
		}

		static void Destroy()
		{
			GetInstance().DestroyImpl();
		}

	private:
		NativeHooks();
		static NativeHooks& GetInstance()
		{
			static NativeHooks Instance;
			return Instance;
		}

		void RunScriptImpl();
		void AddHookImpl(joaat_t script, NativeIndex index, rage::scrNativeHandler hook);
		void RegisterProgramImpl(rage::scrProgram* program);
		void UnregisterProgramImpl(rage::scrProgram* program);
		void DestroyImpl();
	};
}