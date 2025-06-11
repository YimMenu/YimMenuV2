#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

struct CPedTaskSequenceData
{
	int m_TaskType;       // 0x00
	int m_TaskDataSize;   // 0x04
	char m_TaskData[602]; // 0x08
};
static_assert(sizeof(CPedTaskSequenceData) == 0x264);

class CPedTaskSequenceDataNode : CSyncDataNodeFrequent
{
public:
	bool m_HasSequence;                  // 0xC0
	int m_SequenceResourceId;            // 0xC4
	int m_NumTasksInSequence;            // 0xC8
	CPedTaskSequenceData m_TaskData[10]; // 0xCC
	int m_Unk;                           // 0x18B4
};
static_assert(sizeof(CPedTaskSequenceDataNode) == 0x18B8);