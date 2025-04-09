#pragma once

namespace rage
{
	struct rlScTaskStatus
	{
		void* m_Pad = nullptr;
		int m_Status = 0;
		int m_ErrorCode = 0;
	};
}