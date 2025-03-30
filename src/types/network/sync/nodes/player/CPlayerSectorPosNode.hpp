#pragma once
#include <cstdint>
#include "types/rage/vector.hpp"
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPlayerSectorPosNode : CSyncDataNodeFrequent
{
public:
    // this is not a vector!
	float m_SectorPosX;  // 0xC0
	float m_SectorPosY;  // 0xC4
	float m_SectorPosZ;  // 0xC8
    bool m_IsStandingOnEntity; //0x00CC
    bool unk_00CD; //0x00CD
    bool unk_00CE; //0x00CE
    char pad_00CF[1]; //0x00CF
    uint16_t m_EntityStandingOn; //0x00D0
    char pad_00D2[12]; //0x00D2
    rage::fvector3 m_StandingOnEntityOffset; //0x00E0
    char pad_00F0[4]; //0x00F0
    uint32_t m_StealthNoise; //0x00F4
}; //Size: 0x0100
static_assert(sizeof(CPlayerSectorPosNode) == 0x100);