#pragma once
#include "../CPedComponents.hpp"
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPlayerAppearanceDataNode : CSyncDataNodeInfrequent
{
public:
	uint32_t unk_0xC0[60];               //0xC0
	class CPedComponents m_Components;   //0x1A0
	char pad_0x268[8];                   //0x268
	uint32_t unk_0x270[6];               //0x270
	uint32_t unk_0x288[6];               //0x288
	char pad_0x2A0[8];                   //0x2A0
	float unk_0x2A8;                     //0x2A8
	uint8_t unk_0x2AC;                   //0x2AC
	uint8_t unk_0x2AD;                   //0x2AD
	char pad_0x2AE[26];                  //0x2AE
	float m_shape_mix;                   //0x2C8
	float m_skin_mix;                    //0x2CC
	float m_third_mix;                   //0x2D0
	float unk_0x2D4;                     //0x2D4
	float unk_0x2D8[13];                 //0x2D8
	float unk_0x30C[13];                 //0x30C
	float unk_0x340[20];                 //0x340
	uint8_t unk_0x390[13];               //0x390
	uint8_t unk_0x39D[13];               //0x39D
	uint8_t unk_0x3AA[13];               //0x3AA
	uint8_t m_shape_first;               //0x3B7
	uint8_t m_shape_second;              //0x3B8
	uint8_t m_shape_third;               //0x3B9
	uint8_t m_skin_first;                //0x3BA
	uint8_t m_skin_second;               //0x3BB
	uint8_t m_skin_third;                //0x3BC
	uint8_t unk_0x3BD[13];               //0x3BD
	uint8_t unk_0x3CA[11];               //0x3CA
	int16_t unk_0x3D6;                   //0x3D6
	uint8_t unk_0x3D8;                   //0x3D8
	uint8_t unk_0x3D9;                   //0x3D9
	char pad_0x3DA[1];                   //0x3DA
	bool unk_0x3DB;                      //0x3DB
	bool unk_0x3DC;                      //0x3DC
	char pad_0x3DD[3];                   //0x3DD
	uint32_t unk_0x3E0;                  //0x3E0
	uint32_t unk_0x3E4;                  //0x3E4
	uint32_t unk_0x3E8;                  //0x3E8
	uint32_t unk_0x3EC;                  //0x3EC
	uint32_t unk_0x3F0;                  //0x3F0
	float unk_0x3F4;                     //0x3F4
	float m_blend_in_duration;           //0x3F8
	float m_blend_out_duration;          //0x3FC
	uint32_t m_anim_name_hash;           //0x400
	uint32_t m_anim_dict_index;          //0x404
	uint32_t m_anim_flags;               //0x408
	uint32_t unk_0x40C;                  //0x40C
	uint32_t unk_0x410;                  //0x410
	bool m_anim_task_active;             //0x414
	bool unk_0x415;                      //0x415
	bool m_task_move_active;             //0x416
	bool m_mobile_phone_task_active;     //0x417
	bool m_mobile_phone_gesture_active;  //0x418
	bool unk_0x419;                      //0x419
	uint32_t unk_0x41C;                  //0x41C
	uint32_t m_model_hash;               //0x420
	uint32_t m_voice_hash;               //0x424
	uint32_t m_phone_mode;               //0x428
	uint32_t unk_0x42C;                  //0x42C
	uint8_t m_parachute_tint_index;      //0x430
	uint8_t m_parachute_pack_tint_index; //0x431
	uint16_t m_respawn_object;           //0x432
	bool m_has_head_blend_data;          //0x434
	bool unk_0x435;                      //0x435
	bool m_has_respawn_object;           //0x436
	char pad_0x437;                      //0x437
	uint32_t unk_0x438_clip_maybe;       //0x438
	uint32_t unk_0x43C;                  //0x43C
	uint32_t unk_0x440;                  //0x440
	bool unk_0x444;                      //0x444
	bool unk_0x445;                      //0x445
	bool unk_0x446;                      //0x446
	uint8_t unk_0x447;                   //0x447
	uint16_t unk_0x448;                  //0x448
	uint16_t unk_0x44A;                  //0x44A
	uint16_t unk_0x44C;                  //0x44C
	bool unk_0x44E;                      //0x44E
	bool unk_0x44F;                      //0x44F
	bool unk_0x450;                      //0x450
	uint8_t unk_0x451;                   //0x451
	uint32_t unk_0x452;                  //0x452
	uint32_t unk_0x456;                  //0x456
};
static_assert(sizeof(CPlayerAppearanceDataNode) == 0x470);