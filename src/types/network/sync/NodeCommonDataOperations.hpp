#pragma once

namespace rage
{
	class datBitBuffer;
	class netSyncDataNode;
}

class NodeCommonDataOperations
{
public:
	virtual ~NodeCommonDataOperations() = default;
	virtual void ReadFromBuffer(rage::netSyncDataNode* node) {}; // 0x08
	virtual void WriteToBuffer(rage::netSyncDataNode* node) {};  // 0x10
	virtual void Unk() {};                                       // 0x18
	virtual int CalculateSize(rage::netSyncDataNode* node)
	{
		return 0;
	}; // 0x20
	virtual int CalculateSize2(rage::netSyncDataNode* node)
	{
		return 0;
	}; // 0x28
	virtual void LogSyncData(rage::netSyncDataNode* node) {};  // 0x30
	virtual void LogSyncData2(rage::netSyncDataNode* node) {}; // 0x38

	rage::datBitBuffer* m_Buffer;
};
static_assert(sizeof(NodeCommonDataOperations) == 0x10);