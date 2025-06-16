#pragma once
#include "types/script/types.hpp"

struct DailyObjectivesState
{
	SCR_BOOL Completed; // 0
	SCR_ARRAY<uint64_t, 3> Objective; // 1

	static DailyObjectivesState* Get();
};
static_assert(sizeof(DailyObjectivesState) == 5 * 8);