#pragma once
#include <cstdint>
#include "types/rage/vector.hpp"
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CDoorMovementDataNode : CSyncDataNodeFrequent
{
public:
	bool m_IsManualDoor; // 0xC0
	float m_OpenRatio;   // 0xC4
	bool m_Opening;      // 0xC8
	bool m_FullyOpen;    // 0xC9
	bool m_Closed;       // 0xCA
};
static_assert(sizeof(CDoorMovementDataNode) == 0xD0);