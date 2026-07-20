#include "CallHook.hpp"

namespace YimMenu
{
	CallHookMemory::CallHookMemory() :
	    m_Memory(nullptr),
	    m_Offset(0)
	{
		uint8_t* base = static_cast<uint8_t*>(static_cast<void*>(GetModuleHandle(0)));
		uint8_t* limit = base + INT32_MAX - 1024;

		for (uint8_t* addr = base; addr < limit; addr += 0x10000)
		{
			if (m_Memory = VirtualAlloc(addr, 1024, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE))
			{
				LOGF(VERBOSE, "Allocated call hook memory at {}. Base: {}.", m_Memory.As<void*>(), static_cast<void*>(base));
				break;
			}
		}

		if (!m_Memory)
		{
			LOG(FATAL) << "Failed to allocate call hook memory!";
		}
	}

	void* CallHookMemory::AllocateJumpSequenceImpl(void* func)
	{
		m_Offset = m_Offset + ((16 - (m_Offset % 16)) % 16);

		*m_Memory.Add(m_Offset).As<int16_t*>() = 0xB848;
		*m_Memory.Add(m_Offset).Add(2).As<void**>() = func;
		*m_Memory.Add(m_Offset).Add(10).As<int16_t*>() = 0xE0FF;

		m_Offset += 12;

		return m_Memory.Add(m_Offset).Sub(12).As<void*>();
	}

	void CallHookMemory::DestroyImpl()
	{
		VirtualFree(m_Memory.As<void*>(), 0, MEM_RELEASE);
	}

	CallSiteHook::Hook::Hook(void* location, void* hook) :
	    m_Location(location),
	    m_Hook(hook),
	    m_Enabled(false)
	{
		auto seq = CallHookMemory::AllocateJumpSequence(hook);
		m_PatchedBytes[0] = 0xE8;
		*(int32_t*)&m_PatchedBytes[1] = (int32_t)((uint64_t)seq - (uint64_t)location - 5);
		memcpy(m_OriginalBytes, location, 5);
		m_OriginalFunction = PointerCalculator(location).Add(1).Rip().As<void*>();
	}

	void CallSiteHook::Hook::Enable()
	{
		if (!m_Enabled)
		{
			DWORD oldProtect, temp;
			VirtualProtect(m_Location, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
			memcpy(m_Location, m_PatchedBytes, 5);
			VirtualProtect(m_Location, 5, oldProtect, &temp);
			m_Enabled = true;
		}
	}

	void CallSiteHook::Hook::Disable()
	{
		if (m_Enabled)
		{
			DWORD oldProtect, temp;
			VirtualProtect(m_Location, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
			memcpy(m_Location, m_OriginalBytes, 5);
			VirtualProtect(m_Location, 5, oldProtect, &temp);
			m_Enabled = false;
		}
	}

	std::shared_ptr<CallSiteHook::Hook> CallSiteHook::AddHookImpl(void* location, void* hook)
	{
		auto hookPtr = std::make_shared<Hook>(location, hook);

		m_Hooks.push_back(hookPtr);
		return hookPtr;
	}

	void CallSiteHook::DestroyImpl()
	{
		for (auto& hook : m_Hooks)
		{
			if (hook)
				hook->Disable();
		}

		m_Hooks.clear();
		CallHookMemory::Destroy();
	}
}