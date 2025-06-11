#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPedMovementGroupDataNode : CSyncDataNodeFrequent
{
public:
	float m_unk;                           // 0xC0 (CTaskMotionInAutomobile+0x1EC)
	uint32_t m_MovementTaskInded;          // 0xC4
	uint32_t m_MovementTaskStage;          // 0xC8
	uint32_t m_MovementGroup;              // 0xCC
	uint32_t m_OverriddenWeaponGroup;      // 0xD0
	uint32_t m_OverriddenUnkGroup;         // 0xD4 (SET_PED_ALTERNATE_MOVEMENT_ANIM?)
	bool m_IsCrouching;                    // 0xD8
	bool m_IsStealthy;                     // 0xD9
	bool m_IsStrafing;                     // 0xDA
	bool m_IsRagdolling;                   // 0xDB
	bool m_IsRagdollConstraintAnkleActive; // 0xDC
	bool m_IsRagdollConstraintWristActive; // 0xDD
	char m_pad1[2];                        // 0xDE
	char m_TennisData[0x20];               // 0xE0 TODO
};
static_assert(sizeof(CPedMovementGroupDataNode) == 0x100);