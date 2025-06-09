#pragma once
#include "types/script/types.hpp"

struct WeeklyChallenge_Entry
{
	SCR_INT ObjectiveId; // 0
	SCR_INT CurrentObjective; // 1
	SCR_INT ObjectiveCountOverride; // 2
	SCR_BOOL ObjectiveNotified; // 3
	SCR_BOOL ObjectiveRewarded; // 4
	SCR_BOOL UNK_5; // 5 (is this even actually used?)
};
static_assert(sizeof(WeeklyChallenge_Entry) == 6 * 8);

struct WeeklyChallenge
{
	SCR_ARRAY<WeeklyChallenge_Entry, 1> Entries; // 0
	SCR_INT DateObjectiveSet; // 7

	static WeeklyChallenge* Get();
};
static_assert(sizeof(WeeklyChallenge) == 8 * 8);