#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CMigrationDataNode : CProjectBaseSyncDataNode
{
public:
	uint32_t m_ClonedState;           //0x00C0
	uint32_t m_ClonedPlayersThatLeft; //0x00C4
	uint32_t m_UnsyncedNodes;         //0x00C8
}; //Size: 0x00CC
static_assert(sizeof(CMigrationDataNode) == 0xD0);