#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"
#include "types/script/CGameScriptObjInfo.hpp"

class CPickupCreationDataNode : CProjectBaseSyncDataNode
{
public:
	bool m_HasPlacement;                   //0x00C0
	char pad_00C1[7];                      //0x00C1
	CGameScriptObjInfo m_ScriptObjectInfo; //0x00C8
	uint32_t m_PickupHash;                 //0x0118
	uint32_t m_Amount;                     //0x011C
	uint32_t m_CustomModel;                //0x0120
	uint32_t m_LifeTime;                   //0x0124
	uint32_t m_WeaponComponent[12];        //0x0128
	uint32_t m_NumWeaponComponents;        //0x0154
	uint32_t m_TintIndex;                  //0x0158
	bool m_PlayerGift;                     //0x015C
	bool unk_015D;                         //0x015D
	char pad_015E[6];                      //0x015E
	uint32_t unk_0164;                     //0x0164
	bool unk_0168;                         //0x0168
}; //Size: 0x0170
static_assert(sizeof(CPickupCreationDataNode) == 0x170);