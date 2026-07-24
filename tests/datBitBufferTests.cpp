#include "types/rage/datBitBuffer.hpp"

#include <array>
#include <cstdint>
#include <iostream>

#define CHECK(condition) \
	do \
	{ \
		if (!(condition)) \
			return __LINE__; \
	} while (false)

int main()
{
	{
		std::array<std::uint8_t, 16> storage{};
		rage::datBitBuffer writer(storage.data(), static_cast<std::uint32_t>(storage.size()));
		constexpr std::uint64_t expected = 0xFEDCBA9876543210ULL;
		CHECK(writer.WriteQword(expected, 64));

		rage::datBitBuffer reader(storage.data(), static_cast<std::uint32_t>(storage.size()), true);
		std::uint64_t actual{};
		CHECK(reader.ReadQword(&actual, 64));
		CHECK(actual == expected);
	}

	{
		std::array<std::uint8_t, 16> storage{};
		rage::datBitBuffer writer(storage.data(), static_cast<std::uint32_t>(storage.size()));
		CHECK(writer.WriteInt64(-42, 64));

		rage::datBitBuffer reader(storage.data(), static_cast<std::uint32_t>(storage.size()), true);
		std::int64_t actual{};
		CHECK(reader.ReadInt64(&actual, 64));
		if (actual != -42)
		{
			std::cerr << "signed 64-bit round trip produced " << actual << '\n';
			return __LINE__;
		}
	}

	{
		std::array<std::uint8_t, 2> storage{0xAA, 0x55};
		std::array<std::uint8_t, 3> destination{};
		rage::datBitBuffer reader(storage.data(), static_cast<std::uint32_t>(storage.size()), true);
		CHECK(!reader.ReadArrayBytes(destination.data(), static_cast<int>(destination.size())));
		CHECK(reader.m_BitsRead == 0);
	}

	{
		std::array<std::uint8_t, 2> storage{};
		std::array<std::uint8_t, 3> source{1, 2, 3};
		rage::datBitBuffer writer(storage.data(), static_cast<std::uint32_t>(storage.size()));
		CHECK(!writer.WriteArrayBytes(source.data(), static_cast<int>(source.size())));
		CHECK(writer.m_BitsRead == 0);
	}

	{
		std::array<std::uint8_t, 2> storage{};
		rage::datBitBuffer reader(storage.data(), static_cast<std::uint32_t>(storage.size()), true);
		reader.Seek(3);
		reader.AlignToByteBoundary();
		CHECK(reader.m_BitsRead == 8);
	}
}
