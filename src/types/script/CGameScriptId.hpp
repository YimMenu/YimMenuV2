#pragma once
#include "scriptId.hpp"

class CGameScriptId : public rage::scriptId
{
public:
	void Deserialize(rage::datBitBuffer& buffer);

	std::int32_t m_Timestamp;     // 0x30
	std::int32_t m_PositionHash;  // 0x34
	std::int32_t m_InstanceId;    // 0x38
	std::int32_t m_UniqueId;      // 0x3C
};
static_assert(sizeof(CGameScriptId) == 0x40);