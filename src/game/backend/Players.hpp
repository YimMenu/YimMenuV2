#pragma once
#include "PlayerData.hpp"
#include "game/gta/Player.hpp"

namespace YimMenu
{
	class Players
	{
		std::unordered_map<uint8_t, Player> m_Players{};
		std::unordered_map<uint8_t, PlayerData> m_PlayerDatas{};
		Player m_SelectedPlayer{};

	public:
		static void Init()
		{
			GetInstance().InitImpl();
		}

		static void OnPlayerJoin(CNetGamePlayer* player)
		{
			GetInstance().OnPlayerJoinImpl(player);
		}

		static void OnPlayerLeave(CNetGamePlayer* player)
		{
			GetInstance().OnPlayerLeaveImpl(player);
		}

		static Player GetSelected()
		{
			return GetInstance().m_SelectedPlayer;
		}

		static void SetSelected(Player player)
		{
			GetInstance().m_SelectedPlayer = player;
		}

		static std::unordered_map<uint8_t, Player>& GetPlayers()
		{
			return GetInstance().m_Players;
		}

		static Player GetByRID(uint64_t rid)
		{
			return GetInstance().GetByRIDImpl(rid);
		}

		static Player GetByHostToken(uint64_t token)
		{
			return GetInstance().GetByHostTokenImpl(token);
		}

		static Player GetByMessageId(int id)
		{
			return GetInstance().GetByMessageIdImpl(id);
		}

		static PlayerData& GetPlayerData(uint8_t idx)
		{
			return GetInstance().m_PlayerDatas[idx];
		}

		static Player GetRandom()
		{
			auto& players = GetPlayers();

			if (players.empty())
			{
				return Player();
			}

			uint8_t random = static_cast<uint8_t>(rand() % players.size());
			auto it = std::next(players.begin(), random);
			return it->second;
		}

	private:
		static Players& GetInstance()
		{
			static Players Instance;
			return Instance;
		}

		void InitImpl();

		void OnPlayerJoinImpl(CNetGamePlayer* player);
		void OnPlayerLeaveImpl(CNetGamePlayer* player);
		Player GetByRIDImpl(uint64_t rid);
		Player GetByHostTokenImpl(uint64_t token);
		Player GetByMessageIdImpl(int id);
	};
}