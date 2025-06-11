#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

struct CPhysicalHealthDataNode : CSyncDataNodeInfrequent
{
	bool unk_00C0;                 //0x00C0
	bool m_HasMaxHealthChanged;    //0x00C1
	uint32_t m_MaxHealth;          //0x00C4
	uint32_t m_CurrentHealth;      //0x00C8
	uint16_t m_WeaponDamageEntity; //0x00CC
	uint32_t m_WeaponDamageHash;   //0x00D0
	uint64_t unk_00D8;             //0x00D8
};
static_assert(sizeof(CPhysicalHealthDataNode) == 0xE0);