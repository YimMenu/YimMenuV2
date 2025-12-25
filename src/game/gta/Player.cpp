#include "Player.hpp"

#include "Natives.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/network/rlGamerInfo.hpp"
#include "types/network/CNetGamePlayer.hpp"

#include "types/script/globals/GPBD_FM.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/backend/NodeHooks.hpp"
#include "game/backend/Players.hpp"
#include "game/gta/Vehicle.hpp"
#include "types/network/sync/nodes/vehicle/CVehicleProximityMigrationDataNode.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu
{
	Player::Player(uint8_t id)
	{
		m_Handle = Pointers.GetNetPlayerFromPid(id);
	}

	bool Player::IsValid() const
	{
		return m_Handle && m_Handle->IsPhysical() && m_Handle->m_PlayerInfo;
	}

	bool Player::IsLocal() const
	{
		if (!IsValid())
		{
			if (!*Pointers.IsSessionStarted)
				return true;

			return false;
		}

		return m_Handle->IsLocal();
	}

	int Player::GetId() const
	{
		if (!IsValid())
		{
			if (!*Pointers.IsSessionStarted)
				return 0;

			return 255;
		}

		return m_Handle->m_PlayerIndex;
	}

	const char* Player::GetName()
	{
		if (!IsValid())
		{
			return "Invalid";
		}

		return m_Handle->GetName();
	}

	CNetGamePlayer* Player::GetHandle()
	{
		return m_Handle;
	}

	rage::rlGamerInfo* Player::GetGamerInfo()
	{
		if (!IsValid())
			return nullptr;

		return m_Handle->GetGamerInfo();
	}

	Ped Player::GetPed()
	{
		if (!IsValid())
			return nullptr;

		return PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(m_Handle->m_PlayerIndex);
		// return m_Handle->m_PlayerInfo->m_Ped;
	}

	bool Player::IsHost()
	{
		if (IsValid())
			return m_Handle->IsHost();

		return false;
	}

#if 0
	bool Player::IsFriend()
	{
		if (!IsValid())
			return false;

		for (int i = 0; i < 250; i++)
		{
			if (!Pointers.FriendRegistry[i])
				break;

			if (Pointers.FriendRegistry[i]->m_RockstarId == GetRID())
				return true;
		}

		return false;
	}
#endif

	uint32_t Player::GetMessageId()
	{
		return m_Handle->m_MessageId;
	}

	uint64_t Player::GetRID()
	{
		if (!IsValid())
			return 0;

		return m_Handle->GetGamerInfo()->m_GamerHandle.m_RockstarId;
	}

	netSocketAddress Player::GetExternalAddress()
	{
#if 0
		if (auto addr = GetConnectPeerAddress())
			return addr->m_ExternalAddress;
#endif
		if (auto gamer_info = m_Handle->GetGamerInfo())
			return gamer_info->m_ExternalAddress;

		return {};
	}

	netSocketAddress Player::GetInternalAddress()
	{
#if 0
		if (auto addr = GetConnectPeerAddress())
			return addr->m_InternalAddress;
#endif
		if (auto gamer_info = m_Handle->GetGamerInfo())
			return gamer_info->m_InternalAddress;

		return {};
	}

	float Player::GetAverageLatency()
	{
		if (!IsValid())
			return -1.f;

		return NETWORK::NETWORK_GET_AVERAGE_LATENCY(GetId());
	}

	float Player::GetAveragePacketLoss()
	{
		if (!IsValid())
			return -1.f;

		return NETWORK::NETWORK_GET_AVERAGE_PACKET_LOSS(GetId());
	}

	int Player::GetRank()
	{
		if (!IsValid())
			return 0;

		if (auto fm = GPBD_FM::Get())
			return fm->Entries[GetId()].PlayerStats.Rank;

		return 0;
	}

	int Player::GetRP()
	{
		if (!IsValid())
			return 0;

		if (auto fm = GPBD_FM::Get())
			return fm->Entries[GetId()].PlayerStats.RP;

		return 0;
	}

	int Player::GetMoney()
	{
		if (!IsValid())
			return 0;

		if (auto fm = GPBD_FM::Get())
			return fm->Entries[GetId()].PlayerStats.Money;

		return 0;
	}

	int Player::GetWantedLevel()
	{
		return PLAYER::GET_PLAYER_WANTED_LEVEL(GetId());
	}

	void Player::SetWantedLevel(int level)
	{
		PLAYER::SET_PLAYER_WANTED_LEVEL(GetId(), level, false);
		PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(GetId(), false);
	}

	PlayerData& Player::GetData()
	{
		static PlayerData empty_data;
		if (IsValid())
			return Players::GetPlayerData(GetId());
		return empty_data;
	}

	bool Player::IsModder()
	{
		return GetData().m_IsModder;
	}

	void Player::SetVisibleLocally(bool visible)
	{
		if (!IsValid())
			return;

		if (visible)
			NETWORK::SET_PLAYER_VISIBLE_LOCALLY(GetId(), false);
		else
			NETWORK::SET_PLAYER_INVISIBLE_LOCALLY(GetId(), false);
	}

	void Player::TeleportTo(const rage::fvector3& coords)
	{
		if (auto ped = GetPed())
		{
			if (ped.HasControl())
			{
				ped.TeleportTo(coords);
				return;
			}

			if (auto vehicle = ped.GetVehicle())
			{
				auto handle = vehicle.GetHandle();
				FiberPool::Push([handle, coords] {
					auto new_veh = Vehicle(handle);
					if (new_veh.RequestControl())
						new_veh.SetPosition(coords);
				});
				return;
			}
		}

		struct RemoteTeleport
		{
			rage::vector3 m_Position;
			Player m_Player;
		};

		static std::unordered_map<std::uint16_t, RemoteTeleport> s_RemoteTeleports{};
		static std::shared_ptr<NodeHooks::Hook> s_VehicleMigrationHook = NodeHooks::AddHook(
		    "CVehicleProximityMigrationDataNode",
		    [](rage::netObject* object, Player target) {
			    if (auto it = s_RemoteTeleports.find(object->m_ObjectId); it != s_RemoteTeleports.end() && it->second.m_Player == target)
				    return true;

			    return false;
		    },
		    [](rage::netObject* object, Player target, CProjectBaseSyncDataNode* node) {
			    auto proximity_migration = reinterpret_cast<CVehicleProximityMigrationDataNode*>(node);
			    if (auto it = s_RemoteTeleports.find(object->m_ObjectId); it != s_RemoteTeleports.end() && it->second.m_Player == target)
			    {
				    LOG(INFO) << "Modified this node";
				    proximity_migration->m_HasOccupants[0] = true;
				    proximity_migration->m_Occupants[0] = it->second.m_Player.GetPed().GetNetworkObjectId();
				    proximity_migration->m_OverridePosition = true;
				    proximity_migration->m_Position = it->second.m_Position;
				    proximity_migration->m_VelocityX = 1; // seems to help
				    proximity_migration->m_VelocityY = 1;
				    proximity_migration->m_VelocityZ = 1;
			    }
		    },
		    true,
		    true);
		s_VehicleMigrationHook->Enable();

		auto player_id = this->GetId();
		FiberPool::Push([player_id, coords] {
			auto player = Player(player_id);

			if (!player.IsValid())
				return;

			if (auto id = player.GetPed().GetVehicleObjectId())
				Entity::DeleteNetwork(id); // delete so we can tp them on foot

			auto car = Vehicle::Create("rcbandito"_J, player.GetPed().GetPosition());

			if (!car)
				return;

			car.SetVisible(false);
			car.SetFrozen(true);
			car.SetCollision(false);
			car.ForceSync(&player);

			if (!car.IsNetworked())
			{
				LOG(WARNING) << "Player::TeleportTo: spawned vehicle is not networked. Please stop spectating to fix this issue";
				car.Delete();
				return;
			}

			RemoteTeleport tp{coords, player};
			s_RemoteTeleports.emplace(car.GetNetworkObjectId(), tp);

			ScriptMgr::Yield(25ms);

			for (int i = 0; i < 30; i++)
			{
				if (!player.IsValid() || !car || !*Pointers.IsSessionStarted || !player.GetPed())
					break;

				// check if the teleport worked
				if (player.GetPed().GetPosition().GetDistance(coords) <= 5.0f)
					break;

				if (car.HasControl())
					Pointers.MigrateObject(player.GetHandle(), car.GetNetworkObject(), 3);
				// req control immediately after to cycle
				car.RequestControl(0);
				ScriptMgr::Yield(20ms);
			}

			s_RemoteTeleports.erase(car.GetNetworkObjectId());
			if (car)
			{
				car.Delete();
			}
		});
	}

	void Player::SetFallDistanceOverride(float override)
	{
		PLAYER::SET_PLAYER_FALL_DISTANCE_TO_TRIGGER_RAGDOLL_OVERRIDE(GetId(), override);
	}

	int Player::GetMaxArmour()
	{
		return PLAYER::GET_PLAYER_MAX_ARMOUR(GetId()); // Not checking IsValid to let GetId return 0 in SP
	}

	int Player::GetGroup()
	{
		return PLAYER::GET_PLAYER_GROUP(GetId());
	}

	void Player::SetPed(Ped ped, bool delete_old)
	{
		auto old_ped = Self::GetPed();
		PLAYER::CHANGE_PLAYER_PED(GetId(), ped.GetHandle(), true, true);
		Self::Update();
		if (delete_old)
			old_ped.Delete();
	}

	bool Player::operator==(Player other)
	{
		return m_Handle == other.m_Handle;
	}
}