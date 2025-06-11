#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CGlobalFlagsDataNode : CSyncDataNodeInfrequent
{
public:
	uint32_t m_GlobalFlags;    //0x00C0
	uint32_t m_OwnershipToken; //0x00C4
}; //Size: 0x00C8
static_assert(sizeof(CGlobalFlagsDataNode) == 0xC8);