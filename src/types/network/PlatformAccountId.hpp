#pragma once

struct PlatformAccountId
{
	enum Platform : uint8_t
	{
		PLATFORM_INVALID = 0,
		PLATFORM_XBOX = 1,
		PLATFORM_STEAM = 10,
		PLATFORM_EPIC = 15
	};

	union {
		uint64_t m_XboxUserId; //0x0000
		uint64_t m_SteamId;
		char m_EpicAccountId[32 + 1];
		char m_Pad[40];
	};
	Platform m_Platform; //0x0028
};
static_assert(sizeof(PlatformAccountId) == 0x30);