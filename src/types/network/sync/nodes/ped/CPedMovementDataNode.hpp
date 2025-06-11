#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPedMovementDataNode : CSyncDataNodeFrequent
{
public:
	bool m_HasDesiredMoveBlendRatioX; //0x00C0
	bool m_HasDesiredMoveBlendRatioY; //0x00C1
	bool unk_00C2;                    //0x00C2
	float m_DesiredMoveBlendRatioX;   //0x00C4
	float m_DesiredMoveBlendRatioY;   //0x00C8
	float unk_00CC;                   //0x00CC
	float m_DesiredPitch;             //0x00D0
}; //Size: 0x00D4
static_assert(sizeof(CPedMovementDataNode) == 0xD8);