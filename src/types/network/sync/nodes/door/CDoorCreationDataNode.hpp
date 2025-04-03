#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"
#include "types/rage/vector.hpp"

#include <cstdint>

class CDoorCreationDataNode : CProjectBaseSyncDataNode
{
public:
	uint32_t m_ModelHash;           //0x00C0
	rage::fvector3 m_Position;      //0x00D0
	float m_Heading;                //0x00E0 -- added b3258
	uint32_t m_DoorSystemHash;      //0x00E4 -- added b3258
	class CObject* m_Door;          //0x00E8
	bool m_IsScriptDoor;            //0x00F0
	bool m_PlayerWantsControl;      //0x00F1
	bool m_ExistingDoorSystemEntry; //0x00F2 -- added b3258
}; //Size: 0x0100
static_assert(sizeof(CDoorCreationDataNode) == 0x100);