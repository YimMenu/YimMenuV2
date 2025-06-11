#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CSectorPositionDataNode : CSyncDataNodeFrequent
{
public:
	float m_SectorPosX; //0x00C0
	float m_SectorPosY; //0x00C4
	float m_SectorPosZ; //0x00C8
}; //Size: 0x00CC
static_assert(sizeof(CSectorPositionDataNode) == 0xD0);