#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

#include <cstdint>

class CPhysicalScriptGameStateDataNode : CSyncDataNodeInfrequent
{
public:
	bool m_Godmode;                             //0x00C0
	bool m_DontLoadCollision;                   //0x00C1
	bool m_FreezeOnCollisionLoad;               //0x00C2
	bool m_OnlyDamagedByPlayer;                 //0x00C3
	bool m_BulletProof;                         //0x00C4
	bool m_FireProof;                           //0x00C5
	bool m_ExplosionProof;                      //0x00C6
	bool m_CollisionProof;                      //0x00C7
	bool m_MeleeProof;                          //0x00C8
	bool m_CannotBeDamagedByRelationshipGroup;  //0x00C9
	bool m_CanOnlyBeDamagedByRelationshipGroup; //0x00CA
	bool m_SmokeProof;                          //0x00CB
	bool m_SteamProof;                          //0x00CC
	bool m_CanOnlyBeDamagedByParticipants;      //0x00CD
	bool m_DontResetProofsOnCleanupMission;     //0x00CE
	bool m_NoReassign;                          //0x00CF
	bool m_PassControlInTutorial;               //0x00D0
	bool m_VisibleInCutscene;                   //0x00D1
	bool m_VisibleInCutsceneRemainHack;         //0x00D2
	bool m_PickupByCargobobDisabled;            //0x00D3
	uint32_t m_RelationshipGroup;               //0x00D4
	uint32_t m_AlwaysClonedForPlayers;          //0x00D8
	bool m_ModifiedMaxSpeed;                    //0x00DC
	bool m_TriggerDamageEventForZeroDamage;     //0x00DD
	float m_MaxSpeed;                           //0x00E0
};
static_assert(sizeof(CPhysicalScriptGameStateDataNode) == 0xE8);