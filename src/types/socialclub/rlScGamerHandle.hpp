#pragma once

#include <cstdint>

namespace rage
{
	// same as RDR
	class rlScGamerHandle
	{
	public:
		uint64_t m_RockstarId; // 0x00
		uint16_t m_UnkData;   // 0x08
		uint8_t m_Platform;   // 0x0A

		inline rlScGamerHandle() = default;

		inline rlScGamerHandle(uint64_t rockstar_id) :
		    m_RockstarId(rockstar_id),
		    m_Platform(3),
		    m_UnkData(0)
		{
		}
	}; //Size: 0x0010
	static_assert(sizeof(rlScGamerHandle) == 0x10);
}