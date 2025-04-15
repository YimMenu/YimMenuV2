#pragma once

struct TIMER;

namespace YimMenu::Stopwatch
{
	extern void Initialize(TIMER& stopwatch, bool localTimer = false);
	extern void Reset(TIMER& stopwatch, bool localTimer = false);
	extern void Destroy(TIMER& stopwatch);
	extern bool IsInitialized(TIMER& stopwatch);
	extern bool HasTimePassed(TIMER& stopwatch, int ms, bool localTimer = false);
	extern int GetRemainingTime(TIMER& stopwatch, int ms, bool localTimer = false);
	extern std::string GetRemainingTimeStr(TIMER& stopwatch, int ms, bool localTimer = false);
}