#include "Player.hpp"

#include "Natives.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/network/rlGamerInfo.hpp"
#include "types/network/CNetGamePlayer.hpp"

#include "types/script/globals/GPBD_FM.hpp"

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

	void Player::SetVisibleLocally(bool visible)
	{
		if (!IsValid())
			return;

		if (visible)
			NETWORK::SET_PLAYER_VISIBLE_LOCALLY(GetId(), false);
		else
			NETWORK::SET_PLAYER_INVISIBLE_LOCALLY(GetId(), false);
	}

	bool Player::operator==(Player other)
	{
		return m_Handle == other.m_Handle;
	}
}