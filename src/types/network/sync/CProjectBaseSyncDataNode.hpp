#pragma once
#include "netSyncDataNode.hpp"
#include "NodeCommonDataOperations.hpp"

namespace rage
{
	class netSyncData;
	class netObject;
}

class CProjectBaseSyncDataNode : public rage::netSyncDataNode
{
public:
	virtual bool IsSyncNode()
	{
		return false;
	} // 0x50
	virtual bool _0x58()
	{
		return false;
	} // 0x58
	virtual bool IsGlobalFlags()
	{
		return false;
	} // 0x60
	virtual void DoPreCache(rage::netSyncData* data)
	{
	} // 0x68
	virtual std::uint8_t GetSyncFrequency(int index)
	{
		return 0;
	} // 0x70
	virtual int GetSyncInterval(int index)
	{
		return 0;
	} // 0x78
	virtual int GetBandwidthForPlayer(int player)
	{
		return 200;
	} // 0x80 (should always return 200)
	virtual void _0x88(void*)
	{
	} // 0x88
	virtual bool _0x90(void*, void*, int, int, int)
	{
		return false;
	} // 0x90
	virtual int CalculateSize()
	{
		return 0;
	} // 0x98 need to verify later
	virtual bool IsPreCacheDisabled()
	{
		return false;
	} // 0xA0
	virtual bool CanApply(rage::netObject* object)
	{
		return false;
	} // 0xA8
	virtual int GetPlayersInScope()
	{
		return -1;
	} // 0xB0
	virtual void DeserializeImpl()
	{
	} // 0xB8 need to verify later
	virtual void SerializeImpl()
	{
	} // 0xC0 need to verify later
	virtual int CalculateSize2()
	{
		return 0;
	} // 0xC8
	virtual int _0xD0()
	{
		return 0;
	} // 0xD0 calls NodeCommonDataOperations::Unk()
	virtual void Log()
	{
	} // 0xD8
	virtual bool CanPreCache(int)
	{
		return false;
	} // 0xE0 arg is always zero afaik
	virtual bool CanBeEmpty()
	{
		return false;
	} // 0xE8
	virtual bool IsEmpty()
	{
		return false;
	} // 0xF0 returns true if all data is default
	virtual void SetEmpty()
	{
	} // 0xF8 sets all data to their default values
	virtual void Log2()
	{
	} // 0x100
	virtual void ResetScriptData()
	{
	} // 0x108
	virtual bool _0x110()
	{
		return false;
	} // 0x110

private:
	NodeCommonDataOperations m_common_data_operations; // 0xB0 this is generally invalidated by MoveCommonDataOpsVFT()
};
static_assert(sizeof(CProjectBaseSyncDataNode) == 0xC0);

class CSyncDataNodeFrequent : public CProjectBaseSyncDataNode
{
};
class CSyncDataNodeInfrequent : public CProjectBaseSyncDataNode
{
};