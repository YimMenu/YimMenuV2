#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

#include <cstdint>

class CPedInventoryDataNode : CSyncDataNodeInfrequent
{
public:
	char pad_0000[5280];           //0x00C0
	uint32_t m_Items[110];         //0x1560
	uint32_t m_NumItems;           //0x1718
	uint32_t m_Ammos[65];          //0x171C
	uint32_t m_AmmoQuantities[65]; //0x1820
	uint32_t m_NumAmmos;           //0x1924
	uint8_t unk_1680[110];         //0x1928
	uint8_t unk_16E9[110];         //0x1996
	char pad_1680[1320];           //0x1A04
	bool m_InfiniteAmmos[65];      //0x1F2C
	bool m_AmmoAllInfinite;        //0x1F6D
};
static_assert(sizeof(CPedInventoryDataNode) == 0x1F70);