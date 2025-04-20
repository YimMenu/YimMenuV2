#pragma once
#include "rlScTaskStatus.hpp"

namespace rage
{
	struct rlGetAvatarsPlayerList
	{
		union
		{
			char m_PlayerNames[51][250];
			char m_PlayerHandles[51][250];
		};
		int m_NumEntries;
	};
	static_assert(sizeof(rlGetAvatarsPlayerList) == 0x31D4);

	struct rlGetAvatarsResult
	{
		std::uint64_t m_RockstarId; // 0x00
		char m_Nickname[51];        // 0x08
		char m_AvatarUrl[127];      // 0x3B
	};
	static_assert(sizeof(rlGetAvatarsResult) == 0xC0);

	struct rlGetAvatarsResults
	{
		rlGetAvatarsResult m_Results[250];
		int m_NumResults;
	};
	static_assert(sizeof(rlGetAvatarsResults) == 0xBB88);

	// this is probably something else that LLVM decided to inline into the GetAvatars func
	class rlGetAvatarsContext
	{
	public:
		enum class Type : std::uint8_t
		{
			BY_NICKNAME,
			BY_ROCKSTAR_ID
		};

		enum class AvatarSize
		{
			SMALL = 1,
			MEDIUM = 2,
			LARGE = 4
		};

		virtual ~rlGetAvatarsContext() = default; 

		char m_Pad[80];                  // 0x08
		void* m_Result;                  // 0x58
		char m_Pad2[4];                  // 0x60
		Type m_Type;                     // 0x64
		AvatarSize m_AvatarSize;         // 0x68
		rage::rlScTaskStatus m_Status{}; // 0x70
	};
	static_assert(sizeof(rlGetAvatarsContext) == 0x80);
}