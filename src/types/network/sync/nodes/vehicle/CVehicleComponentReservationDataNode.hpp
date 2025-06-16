#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CVehicleComponentReservationDataNode : CSyncDataNodeInfrequent
{
public:
	bool m_HasComponentReservations;   //0x00C0
	uint32_t m_NumPedsUsingComponent;  //0x00C4
	uint16_t m_PedsUsingComponent[32]; //0x00C8
}; //Size: 0x00C8
static_assert(sizeof(CVehicleComponentReservationDataNode) == 0x108);
