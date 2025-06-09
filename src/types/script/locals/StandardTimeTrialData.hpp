#pragma once
#include "types/script/types.hpp"
#include "types/script/Timer.hpp"

namespace rage
{
	class scrThread;
}

struct StandardTimeTrialData
{
	SCR_VEC3 StartCoords; // 0
	SCR_VEC3 EndCoords; // 4
	SCR_FLOAT StartHeading; // 5
	SCR_FLOAT EndHeading; // 6
	SCR_VEC3 vStartDirection; // 7
	SCR_INT Location; // 11
	SCR_INT Flags; // 12
	TIMER Timer1; // 13
	TIMER Timer2; // 15
	TIMER Timer3; // 17
	TIMER Timer4; // 19
	BLIP_INDEX VehBlipIndex; // 21
	VEHICLE_INDEX VehicleIndex; // 22
	SCR_INT ReturnToVehicleTime; // 23
	SCR_INT ParTime; // 24
	SCR_INT PersonalBest; // 25
	BLIP_INDEX TrialBlipIndex; // 26
	uint64_t PAD_0027[23]; // 27

	static StandardTimeTrialData* Get(rage::scrThread* thread);
};
static_assert(sizeof(StandardTimeTrialData) == 50 * 8);