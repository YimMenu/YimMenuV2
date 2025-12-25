#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/scripting/LatentFunction.hpp"
#include "game/gta/Entity.hpp"
#include "Entity.hpp"

namespace YimMenu::Lua
{
	// TODO: we need to automate this
	class Entity : LuaLibrary
	{
	public:
		using LuaLibrary::LuaLibrary;

		static int New(lua_State* state)
		{
			CreateObject<YimMenu::Entity>(state, luaL_checkinteger(state, 1));
			return 1;
		}

		static int GetHandle(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Entity>(state, 1).GetHandle());
			return 1;
		}

		static int IsValid(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsValid());
			return 1;
		}

		static int IsPed(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsPed());
			return 1;
		}

		static int IsVehicle(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsVehicle());
			return 1;
		}

		static int IsObject(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsObject());
			return 1;
		}

		static int IsPlayer(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsPlayer());
			return 1;
		}

		static int IsMissionEntity(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsMissionEntity());
			return 1;
		}

		static int GetModel(lua_State* state)
		{
			lua_pushinteger(state, (int)GetObject<YimMenu::Entity>(state, 1).GetModel());
			return 1;
		}

		static int GetPosition(lua_State* state)
		{
			CopyObject<rage::fvector3>(state, GetObject<YimMenu::Entity>(state, 1).GetPosition());
			return 1;
		}

		static int GetRotation(lua_State* state)
		{
			CopyObject<rage::fvector3>(state, GetObject<YimMenu::Entity>(state, 1).GetRotation(lua_gettop(state) >= 2 ? luaL_checkinteger(state, 2) : 2));
			return 1;
		}

		static int GetVelocity(lua_State* state)
		{
			CopyObject<rage::fvector3>(state, GetObject<YimMenu::Entity>(state, 1).GetVelocity());
			return 1;
		}

		static int SetPosition(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).SetPosition(GetObject<rage::fvector3>(state, 2));
			return 0;
		}

		static int SetRotation(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).SetRotation(GetObject<rage::fvector3>(state, 2), lua_gettop(state) >= 3 ? luaL_checkinteger(state, 3) : 2);
			return 0;
		}

		static int SetVelocity(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).SetVelocity(GetObject<rage::fvector3>(state, 2));
			return 0;
		}

		static int GetHeading(lua_State* state)
		{
			lua_pushnumber(state, GetObject<YimMenu::Entity>(state, 1).GetHeading());
			return 1;
		}

		static int SetHeading(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).SetHeading(luaL_checknumber(state, 2));
			return 0;
		}

		static int GetSpeed(lua_State* state)
		{
			lua_pushnumber(state, GetObject<YimMenu::Entity>(state, 1).GetSpeed());
			return 1;
		}

		static int SetCollision(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).SetCollision(lua_toboolean(state, 2));
			return 0;
		}

		static int SetFrozen(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).SetFrozen(lua_toboolean(state, 2));
			return 0;
		}

		static int Delete(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).Delete();
			return 0;
		}

		// DeleteNetwork

		static int IsNetworked(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsNetworked());
			return 1;
		}

		static int IsRemote(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsRemote());
			return 1;
		}

		static int HasControl(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).HasControl());
			return 1;
		}

		// GetNetworkObject
		// GetOwner

		static int GetNetworkObjectId(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Entity>(state, 1).GetNetworkObjectId());
			return 1;
		}

		static int PreventMigration(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).PreventMigration();
			return 0;
		}

		static int ForceControl(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).ForceControl();
			return 0;
		}

		static int RequestControl(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).RequestControl(lua_gettop(state) >= 2 ? luaL_checkinteger(state, 2) : 100);
			return 0;
		}

		// ForceSync

		static int IsInvincible(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsInvincible());
			return 1;
		}

		static int SetInvincible(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).SetInvincible(lua_toboolean(state, 2));
			return 0;
		}

		static int IsDead(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsDead());
			return 1;
		}

		static int Kill(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).Kill();
			return 0;
		}

		static int GetHealth(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Entity>(state, 1).GetHealth());
			return 1;
		}

		static int SetHealth(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).SetHealth(luaL_checkinteger(state, 2));
			return 0;
		}

		static int GetMaxHealth(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Entity>(state, 1).GetMaxHealth());
			return 1;
		}

		static int IsVisible(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).IsVisible());
			return 1;
		}

		static int SetVisible(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).SetVisible(CheckBooleanSafe(state, 2));
			return 0;
		}

		static int GetAlpha(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Entity>(state, 1).GetAlpha());
			return 1;
		}

		static int SetAlpha(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).SetAlpha(luaL_checkinteger(state, 2));
			return 0;
		}

		static int ResetAlpha(lua_State* state)
		{
			GetObject<YimMenu::Entity>(state, 1).ResetAlpha();
			return 0;
		}

		static int HasInterior(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Entity>(state, 1).HasInterior());
			return 1;
		}

		// Explode

		virtual void Register(lua_State* state) override
		{
			luaL_newmetatable(state, "Entity");
			{
				lua_newtable(state);
				{
					RegisterEntityMethods(state);
				}
				lua_setfield(state, -2, "__index"); // prototype
			}
			Metatable<YimMenu::Entity>::Register(state);

			lua_newtable(state);
			SetConstructor<New>(state);
			lua_setglobal(state, "Entity");
		}
	};

	void RegisterEntityMethods(lua_State* state)
	{
		SetFunction(state, Entity::GetHandle, "get_handle");
		SetFunction(state, Entity::IsValid, "is_valid");
		SetFunction(state, Entity::IsPed, "is_ped");
		SetFunction(state, Entity::IsVehicle, "is_vehicle");
		SetFunction(state, Entity::IsObject, "is_object");
		SetFunction(state, Entity::IsPlayer, "is_player");
		SetFunction(state, Entity::IsMissionEntity, "is_mission_entity");
		SetFunction(state, Entity::GetModel, "get_model");
		SetFunction(state, Entity::GetPosition, "get_position");
		SetFunction(state, Entity::GetRotation, "get_rotation");
		SetFunction(state, Entity::GetVelocity, "get_velocity");
		SetFunction(state, Entity::SetPosition, "set_position");
		SetFunction(state, Entity::SetRotation, "set_rotation");
		SetFunction(state, Entity::SetVelocity, "set_velocity");
		SetFunction(state, Entity::GetHeading, "get_heading");
		SetFunction(state, Entity::SetHeading, "set_heading");
		SetFunction(state, Entity::GetSpeed, "get_speed");
		SetFunction(state, Entity::SetCollision, "set_collision");
		SetFunction(state, Entity::SetFrozen, "set_frozen");
		SetFunction(state, Entity::Delete, "delete");
		SetFunction(state, Entity::IsNetworked, "is_networked");
		SetFunction(state, Entity::IsRemote, "is_remote");
		SetFunction(state, Entity::HasControl, "has_control");
		SetFunction(state, Entity::GetNetworkObjectId, "get_network_object_id");
		SetFunction(state, Entity::PreventMigration, "prevent_migration");
		SetFunction(state, Entity::ForceControl, "force_control");
		SetFunction(state, LatentFunction<Entity::RequestControl>, "request_control");
		SetFunction(state, Entity::IsInvincible, "is_invincible");
		SetFunction(state, Entity::SetInvincible, "set_invincible");
		SetFunction(state, Entity::IsDead, "is_dead");
		SetFunction(state, Entity::Kill, "kill");
		SetFunction(state, Entity::GetHealth, "get_health");
		SetFunction(state, Entity::SetHealth, "set_health");
		SetFunction(state, Entity::GetMaxHealth, "get_max_health");
		SetFunction(state, Entity::IsVisible, "is_visible");
		SetFunction(state, Entity::SetVisible, "set_visible");
		SetFunction(state, Entity::GetAlpha, "get_alpha");
		SetFunction(state, Entity::SetAlpha, "set_alpha");
		SetFunction(state, Entity::ResetAlpha, "reset_alpha");
		SetFunction(state, Entity::HasInterior, "has_interior");
	}

	Entity _Entity;
}