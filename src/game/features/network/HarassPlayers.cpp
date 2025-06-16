#include "core/commands/BoolCommand.hpp"
#include "game/backend/NodeHooks.hpp"
#include "game/backend/Self.hpp"

#include "types/network/sync/nodes/ped/CPedGameStateDataNode.hpp"
#include "types/network/sync/nodes/proximity_migrateable/CSectorDataNode.hpp"
#include "types/network/sync/nodes/player/CPlayerSectorPosNode.hpp"

namespace YimMenu::Features
{
	class HarassPlayers : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		std::shared_ptr<NodeHooks::Hook> m_PedGameStateHook;
		std::shared_ptr<NodeHooks::Hook> m_SectorDataNodeHook;
		std::shared_ptr<NodeHooks::Hook> m_PlayerSectorPosNodeHook;

		virtual void OnEnable() override
		{
			if (!m_PedGameStateHook)
			{
				m_PedGameStateHook = NodeHooks::AddHook(
				    "CPedGameStateDataNode",
				    [](rage::netObject* object, Player target) {
					    return object == Self::GetPed().GetNetworkObject();
				    },
				    [](rage::netObject* object, Player target, CProjectBaseSyncDataNode* node) {
					    auto ped_game_state = reinterpret_cast<CPedGameStateDataNode*>(node);
					    if (auto player_ped = target.GetPed(); player_ped && player_ped.GetNetworkObject())
					    {
						    ped_game_state->m_VehicleId = player_ped.GetVehicleObjectId();
						    ped_game_state->m_VehicleSeat = 2;
						    ped_game_state->m_InVehicle = true;
						    ped_game_state->m_InSeat = true;
					    }
				    },
				    true,
				    true);
			}

			if (!m_SectorDataNodeHook)
			{
				m_SectorDataNodeHook = NodeHooks::AddHook(
				    "CSectorDataNode",
				    [](rage::netObject* object, Player target) {
					    return object == Self::GetPed().GetNetworkObject();
				    },
				    [](rage::netObject* object, Player target, CProjectBaseSyncDataNode* node) {
					    auto sector_data = reinterpret_cast<CSectorDataNode*>(node);
					    if (auto player_ped = target.GetPed())
					    {
						    auto pos = player_ped.GetPosition();

						    sector_data->m_SectorX = int((pos.x / 54.0f) + 512.0f);
						    sector_data->m_SectorY = int((pos.y / 54.0f) + 512.0f);
						    sector_data->m_SectorZ = int((pos.z + 1700.0f) / 69.0f);
					    }
				    },
				    true,
				    true);
			}

			if (!m_PlayerSectorPosNodeHook)
			{
				m_PlayerSectorPosNodeHook = NodeHooks::AddHook(
				    "CPlayerSectorPosNode",
				    [](rage::netObject* object, Player target) {
					    return object == Self::GetPed().GetNetworkObject();
				    },
				    [](rage::netObject* object, Player target, CProjectBaseSyncDataNode* node) {
					    auto sector_pos_data = reinterpret_cast<CPlayerSectorPosNode*>(node);
					    if (auto player_ped = target.GetPed())
					    {
						    auto pos = player_ped.GetPosition();

						    int sectorX = int((pos.x / 54.0f) + 512.0f);
						    int sectorY = int((pos.y / 54.0f) + 512.0f);
						    int sectorZ = int((pos.z + 1700.0f) / 69.0f);

						    sector_pos_data->m_SectorPosX = pos.x - ((sectorX - 512.0f) * 54.0f);
						    sector_pos_data->m_SectorPosY = pos.y - ((sectorY - 512.0f) * 54.0f);
						    sector_pos_data->m_SectorPosZ = pos.z - ((sectorZ * 69.0f) - 1700.0f);

						    sector_pos_data->m_IsStandingOnEntity = false;
					    }
				    },
				    true,
				    true);
			}

			m_PedGameStateHook->Enable();
			m_SectorDataNodeHook->Enable();
			m_PlayerSectorPosNodeHook->Enable();
		}

		virtual void OnDisable() override
		{
			m_PedGameStateHook->Disable();
			m_SectorDataNodeHook->Disable();
			m_PlayerSectorPosNodeHook->Disable();
		}
	};

	static HarassPlayers _HarassPlayers{"harassplayers", "Harass Players", "Spoofs your position to make it appear as if you're next to all the players in the session at all times. Use with caution"};
}