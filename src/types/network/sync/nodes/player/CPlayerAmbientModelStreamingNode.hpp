#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPlayerAmbientModelStreamingNode : CSyncDataNodeInfrequent
{
public:
	int m_AllowedPedModelStartOffset;           // 0xC0
	int m_AllowedVehicleModelStartOffset;       // 0xC4
	int m_VehicleAnimStreamingTargetEntrypoint; // 0xC8
	int16_t m_VehicleAnimStreamingTarget;       // 0xCC
};
static_assert(sizeof(CPlayerAmbientModelStreamingNode) == 0xD0);