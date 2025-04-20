#include "core/commands/IntCommand.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	static IntCommand _IncreasedDamage{"increaseddamageamount", "increased damage", "The damage amount to set", 1, 1000000, 100};

	class increased_damage : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		Hash currentWeapon{};
		float lastModifier = 1.f;

		virtual void OnTick() override
		{
			Hash weapon{};

			if (!WEAPON::GET_CURRENT_PED_WEAPON(Self::GetPed().GetHandle(), &weapon, false))
				return;

			if (weapon != currentWeapon)
			{
				if (currentWeapon != 0)
					WEAPON::SET_WEAPON_DAMAGE_MODIFIER(currentWeapon, 1.0f);

				currentWeapon = weapon;
				lastModifier  = 1.0f;
			}

			int desired = _IncreasedDamage.GetState();
			if (desired != static_cast<int>(lastModifier))
			{
				WEAPON::SET_WEAPON_DAMAGE_MODIFIER(weapon, static_cast<float>(desired));
				lastModifier = static_cast<float>(desired);
			}

			WEAPON::SET_PED_CURRENT_WEAPON_VISIBLE(Self::GetPed().GetHandle(), FALSE, FALSE, FALSE, FALSE);

		}

		virtual void OnDisable() override
		{
			if (currentWeapon != 0)
			{
				WEAPON::SET_WEAPON_DAMAGE_MODIFIER(currentWeapon, 1.0f);
				currentWeapon = 0;
				lastModifier  = 1.0f;
			}
		}
	};

	static increased_damage _IncrDamage{"incrdamage", "IncrDamage", "Increases the damage of your weapons only for you"};
}
