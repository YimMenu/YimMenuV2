#pragma once
#include "types.hpp"

struct TIMER
{
	SCR_INT Time;
	SCR_BOOL IsInitialized;

	void Initialize(bool localTimer = false);
	void Reset(bool localTimer = false);
	void Destroy();
	bool _IsInitialized();
	bool HasTimePassed(int ms, bool localTimer = false);
	int GetRemainingTime(int ms, bool localTimer = false);
	std::string GetRemainingTimeStr(int ms, bool localTimer = false);
};
static_assert(sizeof(TIMER) == 2 * 8);