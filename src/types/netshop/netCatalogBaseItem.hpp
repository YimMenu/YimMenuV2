#pragma once

namespace rage
{
	class netCatalogBaseItem
	{
	public:
		virtual ~netCatalogBaseItem() = 0;

		std::uint32_t m_Hash;            // 0x08
		std::uint32_t m_CategoryHash;    // 0x0C
		std::int32_t  m_Price;           // 0x10
		std::int32_t  m_MembershipPrice; // 0x14 (new in Enhanced, tracks GTA+ discounted price values)
	};
	static_assert(sizeof(netCatalogBaseItem) == 0x18);
}