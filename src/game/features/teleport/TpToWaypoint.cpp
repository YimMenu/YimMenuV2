#include "core/commands/Command.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/Notifications.hpp"

namespace YimMenu::Features
{
	void ResolveZCoordinate(Vector3& vec)
	{
		constexpr float max_ground_check = 1000.f;
		constexpr int max_attempts = 20;
		constexpr float min_safe_z = 1.0f;

		float ground_z = vec.z + 25.f;  // empezar con una z un poco más alta
		int current_attempts = 0;

		do
		{
			STREAMING::REQUEST_COLLISION_AT_COORD(vec.x, vec.y, ground_z);

			float water_height;
			if (WATER::GET_WATER_HEIGHT(vec.x, vec.y, ground_z, &water_height))
			{
				vec.z = std::max(water_height, min_safe_z);
				return;
			}

			if (MISC::GET_GROUND_Z_FOR_3D_COORD(vec.x, vec.y, ground_z, &ground_z, false, false))
			{
				vec.z = std::max(ground_z + 1.0f, min_safe_z);
				return;
			}

			if (current_attempts % 3 == 0)
			{
				ground_z += 25.f;
			}

			++current_attempts;
			ScriptMgr::Yield();
		} while (current_attempts < max_attempts);

		// Último intento como fallback
		vec.z = std::max(PATHFIND::GET_APPROX_HEIGHT_FOR_POINT(vec.x, vec.y), min_safe_z);
	}

	class TpToWaypoint : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (HUD::IS_WAYPOINT_ACTIVE())
			{
				auto coords = HUD::GET_BLIP_COORDS(HUD::GET_CLOSEST_BLIP_INFO_ID(HUD::GET_WAYPOINT_BLIP_ENUM_ID()));
				ResolveZCoordinate(coords);
				Self::GetPed().TeleportTo(coords);
			}
		}
	};

	class AutoTpToWaypoint : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!Self::GetPed())
				return;

			if (HUD::IS_WAYPOINT_ACTIVE())
			{
				auto coords = HUD::GET_BLIP_COORDS(HUD::GET_CLOSEST_BLIP_INFO_ID(HUD::GET_WAYPOINT_BLIP_ENUM_ID()));
				FiberPool::Push([coords] {
					auto new_coords = coords;
					ResolveZCoordinate(new_coords);
					Self::GetPed().TeleportTo(new_coords);
				});
				HUD::SET_WAYPOINT_OFF();
			}
		}
	};

	static TpToWaypoint _TpToWaypoint{"tptowaypoint", "Teleport to Waypoint", "Teleports you to the waypoint"};
	static AutoTpToWaypoint _AutoTpToWaypoint{"autotptowaypoint", "Auto Teleport to Waypoint", "Automatically teleports you to the waypoint"};
}
