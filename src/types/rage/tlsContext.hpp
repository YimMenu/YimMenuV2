#pragma once
#include "sysMemAllocator.hpp"
#include <intrin.h>

namespace rage
{
	class scrThread;
	class tlsContext
	{
	public:
		char m_Pad1[0x7A0];
		rage::scrThread* m_CurrentScriptThread;
		bool m_ScriptThreadActive;

		static tlsContext* Get()
		{
			constexpr std::uint32_t TlsIndex = 0x0;
			return *reinterpret_cast<tlsContext**>(__readgsqword(0x58) + TlsIndex);
		}
	};
	static_assert(sizeof(tlsContext) == 0x7B0);
}