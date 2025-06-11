#pragma once
#include "CGameScriptId.hpp"

class CGameScriptObjInfo
{
public:
	virtual ~CGameScriptObjInfo() = default;

	int m_NetworkId;          // 0x8 (the one you get from VEH_TO_NET etc., not the network object id)
	uint16_t m_Unk;           // 0xC
	CGameScriptId m_ScriptId; // 0x10
};
static_assert(sizeof(CGameScriptObjInfo) == 0x50);