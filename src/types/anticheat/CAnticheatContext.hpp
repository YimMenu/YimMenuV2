#pragma once
#include "types/rage/ObfVar.hpp"

struct CAnticheatContext
{
	rage::Obf32 m_LastScanTime;
	rage::Obf32 m_ScanInterval;
	void* m_ScanData;
	rage::Obf32 m_ScanDataSize;
	rage::Obf32 m_ScanDataSize2;
	rage::Obf32 m_GameBuild;
	std::uint64_t qword58;
	std::uint32_t dword60;
	char gap64[2572];
	std::uint32_t dwordA70;
	std::uint64_t qwordA78;
	std::uint32_t dwordA80;
	char gapA84[3];
	char byteA87[9];
	bool m_DebugBattlEyeEnabled;
	bool m_BattlEyeEnabled;
	bool m_IsDebugMode;
	volatile __int32 m_CurrentScanIndex;
	std::uint64_t qwordA98;
};
static_assert(sizeof(CAnticheatContext) == 0xAA0);