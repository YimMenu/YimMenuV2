#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

#include <cstdint>

class CVehicleCreationDataNode : CProjectBaseSyncDataNode
{
public:
	uint32_t m_PopType;       //0x00C0
	uint32_t m_RandomSeed;    //0x00C4
	uint32_t m_ModelHash;     //0x00C8
	uint32_t m_VehicleStatus; //0x00CC
	uint32_t m_MaxHealth;     //0x00D0
	uint32_t m_CreationToken; //0x00D4
	bool m_CarBudget;         //0x00D8
	bool m_NeedsToBeHotwired; //0x00D9
	bool m_TiresDontBurst;    //0x00DA
	bool m_0xDB;              //0x00DB
};
static_assert(sizeof(CVehicleCreationDataNode) == 0xE0);
