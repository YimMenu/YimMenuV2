#include "core/commands/LoopedCommand.hpp"
#include "core/util/Math.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/frontend/GUI.hpp"
#include "types/pad/ControllerInputs.hpp"

namespace YimMenu::Features
{
	class RapidFire : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		const std::size_t m_TickRate = 5u;
		std::size_t m_CurrentTick = 0;

		bool CanShoot()
		{
			bool result = (m_CurrentTick == 0);
			m_CurrentTick = (m_CurrentTick + 1) % m_TickRate;
			return result;
		}

		virtual void OnTick() override
		{
			if (!HUD::IS_PAUSE_MENU_ACTIVE() && !GUI::IsOpen() && Self::GetPed() && !Self::GetPed().IsDead())
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK) && CanShoot())
				{
					const auto weapon_entity = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(Self::GetPed().GetHandle(), 0);
					if (!weapon_entity)
						return;

					Vector3 dim_min;
					Vector3 dim_max;
					MISC::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(weapon_entity), &dim_min, &dim_max);

					const auto dimensions = (dim_max - dim_min) * 0.5f;
					const auto weapon_position =
					    ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(weapon_entity, dimensions.x, 0, dimensions.z * 0.3f);

					auto camera_direction = Math::RotationToDirection(CAM::GET_GAMEPLAY_CAM_ROT(0));
					auto camera_position = CAM::GET_GAMEPLAY_CAM_COORD() + camera_direction;

					Vector3 end = camera_position + camera_direction * 2000.0;

					const auto raycast_handle =
					    SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camera_position.x,
					        camera_position.y,
					        camera_position.z,
					        end.x,
					        end.y,
					        end.z,
					        -1,
					        0,
					        7);
					BOOL did_raycast_hit{FALSE};
					Vector3 raycast_hit_position{};
					Vector3 raycast_surface_normal_hit_position{};
					int raycast_hit_entity{};
					SHAPETEST::GET_SHAPE_TEST_RESULT(raycast_handle, &did_raycast_hit, &raycast_hit_position, &raycast_surface_normal_hit_position, &raycast_hit_entity);
					if (did_raycast_hit)
					{
						end = raycast_hit_position;
					}

					Hash weapon_hash = Self::GetPed().GetCurrentWeapon();

					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(
					    weapon_position.x,
					    weapon_position.y,
					    weapon_position.z,
					    end.x,
					    end.y,
					    end.z,
					    WEAPON::GET_WEAPON_DAMAGE(weapon_hash, 0),
					    true,
					    weapon_hash,
					    Self::GetPed().GetHandle(),
					    true,
					    false,
					    -1.0);
				}
			}
		}
	};

	static RapidFire _RapidFire{"rapidfire", "Rapid Fire", "Increases the fire rate of your weapons substantially"};
}