#include "core/scripting/LuaLibrary.hpp"
#include "core/scripting/LuaScript.hpp"
#include "core/scripting/LuaUtils.hpp"
#include "game/backend/Players.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Player.hpp"
#include "types/rage/vector.hpp"

namespace YimMenu::Lua
{
	class Player : LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

		static int New(lua_State* state)
		{
			CreateObject<YimMenu::Player>(state, static_cast<uint8_t>(luaL_checkinteger(state, 1)));
			return 1;
		}

		static int IsValid(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Player>(state, 1).IsValid());
			return 1;
		}

		static int IsLocal(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Player>(state, 1).IsLocal());
			return 1;
		}

		static int IsHost(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Player>(state, 1).IsHost());
			return 1;
		}

		static int IsModder(lua_State* state)
		{
			lua_pushboolean(state, GetObject<YimMenu::Player>(state, 1).IsModder());
			return 1;
		}

		static int GetId(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Player>(state, 1).GetId());
			return 1;
		}

		static int GetName(lua_State* state)
		{
			lua_pushstring(state, GetObject<YimMenu::Player>(state, 1).GetName());
			return 1;
		}

		static int GetPed(lua_State* state)
		{
			CopyObject<YimMenu::Ped>(state, GetObject<YimMenu::Player>(state, 1).GetPed());
			return 1;
		}

		static int GetMessageId(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Player>(state, 1).GetMessageId());
			return 1;
		}

		static int GetRID(lua_State* state)
		{
			lua_pushinteger(state, static_cast<lua_Integer>(GetObject<YimMenu::Player>(state, 1).GetRID()));
			return 1;
		}

		// Pushes (ip_string, port) — ip formatted as "a.b.c.d".
		static int PushAddress(lua_State* state, netSocketAddress addr)
		{
			char buf[16];
			std::snprintf(buf, sizeof(buf), "%u.%u.%u.%u",
			    addr.m_IpAddress.m_Field1, addr.m_IpAddress.m_Field2,
			    addr.m_IpAddress.m_Field3, addr.m_IpAddress.m_Field4);
			lua_pushstring(state, buf);
			lua_pushinteger(state, addr.m_Port);
			return 2;
		}

		static int GetExternalAddress(lua_State* state)
		{
			return PushAddress(state, GetObject<YimMenu::Player>(state, 1).GetExternalAddress());
		}

		static int GetInternalAddress(lua_State* state)
		{
			return PushAddress(state, GetObject<YimMenu::Player>(state, 1).GetInternalAddress());
		}

		static int GetAverageLatency(lua_State* state)
		{
			lua_pushnumber(state, GetObject<YimMenu::Player>(state, 1).GetAverageLatency());
			return 1;
		}

		static int GetAveragePacketLoss(lua_State* state)
		{
			lua_pushnumber(state, GetObject<YimMenu::Player>(state, 1).GetAveragePacketLoss());
			return 1;
		}

		static int GetRank(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Player>(state, 1).GetRank());
			return 1;
		}

		static int GetRP(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Player>(state, 1).GetRP());
			return 1;
		}

		static int GetMoney(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Player>(state, 1).GetMoney());
			return 1;
		}

		static int GetWantedLevel(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Player>(state, 1).GetWantedLevel());
			return 1;
		}

		static int SetWantedLevel(lua_State* state)
		{
			GetObject<YimMenu::Player>(state, 1).SetWantedLevel(luaL_checkinteger(state, 2));
			return 0;
		}

		static int GetMaxArmour(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Player>(state, 1).GetMaxArmour());
			return 1;
		}

		static int GetGroup(lua_State* state)
		{
			lua_pushinteger(state, GetObject<YimMenu::Player>(state, 1).GetGroup());
			return 1;
		}

		static int SetVisibleLocally(lua_State* state)
		{
			GetObject<YimMenu::Player>(state, 1).SetVisibleLocally(CheckBooleanSafe(state, 2));
			return 0;
		}

		static int TeleportTo(lua_State* state)
		{
			GetObject<YimMenu::Player>(state, 1).TeleportTo(GetObject<rage::fvector3>(state, 2));
			return 0;
		}

		static int SetFallDistanceOverride(lua_State* state)
		{
			GetObject<YimMenu::Player>(state, 1).SetFallDistanceOverride(static_cast<float>(luaL_checknumber(state, 2)));
			return 0;
		}

		static int SetPed(lua_State* state)
		{
			bool delete_old = lua_isnoneornil(state, 3) ? true : CheckBooleanSafe(state, 3);
			GetObject<YimMenu::Player>(state, 1).SetPed(GetObject<YimMenu::Ped>(state, 2), delete_old);
			return 0;
		}

		static int PlayersGetAll(lua_State* state)
		{
			lua_newtable(state);
			int idx = 1;
			for (auto& [id, player] : YimMenu::Players::GetPlayers())
			{
				CopyObject<YimMenu::Player>(state, player);
				lua_rawseti(state, -2, idx++);
			}
			return 1;
		}

		static int PlayersGetLocal(lua_State* state)
		{
			CopyObject<YimMenu::Player>(state, Self::GetPlayer());
			return 1;
		}

		static int PlayersGetSelected(lua_State* state)
		{
			CopyObject<YimMenu::Player>(state, YimMenu::Players::GetSelected());
			return 1;
		}

		static int PlayersSetSelected(lua_State* state)
		{
			YimMenu::Players::SetSelected(GetObject<YimMenu::Player>(state, 1));
			return 0;
		}

		static int PlayersGetByRID(lua_State* state)
		{
			auto rid = static_cast<uint64_t>(luaL_checkinteger(state, 1));
			CopyObject<YimMenu::Player>(state, YimMenu::Players::GetByRID(rid));
			return 1;
		}

		static int PlayersGetByMessageId(lua_State* state)
		{
			CopyObject<YimMenu::Player>(state, YimMenu::Players::GetByMessageId(luaL_checkinteger(state, 1)));
			return 1;
		}

		static int PlayersGetRandom(lua_State* state)
		{
			CopyObject<YimMenu::Player>(state, YimMenu::Players::GetRandom());
			return 1;
		}

		virtual void Register(lua_State* state) override
		{
			luaL_newmetatable(state, "Player");
			{
				lua_newtable(state);
				{
					SetFunction(state, IsValid, "is_valid");
					SetFunction(state, IsLocal, "is_local");
					SetFunction(state, IsHost, "is_host");
					SetFunction(state, IsModder, "is_modder");
					SetFunction(state, GetId, "get_id");
					SetFunction(state, GetName, "get_name");
					SetFunction(state, GetPed, "get_ped");
					SetFunction(state, GetMessageId, "get_message_id");
					SetFunction(state, GetRID, "get_rid");
					SetFunction(state, GetExternalAddress, "get_external_address");
					SetFunction(state, GetInternalAddress, "get_internal_address");
					SetFunction(state, GetAverageLatency, "get_average_latency");
					SetFunction(state, GetAveragePacketLoss, "get_average_packet_loss");
					SetFunction(state, GetRank, "get_rank");
					SetFunction(state, GetRP, "get_rp");
					SetFunction(state, GetMoney, "get_money");
					SetFunction(state, GetWantedLevel, "get_wanted_level");
					SetFunction(state, SetWantedLevel, "set_wanted_level");
					SetFunction(state, GetMaxArmour, "get_max_armour");
					SetFunction(state, GetGroup, "get_group");
					SetFunction(state, SetVisibleLocally, "set_visible_locally");
					SetFunction(state, TeleportTo, "teleport_to");
					SetFunction(state, SetFallDistanceOverride, "set_fall_distance_override");
					SetFunction(state, SetPed, "set_ped");
				}
				lua_setfield(state, -2, "__index");
			}
			Metatable<YimMenu::Player>::Register(state);

			lua_newtable(state);
			SetConstructor<New>(state);
			lua_setglobal(state, "Player");
			
			lua_newtable(state);
			SetFunction(state, PlayersGetAll, "get_all");
			SetFunction(state, PlayersGetLocal, "get_local");
			SetFunction(state, PlayersGetSelected, "get_selected");
			SetFunction(state, PlayersSetSelected, "set_selected");
			SetFunction(state, PlayersGetByRID, "get_by_rid");
			SetFunction(state, PlayersGetByMessageId, "get_by_message_id");
			SetFunction(state, PlayersGetRandom, "get_random");
			lua_setglobal(state, "players");
		}
	};

	Player _Player;
}
