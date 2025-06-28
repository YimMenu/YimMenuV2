#pragma once
#include "types.hpp"

// names taken from GTA5_Enhanced.exe+0x2252260 (0F 84 7F 01 00 00 4C 8B 47 20 48 8D 15 -0x21) (SCRIPT_EVENT_FPOM)
struct MP_SCRIPT_DATA
{
	SCR_INT MissionIndex; // this is an enum
	SCR_INT Variation;
	SCR_INT Creator;
	TEXT_LABEL_23 CloudFileName;
	SCR_INT SharedRegId;
	uint64_t PAD_0005[6]; // not serialized in the metric
	SCR_INT InstanceId; 
	SCR_INT UniqueId;
	SCR_INT BitSet;
	SCR_INT GenericInt;
	SCR_INT TruckBitSet;
};
static_assert(sizeof(MP_SCRIPT_DATA) == 21 * 8);