#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Pools.hpp"
#include "types/fx/ExplosionType.hpp"
#include <game/gta/Natives.hpp>
#include "core/commands/ListCommand.hpp"
#include "core/commands/FloatCommand.hpp"
#include "game/gta/Scripts.hpp"

namespace YimMenu::Features
{
	static const std::vector<std::pair<int, const char*>> g_ExplosionTypeArray = {
	    {static_cast<int>(ExplosionType::DONTCARE), "Don't Care"},
	    {static_cast<int>(ExplosionType::GRENADE), "Grenade"},
	    {static_cast<int>(ExplosionType::GRENADELAUNCHER), "Grenade Launcher"},
	    {static_cast<int>(ExplosionType::STICKYBOMB), "Sticky Bomb"},
	    {static_cast<int>(ExplosionType::MOLOTOV), "Molotov"},
	    {static_cast<int>(ExplosionType::ROCKET), "Rocket"},
	    {static_cast<int>(ExplosionType::TANKSHELL), "Tank Shell"},
	    {static_cast<int>(ExplosionType::HI_OCTANE), "Hi Octane"},
	    {static_cast<int>(ExplosionType::CAR), "Car"},
	    {static_cast<int>(ExplosionType::PLANE), "Plane"},
	    {static_cast<int>(ExplosionType::PETROL_PUMP), "Petrol Pump"},
	    {static_cast<int>(ExplosionType::BIKE), "Bike"},
	    {static_cast<int>(ExplosionType::DIR_STEAM), "Directional Steam"},
	    {static_cast<int>(ExplosionType::DIR_FLAME), "Directional Flame"},
	    {static_cast<int>(ExplosionType::DIR_WATER_HYDRANT), "Directional Water Hydrant"},
	    {static_cast<int>(ExplosionType::DIR_GAS_CANISTER), "Directional Gas Canister"},
	    {static_cast<int>(ExplosionType::BOAT), "Boat"},
	    {static_cast<int>(ExplosionType::SHIP_DESTROY), "Ship Destroy"},
	    {static_cast<int>(ExplosionType::TRUCK), "Truck"},
	    {static_cast<int>(ExplosionType::BULLET), "Bullet"},
	    {static_cast<int>(ExplosionType::SMOKEGRENADELAUNCHER), "Smoke Grenade Launcher"},
	    {static_cast<int>(ExplosionType::SMOKEGRENADE), "Smoke Grenade"},
	    {static_cast<int>(ExplosionType::BZGAS), "BZ Gas"},
	    {static_cast<int>(ExplosionType::FLARE), "Flare"},
	    {static_cast<int>(ExplosionType::GAS_CANISTER), "Gas Canister"},
	    {static_cast<int>(ExplosionType::EXTINGUISHER), "Extinguisher"},
	    {static_cast<int>(ExplosionType::PROGRAMMABLEAR), "Programmable AR"},
	    {static_cast<int>(ExplosionType::TRAIN), "Train"},
	    {static_cast<int>(ExplosionType::BARREL), "Barrel"},
	    {static_cast<int>(ExplosionType::PROPANE), "Propane"},
	    {static_cast<int>(ExplosionType::BLIMP), "Blimp"},
	    {static_cast<int>(ExplosionType::DIR_FLAME_EXPLODE), "Directional Flame Explode"},
	    {static_cast<int>(ExplosionType::TANKER), "Tanker"},
	    {static_cast<int>(ExplosionType::PLANE_ROCKET), "Plane Rocket"},
	    {static_cast<int>(ExplosionType::VEHICLE_BULLET), "Vehicle Bullet"},
	    {static_cast<int>(ExplosionType::GAS_TANK), "Gas Tank"},
	    {static_cast<int>(ExplosionType::BIRD_CRAP), "Bird Crap"},
	    {static_cast<int>(ExplosionType::RAILGUN), "Railgun"},
	    {static_cast<int>(ExplosionType::BLIMP2), "Blimp 2"},
	    {static_cast<int>(ExplosionType::FIREWORK), "Firework"},
	    {static_cast<int>(ExplosionType::SNOWBALL), "Snowball"},
	    {static_cast<int>(ExplosionType::PROXMINE), "Proximity Mine"},
	    {static_cast<int>(ExplosionType::VALKYRIE_CANNON), "Valkyrie Cannon"},
	    {static_cast<int>(ExplosionType::AIR_DEFENCE), "Air Defence"},
	    {static_cast<int>(ExplosionType::PIPEBOMB), "Pipe Bomb"},
	    {static_cast<int>(ExplosionType::VEHICLEMINE), "Vehicle Mine"},
	    {static_cast<int>(ExplosionType::EXPLOSIVEAMMO), "Explosive Ammo"},
	    {static_cast<int>(ExplosionType::APCSHELL), "APC Shell"},
	    {static_cast<int>(ExplosionType::BOMB_CLUSTER), "Cluster Bomb"},
	    {static_cast<int>(ExplosionType::BOMB_GAS), "Gas Bomb"},
	    {static_cast<int>(ExplosionType::BOMB_INCENDIARY), "Incendiary Bomb"},
	    {static_cast<int>(ExplosionType::BOMB_STANDARD), "Standard Bomb"},
	    {static_cast<int>(ExplosionType::TORPEDO), "Torpedo"},
	    {static_cast<int>(ExplosionType::TORPEDO_UNDERWATER), "Underwater Torpedo"},
	    {static_cast<int>(ExplosionType::BOMBUSHKA_CANNON), "Bombushka Cannon"},
	    {static_cast<int>(ExplosionType::BOMB_CLUSTER_SECONDARY), "Cluster Bomb (Secondary)"},
	    {static_cast<int>(ExplosionType::HUNTER_BARRAGE), "Hunter Barrage"},
	    {static_cast<int>(ExplosionType::HUNTER_CANNON), "Hunter Cannon"},
	    {static_cast<int>(ExplosionType::ROGUE_CANNON), "Rogue Cannon"},
	    {static_cast<int>(ExplosionType::MINE_UNDERWATER), "Underwater Mine"},
	    {static_cast<int>(ExplosionType::ORBITAL_CANNON), "Orbital Cannon"},
	    {static_cast<int>(ExplosionType::BOMB_STANDARD_WIDE), "Standard Bomb (Wide)"},
	    {static_cast<int>(ExplosionType::EXPLOSIVEAMMO_SHOTGUN), "Explosive Ammo (Shotgun)"},
	    {static_cast<int>(ExplosionType::OPPRESSOR2_CANNON), "Oppressor Mk II Cannon"},
	    {static_cast<int>(ExplosionType::MORTAR_KINETIC), "Kinetic Mortar"},
	    {static_cast<int>(ExplosionType::VEHICLEMINE_KINETIC), "Vehicle Mine (Kinetic)"},
	    {static_cast<int>(ExplosionType::VEHICLEMINE_EMP), "Vehicle Mine (EMP)"},
	    {static_cast<int>(ExplosionType::VEHICLEMINE_SPIKE), "Vehicle Mine (Spike)"},
	    {static_cast<int>(ExplosionType::VEHICLEMINE_SLICK), "Vehicle Mine (Slick)"},
	    {static_cast<int>(ExplosionType::VEHICLEMINE_TAR), "Vehicle Mine (Tar)"},
	    {static_cast<int>(ExplosionType::SCRIPT_DRONE), "Script Drone"},
	    {static_cast<int>(ExplosionType::RAYGUN), "Ray Gun"},
	    {static_cast<int>(ExplosionType::BURIEDMINE), "Buried Mine"},
	    {static_cast<int>(ExplosionType::SCRIPT_MISSILE), "Script Missile"},
	    {static_cast<int>(ExplosionType::RCTANK_ROCKET), "RC Tank Rocket"},
	    {static_cast<int>(ExplosionType::BOMB_WATER), "Water Bomb"},
	    {static_cast<int>(ExplosionType::BOMB_WATER_SECONDARY), "Water Bomb (Secondary)"},
	    {static_cast<int>(ExplosionType::_0xF728C4A9), "Unknown Explosion F728C4A9"},
	    {static_cast<int>(ExplosionType::_0xBAEC056F), "Unknown Explosion BAEC056F"},
	    {static_cast<int>(ExplosionType::FLASHGRENADE), "Flash Grenade"},
	    {static_cast<int>(ExplosionType::STUNGRENADE), "Stun Grenade"},
	    {static_cast<int>(ExplosionType::_0x763D3B3B), "Unknown Explosion 763D3B3B"},
	    {static_cast<int>(ExplosionType::SCRIPT_MISSILE_LARGE), "Script Missile (Large)"},
	    {static_cast<int>(ExplosionType::SUBMARINE_BIG), "Submarine (Big)"},
	    {static_cast<int>(ExplosionType::EMPLAUNCHER_EMP), "EMP Launcher"},
	};

