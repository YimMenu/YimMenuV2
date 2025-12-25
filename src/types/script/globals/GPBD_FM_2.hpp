#pragma once
#include "../Timer.hpp"
#include "../types.hpp"

enum class eRaceRoundType
{
	NOT_SELECTED = -1,
	FINISH_FIRST,
	MOST_POINTS,
	FASTEST_TIME
};

enum class eRaceFinalRoundType
{
	NOT_SELECTED,
	HEAD_TO_HEAD
};

enum class eRandomEventClientState
{
	INACTIVE,
	TRIGGERING, // This is different than the server available state
	ACTIVE,
	CLEANUP
};

enum class eRandomEventClientFlags
{
	FORCE_LAUNCH
};

enum class eRandomEventClientInitState
{
	INITIALIZING,
	INITIALIZED
};

struct GANGOPS_DATA
{
	SCR_INT UNK_0000;                                 // 0
	SCR_ARRAY<uint64_t, 4> PlayerIndexes;             // 1
	SCR_ARRAY<uint64_t, 4> PlayerRoles;               // 6
	SCR_ARRAY<uint64_t, 4> ArePlayersReady;           // 11
	SCR_ARRAY<uint64_t, 5> PlayerCuts;                // 16
	SCR_INT HighlightedPlayer;                        // 22
	SCR_INT GangopsFlowMissionProgFlags;              // 23
	SCR_INT GangopsFMMissionProgFlags;                // 24
	SCR_INT GangopsFMMissionSkipFlags;                // 25
	SCR_INT GangopsHeistStatusFlags;                  // 26
	SCR_INT Flags;                                    // 27
	SCR_BOOL IsPlanningScreenReady;                   // 28
	SCR_BOOL QuittedPlanningScreen;                   // 29
	SCR_BOOL IsTutorialActive;                        // 30
	SCR_ARRAY<uint64_t, 4> IsTutorialActiveForPlayer; // 31
	TIMER FinaleForceLaunchTimer;                     // 36 (H2_FINALE_FORCE_LAUNCH_TIME)
	SCR_BOOL IsFinaleForceLaunched;                   // 38 (if players don't click ready in 3 minutes)
};
static_assert(sizeof(GANGOPS_DATA) == 39 * 8);

struct RANDOM_EVENTS_CLIENT_EVENT_DATA
{
	alignas(8) eRandomEventClientState State;                // 0
	SCR_ARRAY<SCR_BITSET<eRandomEventClientFlags>, 1> Flags; // 1
};
static_assert(sizeof(RANDOM_EVENTS_CLIENT_EVENT_DATA) == 3 * 8);

struct RANDOM_EVENTS_CLIENT_DATA
{
	alignas(8) eRandomEventClientInitState InitState;         // 0
	SCR_ARRAY<RANDOM_EVENTS_CLIENT_EVENT_DATA, 24> EventData; // 1
	SCR_BITSET<uint64_t> IsParticipantInEventFlags;           // 75
	SCR_INT UNK_0076;                                         // 76 (unused)
};
static_assert(sizeof(RANDOM_EVENTS_CLIENT_DATA) == 76 * 8);

struct HOCW_DATA
{
	uint64_t PAD_0000[2];
	SCR_INT SafeCashValue; // 2
	uint64_t PAD_0003[13];
};
static_assert(sizeof(HOCW_DATA) == 16 * 8);

struct SALVAGE_YARD_VEHICLE_SALE_DATA
{
	uint64_t PAD_0000[27];
	HOCW_DATA HOWCData; // 27
	uint64_t PAD_0043[9];
};
static_assert(sizeof(SALVAGE_YARD_VEHICLE_SALE_DATA) == 52 * 8);

struct GPBD_FM_2_Entry
{
	SCR_INT NumTeams;                                  // 0
	SCR_INT NumRounds;                                 // 1
	SCR_INT RoundsPlayed;                              // 2
	SCR_INT RoundScore;                                // 3
	SCR_INT CurrentTeam;                               // 4
	SCR_INT Flags;                                     // 5
	SCR_INT TotalScore;                                // 6
	SCR_INT TotalKills;                                // 7
	SCR_INT TotalDeaths;                               // 8
	SCR_INT RPEarned;                                  // 9
	SCR_INT CashEarned;                                // 10
	uint64_t PAD_0011[2];                              // 11
	SCR_INT APEarned;                                  // 13
	SCR_INT Duration;                                  // 14
	alignas(8) eRaceRoundType RaceRoundType;           // 15
	alignas(8) eRaceFinalRoundType RaceFinalRoundType; // 16
	SCR_INT Flags2;                                    // 17
	SCR_INT Vote;                                      // 18
	SCR_INT NumVotes;                                  // 19
	SCR_INT MaxVotes;                                  // 20
	SCR_INT PlayerTeam;                                // 21
	uint64_t PAD_0022[8];                              // 22 (mission stuff)
	SCR_INT TunableCloudCRC;                           // 30
	SCR_INT CatalogCloudCRC;                           // 31
	SCR_INT UNK_0032;                                  // 32
	SCR_INT Flags3;                                    // 33
	SCR_INT UNK_0034;                                  // 34
	SCR_BOOL HasVoted;                                 // 35
	TIMER UNK_0036;                                    // 36
	TIMER UNK_0038;                                    // 38
	SCR_VEC3 CoronaPosition;                           // 40
	GANGOPS_DATA GangopsData;                          // 43
	RANDOM_EVENTS_CLIENT_DATA RandomEventsClientData;  // 82
	SALVAGE_YARD_VEHICLE_SALE_DATA SYVehSaleData;      // 158 added b889g9
	uint64_t PAD_0210[105];
};
static_assert(sizeof(GPBD_FM_2_Entry) == 315 * 8);

struct GPBD_FM_2
{
	SCR_ARRAY<GPBD_FM_2_Entry, 32> Entries;

	static GPBD_FM_2* Get();
};
static_assert(sizeof(GPBD_FM_2) == 10081 * 8);