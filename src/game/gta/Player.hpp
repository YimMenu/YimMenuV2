#pragma once
#include "Ped.hpp"
#include "types/network/netSocketAddress.hpp"

class CNetGamePlayer;
union netAddress;

namespace rage
{
	class rlGamerInfo;
	class rlGamerInfoBase;
	class netAddress;
}

namespace YimMenu
{
	class PlayerData;

	class Player
	{
		CNetGamePlayer* m_Handle;

	public:
		Player() :
		    m_Handle(nullptr)
		{
		}

		Player(uint8_t id);

		constexpr Player(CNetGamePlayer* netGamePlayer) :
		    m_Handle(netGamePlayer)
		{
		}

		// object
		bool IsValid() const;
		bool IsLocal() const;
		int GetId() const;
		const char* GetName();
		CNetGamePlayer* GetHandle();
		rage::rlGamerInfo* GetGamerInfo();
		// rage::rlGamerInfoBase* GetConnectPeerAddress();
		// rage::netAddress* GetAddress();
		Ped GetPed();
		bool IsHost();
		// bool IsFriend();
		uint32_t GetMessageId();
		uint64_t GetRID();
		netSocketAddress GetExternalAddress();
		netSocketAddress GetInternalAddress();
		// uint32_t GetConnectionType();
		float GetAverageLatency();
		float GetAveragePacketLoss();

		// stats
		int GetRank();
		int GetRP();
		int GetMoney();

		// wanted
		int GetWantedLevel();
		void SetWantedLevel(int level); // only works for local player for now

		// backend/data store (should be refactored?)
		PlayerData& GetData();
		bool IsModder();
		// void AddDetection(Detection det);

		// visibility
		void SetVisibleLocally(bool visible);

		// teleportation

		/// <summary>
		/// Teleports remote players using the migration exploit. Returns immediately but takes several ticks to perform the teleport.
		/// The local player is teleported instantly
		/// </summary>
		/// <param name="coords">The position to teleport to</param>
		void TeleportTo(const rage::fvector3& coords);

		void SetFallDistanceOverride(float override);

		int GetMaxArmour();

		int GetGroup();

		void SetPed(Ped ped, bool delete_old = true);

		bool operator==(Player other);

		inline operator bool()
		{
			return IsValid();
		}

		inline operator int() = delete;
	};
	static_assert(sizeof(Player) == 8, "don't add anything else to Player");
}