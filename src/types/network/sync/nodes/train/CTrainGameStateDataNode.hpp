#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CTrainGameStateDataNode : CSyncDataNodeInfrequent
{
public:
	bool m_IsEngine;               //0x00C0
	bool m_IsCaboose;              //0x00C1
	bool m_IsMissionTrain;         //0x00C2
	bool m_Direction;              //0x00C3
	bool m_HasPassengerCarriages;  //0x00C4
	bool m_RenderDerailed;         //0x00C5
	bool unk_00C6;                 //0x00C6
	bool unk_00C7;                 //0x00C7
	uint16_t m_EngineId;           //0x00C8
	int8_t m_TrainConfigIndex;     //0x00CA
	int8_t m_CarriageConfigIndex;  //0x00CB
	int8_t m_TrackId;              //0x00CC
	char pad_00CD[3];              //0x00CD
	float m_DistanceFromEngine;    //0x00D0
	float m_CruiseSpeed;           //0x00D4
	uint16_t m_LinkedToBackwardId; //0x00D8
	uint16_t m_LinkedToForwardId;  //0x00DA
	uint32_t m_TrainState;         //0x0DC
	bool unk_00E0;                 //0x00E0
	bool m_ForceDoorsOpen;         //0x0E1
}; //Size: 0x00E4
static_assert(sizeof(CTrainGameStateDataNode) == 0xE8);