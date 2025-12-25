#pragma once
#include <cstdint>

class MatchmakingAttributes
{
public:
	uint32_t m_GameMode;       //0x0000
	uint32_t m_NumParams;      //0x0004
	uint32_t m_ParamUnk[8];    //0x0008
	char m_ParamNames[8][24];  //0x0028
	uint32_t m_ParamValues[8]; //0x00E8
	uint32_t m_ParamBitset;    //0x0108
}; //Size: 0x010C
static_assert(sizeof(MatchmakingAttributes) == 0x10C);