#pragma once
#include "types/script/types.hpp"

namespace rage
{
	class scrThread;
}

struct HSWTimeTrialData
{
	SCR_INT Status; // 0
	SCR_ARRAY<uint64_t, 1> Flags; // 1
	SCR_INT Location; // 3
	SCR_INT PersonalBest; // 4
	SCR_INT UNK_5; // 5
	BLIP_INDEX BlipIndex; // 6
	SCR_INT CheckpointIndex; // 7

	static HSWTimeTrialData* Get(rage::scrThread* thread);
};
static_assert(sizeof(HSWTimeTrialData) == 8 * 8);