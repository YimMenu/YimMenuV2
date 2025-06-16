#pragma once

#include <cstdint>

namespace rage
{
	class datBitBuffer;
	class netSyncTree;

	class netSyncNodeBase
	{
	public:
		virtual ~netSyncNodeBase() = default;                                                                                              // 0x00
		virtual bool IsDataNode() = 0;                                                                                                     // 0x08
		virtual bool IsParentNode() = 0;                                                                                                   // 0x10
		virtual void MoveCommonDataOpsVFT() = 0;                                                                                           // 0x18
		virtual void ClearChildren() = 0;                                                                                                  // 0x20
		virtual void _0x28(void*, void*, void*, int* out_count) = 0;                                                                       // 0x28
		virtual bool Serialize(int flags, int flags2, void*, rage::datBitBuffer* buffer, int, void*, bool, int*, int* num_serialized) = 0; // 0x30
		virtual bool Deserialize(int flags, int flags2, rage::datBitBuffer* buffer, void*) = 0;                                            // 0x38
		virtual int CalculateSize(int flags, int flags2, void*) = 0;                                                                       // 0x40
		virtual int CalculateSize2(int flags, int flags2, bool) = 0;                                                                       // 0x48

		netSyncNodeBase* m_NextSibling; //0x0008
		netSyncNodeBase* m_PrevSibling; //0x0010
		netSyncTree* m_Root;            //0x0018
		netSyncNodeBase* m_Parent;      //0x0020

		uint32_t m_Flags1; //0x0028
		uint32_t m_Flags2; //0x002C
		uint32_t m_Flags3; //0x0030

		uint32_t m_Pad2; //0x0034

		netSyncNodeBase* m_FirstChild; //0x0038
	}; //Size: 0x0040
	static_assert(sizeof(netSyncNodeBase) == 0x40);
}