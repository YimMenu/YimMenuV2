#pragma once
#include <cstdint>
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPhysicalGameStateDataNode : CSyncDataNodeInfrequent
{
public:
	bool m_IsVisible; // 0xC0
	bool m_flag2;     // 0xC1
	bool m_flag3;     // 0xC2
	bool m_flag4;     // 0xC3
	char m_pad;       // 0xC4
	uint32_t m_val1;  // 0xC8
	int16_t m_unk204; // 0xCC
	bool m_unk5;      // 0xCE
}; // 0x00CC
static_assert(sizeof(CPhysicalGameStateDataNode) == 0xD0);