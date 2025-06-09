#pragma once
#include "types/script/types.hpp"

namespace rage
{
	class scrThread;
}

struct BikeTimeTrialData
{
	SCR_INT Status; // 0
	SCR_ARRAY<uint64_t, 1> Flags; // 1
	SCR_INT Location; // 3
	SCR_INT UNK_4; // 4
	SCR_INT BlipIndex; // 5
	BLIP_INDEX CheckpointIndex; // 6

	static BikeTimeTrialData* Get(rage::scrThread* thread);
};
static_assert(sizeof(BikeTimeTrialData) == 7 * 8);