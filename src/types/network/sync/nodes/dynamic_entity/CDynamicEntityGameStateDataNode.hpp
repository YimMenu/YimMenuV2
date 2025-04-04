#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

#include <cstdint>

struct CDecorator
{
	uint32_t m_Type;
	uint32_t m_NameHash;
	uint32_t m_Value;
};

class CDynamicEntityGameStateDataNode : CSyncDataNodeInfrequent
{
public:
	uint32_t m_InteriorIndex; //0x00C0
	bool unk_00C4;            //0x00C4
	bool unk_00C5;            //0x00C5
	uint32_t m_DecorCount;    //0x00C8
	CDecorator m_Decors[11];  //0x00CC
};
static_assert(sizeof(CDynamicEntityGameStateDataNode) == 0x150);