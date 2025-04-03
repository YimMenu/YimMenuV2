#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"
#include "types/network/sync/nodes/physical/CPhysicalHealthDataNode.hpp"

#include <cstdint>

class CHeliHealthDataNode : CPhysicalHealthDataNode // intentionally private since the physical health node fields aren't serialized
{
public:
	void* m_CommonDataOpsVFT;  //0x00E0 NodeCommonDataOperations
	void* m_CommonDataOpsNode; //0x00E8

	uint32_t m_MainRotorHealth;          //0x00F0
	uint32_t m_RearRotorHealth;          //0x00F4
	bool m_CanTailBoomBreakOff;          //0x00F8
	bool m_IsTailBoomBroken;             //0x00F9
	bool m_Unk;                          //0x00FA
	bool m_DisableExplodeFromBodyDamage; //0x00FB
	uint32_t m_BodyHealth;               //0x00FC
	uint32_t m_PetrolTankHealth;         //0x0100
	uint32_t m_EngineHealth;             //0x0104
	float m_UnkDeformationLevel;         //0x0108
	float m_Unk2DeformationLevel;        //0x010C
	float m_Unk3DeformationLevel;        //0x0110
};
static_assert(sizeof(CHeliHealthDataNode) == 0x118);