#pragma once
#include "rlSessionConfig.hpp"
#include "rlGamerInfoBase.hpp"
#include "rlSessionInfo.hpp"

namespace rage
{
	class rlSessionDetail
	{
	public:
		class rage::rlGamerInfoBase m_BaseGamerInfo; // 0x00
		std::uint64_t m_HostToken;                   // 0xC0
		class rage::rlSessionInfo m_SessionInfo;     // 0xC8
		class rage::rlSessionConfig m_SessionConfig; // 0x198
		rage::rlGamerHandle m_Handle;                // 0x2C8
		char m_Name[0x14];                           // 0x2D8
		uint32_t m_PlayerCount;                      // 0x2EC
		uint32_t m_SpectatorCount;                   // 0x2F0
		uint16_t m_SessionDataStructSize;            // 0x2F4
		char m_SessionDataStruct[0x100];             // 0x2F6 likely a union of two structs, sizes 0x44 and 0x28
		uint16_t m_MatchmakingDataStructSize;        // 0x3F6
		char m_MatchmakingDataStruct[0x80];          // 0x3F8 stores matchmaking tunable data?
	}; //Size: 0x03CA
	static_assert(sizeof(rlSessionDetail) == 0x478);

	class rlSessionDetailMsg
	{
	public:
		int m_Status;
		int m_RequiredVersion;
		int m_RequestToken;
		int m_Unk;
		rlSessionDetail m_Detail;
	};
	static_assert(sizeof(rlSessionDetailMsg) == 0x488);
}