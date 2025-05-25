#include "core/commands/LoopedCommand.hpp"
#include "core/commands/FloatCommand.hpp"
#include "core/util/Math.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	static FloatCommand _SuperRunRunSpeed{"superrunrunspeed", "Run Speed", "Run speed (in m/s)", 0.0f, std::nullopt, 10.0f};
	static FloatCommand _SuperRunSprintSpeed{"superrunsprintspeed", "Sprint Speed", "Sprint speed (in m/s)", 0.0f, std::nullopt, 30.0f};

	class SuperRun : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (auto ped = Self::GetPed())
			{
				auto pedHandle = ped.GetHandle();

				if (PED::IS_PED_RAGDOLL(pedHandle))
					return;

				// don't set speed if in 1st person camera and moving backwards due to it not working properly
				if (ENTITY::GET_ENTITY_SPEED_VECTOR(pedHandle, 1).y < 0.0f && CAM::GET_FOLLOW_PED_CAM_VIEW_MODE() == 4)
					return;

				if (TASK::IS_PED_RUNNING(pedHandle) || TASK::IS_PED_SPRINTING(pedHandle)) {
					const float run_speed = TASK::IS_PED_SPRINTING(pedHandle) ?
						_SuperRunSprintSpeed.GetState() :
						_SuperRunRunSpeed.GetState();

					if (ENTITY::GET_ENTITY_SPEED(pedHandle) < run_speed) {
						Vector3 location = ENTITY::GET_ENTITY_COORDS(pedHandle, false /*Unused*/);
						Vector3 rot = ENTITY::GET_ENTITY_ROTATION(pedHandle, 2);
						float yaw   = Math::DegToRad(rot.z + 90);
	
						Vector3 offset;
						offset.x = location.x + (run_speed * cos(yaw));
						offset.y = location.y + (run_speed * sin(yaw));
						offset.z = location.z;
	
						float groundZ;
						MISC::GET_GROUND_Z_FOR_3D_COORD(offset.x, offset.y, 1000.f, &groundZ, false, false);
						if (groundZ < location.z)
							offset.z = groundZ;
	
						Vector3 vel = offset - location;
	
						ENTITY::SET_ENTITY_VELOCITY(ped.GetHandle(), vel.x, vel.y, vel.z);
					}
				}
			}
		}
	};

	static SuperRun _Superrun{"superrun", "Super Run", "Run faster than normal"};
}