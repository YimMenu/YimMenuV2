#pragma once

#include <cstdint>

namespace rage
{
	class datBitBuffer;
	// this appears to have been unchanged in E&E
	enum rlPlatforms : uint8_t
	{
		UNK0,
		XBOX,
		PLAYSTATION,
		PC,
	};

	class rlGamerHandle
	{
	public:
		int64_t m_RockstarId;   // 0x00
		uint8_t m_Platform;     // 0x08
		uint8_t m_ProfileIndex; // 0x09 (maybe, or some kind of discriminator)

		inline rlGamerHandle() = default;

		inline rlGamerHandle(int64_t rockstar_id) :
		    m_RockstarId(rockstar_id),
		    m_Platform(rlPlatforms::PC),
		    m_ProfileIndex(0)
		{
		}

		void Serialize(rage::datBitBuffer& buffer) const;
		void Deserialize(rage::datBitBuffer& buffer);
	}; //Size: 0x0010
	static_assert(sizeof(rlGamerHandle) == 0x10);
}