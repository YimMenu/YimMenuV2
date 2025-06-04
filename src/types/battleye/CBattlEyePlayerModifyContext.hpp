#pragma once
#include "types/rage/atArray.hpp"
#include "types/network/netSocketAddress.hpp"

namespace rage
{
	using atDynString = rage::atArray<char>; // this is technically true
}

class CBattlEyePlayerModifyContext
{
public:
	rage::atDynString m_Ticket;
	rage::atDynString m_GamerHandleHash;
	netSocketAddress m_Address;
	uint64_t m_HostToken;
	char m_Name[17];
	bool m_IsLocal;
};
static_assert(sizeof(CBattlEyePlayerModifyContext) == 0x48);