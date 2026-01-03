#pragma once
#include "../types.hpp"
#include "../Timer.hpp"

namespace rage
{
	class scrThread;
}

enum class eRandomEventFMFlags
{
	RESTART = 2,
	DISABLE_DISTANCE_CHECK = 4
};

struct RANDOM_EVENTS_LOCAL_DATA
{
	SCR_INT RegisteredEvents;              // 0
	SCR_ARRAY<uint64_t, 1> TriggerPtr;     // 1
	SCR_INT TriggerPositionPtr;            // 3
	SCR_INT TriggerRangePtr;               // 4
	SCR_INT AvailablePtr;                  // 5
	SCR_INT InactiveTime;                  // 6
	SCR_INT AvailableTime;                 // 7
	SCR_BITSET<eRandomEventFMFlags> Flags; // 8
	TIMER LastTriggerAttempt;              // 9
	SCR_INT UNK_0011;                      // 11 (unused, ranges from 0 to 4)
};
static_assert(sizeof(RANDOM_EVENTS_LOCAL_DATA) == 12 * 8);

struct RANDOM_EVENTS_FMMC_DATA
{
	SCR_INT FMMCType; // 0
};
static_assert(sizeof(RANDOM_EVENTS_FMMC_DATA) == 1 * 8);

struct RANDOM_EVENTS_MISSION_DATA
{
	SCR_INT EventsCount;                             // 0
	SCR_ARRAY<RANDOM_EVENTS_FMMC_DATA, 24> FMMCData; // 1
};
static_assert(sizeof(RANDOM_EVENTS_MISSION_DATA) == 26 * 8);

struct RANDOM_EVENTS_FREEMODE_DATA
{
	SCR_ARRAY<RANDOM_EVENTS_LOCAL_DATA, 24> EventData; // 0
	RANDOM_EVENTS_MISSION_DATA MissionData;            // 289

	static RANDOM_EVENTS_FREEMODE_DATA* Get(rage::scrThread* thread);
};
static_assert(sizeof(RANDOM_EVENTS_FREEMODE_DATA) == 315 * 8);