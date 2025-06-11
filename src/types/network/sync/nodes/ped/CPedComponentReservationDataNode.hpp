#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPedComponentReservationDataNode : CSyncDataNodeInfrequent
{
public:
	uint32_t m_NumPedsUsingComponent;  //0x00C0
	uint16_t m_PedsUsingComponent[32]; //0x00C4
}; //Size: 0x00C8
static_assert(sizeof(CPedComponentReservationDataNode) == 0x108);
