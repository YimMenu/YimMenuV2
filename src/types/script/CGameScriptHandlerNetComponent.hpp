#pragma once
#include "scriptHandlerNetComponent.hpp"

class CNetGamePlayer;
class MsgScriptNewHost;

struct CScriptParticipant
{
	CScriptParticipant* m_Next;
	CScriptParticipant* m_Prev;
	CNetGamePlayer* m_Player;
	std::uint16_t m_ParticipantId;
	std::uint16_t m_SlotNumber;
	int m_JoinTime;
	char gap20[8];
};

// TODO: verify if this is correct in Enhanced
class CGameScriptHandlerNetComponent : public rage::scriptHandlerNetComponent
{
public:
	virtual ~CGameScriptHandlerNetComponent() override = default;

	virtual bool Update() = 0;
	virtual void _0x10(CNetGamePlayer*) = 0; // creates a scriptId?
	virtual void* PlayerLeft(CNetGamePlayer* player) = 0;
	virtual void* SendHostMigrationEvent(CNetGamePlayer* player) = 0;
	virtual void PlayerJoined(void**, void* msg_ctx) = 0;
	virtual void PlayerJoinedAck(void**, void* msg_ctx) = 0;
	virtual void PlayerJoinedHostAck(void*, void*) = 0;
	virtual void* _0x40(void*, void*) = 0; // ...
	virtual void* _0x48(void*, void*, void*) = 0;
	virtual void* _0x50(void*, void*) = 0;
	virtual void* _0x58(void*, void*) = 0;
	virtual void* _0x60(void*, void*) = 0;
	virtual void* _0x68(void*, void*) = 0;
	virtual void _0x70(void*, void*) = 0;
	virtual void _0x78(void*, void*) = 0;
	virtual short _0x80(void*, void*) = 0;
	virtual void* _0x88(void*, void*) = 0;
	virtual void* _0x90(void*, void*) = 0;
	virtual bool _0x98(void*, void*) = 0;
	virtual void* _0xA0(void*, void*) = 0;
	virtual void* _0xA8(void*, void*) = 0;
	virtual short _0xB0(void*, void*) = 0;
	virtual bool RegisterHostBroadcastData(void* data, int size, char* a3) = 0;
	virtual bool RegisterPlayerBroadcastData(int a1, int size, bool a3) = 0;
	virtual bool _0xC8() = 0;
	virtual bool _0xD0() = 0;
	virtual bool AddPlayerToScript(CNetGamePlayer* player, short* out_participant_id, short* out_slot_number, int* out_fail_reason) = 0;
	virtual bool AddPlayerToScriptInternal(CNetGamePlayer* player, short participant_id, short slot_number) = 0;
	virtual bool RemovePlayerFromScript(CNetGamePlayer* player) = 0;
	virtual void* PlayerLeftImpl(CNetGamePlayer*, bool) = 0;
	virtual bool DoHostMigration(CNetGamePlayer* player, short host_token, bool unk) = 0;
	virtual void* LeaveFromScript() = 0;
	virtual bool _0x108() = 0;
	virtual void* _0x110() = 0;
	virtual bool _0x118() = 0; // related to above function

	int m_State;
	int m_AckPendingPlayers;
	CScriptParticipant* m_FirstParticipant;
	char gap20[16];
	CScriptParticipant* m_Host;
	std::int16_t m_LocalSlotNumber;
	char pad_003A[6];
	unsigned int m_ParticipantBitset;
	uint16_t m_HostToken;
	CNetGamePlayer* m_LastHost;
	CNetGamePlayer* m_NextHost;
	CNetGamePlayer* m_UnkHost;
	char gap60[8];
	MsgScriptNewHost* m_QueuedNewHostMessage; // added b3407, queues a host message if a tunable is enabled and verifies it?
	CScriptParticipant* m_Participants[32];
	char pad_0168[8];
	int m_NextHostVerifyTime;
	char m_MaxParticipants;
	char pad_0175[23];
	uint8_t m_NumParticipants;
	uint8_t m_NumCandidates;
	uint8_t m_HostAckError;
	uint8_t m_HostArrayCount;
	uint8_t m_PlayerArrayCount;
	uint8_t m_HostMigrationState;
	std::uint8_t m_Flags;
	char pad_0193[13];
	char m_ScriptStatusQueried;

	inline bool IsLocalPlayerHost() const
	{
		if (!m_Host)
			return true; // or return false?

		return m_Host->m_SlotNumber == m_LocalSlotNumber;
	}

	inline CNetGamePlayer* GetHost() const
	{
		if (!m_Host)
			return nullptr;

		return m_Host->m_Player;
	}
};
static_assert(sizeof(CGameScriptHandlerNetComponent) == 0x1B0);