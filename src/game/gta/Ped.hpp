#pragma once
#include "Entity.hpp"
#include "Vehicle.hpp"

enum class PedConfigFlag : std::uint32_t;

namespace YimMenu
{
	class Ped : public Entity
	{
	public:
		using Entity::Entity;

		static Ped Create(uint32_t model, rage::fvector3 coords, float heading = 0.0f);

		// info
		Vehicle GetVehicle();
		std::uint16_t GetVehicleObjectId(); // works even if the vehicle isn't cloned

		// ragdoll
		bool GetRagdoll();
		void SetRagdoll(bool enabled);

		// bones
		rage::fvector3 GetBonePosition(int bone);

		// config flags
		bool GetConfigFlag(PedConfigFlag flag);
		void SetConfigFlag(PedConfigFlag flag, bool value);

		// relationships
		bool IsEnemy();

		// accuracy
		int GetAccuracy();
		void SetAccuracy(int accuracy);

		// player
		// We're returning a handle here and not a Player because we don't want to create a cyclic import dependency
		int GetPlayer();

		// weapons
		void SetInfiniteAmmo(bool infinite);
		void SetInfiniteClip(bool infinite);

		// teleport
		void TeleportTo(const rage::fvector3& pos); // similar to SetPosition, but handles vehicles correctly

		// weapons
		void GiveWeapon(std::uint32_t hash, bool equip = false);
		void RemoveWeapon(std::uint32_t hash);
		std::uint32_t GetCurrentWeapon();
	};
}