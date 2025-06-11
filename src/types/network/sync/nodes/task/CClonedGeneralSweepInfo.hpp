#pragma once

#include <cstdint>

#pragma pack(push, 1)
class CClonedGeneralSweepInfo
{
public:
	char pad_0000[48];         //0x0000
	float m_track_point[4];    //0x0030
	uint16_t m_tracked_entity; //0x0040
	char pad_0042[14];         //0x0042
	float m_delta_per_second;  //0x0050
	char pad_0054[4];          //0x0054
	uint32_t m_low_clip;       //0x0058
	uint32_t m_med_clip;       //0x005C
	uint32_t m_high_clip;      //0x0060
	uint32_t m_clip_set_id;    //0x0064
	uint32_t m_sweep_flags;    //0x0068
	float m_turn_rate;         //0x006C
};
static_assert(sizeof(CClonedGeneralSweepInfo) == 0x70);
#pragma pack(pop)