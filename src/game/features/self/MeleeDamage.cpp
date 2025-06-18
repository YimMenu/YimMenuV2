#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Pools.hpp"
#include <game/gta/Natives.hpp>
#include "core/commands/FloatCommand.hpp"

namespace YimMenu::Features
{
	static FloatCommand _MeleeDamageScale{
	    "meleedamagescale",
	    "Melee Damage Scale",
	    "Sets the damage scale for melee",
	    0.0f,
	    10.0f,
	    1.0f};

	class MeleeDamage : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		void applyForceToTarget(Hash target, float scale)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(target);

			Vector3 from = ENTITY::GET_ENTITY_COORDS(Self::GetPed().GetHandle(), true);
			Vector3 to = ENTITY::GET_ENTITY_COORDS(target, true);

			Vector3 direction = {
			    to.x - from.x,
			    to.y - from.y,
			    0.0f};

			float len = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			if (len > 0.0f)
			{
				direction.x /= len;
				direction.y /= len;
			}

			float forceScale = scale;
			direction.x *= forceScale;
			direction.y *= forceScale;

			ENTITY::APPLY_FORCE_TO_ENTITY(
			    target,
			    0,
			    0.0f,
			    0.0f,
			    15.0f,
			    0,
			    0,
			    0,
			    0,
			    true,
			    false,
			    true,
			    false,
			    true);

			ENTITY::APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(
			    target,
			    0,
			    direction.x,
			    direction.y,
			    -1.0f,
			    true,
			    false,
			    true,
			    true);
		}

		void OnTick() override
		{
			float scale = _MeleeDamageScale.GetState();
			if (scale <= 0.0f)
				return;

			Hash weapon = WEAPON::GET_SELECTED_PED_WEAPON(Self::GetPed().GetHandle());

			PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(Self::GetPlayer().GetId(), scale, 1);

			Hash target = PED::GET_MELEE_TARGET_FOR_PED(Self::GetPed().GetHandle());
			if (target != 0 && ENTITY::DOES_ENTITY_EXIST(target))
			{
				if (PED::IS_PED_PERFORMING_MELEE_ACTION(Self::GetPed().GetHandle()))
				{
					if (WEAPON::HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(target, weapon, 0))
					{
						applyForceToTarget(target, scale);
					}
				}
			}
		}
		void OnDisable() override
		{
			PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(Self::GetPlayer().GetId(), 1.0f, 1);
		}

	};

	static MeleeDamage _MeleeDamage{
	    "meleedamage",
	    "Melee Damage",
	    "Allows altering your melee damage output"};
}
