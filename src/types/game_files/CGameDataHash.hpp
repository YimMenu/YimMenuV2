#pragma once
#include "types/rage/ObfVar.hpp"
#include <array>

#pragma pack(push, 8)
class CGameDataHash
{
public:
	bool m_IsJapaneseVersion;
	std::array<rage::Obf32, 16> m_Data;
	char m_GameSkeletonHash[0x18]; // Obf64
};
static_assert(sizeof(CGameDataHash) == 0x11C);
#pragma pack(pop)
