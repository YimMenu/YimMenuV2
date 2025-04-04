#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"
#include "types/rage/vector.hpp"

class CEntityOrientationDataNode : CSyncDataNodeFrequent
{
public:
	rage::matrix44 m_Eulers;
}; //Size: 0x0100
static_assert(sizeof(CEntityOrientationDataNode) == 0x100);