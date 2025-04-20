#pragma once
#include "types.hpp"

struct TIMER
{
	SCR_INT Time;
	SCR_BOOL IsInitialized;
};
static_assert(sizeof(TIMER) == 2 * 8);