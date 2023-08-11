#pragma once
#include <cstdint>

namespace YimMenu
{
	inline constexpr std::uint8_t StrToHex(const char& ch) noexcept
	{
		if (ch >= '0' && ch <= '9')
			return ch - '0';

		if (ch >= 'A' && ch <= 'F')
			return ch - 'A' + 10;

		return ch - 'a' + 10;
	}
}