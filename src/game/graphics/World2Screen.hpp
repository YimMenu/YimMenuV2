#pragma once
#include "../../types/rage/vector.hpp"

namespace YimMenu
{
	class World2Screen
	{
	public:
		static bool W2S(const rage::vector3 entityCoords, rage::vector2& screen);
	};
}
