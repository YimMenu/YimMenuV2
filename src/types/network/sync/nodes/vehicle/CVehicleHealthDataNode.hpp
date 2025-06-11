#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CVehicleHealthDataNode : CSyncDataNodeInfrequent
{
public:
	float m_tires_unk14[10];           //0x00C0
	float m_tires_open_wheel_heat[10]; //0x00E8
	bool m_tires_bursted[10];          //0x0110
	bool m_tires_bursted_on_rim[10];   //0x011A
	bool m_tires_unk11[10];            //0x0124
	bool m_tires_unk12[10];            //0x012E
	uint64_t m_unk24;                  //0x0138
	int32_t m_engine_health;           //0x0140
	uint32_t m_petrol_tank_health;     //0x0144
	uint32_t m_num_tires;              //0x0148
	bool m_tires_fine;                 //0x014C
	bool m_unk7;                       //0x014D
	char pad_014E[1];                  //0x014E
	bool m_health_changed;             //0x014F
	uint32_t m_health;                 //0x0150
	uint32_t m_body_health;            //0x0154
	uint32_t m_damage_weapon;          //0x0158
	int16_t m_damager_net_id;          //0x015C
	uint8_t m_total_repairs;           //0x015E
	uint8_t m_unk21;                   //0x015F
	bool m_unk1;                       //0x0160
	bool m_unk2;                       //0x0161
	bool m_body_health_changed;        //0x0162
	uint32_t m_pad2;                   // 0x0164
}; //Size: 0x0380
static_assert(sizeof(CVehicleHealthDataNode) == 0x168);