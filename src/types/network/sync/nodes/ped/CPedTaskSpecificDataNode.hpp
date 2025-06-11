#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPedTaskSpecificDataNode : CSyncDataNodeFrequent
{
public:
	uint32_t m_TaskIndex;          //0x00C0
	uint32_t m_TaskType;           //0x00C4
	uint32_t m_BufferSize;         //0x00C8
	uint8_t m_TaskDataBuffer[603]; //0x00CC
}; //Size: 0x0328
static_assert(sizeof(CPedTaskSpecificDataNode) == 0x328);