#pragma once
#include "Entity.hpp"

namespace YimMenu
{
	class Object : public Entity
	{
	public:
		using Entity::Entity;

		static Object Create(uint32_t model, rage::fvector3 coords);
		bool IsCamera();
		bool IsSignalJammer();
	};
}