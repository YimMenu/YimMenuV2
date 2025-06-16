#pragma once
#include <chrono>

namespace YimMenu
{
	class RateLimiter
	{
		uint32_t m_AttemptsAllowedInTimePeriod;
		std::chrono::milliseconds m_TimePeriod;
		std::chrono::system_clock::time_point m_LastEventTime{};
		uint32_t m_NumAttemptsAllowed = 0;

	public:
		RateLimiter(std::chrono::milliseconds period, uint32_t numAllowedAttempts) :
		    m_AttemptsAllowedInTimePeriod(numAllowedAttempts),
		    m_TimePeriod(period)
		{
		}

		// Returns true if the rate limit has been exceeded
		bool Process()
		{
			if (std::chrono::system_clock::now() - m_LastEventTime < m_TimePeriod)
			{
				if (++m_NumAttemptsAllowed > m_AttemptsAllowedInTimePeriod)
					return true;
			}
			else
			{
				m_LastEventTime = std::chrono::system_clock::now();
				m_NumAttemptsAllowed = 1;
			}
			return false;
		}

		// Check if the rate limit was exceeded by the last process() call. Use this to prevent the player from being flooded with notifications
		bool ExceededLastProcess()
		{
			return (m_NumAttemptsAllowed - 1) == m_AttemptsAllowedInTimePeriod;
		}
	};
}