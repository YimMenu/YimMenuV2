#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPedHealthDataNode : CSyncDataNodeInfrequent
{
public:
	uint32_t unk_00C0;                //0x00C0
	uint32_t m_Health;                //0x00C4
	uint32_t m_Armor;                 //0x00C8
	uint32_t unk_00CC;                //0x00CC
	uint32_t unk_00D0;                //0x00D0
	uint32_t m_WeaponDamageHash;      //0x00D4
	uint32_t m_HurtEndTime;           //0x00D8
	uint32_t m_WeaponDamageComponent; //0x00DC
	uint16_t m_WeaponDamageEntity;    //0x00E0
	bool m_HasMaxHealth;              //0x00E2
	bool m_HasDefaultArmor;           //0x00E3
	bool unk_00E4;                    //0x00E4
	bool m_KilledWithHeadshot;        //0x00E5
	bool m_KilledWithMelee;           //0x00E6
	char m_HurtStarted;               //0x00E7
	bool unk_00E8;                    //0x00E8
	bool unk_00E9;                    //0x00E9
};
static_assert(sizeof(CPedHealthDataNode) == 0xF0);