#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPedScriptCreationDataNode : CProjectBaseSyncDataNode
{
public:
	bool m_StayInCarWhenJacked; //0x00C0
}; //Size: 0x00C1
static_assert(sizeof(CPedScriptCreationDataNode) == 0xC8);