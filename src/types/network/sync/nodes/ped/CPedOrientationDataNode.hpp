#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPedOrientationDataNode : CSyncDataNodeFrequent
{
public:
	float m_Heading;        //0x00C0
	float m_DesiredHeading; //0x00C4
};
static_assert(sizeof(CPedOrientationDataNode) == 0xC8);