#pragma once
#include "netArrayHandlerBase.hpp"

namespace rage
{
	class netArrayHandler : public netArrayHandlerBase
	{
	public:

		netSyncElement* m_Array;           // 0x108
		netSyncElement m_ExtractedElement; // 0x110
		uint8_t _m_pad4[0x25];             // 0x120
		char m_Flags;                      // 0x145
	};
	static_assert(sizeof(netArrayHandler) == 0x148);
}