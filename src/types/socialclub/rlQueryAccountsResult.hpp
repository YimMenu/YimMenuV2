#pragma once

namespace rage
{
	class rlQueryAccountsResult
	{
	public:
		enum class Relationship : std::uint32_t
		{
			NONE = 1,
			BLOCKED_BY_ME = 2,
			BLOCKED_BY_THEM = 4,
			BLOCKED_BY_BOTH = 6,
			INVITED_BY_ME = 8,
			INVITED_BY_THEM = 16,
			FRIEND = 32
		};

		std::uint64_t m_RockstarId;  // 0x00 (gets parsed as a 32 bit value? wtf?)
		char m_Nickname[51];         // 0x08
		char m_AvatarUrl[2048];      // 0x3B
		bool m_IsVisible;            // 0x83B
		Relationship m_Relationship; // 0x83C
		bool m_IsClanmate;           // 0x840
	};
	static_assert(sizeof(rlQueryAccountsResult) == 0x848);
}