#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "core/scripting/LatentFunction.hpp"
#include "game/gta/Vehicle.hpp"
#include "Entity.hpp"

namespace YimMenu::Lua
{
	// TODO: we need to automate this
	class Vehicle : LuaLibrary
	{
	public:
		using LuaLibrary::LuaLibrary;

		static int New(lua_State* state)
		{
			CreateObject<YimMenu::Vehicle>(state, luaL_checkinteger(state, 1));
			return 1;
		}

		static int Create(lua_State* state)
		{
			CopyObject<YimMenu::Vehicle>(state, YimMenu::Vehicle::Create(GetHashArgument(state, 1), GetObject<rage::fvector3>(state, 2), lua_gettop(state) >= 3 ? luaL_checknumber(state, 3) : 0.0f));
			return 1;
		}

		static int Fix(lua_State* state)
		{
			GetObject<YimMenu::Vehicle>(state, 1).Fix();
			return 0;
		}

		static int GetGear(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Vehicle>(state, 1).GetGear());
			return 1;
		}

		static int GetRevRatio(lua_State* state)
		{
			lua_pushnumber(state, GetObject<YimMenu::Vehicle>(state, 1).GetRevRatio());
			return 1;
		}

		static int GetSpeed(lua_State* state)
		{
			lua_pushnumber(state, GetObject<YimMenu::Vehicle>(state, 1).GetSpeed());
			return 1;
		}

		static int Upgrade(lua_State* state)
		{
			GetObject<YimMenu::Vehicle>(state, 1).Upgrade();
			return 0;
		}

		static int GetPlateText(lua_State* state)
		{
			auto text = GetObject<YimMenu::Vehicle>(state, 1).GetPlateText();
			lua_pushlstring(state, text.c_str(), text.size());
			return 1;
		}

		static int SetPlateText(lua_State* state)
		{
			GetObject<YimMenu::Vehicle>(state, 1).SetPlateText(CheckStringSafe(state, 2));
			return 0;
		}

		// GetOwnedMods

		static int IsSeatFree(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Vehicle>(state, 1).IsSeatFree(luaL_checkinteger(state, 2)));
			return 1;
		}

		static int SupportsBoost(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Vehicle>(state, 1).SupportsBoost());
			return 1;
		}

		static int IsBoostActive(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Vehicle>(state, 1).IsBoostActive());
			return 1;
		}

		static int SetBoostCharge(lua_State* state)
		{
			GetObject<YimMenu::Vehicle>(state, 1).SetBoostCharge(lua_gettop(state) >= 2 ? luaL_checkinteger(state, 3) : 100);
			return 0;
		}

		static int LowerStance(lua_State* state)
		{
			GetObject<YimMenu::Vehicle>(state, 1).LowerStance(CheckBooleanSafe(state, 2));
			return 0;
		}

		static int BringToHalt(lua_State* state)
		{
			GetObject<YimMenu::Vehicle>(state, 1).BringToHalt(luaL_checknumber(state, 2), luaL_checkinteger(state, 3));
			return 0;
		}

		static int SetOnGroundProperly(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Vehicle>(state, 1).SetOnGroundProperly());
			return 1;
		}

		static int GetFullName(lua_State* state)
		{
			auto name = GetObject<YimMenu::Vehicle>(state, 1).GetFullName();
			lua_pushlstring(state, name.c_str(), name.size());
			return 1;
		}

		virtual void Register(lua_State* state) override
		{
			luaL_newmetatable(state, "Vehicle");
			{
				lua_newtable(state);
				{
					RegisterEntityMethods(state); // re-registering the entity methods under the vehicle table is more efficient than subclassing
					SetFunction(state, Fix, "fix");
					SetFunction(state, GetGear, "get_gear");
					SetFunction(state, GetRevRatio, "get_rev_ratio");
					SetFunction(state, GetSpeed, "get_speed");
					SetFunction(state, Upgrade, "upgrade");
					SetFunction(state, GetPlateText, "get_plate_text");
					SetFunction(state, SetPlateText, "set_plate_text");
					SetFunction(state, IsSeatFree, "is_seat_free");
					SetFunction(state, SupportsBoost, "supports_boost");
					SetFunction(state, IsBoostActive, "is_boost_active");
					SetFunction(state, SetBoostCharge, "set_boost_charge");
					SetFunction(state, LowerStance, "lower_stance");
					SetFunction(state, BringToHalt, "bring_to_halt");
					SetFunction(state, SetOnGroundProperly, "set_on_ground_properly");
					SetFunction(state, GetFullName, "get_full_name");
				}
				lua_setfield(state, -2, "__index"); // prototype
			}
			Metatable<YimMenu::Vehicle>::Register(state);
			Metatable<YimMenu::Entity>::AddSubclass<YimMenu::Vehicle>();

			lua_newtable(state);
			SetConstructor<New>(state);
			SetFunction(state, LatentFunction<Create>, "create");
			lua_setglobal(state, "Vehicle");
		}
	};

	Vehicle _Vehicle;
}
