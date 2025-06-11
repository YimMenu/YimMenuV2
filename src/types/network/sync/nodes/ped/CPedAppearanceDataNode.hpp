#pragma once
#include "../CPedComponents.hpp"
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPedAppearanceDataNode : CSyncDataNodeInfrequent
{
private:
	uint32_t unk_0xC0[6]; //0xC0
	uint32_t unk_0xD8[6]; //0xD8
public:
	class CPedComponents m_Components; //0xF0
private:
	char pad_0x1B8[8];  //0x1B8
	uint32_t unk_0x1C0; //0x1C0
	uint8_t unk_0x1C4;  //0x1C4
	uint8_t unk_0x1C5;  //0x1C5
	char pad_0x1C6[2];  //0x1C6
	uint32_t unk_0x1C8; //0x1C8
	uint32_t unk_0x1CC; //0x1CC
	uint32_t unk_0x1D0; //0x1D0
	bool unk_0x1D4;     //0x1D4
	bool unk_0x1D5;     //0x1D5
	bool unk_0x1D6;     //0x1D6
	uint8_t unk_0x1D7;  //0x1D7
	uint16_t unk_0x1D8; //0x1D8
	uint16_t unk_0x1DA; //0x1DA
	uint16_t unk_0x1DC; //0x1DC
	bool unk_0x1DE;     //0x1DE
	bool unk_0x1DF;     //0x1DF
	bool unk_0x1E0;     //0x1E0
	uint8_t unk_0x1E1;  //0x1E1
};
static_assert(sizeof(CPedAppearanceDataNode) == 0x1E8);