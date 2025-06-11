#pragma once
#include "netSocketAddress.hpp"

namespace rage
{
	// TODO: verify for Enhanced
	class netAddress
	{
	public:
		netSocketAddress m_InternalIp; // 0x00
		netSocketAddress m_ExternalIp; // 0x08
		uint64_t m_PeerId;             // 0x10 for peer relay cxns
		char m_Pad[6];                 // 0x18 TODO: what is this? it's not a usual address (padding would exist otherwise)
		uint8_t m_ConnectionType;      // 0x1E 1 = direct 2 = relay 3 = peer relays
	};
	static_assert(sizeof(netAddress) == 0x20);
}