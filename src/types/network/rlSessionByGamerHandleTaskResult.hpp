#pragma once
#include "rlGamerHandle.hpp"
#include "rlSessionInfo.hpp"

namespace rage
{
	class rlSessionByGamerTaskResult
	{
	public:
		rlGamerHandle m_GamerHandle{0};
		rlSessionInfo m_SessionInfo{};
	};
}