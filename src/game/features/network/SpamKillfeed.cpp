#include "core/commands/BoolCommand.hpp"
#include "game/backend/NodeHooks.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/Players.hpp"
#include "types/network/sync/nodes/ped/CPedHealthDataNode.hpp"

namespace YimMenu::Features
{
	class SpamKillfeed : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		std::shared_ptr<NodeHooks::Hook> m_PedHealthHook;

		virtual void OnEnable() override
		{
			if (!m_PedHealthHook)
			{
				m_PedHealthHook = NodeHooks::AddHook(
				    "CPedHealthDataNode",
				    [](rage::netObject* object, Player target) {
					    return object == Self::GetPed().GetNetworkObject();
				    },
				    [](rage::netObject* object, Player target, CProjectBaseSyncDataNode* node) {
					    auto ped_health = reinterpret_cast<CPedHealthDataNode*>(node);
					    if (std::rand() % 2)
					    {
						    // dead
						    if (auto random = Players::GetRandom(); random.IsValid() && random.GetPed())
							    ped_health->m_WeaponDamageEntity = random.GetPed().GetNetworkObjectId();
						    ped_health->m_WeaponDamageHash = "WEAPON_EXPLOSION"_J;
						    ped_health->m_HasMaxHealth = false;
						    ped_health->m_HurtStarted = true;
						    ped_health->m_Health = 0;
						    ped_health->m_WeaponDamageComponent = 5;
					    }
					    else
					    {
						    // alive
						    ped_health->m_HasMaxHealth = true;
						    ped_health->m_Health = 100;
					    }
				    },
				    true,
				    true);
			}

			m_PedHealthHook->Enable();
		}

		virtual void OnDisable() override
		{
			if (m_PedHealthHook)
				m_PedHealthHook->Disable();
		}
	};

	static SpamKillfeed _SpamKillfeed{"spamkillfeed", "Spam Killfeed", "Spams the killfeed of all players with fake kill entries. Use with caution"};
}