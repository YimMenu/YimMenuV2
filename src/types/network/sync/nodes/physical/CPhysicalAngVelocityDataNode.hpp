#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPhysicalAngVelocityDataNode : CSyncDataNodeFrequent
{
public:
	int32_t m_AngVelocityX;
	int32_t m_AngVelocityY;
	int32_t m_AngVelocityZ;
}; // 0x00CC
static_assert(sizeof(CPhysicalAngVelocityDataNode) == 0xD0);