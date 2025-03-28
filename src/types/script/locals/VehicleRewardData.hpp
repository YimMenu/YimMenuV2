#pragma once
#include "../types.hpp"

namespace rage
{
	class scrThread;
}

struct VEHICLE_REWARD_DATA
{
	uint64_t PAD_0000[3];
	SCR_INT TransactionStatus; // 4
	SCR_INT Garage; // 5
	SCR_INT GarageOffset; // 6
	SCR_INT ControlStatus; // 7
	uint64_t PAD_0008[40];

	static VEHICLE_REWARD_DATA* Get(rage::scrThread* thread);
};
static_assert(sizeof(VEHICLE_REWARD_DATA) == 47 * 8);