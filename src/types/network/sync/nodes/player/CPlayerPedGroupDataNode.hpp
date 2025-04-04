#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CGroup;
class CPed;
struct CGroupMember
{
	std::int16_t m_ObjectId;
	CPed* m_Ped; // this isn't serialized
};
static_assert(sizeof(CGroupMember) == 0x10);

class CPlayerPedGroupDataNode : CSyncDataNodeInfrequent
{
public:
	char m_unused[0x10];		   // 0xC0
	CGroup* m_Group;			   // 0xD0 (not serialized)
	CGroupMember m_Members[7];	   // 0xD8
	CGroupMember m_Leader;         // 0x148
	char m_unused2[8];             // 0x158
	float m_MaxSeparation;         // 0x160
	char m_unused3[0xC];           // 0x164
	int m_PopType;                 // 0x170
	uint8_t m_0x174;               // 0x174
	bool m_NeedsGroupEventScan;    // 0x175
	char m_0x176[18];              // 0x176
};
static_assert(sizeof(CPlayerPedGroupDataNode) == 0x188);