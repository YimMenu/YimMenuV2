#pragma once
#include "types/rage/vector.hpp"
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CVehicleProximityMigrationDataNode : CProjectBaseSyncDataNode
{
public:
	uint32_t m_MaxOccupants;
	bool m_HasOccupants[16];
	int16_t m_Occupants[16];
	char pad[16];
	bool m_OverridePosition;
	rage::fvector3 m_Position;
	std::int32_t m_VelocityX;
	std::int32_t m_VelocityY;
	std::int32_t m_VelocityZ;
	char pad3[116];
};
static_assert(sizeof(CVehicleProximityMigrationDataNode) == 0x1A0);