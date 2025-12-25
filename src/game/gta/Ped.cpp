#include "Ped.hpp"

#include "Natives.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu
{
	Ped Ped::Create(uint32_t model, rage::fvector3 coords, float heading)
	{
		ENTITY_ASSERT_SCRIPT_CONTEXT();
		if (!STREAMING::IS_MODEL_IN_CDIMAGE(model))
		{
#ifdef ENTITY_DEBUG
			LOGF(WARNING, "Invalid model passed to Ped::Create: 0x{:X}", model);
#endif
			return nullptr;
		}

		for (int i = 0; !STREAMING::HAS_MODEL_LOADED(model); i++)
		{
			STREAMING::REQUEST_MODEL(model);
			ScriptMgr::Yield();

			if (i > 30)
			{
#ifdef ENTITY_DEBUG
				LOGF(WARNING, "Model 0x{:X} failed to load after 30 ticks, bailing out", model);
#endif
				return nullptr;
			}
		}

		Pointers.SpectatePatch->Apply();
		auto ped = Ped(PED::CREATE_PED(0, model, coords.x, coords.y, coords.z, heading, true, 0));
		Pointers.SpectatePatch->Restore();

		if (!ped)
		{
#ifdef ENTITY_DEBUG
			LOGF(WARNING, "CREATE_PED failed when creating a ped with model {:X}", model);
#endif
			return nullptr;
		}

		ped.SetPosition(coords);
		ped.SetVelocity({});

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		return ped;
	}

	Vehicle Ped::GetVehicle()
	{
		ENTITY_ASSERT_VALID();
		if (!PED::IS_PED_IN_ANY_VEHICLE(GetHandle(), false))
			return nullptr;
		return Vehicle(PED::GET_VEHICLE_PED_IS_USING(GetHandle()));
	}

	Vehicle Ped::GetLastVehicle()
	{
		ENTITY_ASSERT_VALID();
		if (PED::IS_PED_IN_ANY_VEHICLE(GetHandle(), false))
			return nullptr;
		return Vehicle(PED::GET_VEHICLE_PED_IS_IN(GetHandle(), true));
	}

	std::uint16_t Ped::GetVehicleObjectId()
	{
		ENTITY_ASSERT_VALID();
		if (!IsNetworked())
			return 0;

		return *reinterpret_cast<std::uint16_t*>(reinterpret_cast<__int64>(GetNetworkObject()) + 0x3D8);
	}

	void Ped::SetInVehicle(Vehicle veh, int seat)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();

		PED::SET_PED_INTO_VEHICLE(GetHandle(), veh.GetHandle(), seat);
	}

	bool Ped::GetRagdoll()
	{
		ENTITY_ASSERT_VALID();
		return PED::CAN_PED_RAGDOLL(GetHandle());
	}

	void Ped::SetRagdoll(bool enabled)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		PED::SET_PED_CAN_RAGDOLL(GetHandle(), enabled);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(GetHandle(), enabled ? 1 : 0);
	}

	rage::fvector3 Ped::GetBonePosition(int bone)
	{
		ENTITY_ASSERT_VALID();
		return PED::GET_PED_BONE_COORDS(GetHandle(), bone, 0, 0, 0);
	}

	bool Ped::GetConfigFlag(PedConfigFlag flag)
	{
		ENTITY_ASSERT_VALID();
		return PED::GET_PED_CONFIG_FLAG(GetHandle(), (int)flag, false);
	}

	void Ped::SetConfigFlag(PedConfigFlag flag, bool value)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		PED::SET_PED_CONFIG_FLAG(GetHandle(), (int)flag, value);
	}

	void Ped::SetCombatAttribute(PedCombatAttribute attribute, bool value)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		PED::SET_PED_COMBAT_ATTRIBUTES(GetHandle(), (int)attribute, value);
	}

	bool Ped::IsEnemy()
	{
		ENTITY_ASSERT_VALID();

		// TODO: maybe use a class member?
		auto r1 = PED::GET_RELATIONSHIP_BETWEEN_PEDS(GetHandle(), PLAYER::PLAYER_PED_ID());
		auto r2 = PED::GET_RELATIONSHIP_BETWEEN_PEDS(PLAYER::PLAYER_PED_ID(), GetHandle());
		auto r3 = PED::IS_PED_IN_COMBAT(GetHandle(), PLAYER::PLAYER_PED_ID()) ? 5 : 0;

		if (r1 == 3 || r2 == 3)
			return true;
		if (r1 == 4 || r2 == 4)
			return true;
		if (r1 == 5 || r2 == 5 || r3 == 5)
			return true;
		return false;
	}

	int Ped::GetAccuracy()
	{
		ENTITY_ASSERT_VALID();
		return PED::GET_PED_ACCURACY(GetHandle());
	}

	void Ped::SetAccuracy(int accuracy)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		PED::SET_PED_ACCURACY(GetHandle(), accuracy);
	}

	int Ped::GetPlayer()
	{
		ENTITY_ASSERT_VALID();
#ifdef ENTITY_DEBUG
		if (!IsPlayer())
		{
			LOG(WARNING) << __FUNCTION__ << ": ped is not a player!";
		}
#endif
		return NETWORK::NETWORK_GET_PLAYER_INDEX_FROM_PED(GetHandle());
	}

	void Ped::SetInfiniteAmmo(bool infinite)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();

		WEAPON::SET_PED_INFINITE_AMMO(GetHandle(), infinite, 0);
	}

	void Ped::SetInfiniteClip(bool infinite)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();

		WEAPON::SET_PED_INFINITE_AMMO_CLIP(GetHandle(), infinite); // is this networked?
	}

	void Ped::TeleportTo(const rage::fvector3& pos)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();

		if (auto veh = GetVehicle())
			veh.SetPosition(pos);
		else
			SetPosition(pos);
	}

	void Ped::GiveWeapon(std::uint32_t hash, bool equip)
	{
		ENTITY_ASSERT_VALID();

		WEAPON::GIVE_WEAPON_TO_PED(GetHandle(), hash, 9999, false, equip);
	}

	void Ped::RemoveWeapon(std::uint32_t hash)
	{
		ENTITY_ASSERT_VALID();

		WEAPON::REMOVE_WEAPON_FROM_PED(GetHandle(), hash);
	}

	std::uint32_t Ped::GetCurrentWeapon()
	{
		ENTITY_ASSERT_VALID();
		std::uint32_t weapon;
		WEAPON::GET_CURRENT_PED_WEAPON(GetHandle(), &weapon, 0);
		return weapon;
	}

	bool Ped::HasWeapon(std::uint32_t hash)
	{
		ENTITY_ASSERT_VALID();

		return WEAPON::HAS_PED_GOT_WEAPON(GetHandle(), hash, false);
	}

	int Ped::GetArmour()
	{
		ENTITY_ASSERT_VALID();
		return PED::GET_PED_ARMOUR(GetHandle());
	}

	void Ped::SetArmour(int amount)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		PED::SET_PED_ARMOUR(GetHandle(), amount);
	}

	void Ped::SetLeaderOfGroup(int group)
	{
		ENTITY_ASSERT_VALID();
		PED::SET_PED_AS_GROUP_LEADER(GetHandle(), group);
	}

	void Ped::AddToGroup(int group)
	{
		ENTITY_ASSERT_VALID();
		PED::SET_PED_AS_GROUP_MEMBER(GetHandle(), group);
	}

	void Ped::RemoveFromGroup()
	{
		ENTITY_ASSERT_VALID();
		PED::REMOVE_PED_FROM_GROUP(GetHandle());
	}

	bool Ped::IsMemberOfGroup(int group)
	{
		ENTITY_ASSERT_VALID();
		return PED::IS_PED_GROUP_MEMBER(GetHandle(), group);
	}

	void Ped::RandomizeOutfit()
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		PED::SET_PED_RANDOM_COMPONENT_VARIATION(GetHandle(), 0);
	}

	void Ped::StartScenario(std::string_view name, int duration, bool entry_anim)
	{
		ENTITY_ASSERT_VALID();
		TASK::TASK_START_SCENARIO_IN_PLACE(GetHandle(), name.data(), duration, entry_anim);
	}

	void Ped::SetKeepTask(bool keep)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		PED::SET_PED_KEEP_TASK(GetHandle(), keep);
	}

	void Ped::ClearDamage()
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		PED::CLEAR_PED_BLOOD_DAMAGE(GetHandle());
		PED::CLEAR_PED_WETNESS(GetHandle());
		PED::CLEAR_PED_ENV_DIRT(GetHandle());
		PED::RESET_PED_VISIBLE_DAMAGE(GetHandle());
	}

	void Ped::SetMaxTimeUnderwater(int time)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		PED::SET_PED_MAX_TIME_UNDERWATER(GetHandle(), time);
	}

	void Ped::SetAsCop()
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		PED::SET_PED_AS_COP(GetHandle(), true);
	}

	void Ped::SetMaxAmmoForWeapon(std::uint32_t hash)
	{
		ENTITY_ASSERT_VALID();
		ENTITY_ASSERT_CONTROL();
		int maxAmmo;
		WEAPON::GET_MAX_AMMO(GetHandle(), hash, &maxAmmo);
		WEAPON::SET_PED_AMMO(GetHandle(), hash, maxAmmo, 0);
	}
}
