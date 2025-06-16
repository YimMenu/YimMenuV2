#pragma once

#include "netSyncNodeBase.hpp"

namespace rage
{
	class netSyncDataNode : public netSyncNodeBase
	{
	public:
		uint32_t m_Flags4; //0x40
		uint32_t pad3;     //0x44
		uint64_t pad4;     //0x48

		netSyncDataNode* m_ParentData;  //0x50
		uint32_t m_ChildCount;          //0x58
		netSyncDataNode* m_Children[8]; //0x5C
		uint8_t m_SyncFrequencies[8];   //0x9C
		void* m_CommonDataOpsVFT;       //0xA8 wtf
	};
	static_assert(sizeof(netSyncDataNode) == 0xB0);
}