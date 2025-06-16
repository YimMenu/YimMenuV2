#pragma once

#include <cstdint>
#if 0

	#pragma pack(push, 1)
class ClonedTakeOffPedVariationInfo
{
public:
	char pad_0000[48]; //0x0000
	rage::fvector3 m_attach_offset; //0x0030
	char pad_003C[4]; //0x003C
	rage::fvector3 m_velocity; //0x0040
	char pad_004C[4]; //0x004C
	rage::fvector3 m_attach_offset_rotation; //0x0050
	char pad_005C[4]; //0x005C
	uint32_t m_clip_set_id; //0x0060
	uint32_t m_clip_id_ped; //0x0064
	uint32_t m_clip_id_prop; //0x0068
	int32_t m_variation_component; //0x006C
	uint32_t m_prop_hash; //0x0070
	int32_t m_attach_bone_tag; //0x0074
	float m_blend_in_delta_ped; //0x0078
	float m_blend_in_delta_prop; //0x007C
	float m_phase_to_blend_out; //0x0080
	float m_blend_out_delta; //0x0084
	float m_force_to_apply; //0x0088
	uint8_t m_variation_drawable_id; //0x008C
	uint8_t m_variation_drawable_alt_id; //0x008D
	char pad_008E[1]; //0x008E Drawable texture maybe?
	uint8_t m_running_flags; //0x008F
}; //Size: 0x0090
static_assert(sizeof(ClonedTakeOffPedVariationInfo) == 0x90);
	#pragma pack(pop)
#endif