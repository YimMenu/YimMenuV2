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

	inline constexpr joaat_t Joaat(const std::string_view str)
	{
		joaat_t hash = 0;
		for (auto c : str)
		{
			hash += ToLower(c);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}
		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);
		return hash;
	}

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