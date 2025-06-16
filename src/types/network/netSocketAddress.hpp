#pragma once
#include <cstdint>

struct netSocketAddress
{
	union {
		uint32_t m_Packed;
		struct
		{
			uint8_t m_Field4;
			uint8_t m_Field3;
			uint8_t m_Field2;
			uint8_t m_Field1;
		};
	} m_IpAddress;
	std::uint16_t m_Port;
};
static_assert(sizeof(netSocketAddress) == 0x08);