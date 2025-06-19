#pragma once
#include "types/rage/ObfVar.hpp"
#include <array>

#pragma pack(push, 8)
class CGameDataHash
{
public:
	bool m_IsJapaneseVersion;
	std::array<rage::Obf32, 16> m_Data;
};
static_assert(sizeof(CGameDataHash) == 0x104);
#pragma pack(pop)