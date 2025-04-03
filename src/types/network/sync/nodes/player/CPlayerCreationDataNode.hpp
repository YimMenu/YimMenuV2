#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

#include <cstdint>

class CPlayerCreationDataNode : CProjectBaseSyncDataNode
{
public:
	uint32_t m_ModelHash;      //0x00C0
	uint32_t m_NumUnk;         //0x00C4
	char unk_struct_0xC8[192]; //0x00C8
	uint32_t m_NumScars;       //0x0188
	char m_scar_struct[180];   //0x0190
	bool unk_0240;             //0x0240
	char pad_0241[15];         //0x0241
};
static_assert(sizeof(CPlayerCreationDataNode) == 0x250);