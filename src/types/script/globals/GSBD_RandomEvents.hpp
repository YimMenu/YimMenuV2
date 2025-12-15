#pragma once
#include "../Timer.hpp"
#include "../types.hpp"

enum class eRandomEventInitState
{
	INITIALIZING,
	INITIALIZED
};

enum class eRandomEventState
{
	INACTIVE,
	AVAILABLE,
	ACTIVE,
	CLEANUP
};

enum class eRandomEventFlags
{
	TRIGGERED_BY_CLIENT,
	FORCE_LAUNCH,
	UNK_2, // unused
	FORCE_CLEANUP
};

struct RANDOM_EVENTS_RESERVATION_DATA
{
	SCR_INT ReservedPeds;     // 0
	SCR_INT ReservedVehicles; // 1
	SCR_INT ReservedObjects;  // 2
};
static_assert(sizeof(RANDOM_EVENTS_RESERVATION_DATA) == 3 * 8);

struct RANDOM_EVENTS_DATA
{
	alignas(8) eRandomEventState State;                // 0
	TIMER TimerState;                                  // 1
	SCR_ARRAY<SCR_BITSET<eRandomEventFlags>, 1> Flags; // 3
	SCR_INT Variation;                                 // 5
	SCR_INT Subvariation;                              // 6
	RANDOM_EVENTS_RESERVATION_DATA ReservationData;    // 7
	SCR_VEC3 TriggerPosition;                          // 10
	SCR_FLOAT TriggerRange;                            // 13
	SCR_INT Retries;                                   // 14
};
static_assert(sizeof(RANDOM_EVENTS_DATA) == 15 * 8);

struct RANDOM_EVENTS_VEHICLE_LIST_DATA
{
	SCR_INT Index; // 0
	SCR_INT Variation; // 1
};
static_assert(sizeof(RANDOM_EVENTS_VEHICLE_LIST_DATA) == 2 * 8);

struct RANDOM_EVENTS_TARGET_DATA
{
	PLAYER_INDEX PhantomCarTarget; // 0
	PLAYER_INDEX XMASMuggerTarget; // 1
};
static_assert(sizeof(RANDOM_EVENTS_TARGET_DATA) == 2 * 8);

struct GSBD_RandomEvents
{
	alignas(8) eRandomEventInitState InitState;      // 0
	SCR_ARRAY<RANDOM_EVENTS_DATA, 24> EventData;     // 1
	RANDOM_EVENTS_VEHICLE_LIST_DATA VehicleListData; // 362
	RANDOM_EVENTS_TARGET_DATA TargetData;            // 364

	static GSBD_RandomEvents* Get();
};
static_assert(sizeof(GSBD_RandomEvents) == 366 * 8);