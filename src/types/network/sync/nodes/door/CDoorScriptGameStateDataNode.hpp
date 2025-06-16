#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

struct CDoorScriptGameStateDataNode : CSyncDataNodeInfrequent
{
public:
	uint32_t m_DoorSystemState; // 0xC0
	float m_AutomaticDistance;  // 0xC4
	float m_SlideRate;          // 0xC8
	bool m_HasBrokenFlags;      // 0xCC
	uint32_t m_BrokenFlags;     // 0xD0
	bool m_HasDamagedFlags;     // 0xD4
	uint32_t m_DamagedFlags;    // 0xD8
	bool m_HoldOpen;            // 0xDC
};
static_assert(sizeof(CDoorScriptGameStateDataNode) == 0xE0);