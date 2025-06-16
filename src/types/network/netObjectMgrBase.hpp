#pragma once
#include "netObject.hpp"

class CNetGamePlayer;

namespace rage
{
	class datBitBuffer;
	class netObjectMgrBase
	{
	public:
		virtual ~netObjectMgrBase() = default;

		virtual void Initialize() = 0;
		virtual void Shutdown() = 0;
		virtual void Update(bool) = 0;

		virtual void AddEntity(void*, void*) = 0;
		virtual void UnregisterNetworkObject_(void* unk, bool force) = 0;
		virtual void UnregisterNetworkObject(netObject* object, int reason, bool force1, bool force2) = 0;

		virtual void ChangeOwner(netObject* object, CNetGamePlayer* player, int migrationType) = 0;

		virtual void HandleJoiningPlayer(CNetGamePlayer* player) = 0;
		virtual void HandleLeavingPlayer(CNetGamePlayer* player) = 0;

		virtual void _0x50(CNetGamePlayer* player) = 0;
		virtual void _0x58() = 0;

		virtual void RegisterNetworkObject(netObject* object) = 0;

		virtual void PackCloneCreate(netObject* object, CNetGamePlayer* player, datBitBuffer* buffer) = 0;
		virtual bool PackCloneRemove(netObject* object, CNetGamePlayer* player, bool) = 0;
		virtual void PackCloneSync(netObject* object, CNetGamePlayer* player) = 0;

		virtual void _0x80() = 0;
		virtual void _0x88() = 0;
		virtual const char* _0x90(int) = 0;

		virtual bool HandleCloneCreate(CNetGamePlayer* source, CNetGamePlayer* target, rage::netObject::Type object_type, uint16_t object_id, int object_flags, void*, uint32_t timestamp) = 0;
		virtual void HandleCloneCreateAck(CNetGamePlayer* source, CNetGamePlayer* target, uint16_t object_flags, int ack_code) = 0;

		virtual int HandleCloneSync(CNetGamePlayer* source, CNetGamePlayer* target, rage::netObject::Type object_type, uint16_t object_id, void*, uint16_t, uint32_t timestamp) = 0;
		virtual void HandleCloneSyncAck(CNetGamePlayer* source, CNetGamePlayer* target, void*, uint16_t objectId, int ack_code) = 0;

		virtual void HandleCloneRemove(CNetGamePlayer* source, CNetGamePlayer* target, uint16_t object_id, int) = 0;
		virtual void HandleCloneRemoveAck(CNetGamePlayer* source, CNetGamePlayer* target, uint16_t object_id, int ack_code) = 0;

		virtual void _0xC8() = 0;

	public:
	};
}

class CNetworkObjectMgr : public rage::netObjectMgrBase
{
};