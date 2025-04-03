#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"
#include "types/script/CGameScriptObjInfo.hpp"

struct CDoorScriptInfoDataNode : CSyncDataNodeInfrequent
{
public:
	bool m_HasScriptInfo;            //0x00C0
	CGameScriptObjInfo m_ScriptInfo; //0x00C8
	uint32_t m_DoorSystemHash;       //0x0118
	bool m_ExistingDoorSystemEntry;  //0x011C
};
static_assert(sizeof(CDoorScriptInfoDataNode) == 0x120);