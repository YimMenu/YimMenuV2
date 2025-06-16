#pragma once
#include "types/script/Timer.hpp"
#include "types/script/types.hpp"

namespace rage
{
	class scrThread;
}

struct RCBanditoTimeTrialData
{
	SCR_INT Location; // 0
	SCR_INT CountdownStatus; // 1
	SCR_INT Status; // 2
	SCR_INT RespawnStatus; // 3
	SCR_ARRAY<uint64_t, 1> Flags; // 4
	TIMER Timer1; // 6
	TIMER Timer2; // 8
	TIMER Timer3; // 10
	TIMER Timer4; // 12
	BLIP_INDEX TrialBlipIndex; // 14
	BLIP_INDEX CheckpointBlipIndex; // 15
	SCR_INT CheckpointIndex1; // 16
	SCR_INT CheckpointIndex2; // 17
	SCR_INT UNK_17; // 18
	SCR_INT Checkpoint; // 19
	SCR_INT Partime; // 20
	SCR_INT BestTime; // 21
	uint64_t PAD_0022[22]; // 22

	static RCBanditoTimeTrialData* Get(rage::scrThread* thread);
};
static_assert(sizeof(RCBanditoTimeTrialData) == 44 * 8);