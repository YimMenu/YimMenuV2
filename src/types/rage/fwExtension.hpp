#pragma once

#include <cstdint>

namespace rage
{
	class fwExtension
	{
	public:
		virtual ~fwExtension() = default;
		virtual void unk_0x08() = 0;
		virtual void unk_0x10() = 0;
		virtual uint32_t GetId() = 0;
	}; //Size: 0x0008
	static_assert(sizeof(fwExtension) == 0x8);
}