#pragma once
#include "types/script/types.hpp"

struct FixerSecContractData
{
	SCR_INT Type; // 0
	SCR_INT Difficulty; // 1
	SCR_INT Reward; // 2
};
static_assert(sizeof(FixerSecContractData) == 3 * 8);

struct FixerFlowData
{
	SCR_INT FixerGeneralFlags; // 0
	SCR_INT FixerCompletedFlags; // 1
	SCR_INT PayphoneBonusKillMethod; // 2
	SCR_INT FixerStoryFlags; // 3
	SCR_INT PAD_0004; // added b889g9
	SCR_INT PAD_0005; // added b889g9
	SCR_INT FixerStoryStrand; // 6
	SCR_INT FixerStoryCooldown; // 7
	SCR_INT FixerFlags; // 8
	SCR_INT FixerShortTrips; // 9
	SCR_INT FixerCount; // 10
	SCR_ARRAY<uint64_t, 6> FixerSecContractCompleted; // 11
	SCR_INT FixerEarnings; // 18
	SCR_ARRAY<FixerSecContractData, 3> FixerSecContracts; // 19
};
static_assert(sizeof(FixerFlowData) == 29 * 8);

struct ULPFlowData
{
	SCR_INT ULPMissionCurrent; // 0
	SCR_INT ULPMissionProgress; // 1
};
static_assert(sizeof(ULPFlowData) == 2 * 8);

struct XM22FlowData
{
	SCR_INT XM22Missions; // 0
	SCR_INT XM22Current; // 1
	SCR_INT XM22Flow; // 2
};
static_assert(sizeof(XM22FlowData) == 3 * 8);

struct SUM23AvopFlowData
{
	SCR_INT SUM23AvopCurrent; // 0
	SCR_INT SUM23AvopProgress; // 1
	SCR_ARRAY<uint64_t, 3> Difficulties; // 2
	SCR_ARRAY<uint64_t, 3> Rewards; // 6
	SCR_INT DifficultyFlags; // 10
};
static_assert(sizeof(SUM23AvopFlowData) == 11 * 8);

struct SALV23VehicleData
{
	SCR_INT SALV23VehRob; // 0
	SCR_INT SALV23VehModel; // 1
	SCR_INT SALV23VehMods; // 2
	SCR_BOOL SALV23CanKeep; // 3
	SCR_BOOL SALV23SaleVal; // 4
	SCR_INT PAD_0005; // 5
	SCR_INT SALV23VehSlot; // 6
	SCR_INT SALV23VehWeek; // 7
	SCR_INT PackedInt42101; // 8
	SCR_INT SALV23Disrupt; // 9
};
static_assert(sizeof(SALV23VehicleData) == 10 * 8);

struct SALV23FlowData
{
	SCR_INT SALV23GenFlags; // 0
	SCR_INT SALV23FMProg; // 1
	SCR_INT SALV23InstProg; // 2
	SCR_INT PackedInt42102; // 3
	SCR_INT SALV23ScopeFlags; // 4
	SCR_ARRAY<uint64_t, 7> SALV23CFRCounts; // 5
	SCR_ARRAY<uint64_t, 7> SALV23CFRCrewCounts2; // 13, added b889g9
	SALV23VehicleData SALV23Vehicles; // 21
	SCR_ARRAY<uint64_t, 3> SALV23VehRobStatus; // 31
	SCR_INT SALV23Flags; // 35
	SCR_BOOL UNK_28; // 36
};
static_assert(sizeof(SALV23FlowData) == 37 * 8);

struct Bounty24STDData
{
	SCR_INT TargMis; // 0
	SCR_INT TargTar; // 1
	SCR_INT TargRwd; // 2
};
static_assert(sizeof(Bounty24STDData) == 3 * 8);

struct Bounty24FlowData
{
	SCR_INT UNK_0; // 0
	SCR_ARRAY<Bounty24STDData, 3> STD;
};
static_assert(sizeof(Bounty24FlowData) == 11 * 8);

struct Hacker24FlowData
{
	SCR_INT Hacker24GenFlags; // 0
	SCR_INT Hacker24InstFlags; // 1
	SCR_INT Hacker24ActiveRob; // 2
	SCR_INT UNK_3; // 3
	SCR_INT Hacker24Flags; // 4
	SCR_INT UNK_5; // 5
	uint64_t PAD_0006[8]; // 6 (unused?)
	SCR_BOOL PackedBool51273; // 14
	SCR_BOOL PackedBool51274; // 15
	SCR_BOOL PackedBool51275; // 16
};
static_assert(sizeof(Hacker24FlowData) == 17 * 8);

struct Drug25FlowData
{
	SCR_INT PAD_0000; // unused
	SCR_ARRAY<uint64_t, 3> DrugMissions; // 1
	SCR_INT LastMissionCompleted; // 6
};
static_assert(sizeof(Drug25FlowData) == 6 * 8);

struct M25FlowData
{
	SCR_INT M25GeneralBs; // 0
	SCR_INT M25Flags; // 1
	SCR_INT M25AviMissionCurrent; // 2
};
static_assert(sizeof(M25FlowData) == 3 * 8);

struct GPBD_Flow_Entry
{
	SCR_INT TunerFlowFlags; // 0
	SCR_INT TunerGenFlags; // 1
	SCR_INT TunerMisFlags; // 2
	SCR_INT TunerCompFlags; // 3
	SCR_INT TunerCurrent; // 4
	SCR_INT TunerCount; // 5
	SCR_INT TunerEarnings; // 6
	SCR_ARRAY<uint64_t, 3> TunerRobberies; // 7
	SCR_INT TunerJammerFlags; // 11
	SCR_INT TunerElevatorPassFlags; // 12
	SCR_INT TunerMethTankerFlags; // 13
	SCR_INT TunerBunkerFlags; // 14
	SCR_INT TunerBunkerTruckFlags; // 15
	SCR_ARRAY<uint64_t, 8> TunerContractPosixes; // 16
	SCR_BITSET<uint64_t> TunerCBVDeliveredFlags; // 25
	SCR_INT TunerCBVState; // 26
	FixerFlowData FixerFlow; // 27
	SCR_BOOL HasFixerUsbCollected; // 56
	ULPFlowData ULPFlow; // 57
	XM22FlowData XM22Flow; // 59
	SUM23AvopFlowData SUM23AvopFlow; // 62
	SALV23FlowData SALV23Flow; // 73
	Bounty24FlowData Bounty24Flow; // 110
	Hacker24FlowData Hacker24Flow; // 121
	Drug25FlowData Drug25Flow; // 138, added b889g9
	M25FlowData M25Flow; // 145, added b1013.17g9
	SCR_INT HeistFlags; // 148, added b1013.17g9
	SCR_INT UNK_149; // unused, added b1013.17g9
};
static_assert(sizeof(GPBD_Flow_Entry) == 149 * 8);

struct GPBD_Flow
{
	SCR_ARRAY<GPBD_Flow_Entry, 32> Entries;

	static GPBD_Flow* Get();
};
static_assert(sizeof(GPBD_Flow) == 4769 * 8);