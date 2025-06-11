#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

struct CEntityScriptGameStateDataNode : CSyncDataNodeInfrequent
{
	bool m_Fixed;                       //0x00C0
	bool m_UsesCollision;               //0x00C1
	bool m_CompletelyDisabledCollision; //0x00C2
}; //Size: 0x00C3
static_assert(sizeof(CEntityScriptGameStateDataNode) == 0xC8);