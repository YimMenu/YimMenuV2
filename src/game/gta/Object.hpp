#pragma once
#include "Entity.hpp"

namespace YimMenu
{
	class Object : public Entity
	{
	public:
		using Entity::Entity;

		static Object Create(uint32_t model, rage::fvector3 coords);
		static bool IsCamera(int objectHash);
		static bool IsCache(int objectHash);
		static bool IsSignalJammer(int objectHash);
	};
}