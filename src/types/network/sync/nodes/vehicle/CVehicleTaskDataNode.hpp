#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CVehicleTaskDataNode : CSyncDataNodeInfrequent
{
public:
	uint32_t m_TaskType;     // 0xC0
	uint32_t m_TaskDataSize; // 0xC4
	char m_TaskData[255];    // 0xC8
}; //Size: 0x0180
static_assert(sizeof(CVehicleTaskDataNode) == 0x1C8);