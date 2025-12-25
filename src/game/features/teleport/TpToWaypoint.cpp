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
		float ground_z = vec.z;
		int current_attempts = 0;
		bool found_ground = false;

		do
		{
			STREAMING::REQUEST_COLLISION_AT_COORD(vec.x, vec.y, vec.z);

			// find ground first and if found set z to new value and break
			if (MISC::GET_GROUND_Z_FOR_3D_COORD(vec.x, vec.y, max_ground_check, &ground_z, false, false))
			{
				vec.z = ground_z + 1.0f;
				found_ground = true;
				break;
			}

			if (current_attempts % 3 == 0)
			{
				ground_z += 25.f;
			}

			++current_attempts;
			ScriptMgr::Yield();
		} while (current_attempts < max_attempts);
		
		// whether ground was found or not check for water height
		float water_height;
		if (WATER::GET_WATER_HEIGHT(vec.x, vec.y, vec.z, &water_height))
		{
			vec.z = water_height;
			return;
		}	

		// fallback value
		if (!found_ground)
			vec.z = PATHFIND::GET_APPROX_HEIGHT_FOR_POINT(vec.x, vec.y);
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
					auto new_coords{coords};
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
