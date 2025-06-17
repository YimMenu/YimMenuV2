#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Pools.hpp"
#include <game/gta/Natives.hpp>
#include "core/commands/FloatCommand.hpp"

namespace YimMenu::Features
{
	static FloatCommand _MeleeDamageScale{"meleedamagescale", "Melee Damage Scale", "Sets the damage scale for melee", 0.0f, 10.0f, 1.0f};

	class MeleeDamage : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		void OnTick() override
		{
			float scale = _MeleeDamageScale.GetState();
			if (scale > 0.0f)
			{
				Hash weapon;
				if (WEAPON::GET_CURRENT_PED_WEAPON(Self::GetPed().GetHandle(), &weapon, 0))
				{
					PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(Self::GetPlayer().GetId(), scale, 0);

					Hash target = PED::GET_MELEE_TARGET_FOR_PED(Self::GetPed().GetHandle());
					if (target != 0)
					{
						Vector3 forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(Self::GetPed().GetHandle());

						if (ENTITY::IS_ENTITY_A_PED(target))
						{
							float forceScale = scale * 1.0f; // Set ped force lower since they weigh less
						}
						float forceScale = scale * 5.0f;
						Vector3 force{
						    forward.x * forceScale,
						    forward.y * forceScale,
						    0.1f // Small vertical lift
						};

						ENTITY::APPLY_FORCE_TO_ENTITY(
						    target,
						    0,
						    force.x,
						    force.y,
						    force.z,
						    0.0f,
						    0.0f,
						    0.0f,
						    true,
						    true,
						    true,
						    true,
						    false,
						    true);
					}
				}
			}
		}
	};

	static MeleeDamage _MeleeDamage{"meleedamage", "Melee Damage", "Allows altering your melee damage output"};
}