#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"
#include "types/rage/vector.hpp"

#include <cstdint>

class CPlayerCameraDataNode : CSyncDataNodeFrequent
{
public:
	rage::fvector3 m_FreeCamPos;         //0x00C0
	rage::fvector3 m_TargetOffset;       //0x00D0
	rage::fvector3 m_LockOnTargetOffset; //0x00E0
	rage::fvector3 m_0xF0;               //0x00F0
	float m_CameraX;                     //0x0100
	float m_CameraZ;                     //0x0104
	uint16_t m_FreeAimLockedOnTarget;    //0x0108
	bool m_FreeCam;                      //0x010A
	bool m_0x10B;                        //0x010B
	bool m_0x10C;                        //0x010C
	bool m_HasPositionOffset;            //0x010D
	bool m_0x10E;                        //0x010E
	bool m_IsLongRangeTarget;            //0x010F
	bool m_0x110;                        //0x0110
	bool m_0x111;                        //0x0111
	bool m_0x112;                        //0x0112
	bool m_0x113;                        //0x0113
	bool m_0x114;                        //0x0114
	bool m_0x115;                        //0x0115
	bool m_0x116;                        //0x0116
	bool m_0x117;                        //0x0117
	bool m_0x118;                        //0x0118
	bool m_0x119;                        //0x0119
	bool m_0x11A;                        //0x011A
};
static_assert(sizeof(CPlayerCameraDataNode) == 0x120);