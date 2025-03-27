#pragma once

// of all the things they backported from RDR this is probably the dumbest
class PoolEncryption
{
public:
	bool m_IsSet;      //0x0000
	uint64_t m_First;  //0x0008
	uint64_t m_Second; //0x0010
}; //Size: 0x0018
static_assert(sizeof(PoolEncryption) == 0x18);