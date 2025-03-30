#pragma once
#include "types/rage/vector.hpp"
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"
#include "types/script/CGameScriptObjInfo.hpp"

class CPickupPlacementCreationDataNode : CProjectBaseSyncDataNode
{
public:
	bool m_HasPickupData; //0x00C0
	rage::fvector3 m_PickupPos; //0x00D0
	rage::fvector4 m_PickupOrientation; //0x00E0
	uint32_t m_PickupType; //0x00F0
	uint32_t m_PickupFlags; //0x00F4
	uint32_t m_Amount; //0x00F8
	uint32_t m_CustomModel; //0x00FC
	uint32_t m_CustomRegenerationTime; //0x0100
	uint32_t m_TeamPermits; //0x0104
	CGameScriptObjInfo m_ScriptObjectInfo; //0x0108
}; //Size: 0x0160
static_assert(sizeof(CPickupPlacementCreationDataNode) == 0x160);
