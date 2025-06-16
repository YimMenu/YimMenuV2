#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPedCreationDataNode : CProjectBaseSyncDataNode
{
public:
	uint32_t m_PopType;                //0x00C0
	uint32_t m_ModelHash;              //0x00C4
	uint32_t m_RandomSeed;             //0x00C8
	uint32_t m_MaxHealth;              //0x00CC
	bool m_SpawnInVehicle;             //0x00D0
	char pad_0xD1[1];                  //0x00D1
	uint16_t m_VehicleId;              //0x00D2
	uint32_t m_VehicleSeat;            //0x00D4
	bool m_HasProp;                    //0x00D8
	char pad_0xD9[3];                  //0x00D9
	uint32_t m_PropModel;              //0x00DC
	bool m_IsStanding;                 //0x00E0
	bool m_IsRespawnObjectId;          //0x00E1
	bool m_IsRespawnFlaggedForRemoval; //0x00E2
	bool m_HasAttrDamageToPlayer;      //0x00E3
	uint8_t m_AttrDamageToPlayer;      //0x00E4
	uint32_t m_VoiceHash;              //0x00E8
}; //Size: 0x00EC
static_assert(sizeof(CPedCreationDataNode) == 0xF0);