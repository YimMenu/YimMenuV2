#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CVehicleDamageStatusDataNode : CSyncDataNodeInfrequent
{
public:
	uint8_t m_bullet_counts[6];        // 0xC0
	uint8_t m_front_damage_level;      // 0xC6
	uint8_t m_rear_damage_level;       // 0xC7
	uint8_t m_left_damage_level;       // 0xC8
	uint8_t m_right_damage_level;      // 0xC9
	uint8_t m_rear_left_damage_level;  // 0xCA
	uint8_t m_rear_right_damage_level; // 0xCB
	uint8_t m_windows_state[8];        // 0xCC
	float m_unk2[8];                   // 0xD4
	bool m_sirens_broken[20];          // 0xF4
	bool m_lights_broken[20];          // 0x108
	uint8_t m_front_bumper_state;      // 0x11E
	uint8_t m_rear_bumper_state;       // 0x11F
	uint8_t m_unk3[8];                 // 0x120
	bool m_has_damage_levels;          // 0x128
	bool m_has_broken_lights;          // 0x129
	bool m_has_broken_sirens;          // 0x12A
	bool m_has_broken_windows;         // 0x12B
	bool m_has_broken_bumpers;         // 0x12C
	bool m_has_bullets;                // 0x12D
	bool m_has_unk;                    // 0x12E
}; //Size: 0x00C8
static_assert(sizeof(CVehicleDamageStatusDataNode) == 0x130);
