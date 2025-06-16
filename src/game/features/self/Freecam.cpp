#include "core/commands/FloatCommand.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "core/util/Math.hpp"
#include "game/backend/Self.hpp"
#include "game/frontend/GUI.hpp"
#include "game/gta/Natives.hpp"
#include "types/pad/ControllerInputs.hpp"


namespace YimMenu::Features
{
	static FloatCommand _FreecamSpeed{"freecamspeed", "Freecam Speed", "How fast the freecam will move positions", 0.01f, 10.0f, 0.10f};

	class Freecam : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		static inline int camEntity = 0;
		static inline Vector3 position{};
		static inline Vector3 rotation{};

		void CreateFreecam()
		{
			if (camEntity)
				return;

			camEntity = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 0);
			position = CAM::GET_GAMEPLAY_CAM_COORD();
			rotation = CAM::GET_GAMEPLAY_CAM_ROT(2);

			CAM::SET_CAM_COORD(camEntity, position.x, position.y, position.z);
			CAM::SET_CAM_ROT(camEntity, rotation.x, rotation.y, rotation.z, 2);
			CAM::SET_CAM_ACTIVE(camEntity, true);
			CAM::RENDER_SCRIPT_CAMS(true, true, 500, true, true, 0);
		}

		void UpdateFreecamPosition()
		{
			if (GUI::IsOpen())
				return;
			Vector3 PosChange{};
			static float accel = 0.0f;

			// Left Shift
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (Hash)ControllerInputs::INPUT_SPRINT))
			{
				PosChange.z += _FreecamSpeed.GetState() / 2;
			}
			// Left Control
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_DUCK) /* || PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_HORSE_STOP) */)
			{
				PosChange.z -= _FreecamSpeed.GetState() / 2;
			}
			// Forward
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (Hash)ControllerInputs::INPUT_MOVE_UP_ONLY))
			{
				PosChange.y += _FreecamSpeed.GetState();
			}
			// Backward
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (Hash)ControllerInputs::INPUT_MOVE_DOWN_ONLY))
			{
				PosChange.y -= _FreecamSpeed.GetState();
			}
			// Left
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (Hash)ControllerInputs::INPUT_MOVE_LEFT_ONLY))
			{
				PosChange.x -= _FreecamSpeed.GetState();
			}
			// Right
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (Hash)ControllerInputs::INPUT_MOVE_RIGHT_ONLY))
			{
				PosChange.x += _FreecamSpeed.GetState();
			}


			if (PosChange.x == 0.0f && PosChange.y == 0.0f && PosChange.z == 0.0f)
			{
				accel = 0.0f;
			}
			else if (accel < 10)
			{
				accel += 0.15f;
			}

			Vector3 rot = CAM::GET_CAM_ROT(camEntity, 2);
			float yaw = Math::DegToRad(rot.z);

			position.x += (PosChange.x * cos(yaw) - PosChange.y * sin(yaw)) * accel;
			position.y += (PosChange.x * sin(yaw) + PosChange.y * cos(yaw)) * accel;
			position.z += PosChange.z * accel;

			CAM::SET_CAM_COORD(camEntity, position.x, position.y, position.z);
			STREAMING::SET_FOCUS_POS_AND_VEL(position.x, position.y, position.z, 0.0f, 0.0f, 0.0f);
		}

		virtual void OnTick() override
		{
			CreateFreecam();
			UpdateFreecamPosition();

			rotation = CAM::GET_GAMEPLAY_CAM_ROT(2);
			CAM::SET_CAM_ROT(camEntity, rotation.x, rotation.y, rotation.z, 2);

			TASK::CLEAR_PED_TASKS(Self::GetPed().GetHandle());
			TASK::CLEAR_PED_SECONDARY_TASK(Self::GetPed().GetHandle());
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(Self::GetPed().GetHandle());
			Self::GetPed().SetFrozen(true);
			Self::GetPed().SetVisible(false);

			if (!GUI::IsOpen())
			{
				static Hash controls[]{
				    (Hash)ControllerInputs::INPUT_LOOK_LR,
				    (Hash)ControllerInputs::INPUT_LOOK_UD,
				    (Hash)ControllerInputs::INPUT_LOOK_UP_ONLY,
				    (Hash)ControllerInputs::INPUT_LOOK_DOWN_ONLY,
				    (Hash)ControllerInputs::INPUT_LOOK_LEFT_ONLY,
				    (Hash)ControllerInputs::INPUT_LOOK_RIGHT_ONLY,
				};
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);

				for (Hash c : controls)
				{
					PAD::ENABLE_CONTROL_ACTION(0, c, true);
				}
			}
		}

		virtual void OnDisable() override
		{
			if (!camEntity)
				return;

			CAM::SET_CAM_ACTIVE(camEntity, false);
			CAM::RENDER_SCRIPT_CAMS(false, true, 500, true, true, 0);
			CAM::DESTROY_CAM(camEntity, false);
			STREAMING::CLEAR_FOCUS();

			Self::GetPed().SetFrozen(false);
			Self::GetPed().SetVisible(true);

			camEntity = 0;
		}
	};

	static Freecam _Freecam{"freecam", "Freecam", "Detaches your camera and allows you to go anywhere!"};
}