#pragma once

namespace rage
{
	struct netCatalogBaseItem
	{
		void* m_Vft;                    // 0x00
		std::uint32_t m_Hash;           // 0x08
		std::uint32_t m_CategoryHash;   // 0x0C
		std::int32_t m_Price;           // 0x10
		std::int32_t m_MembershipPrice; // 0x14
		std::int32_t m_StatValue;       // 0x18
		std::uint32_t m_Unknown;        // 0x1C
	};
	static_assert(sizeof(netCatalogBaseItem) == 0x20);
}