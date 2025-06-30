#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/scripting/LatentFunction.hpp"
#include "game/gta/Ped.hpp"
#include "Entity.hpp"

namespace YimMenu::Lua
{
	class Ped : LuaLibrary
	{
	public:
		using LuaLibrary::LuaLibrary;

		static int New(lua_State* state)
		{
			CreateObject<YimMenu::Ped>(state, luaL_checkinteger(state, 1));
			return 1;
		}

		static int Create(lua_State* state)
		{
			CopyObject<YimMenu::Ped>(state, YimMenu::Ped::Create(GetHashArgument(state, 1), GetObject<rage::fvector3>(state, 2), lua_gettop(state) >= 3 ? luaL_checknumber(state, 3) : 0.0f));
			return 1;
		}

		static int GetVehicle(lua_State* state)
		{
			CopyObject<YimMenu::Vehicle>(state, GetObject<YimMenu::Ped>(state, 1).GetVehicle());
			return 1;
		}

		static int GetLastVehicle(lua_State* state)
		{
			CopyObject<YimMenu::Vehicle>(state, GetObject<YimMenu::Ped>(state, 1).GetLastVehicle());
			return 1;
		}

		static int GetVehicleObjectId(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Ped>(state, 1).GetVehicleObjectId());
			return 1;
		}