	static ListCommand _SelectedExplosion{
	    "selectedexplosion",
	    "Explosion Type",
	    "Select an explosion type",
	    g_ExplosionTypeArray,
	    static_cast<int>(ExplosionType::BULLET)};

	static FloatCommand _ExplosionDamageScale{
	    "explosiondamage",
	    "Explosion Damage Scale",
	    "Sets the damage scale for explosions",
	    0.0f,
	    1000.0f,
	    1.0f};

	static FloatCommand _CameraShake{
	    "explosioncamerashake",
	    "Explosion Camera Shake",
	    "Controls how much the camera shakes during explosions",
	    0.0f,
	    10.0f,
	    0.1f};

	class ExplosiveAmmo : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		void OnTick() override
		{
			TriggerExplosion();
		}

		void TriggerExplosion()
		{
			Hash weapon = WEAPON::GET_SELECTED_PED_WEAPON(Self::GetPed().GetHandle());

			// Ensure ped is using a non-melee/non-explosive weapon AND that their not using melee of any kind before applying
			if (WEAPON::IS_PED_ARMED(Self::GetPed().GetHandle(), 4) && !PED::IS_PED_PERFORMING_MELEE_ACTION(Self::GetPed().GetHandle()))
			{
				Vector3 impactCoords;
				if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(Self::GetPed().GetHandle(), &impactCoords))
				{
					auto explosionType = static_cast<ExplosionType>(_SelectedExplosion.GetState());
					float damageScale = _ExplosionDamageScale.GetState();
					float shake = _CameraShake.GetState();

					Scripts::RunWithSpoofedThreadName("am_mp_orbital_cannon"_J, [=] {
						FIRE::ADD_OWNED_EXPLOSION(
						    Self::GetPed().GetHandle(),
						    impactCoords.x,
						    impactCoords.y,
						    impactCoords.z,
						    static_cast<int>(explosionType),
						    damageScale,
						    true,  // isAudible
						    false, // isInvisible
						    shake);
					});
				}
			}
		}
	};

	static ExplosiveAmmo _ExplosiveAmmo{"ExplosiveAmmo", "Explosive Ammo", "Every bullet you shoot explodes."};
}
