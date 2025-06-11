#pragma once
#include <cstdint>

class CPedComponents
{
public:
	uint32_t m_ComponentBitset; //0x0
	char pad_0x4[4];            //0x4
	uint32_t unk_0x8[12];       //0x8
	uint32_t m_Drawables[12];   //0x38
	uint32_t m_Textures[12];    //0x68
	uint32_t m_Palettes[12];    //0x98

	inline uint32_t GetDrawable(int index) const
	{
		if (m_ComponentBitset & (1 << index))
		{
			return m_Drawables[index];
		}

		return 0;
	}

	inline uint32_t GetTexture(int index) const
	{
		if (m_ComponentBitset & (1 << index))
		{
			return m_Textures[index];
		}

		return 0;
	}

	inline uint32_t GetPalette(int index) const
	{
		if (m_ComponentBitset & (1 << index))
		{
			return m_Palettes[index];
		}

		return 0;
	}
};
static_assert(sizeof(CPedComponents) == 0xC8);