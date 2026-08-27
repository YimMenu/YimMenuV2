#pragma once

class NetworkGameFilterMatchmakingComponent
{
public:
	// do not use for actual network filters, this will break things
	inline void SetParameter(const char* name, int index, int value)
	{
		std::strcpy(m_ParamNames[index], name);
		m_ParamMappings[index] = index;
		m_ParamValues[index] = value;
		m_EnabledParamsBitset |= (1 << index);

		if (m_NumParameters <= (uint32_t)index)
			m_NumParameters++;
	}

	uint32_t m_FilterType;          //0x0000
	char m_FilterName[24];          //0x0004
	uint32_t m_NumParameters;       //0x001C
	uint16_t m_GameMode;            //0x0020
	uint16_t m_SessionType;         //0x0022
	uint32_t m_ParamUnk[8];         //0x0024
	char m_ParamNames[8][24];       //0x0044
	char pad_0104[4];               //0x0104
	uint32_t m_ParamMappings[8];    //0x0108
	char pad_0128[352];             //0x0128
	uint32_t m_ParamValues[8];      //0x0288
	char pad_02A8[96];              //0x02A8
	uint32_t m_EnabledParamsBitset; //0x0308
	char pad_030C[8];               //0x030C
}; //Size: 0x0314
static_assert(sizeof(NetworkGameFilterMatchmakingComponent) == 0x314);