		static int SetInVehicle(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).SetInVehicle(GetObject<YimMenu::Vehicle>(state, 2), lua_gettop(state) >= 3 ? luaL_checkinteger(state, 3) : 0);
			return 0;
		}

		static int GetRagdoll(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Ped>(state, 1).GetRagdoll());
			return 1;
		}

		static int SetRagdoll(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).SetRagdoll(CheckBooleanSafe(state, 2));
			return 0;
		}

		static int GetBonePosition(lua_State* state)
		{
			MoveObject<rage::fvector3>(state, GetObject<YimMenu::Ped>(state, 1).GetBonePosition(luaL_checkinteger(state, 2)));
			return 0;
		}

		// GetConfigFlag
		// SetConfigFlag
		// SetCombatAttribute

		static int IsEnemy(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Ped>(state, 1).IsEnemy());
			return 1;
		}

		static int GetAccuracy(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Ped>(state, 1).GetAccuracy());
			return 1;
		}

		static int SetAccuracy(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).SetAccuracy(luaL_checkinteger(state, 2));
			return 0;
		}

		// GetPlayer

		static int GiveWeapon(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).GiveWeapon(GetHashArgument(state, 2), lua_gettop(state) >= 3 ? CheckBooleanSafe(state, 3) : false);
			return 0;
		}

		static int RemoveWeapon(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).RemoveWeapon(GetHashArgument(state, 2));
			return 0;
		}

		static int GetCurrentWeapon(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Ped>(state, 1).GetCurrentWeapon());
			return 1;
		}

		static int HasWeapon(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Ped>(state, 1).HasWeapon(GetHashArgument(state, 2)));
			return 1;
		}

		static int SetInfiniteAmmo(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).SetInfiniteAmmo(CheckBooleanSafe(state, 2));
			return 0;
		}

		static int SetInfiniteClip(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).SetInfiniteClip(CheckBooleanSafe(state, 2));
			return 0;
		}

		static int SetMaxAmmoForWeapon(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).SetMaxAmmoForWeapon(GetHashArgument(state, 2));
			return 0;
		}

		static int TeleportTo(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).TeleportTo(GetObject<rage::fvector3>(state, 2));
			return 0;
		}

		static int GetArmour(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Ped>(state, 1).GetArmour());
			return 1;
		}

		static int SetArmour(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).SetArmour(luaL_checkinteger(state, 2));
			return 0;
		}

		static int SetLeaderOfGroup(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).SetLeaderOfGroup(luaL_checkinteger(state, 2));
			return 0;
		}

		static int AddToGroup(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).AddToGroup(luaL_checkinteger(state, 2));
			return 0;
		}

		static int RemoveFromGroup(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).RemoveFromGroup();
			return 0;
		}

		static int IsMemberOfGroup(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Ped>(state, 1).IsMemberOfGroup(luaL_checkinteger(state, 2)));
			return 1;
		}

		static int RandomizeOutfit(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).RandomizeOutfit();
			return 0;
		}

		static int StartScenario(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).StartScenario(CheckStringSafe(state, 2), lua_gettop(state) >= 3 ? luaL_checkinteger(state, 3) : -1, lua_gettop(state) >= 4 ? CheckBooleanSafe(state, 4) : true);
			return 0;
		}

		static int SetKeepTask(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).SetKeepTask(CheckBooleanSafe(state, 2));
			return 0;
		}

		static int ClearDamage(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).ClearDamage();
			return 0;
		}

		static int SetMaxTimeUnderwater(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).SetMaxTimeUnderwater(luaL_checkinteger(state, 2));
			return 0;
		}

		static int SetAsCop(lua_State* state)
		{
			GetObject<YimMenu::Ped>(state, 1).SetAsCop();
			return 0;
		}

		virtual void Register(lua_State* state) override
		{
			luaL_newmetatable(state, "Ped");
			{
				lua_newtable(state);
				{
					RegisterEntityMethods(state); // re-registering the entity methods under the vehicle table is more efficient than subclassing
					SetFunction(state, GetVehicle, "get_vehicle");
					SetFunction(state, GetLastVehicle, "get_last_vehicle");
					SetFunction(state, GetVehicleObjectId, "get_vehicle_object_id");
					SetFunction(state, SetInVehicle, "set_in_vehicle");
					SetFunction(state, GetRagdoll, "get_ragdoll");
					SetFunction(state, SetRagdoll, "set_ragdoll");
					SetFunction(state, GetBonePosition, "get_bone_position");
					SetFunction(state, IsEnemy, "is_enemy");
					SetFunction(state, GetAccuracy, "get_accuracy");
					SetFunction(state, SetAccuracy, "set_accuracy");
					SetFunction(state, GiveWeapon, "give_weapon");
					SetFunction(state, RemoveWeapon, "remove_weapon");
					SetFunction(state, GetCurrentWeapon, "get_current_weapon");
					SetFunction(state, HasWeapon, "has_weapon");
					SetFunction(state, SetInfiniteAmmo, "set_infinite_ammo");
					SetFunction(state, SetInfiniteClip, "set_infinite_clip");
					SetFunction(state, SetMaxAmmoForWeapon, "set_max_ammo_for_weapon");
					SetFunction(state, TeleportTo, "teleport_to");
					SetFunction(state, GetArmour, "get_armour");
					SetFunction(state, SetArmour, "set_armour");
					SetFunction(state, SetLeaderOfGroup, "set_leader_of_group");
					SetFunction(state, AddToGroup, "add_to_group");
					SetFunction(state, RemoveFromGroup, "remove_from_group");
					SetFunction(state, IsMemberOfGroup, "is_member_of_group");
					SetFunction(state, RandomizeOutfit, "randomize_outfit");
					SetFunction(state, StartScenario, "start_scenario");
					SetFunction(state, SetKeepTask, "set_keep_task");
					SetFunction(state, ClearDamage, "clear_damage");
					SetFunction(state, SetMaxTimeUnderwater, "set_max_time_underwater");
					SetFunction(state, SetAsCop, "set_as_cop");
				}
				lua_setfield(state, -2, "__index"); // prototype
			}
			Metatable<YimMenu::Ped>::Register(state);
			Metatable<YimMenu::Entity>::AddSubclass<YimMenu::Ped>();

			lua_newtable(state);
			SetConstructor<New>(state);
			SetFunction(state, LatentFunction<Create>, "create");
			lua_setglobal(state, "Ped");
		}
	};

	Ped _Ped;
}
