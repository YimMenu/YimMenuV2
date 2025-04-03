#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"
#include "types/rage/vector.hpp"

#include <cstdint>

enum eVehicleGadgetType : uint32_t
{
	FORKS,
	SEARCH_LIGHT,
	PICK_UP_ROPE_WITH_HOOK,
	PICK_UP_ROPE_WITH_MAGNET,
	DIGGER_ARM,
	HANDLER_FRAME,
	BOMB_BAY,
};

struct CVehicleGadgetData
{
	eVehicleGadgetType m_Type; //0x0000
	uint8_t m_Data[95];        //0x0004
}; //Size: 0x64
static_assert(sizeof(CVehicleGadgetData) == 0x64);

class CVehicleGadgetDataNode : CSyncDataNodeFrequent
{
public:
	CVehicleGadgetData m_GadgetData[2]; //0x00C0
	rage::fvector3 m_ParentOffset;      //0x0190
	uint32_t m_GadgetCount;             //0x01A0
	bool m_HasParentOffset;             //0x01A4
};
static_assert(sizeof(CVehicleGadgetDataNode) == 0x1B0);