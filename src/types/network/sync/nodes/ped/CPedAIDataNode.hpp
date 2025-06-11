#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPedAIDataNode : CSyncDataNodeInfrequent
{
public:
	uint32_t m_RelationshipGroup; //0x00C0
	uint32_t m_DecisionMakerType; //0x00C4
}; //Size: 0x00C8
static_assert(sizeof(CPedAIDataNode) == 0xC8);
