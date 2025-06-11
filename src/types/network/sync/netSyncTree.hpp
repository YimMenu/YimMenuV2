#pragma once
#include "netSyncNodeBase.hpp"

namespace rage
{
	class netSyncTree
	{
	public:
		virtual ~netSyncTree() = default;

		char pad_0008[8];                  //0x0008
		netSyncNodeBase* m_NextSyncNode;   //0x0010
		netSyncNodeBase* m_LastSyncNode;   //0x0018
		uint32_t m_ChildNodeCount;         //0x0020
		uint32_t m_UnkArrayCount;          //0x0024
		char pad_0028[8];                  //0x0028
		netSyncNodeBase* m_ChildNodes[42]; //0x0030
		uint32_t m_ChildNodeMaxCount;      //0x0180
		netSyncNodeBase* m_UnkArray[32];   //0x0188
		uint32_t m_UnkArrayMaxCount;       //0x0288
		char pad_0290[560];                //0x0290
	}; //Size: 0x0030
	static_assert(sizeof(netSyncTree) == 0x4C0);
}