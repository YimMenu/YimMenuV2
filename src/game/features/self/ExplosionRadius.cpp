#include "core/commands/LoopedCommand.hpp"  
#include "game/backend/Self.hpp"  
#include "game/gta/Pools.hpp"  
#include <game/gta/Natives.hpp>  
#include "core/commands/FloatCommand.hpp"  

namespace YimMenu::Features  
{  
	static FloatCommand _ExplosionRadiusScale{"explosionradiusscale", "Weapon Explosion RadiusScale", "Modifying Weapon Explosion RadiusScale", 0.0f, 10.0f, 1.0f};  

	class ExplosionRadius : public LoopedCommand  
	{  
		using LoopedCommand::LoopedCommand;  

		void OnTick() override  
		{  
			Hash weapon;  
			if (WEAPON::GET_CURRENT_PED_WEAPON(Self::GetPed().GetHandle(), &weapon, 0))  
			{  
				WEAPON::SET_WEAPON_AOE_MODIFIER(weapon, _ExplosionRadiusScale.GetState());  
			}  
		}  
	};  

	static ExplosionRadius _ExplosionRadius{"explosionradius", "Weapon Explosion Radius", "Modifying Weapon Explosion Radius"};  
}