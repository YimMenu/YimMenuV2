#pragma once
#include <cstdint>
#include <string_view>

namespace YimMenu
{
	using joaat_t = std::uint32_t;

	inline constexpr char ToLower(char c)
	{
		return c >= 'A' && c <= 'Z' ? c | 1 << 5 : c;
	}

	extern constexpr joaat_t Joaat(const std::string_view str);
	inline consteval joaat_t operator""_J(const char* s, std::size_t n)
	{
		joaat_t result = 0;

		for (std::size_t i = 0; i < n; i++)
		{
			result += ToLower(s[i]);
			result += (result << 10);
			result ^= (result >> 6);
		}

		result += (result << 3);
		result ^= (result >> 11);
		result += (result << 15);

		return result;
	}
}