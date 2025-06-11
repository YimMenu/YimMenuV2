#pragma once
#include "netSocketAddress.hpp"
#include "netAddress.hpp"
#include "rlGamerHandle.hpp"

namespace rage
{
	class rlGamerInfoBase
	{
	public:
		bool m_SecurityEnabled;             // 0x00
		uint64_t m_PeerId;                  // 0x08
		rlGamerHandle m_GamerHandle;        // 0x10
		char m_AESKey[0x28];                // 0x20
		netAddress m_RelayAddress;          // 0x48
		char m_RelaySignature[0x40];        // 0x68
		netSocketAddress m_ExternalAddress; // 0xA8
		netSocketAddress m_InternalAddress; // 0xB0
		uint32_t m_NatType;                 // 0xB8
		bool m_ForceRelays;                 // 0xBC
	};
	static_assert(sizeof(rlGamerInfoBase) == 0xC0);
}