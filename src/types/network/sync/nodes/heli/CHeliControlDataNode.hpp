#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"
#include "types/network/sync/nodes/vehicle/CVehicleControlDataNode.hpp"

#include <cstdint>

class CHeliControlDataNode : CVehicleControlDataNode
{
public:
	void* m_CommonDataOpsVFT;  //0x0130 NodeCommonDataOperations
	void* m_CommonDataOpsNode; //0x0138

	float m_YawControl;              //0x0140
	float m_PitchControl;            //0x0144
	float m_RollControl;             //0x0148
	float m_ThrottleControl;         //0x014C
	bool m_EngineOff;                //0x0150
	int m_LandingGearState;          //0x0154
	bool m_HasLandingGear;           //0x0158
	bool m_HasVehicleTask;           //0x0159
	bool m_IsThrusterModel;          //0x015A
	float m_ThrusterSideRcsThrottle; //0x015C
	float m_ThrusterThrottle;        //0x0160
	bool m_Unk8;                     //0x0164
};
static_assert(sizeof(CHeliControlDataNode) == 0x168);