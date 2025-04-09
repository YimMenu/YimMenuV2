#pragma once
#include "CNetGamePlayer.hpp"

#include <cstdint>

class CNetGamePlayerDataMsg;

namespace rage
{
	class netConnectionManager;
	class netPlayerMgrBase
	{
	public:
		virtual ~netPlayerMgrBase() = default;
		virtual void Initialize() = 0; // 0x8
		virtual void Shutdown() = 0; // 0x10
		virtual void Update() = 0; // updates something every X seconds (0x18)
		virtual CNetGamePlayer* AddPlayer(rage::rlGamerInfo* gamer_info, uint32_t a2, CNetGamePlayerDataMsg* player_data, CNonPhysicalPlayerData* non_physical_player_data) = 0; // 0x20
		virtual void RemovePlayer(CNetGamePlayer* player) = 0; // 0x28
		virtual void UpdatePlayerListsForPlayer(CNetGamePlayer* player) = 0; // 0x30
		virtual CNetGamePlayer* AddPlayer2(rage::rlGamerInfo* gamer_info, uint32_t a3, CNetGamePlayerDataMsg* player_data, CNonPhysicalPlayerData* non_physical_player_data) = 0; // 0x38
		// TODO: reverse the rest

		rage::netConnectionManager* m_NetConnectionMgr; // 0x08
		void* m_BandwidthMgr;                           // 0x10
		char pad_0018[216];                             // 0x18
		CNetGamePlayer* m_LocalPlayer;                  // 0xF0
		char pad_00F8[144];                             // 0xF8
		CNetGamePlayer* m_Players[32];                  // 0x188
		uint32_t m_MaxPlayers;                          // 0x288
		char pad_028C[4];                               // 0x28C
		int m_UnloadedPlayerCount;                      // 0x290 seems like the inverse of the below thing
		int m_LoadedPlayerCount;                        // 0x294
		int m_LoadedNonLocalPlayerCount;                // 0x298 
		int m_PhysicalPlayerCount;                      // 0x29C
		int m_LocalPhysicalPlayerCount;                 // 0x2A0 lol? should always be one
		int m_NonLocalPhysicalPlayerCount;              // 0x2A4
		char pad_0296[1608];                            // 0x296
	};
	static_assert(sizeof(netPlayerMgrBase) == 0x8F0);
}