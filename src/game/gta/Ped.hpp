#pragma once
#include "Entity.hpp"
#include "Vehicle.hpp"

enum class PedConfigFlag : std::uint32_t;
enum class PedCombatAttribute : std::uint32_t;

namespace YimMenu
{
	class Ped : public Entity
	{
	public:
		using Entity::Entity;

		static Ped Create(uint32_t model, rage::fvector3 coords, float heading = 0.0f);

		// vehicles
		Vehicle GetVehicle();
		Vehicle GetLastVehicle();           // only returns a valid handle if the ped isn't already in a vehicle
		std::uint16_t GetVehicleObjectId(); // works even if the vehicle isn't cloned
		void SetInVehicle(Vehicle veh, int seat = -1);

		// ragdoll
		bool GetRagdoll();
		void SetRagdoll(bool enabled);

		// bones
		rage::fvector3 GetBonePosition(int bone);

		// config flags
		bool GetConfigFlag(PedConfigFlag flag);
		void SetConfigFlag(PedConfigFlag flag, bool value);

		// combat attributes
		void SetCombatAttribute(PedCombatAttribute attribute, bool value);

		// relationships
		bool IsEnemy();

		// accuracy
		int GetAccuracy();
		void SetAccuracy(int accuracy);

		// player
		// We're returning a handle here and not a Player because we don't want to create a cyclic import dependency
		int GetPlayer();

		// weapons
		void GiveWeapon(std::uint32_t hash, bool equip = false);
		void RemoveWeapon(std::uint32_t hash);
		std::uint32_t GetCurrentWeapon();
		bool HasWeapon(std::uint32_t hash);
		void SetInfiniteAmmo(bool infinite);
		void SetInfiniteClip(bool infinite);
		void SetMaxAmmoForWeapon(std::uint32_t hash);

		// teleport
		void TeleportTo(const rage::fvector3& pos); // similar to SetPosition, but handles vehicles correctly

		// armour
		int GetArmour();
		void SetArmour(int amount);

		// groups
		void SetLeaderOfGroup(int group);
		void AddToGroup(int group);
		void RemoveFromGroup();
		bool IsMemberOfGroup(int group);

		// outfits
		void RandomizeOutfit();

		// tasks
		void StartScenario(std::string_view name, int duration = -1, bool entry_anim = true);
		void SetKeepTask(bool keep);

		// misc
		void ClearDamage();
		void SetMaxTimeUnderwater(int time);
		void SetAsCop();
	};
}