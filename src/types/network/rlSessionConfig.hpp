#pragma once
#include "MatchmakingAttributes.hpp"

namespace rage
{
	class rlSessionConfig
	{
	public:
		char m_pad[0x4];                               // 0x00
		int m_PublicSlots;                             // 0x04
		int m_PrivateSlots;                            // 0x08
		MatchmakingAttributes m_MatchmakingAttributes; // 0x0C
		char m_pad2[0x18];                             // 0x10C
	};
	static_assert(sizeof(rage::rlSessionConfig) == 0x130);
}