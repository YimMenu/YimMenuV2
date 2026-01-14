#pragma once

class NetworkGameFilterMatchmakingComponent
{
public:
	// do not use for actual network filters, this will break things
	inline void SetParameter(const char* name, int index, int value)
	{
		std::strcpy(m_param_names[index], name);
		m_param_mappings[index] = index;
		m_param_values[index] = value;
		m_enabled_params_bitset |= (1 << index);

		if (m_num_parameters <= (uint32_t)index)
			m_num_parameters++;
	}

	uint32_t m_filter_type;           //0x0000
	char m_filter_name[24];           //0x0004
	uint32_t m_num_parameters;        //0x001C
	uint16_t m_game_mode;             //0x0020
	uint16_t m_session_type;          //0x0022
	uint32_t m_param_unk[8];          //0x0024
	char m_param_names[8][24];        //0x0044
	char pad_0104[4];                 //0x0104
	uint32_t m_param_mappings[8];     //0x0108
	char pad_0128[352];               //0x0128
	uint32_t m_param_values[8];       //0x0288
	char pad_02A8[96];                //0x02A8
	uint32_t m_enabled_params_bitset; //0x0308
	char pad_030C[8];                 //0x030C
}; //Size: 0x0314
static_assert(sizeof(NetworkGameFilterMatchmakingComponent) == 0x314);
