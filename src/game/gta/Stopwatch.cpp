#include "Stopwatch.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/script/Timer.hpp"

namespace YimMenu::Stopwatch
{
	void Initialize(TIMER& stopwatch, bool localTimer)
	{
		if (!stopwatch.IsInitialized)
		{
			stopwatch.Time = (*Pointers.IsSessionStarted && !localTimer) ? *Pointers.NetworkTime : *Pointers.GameTimer;
			stopwatch.IsInitialized = true;
		}
	}

	void Reset(TIMER& stopwatch, bool localTimer)
	{
		stopwatch.Time = (*Pointers.IsSessionStarted && !localTimer) ? *Pointers.NetworkTime : *Pointers.GameTimer;
		stopwatch.IsInitialized = true;
	}

	void Destroy(TIMER& stopwatch)
	{
		stopwatch.IsInitialized = false;
	}

	bool IsInitialized(TIMER& stopwatch)
	{
		return stopwatch.IsInitialized;
	}

	bool HasTimePassed(TIMER& stopwatch, int ms, bool localTimer)
	{
		if (ms < 0)
			return true;

		Initialize(stopwatch, localTimer);

		int timePassed = (*Pointers.IsSessionStarted && !localTimer) ? (*Pointers.NetworkTime - stopwatch.Time) : (*Pointers.GameTimer - stopwatch.Time);
		if (timePassed >= ms)
			return true;

		return false;
	}

	int GetRemainingTime(TIMER& stopwatch, int ms, bool localTimer)
	{
		int timePassed = (*Pointers.IsSessionStarted && !localTimer) ? (*Pointers.NetworkTime - stopwatch.Time) : (*Pointers.GameTimer - stopwatch.Time);
		return (ms - timePassed);
	}

	std::string GetRemainingTimeStr(TIMER& stopwatch, int ms, bool localTimer)
	{
		int timePassed   = (*Pointers.IsSessionStarted && !localTimer) ? (*Pointers.NetworkTime - stopwatch.Time) : (*Pointers.GameTimer - stopwatch.Time);
		int difference   = (ms - timePassed);
		int totalSeconds = difference / 1000;
		int hours        = totalSeconds / 3600;
		int minutes      = (totalSeconds % 3600) / 60;
		int seconds      = totalSeconds % 60;

		if (hours < 1)
			return std::format("{:02}:{:02}", minutes, seconds);
		else
			return std::format("{:02}:{:02}:{:02}", hours, minutes, seconds);
	}
}