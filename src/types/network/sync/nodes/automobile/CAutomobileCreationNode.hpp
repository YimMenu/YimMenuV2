#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CAutomobileCreationDataNode : CProjectBaseSyncDataNode
{
public:
	bool m_AllDoorsClosed;  //0x00C0
	bool m_DoorsClosed[10]; //0x00C1
};
static_assert(sizeof(CAutomobileCreationDataNode) == 0xD0);