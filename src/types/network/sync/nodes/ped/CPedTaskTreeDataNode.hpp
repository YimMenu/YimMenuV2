#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

struct CPedTaskData
{
	int m_TaskType;   // 0x00
	int m_Priority;   // 0x04
	int m_TreeDepth;  // 0x08
	int m_SequenceId; // 0x0C
	bool m_Active;    // 0x10
};
static_assert(sizeof(CPedTaskData) == 0x14);

class CPedTaskTreeDataNode : CSyncDataNodeFrequent
{
public:
	CPedTaskData m_Tasks[8];  // 0xC0
	int m_TaskBitset;         // 0x160
	int m_ScriptCommand;      // 0x164
	int m_ScriptCommandStage; // 0x168
};
static_assert(sizeof(CPedTaskTreeDataNode) == 0x170);