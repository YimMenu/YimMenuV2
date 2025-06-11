#pragma once

#include "rlGamerInfoBase.hpp"

namespace rage
{
	class rlGamerInfo : public rlGamerInfoBase
	{
	public:
		uint64_t m_HostToken; // 0xC0

		union {
			rlGamerHandle m_GamerHandle2;
			uint32_t m_PeerId2; // not found in all instances (TODO I don't think it's found at all anymore)
		}; // 0xC8
		uint32_t m_ROSPrivilege; // 0xD8
		char m_name[17];         // 0xDC
	};
	static_assert(sizeof(rlGamerInfo) == 0xF0);
}