#include "Players.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/network/CNetGamePlayer.hpp"
#include "types/network/rlGamerInfo.hpp"

namespace YimMenu
{
	void Players::InitImpl()
	{
		for (uint8_t idx = 0; idx < 32u; idx++)
		{
			if (const auto netPlayer = Pointers.GetNetPlayerFromPid(idx); netPlayer && netPlayer->IsPhysical())
			{
				OnPlayerJoin(netPlayer);
			}
		}
	}

	void Players::OnPlayerJoinImpl(CNetGamePlayer* player)
	{
		auto new_player = Player(player);

		m_Players[player->m_PlayerIndex] = new_player;
		m_PlayerDatas[player->m_PlayerIndex] = PlayerData();
	}

	void Players::OnPlayerLeaveImpl(CNetGamePlayer* player)
	{
		m_Players.erase(player->m_PlayerIndex);
		m_PlayerDatas.erase(player->m_PlayerIndex);
	}

	Player Players::GetByRIDImpl(uint64_t rid)
	{
		for (auto& [idx, player] : Players::GetPlayers())
		{
			if (player.GetGamerInfo()->m_GamerHandle.m_RockstarId == rid)
			{
				return player;
			}
		}

		return nullptr;
	}

	Player Players::GetByHostTokenImpl(uint64_t token)
	{
		for (auto& [idx, player] : Players::GetPlayers())
		{
			if (player.GetGamerInfo()->m_HostToken == token)
			{
				return player;
			}
		}

		return nullptr;
	}

	Player Players::GetByMessageIdImpl(int id)
	{
		for (auto& [idx, player] : Players::GetPlayers())
		{
			if (player.GetHandle()->m_MessageId == id)
			{
				return player;
			}
		}

		return nullptr;
	}
}