#pragma once
#include "rlGamerInfoBase.hpp"

namespace rage
{
	class rlSessionInfo
	{
	public:
		uint64_t m_SessionId;              // 0x00
		uint64_t m_SessionToken;           // 0x08
		rlGamerInfoBase m_HostInfo;        // 0x10
	};
	static_assert(sizeof(rlSessionInfo) == 0xD0);
}