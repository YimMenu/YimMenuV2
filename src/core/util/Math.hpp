#pragma once
#include "types/rage/vector.hpp"

namespace YimMenu::Math
{
	inline float DegToRad(float deg)
	{
		double radian = (3.14159265359 / 180) * deg;
		return static_cast<float>(radian);
	}

	inline rage::fvector3 RotationToDirection(rage::fvector3 rotation)
	{
		float x = DegToRad(rotation.x);
		float z = DegToRad(rotation.z);

		float num = abs(cos(x));

		return rage::fvector3{static_cast<float>(-sin(z) * num), static_cast<float>(cos(z) * num), static_cast<float>(sin(x))};
	}

	inline float DistanceBetweenVectors(rage::fvector3 a, rage::fvector3 b)
	{
		return (float)sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + pow((a.z - b.z), 2));
	}
}