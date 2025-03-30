#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"
#include "types/rage/vector.hpp"

struct ObjectCreationTelemetry
{
	uint32_t unk_0000;     //0x0000 "et"
	uint32_t m_ScriptHash; //0x0004 "es"
	uint32_t unk_0008;     //0x0008 "ep"
	bool unk_000C;         //0x000C "ec"
	bool m_HasData;        //0x000D
};

class CObjectCreationDataNode : CProjectBaseSyncDataNode
{
public:
	ObjectCreationTelemetry m_TelemetryData; //0x00C0 -- netObject + 0x270
	uint16_t unk_00D0;                       //0x00D0
	char pad_0xC2[14];                       //0x00D2
	rage::fvector4 m_ObjectOrientation[4];   //0x00E0
	rage::fvector3 m_DummyPosition;          //0x0120
	rage::fvector3 m_ObjectPosition;         //0x0130
	rage::fvector3 m_ScriptGrabPosition;     //0x0140
	char pad_0150[8];                        //0x0150
	float m_ScriptGrabRadius;                //0x0158
	uint32_t m_CreatedBy;                    //0x015C
	uint32_t m_Model;                        //0x0160
	uint32_t m_FragGroupIndex;               //0x0164
	uint32_t m_OwnershipToken;               //0x0168
	uint32_t unk_016C;                       //0x016C
	bool m_NoReassign;                       //0x0170
	bool unk_0171;                           //0x0171
	bool m_PlayerWantsControl;               //0x0172
	bool m_HasInitPhysics;                   //0x0173
	bool m_ScriptGrabbedFromWorld;           //0x0174
	bool m_IsFragObject;                     //0x0175
	bool m_IsBroken;                         //0x0176
	bool unk_0177;                           //0x0177
	bool m_HasExploded;                      //0x0178
	bool m_KeepRegistered;                   //0x0179
	bool unk_017A;                           //0x017A
	bool unk_017B;                           //0x017B
	bool unk_017C;                           //0x017C
}; //Size: 0x0180
static_assert(sizeof(CObjectCreationDataNode) == 0x180);