#pragma once
#include <iostream>
#include <string>

namespace YimMenu
{
	// Function to trim leading and trailing whitespace from a string
	inline std::string TrimString(std::string& str)
	{
		auto start = str.begin();
		auto end = str.end();

		// Find the first non-whitespace character from the start
		while (start != end && std::isspace(*start))
		{
			++start;
		}

		// Find the last non-whitespace character from the end
		while (start != end && std::isspace(*(end - 1)))
		{
			--end;
		}

		return std::string(start, end);
	}

	inline void StrCpySafe(char* dest, const char* src, int dest_size)
	{
		auto len = dest_size - 1;
		strncpy(dest, src, len);
		if (strlen(src) > len)
			dest[len] = '\0';
	}

	inline void ReplaceString(std::string& str, const char* str1, const char* str2)
	{
		size_t pos = 0;
		while ((pos = str.find(str1, pos)) != std::string::npos)
			str.replace(pos, strlen(str1), str2);
	}
}
