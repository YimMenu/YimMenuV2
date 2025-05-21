#pragma once
#include "core/memory/PointerCalculator.hpp"

namespace YimMenu
{
	class CallHookMemory
	{
		static CallHookMemory& GetInstance()
		{
			static CallHookMemory instance;
			return instance;
		}

		void* AllocateJumpSequenceImpl(void* func);
		void DestroyImpl();

		PointerCalculator m_Memory;
		int m_Offset;

	public:
		CallHookMemory();

		static void* AllocateJumpSequence(void* func)
		{
			return GetInstance().AllocateJumpSequenceImpl(func);
		}

		static void Destroy()
		{
			GetInstance().DestroyImpl();
		}
	};

	class CallSiteHook
	{
	public:
		class Hook
		{
			Hook(Hook&& that) = delete;
			Hook& operator=(Hook&& that) = delete;
			Hook(Hook const&) = delete;
			Hook& operator=(Hook const&) = delete;

			void* m_Location;
			void* m_Hook;
			uint8_t m_PatchedBytes[5];
			uint8_t m_OriginalBytes[5];
			void* m_OriginalFunction;
			bool m_Enabled;

		public:
			Hook(void* location, void* hook);

			void Enable();
			void Disable();

			template<typename T>
			T GetOriginal()
			{
				return reinterpret_cast<T>(m_OriginalFunction);
			}
		};

		static std::shared_ptr<Hook> AddHook(void* location, void* hook)
		{
			return GetInstance().AddHookImpl(location, hook);
		}

		static void Destroy()
		{
			GetInstance().DestroyImpl();
		}

	private:
		static CallSiteHook& GetInstance()
		{
			static CallSiteHook Instance;
			return Instance;
		}

		std::shared_ptr<Hook> AddHookImpl(void* location, void* hook);
		void DestroyImpl();

		static inline std::vector<std::shared_ptr<Hook>> m_Hooks;
	};

	using CallHook = std::shared_ptr<CallSiteHook::Hook>;
}