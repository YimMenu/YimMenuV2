#pragma once
#include "Entity.hpp"

namespace YimMenu
{
	class Vehicle : public Entity
	{
	public:
		using Entity::Entity;

		static Vehicle Create(std::uint32_t model, rage::fvector3 coords, float heading = 0.0f);

		void Fix();

		// gears
		int GetGear();
		float GetRevRatio(); // doesn't work

		// speed
		float GetMaxSpeed();

		void Upgrade();
		void SetPlateText(const std::string text);
	};
}