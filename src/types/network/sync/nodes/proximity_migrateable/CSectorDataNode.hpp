#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CSectorDataNode : CSyncDataNodeFrequent
{
public:
	uint16_t m_SectorX; //0xC0
	uint16_t m_SectorY; //0xC2
	uint16_t m_SectorZ; //0xC4
};
static_assert(sizeof(CSectorDataNode) == 0xC8);