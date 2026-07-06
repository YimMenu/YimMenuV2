#pragma once
#include "vector.hpp"

namespace rage
{
	class CViewport
	{
	public:
		char pad_0000[0x40]; // 0x0000 - 0x0040
		rage::matrix44 ViewMatrix; // 0x0040 - 0x0080
		rage::matrix44 ProjectionMatrix; // 0x0080 - 0x00C0
		//char pad_00C0[0x140]; // 0x00C0 - 0x0200
		//rage::matrix44 ScreenMatrix; // 0x0200 - 0x0240
		//rage::matrix44 ViewProjectionScreenMatrix; // 0x0240 - 0x0280
	};
}