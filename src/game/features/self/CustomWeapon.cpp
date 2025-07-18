#include "CustomWeapon.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Object.hpp"
#include "types/entity/DecalTypes.hpp"
#include "types/script/Timer.hpp"
#include "game/gta/RayCast.hpp"

namespace YimMenu::Features
{
	void CustomWeapon::OnTick()
	{
		bool isCustomWeaponActionAllowed = !_CustomWeaponEnabledOnWeaponOut.GetState() || WEAPON::IS_PED_ARMED(Self::GetPed().GetHandle(), 4 | 2);

		if (!isCustomWeaponActionAllowed)
			return;

		CustomWeapons selectedWeaponType = static_cast<CustomWeapons>(_CustomWeaponType.GetState());

		for (const auto& control : attackControls)
			PAD::DISABLE_CONTROL_ACTION(0, static_cast<int>(control), true);

		Entity m_Entity{nullptr};
		
		switch (selectedWeaponType)
		{
		case CustomWeapons::CAGE_GUN:
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					FiberPool::Push([=]() mutable {
						if (RayCast(&m_Entity).Cast())
						{
							if (m_Entity.IsPed())
							{
								auto location = m_Entity.GetPosition();
								location.z -= 1.0f;

								Object::Create("prop_gold_cont_01"_J, location);
							}
							else
							{
								Notifications::Show("Custom Weapon", "Entity is not a ped.", NotificationType::Warning);
							}
						}
					});
				}
			}
			break;
		}
		case CustomWeapons::DELETE_GUN:
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					if (RayCast(&m_Entity).Cast())
					{
						if (m_Entity.IsPed() && m_Entity.IsPlayer())
							Notifications::Show("Custom Weapon", "Player entity cannot be deleted.", NotificationType::Warning);
						else
						{
							auto location = m_Entity.GetPosition();
							auto distance = Self::GetPed().GetPosition().GetDistance(location);

							if (distance > 500)
								Notifications::Show("Custom Weapon", "Entity is too far.", NotificationType::Warning);
							else
								m_Entity.Delete();
						}
					}
				}
			}
			break;
		}
		case CustomWeapons::GRAVITY_GUN:
		{
			static std::vector<Entity> entities;
			static Vector3 location;
			static Vector3 entityPos;
			static float distance;
			static constexpr double multiplier = 3.0;
			static const int scroll = 0;

			auto ApplyVelocity = [](Entity entity) {
				if (entity.IsValid())
				{
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_NEXT))
						distance -= 5;
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_PREV))
						distance += 5;

					if (!entity.RequestControl(0))
						return;

					entity.SetCollision(false);

					entityPos = entity.GetPosition();

					Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
					float pitch = Math::DegToRad(rot.x); // vertical
					// float roll = rot.y;
					float yaw = Math::DegToRad(rot.z + 90); // horizontal

					Vector3 velocity;

					velocity.x = location.x + (distance * cos(pitch) * cos(yaw)) - entityPos.x;
					velocity.y = location.y + (distance * sin(yaw) * cos(pitch)) - entityPos.y;
					velocity.z = location.z + (distance * sin(pitch)) - entityPos.z;

					velocity.x *= (float)multiplier;
					velocity.y *= (float)multiplier;
					velocity.z *= (float)multiplier;

					entity.SetVelocity(velocity);
					entity.SetAlpha(105);
				}
			};

			FiberPool::Push([=]() mutable {
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
				{
					location = Self::GetPed().GetPosition();

					if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
					{
						if (RayCast(&m_Entity).Cast())
						{
							auto entityHandle = m_Entity.GetHandle();

							if (m_Entity.IsPed() && m_Entity.IsPlayer())
							{
								Notifications::Show("Custom Weapon", "Gravity gun cannot be applied on player entity.", NotificationType::Warning);
							}
							else
							{
								const auto tempDistance = m_Entity.GetPosition().GetDistance(location);

								if (entities.size() == 0)
								{
									distance = tempDistance;
								}

								if (tempDistance > 500)
								{
									Notifications::Show("Custom Weapon", "Entity is too far.", NotificationType::Warning);
								}
								else
								{
									if (m_Entity.RequestControl(0) && m_Entity.IsPed() && !PED::IS_PED_RAGDOLL(entityHandle))
									{
										TASK::SET_HIGH_FALL_TASK(entityHandle, 0, 0, 0);
									}

									entities.push_back(m_Entity);
								}
							}
						}
					}

					if (entities.size() > 0)
					{
						for (const auto& entity : entities)
						{
							ApplyVelocity(entity);
						}
					}
				}
				else if (entities.size() > 0)
				{
					for (Entity& entity : entities)
					{
						if (entity.RequestControl(0))
						{
							if (_GravityGunLaunchOnRelease.GetState())
							{
								distance += 100;
								ApplyVelocity(entity);
							}

							entity.SetCollision(true);
							entity.ResetAlpha();
						}
					}

					entities.clear();
				}
			});
			break;
		}
		case CustomWeapons::STEAL_VEHICLE_GUN:
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					if (RayCast(&m_Entity).Cast())
					{
						auto entityHandle = m_Entity.GetHandle();

						if (m_Entity.IsVehicle())
						{
							for (size_t i = 0; i < 8 && !m_Entity.As<Vehicle>().IsSeatFree(-1); i++)
							{
								const auto ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(entityHandle, -1, 0);

								if (PED::IS_PED_A_PLAYER(ped))
									return

								TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
							}

							Self::GetPed().SetInVehicle(m_Entity.As<Vehicle>(), -1);
						}
						else
						{
							Notifications::Show("Custom Weapon", "Invalid vehicle.", NotificationType::Warning);
						}
					}
				}
			}
			break;
		}
		case CustomWeapons::REPAIR_GUN:
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					if (RayCast(&m_Entity).Cast())
					{
						if (m_Entity.IsVehicle())
						{
							m_Entity.As<Vehicle>().Fix();
						}
						else
						{
							Notifications::Show("Custom Weapon", "Invalid vehicle.", NotificationType::Warning);
						}
					}
				}
			}
			break;
		}
		case CustomWeapons::VEHICLE_GUN:
		{
			static TIMER vehicleGunTimer;

			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK) && vehicleGunTimer.HasTimePassed(100, true))
				{
					if (!_VehicleGunModel.GetString().length())
					{
						Notifications::Show("Custom Weapon", "No vehicle model name provided.", NotificationType::Error);
						return;
					}

					auto modelHash = Joaat(_VehicleGunModel.GetString());
					if (!STREAMING::IS_MODEL_IN_CDIMAGE(modelHash))
					{
						Notifications::Show("Custom Weapon", "Invalid vehicle model name provided.", NotificationType::Error);
					}
					else
					{
						Vector3 location = CAM::GET_GAMEPLAY_CAM_COORD();

						FiberPool::Push([location, modelHash]() {
							constexpr int rotation_order = 2;
							auto rot = CAM::GET_GAMEPLAY_CAM_ROT(rotation_order);

							float pitch = Math::DegToRad(rot.x); // vertical
							//float roll = rot.y;
							float yaw = Math::DegToRad(rot.z); // horizontal

							Vector3 forward{-sin(yaw) * cos(pitch), cos(yaw) * cos(pitch), sin(pitch)};
							Vector3 spawnLoc = location;

							spawnLoc.x += forward.x * 10.f;
							spawnLoc.y += forward.y * 10.f;
							spawnLoc.z += forward.z * 10.f;

							auto veh = Vehicle::Create(modelHash, spawnLoc, Self::GetPed().GetHeading(), false);

							Vector3 velocity{forward.x * 150.f, forward.y * 150.f, forward.z * 150.f};

							veh.SetRotation(rot, rotation_order);
							veh.SetVelocity(velocity);

							auto vehHandle = veh.GetHandle();
							ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&vehHandle);
						});
					}

					vehicleGunTimer.Reset(true);
				}
			}
			break;
		}
		case CustomWeapons::TELEPORT_GUN:
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					Vector3 coords;

					if (RayCast(&m_Entity, &coords).Cast())
					{
						if (m_Entity.IsVehicle())
						{
							Self::GetPed().SetInVehicle(m_Entity.As<Vehicle>(), -2);
						}
						else
						{
							if (Self::GetVehicle())
								TASK::CLEAR_PED_TASKS_IMMEDIATELY(Self::GetPed().GetHandle());

							Self::GetPed().TeleportTo(coords);
						}
					}
				}
			}
			break;
		}
		case CustomWeapons::PAINT_GUN:
		{
			static Color paintGunColor;
			Color color;

			if (_PaintGunRainbowColorEnabled.GetState())
			{
				RainbowColor(paintGunColor, _PaintGunRainbowColorSpeed.GetState(), static_cast<RainbowColorStyle>(_PaintGunRainbowColorStyle.GetState()));
				color = Color(paintGunColor.r / 255.f, paintGunColor.g / 255.f, paintGunColor.b / 255.f, paintGunColor.a / 255.f);
			}
			else
			{
				color = Color(_PaintGunColor.GetState());
			}

			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					Vector3 coords;

					if (RayCast(&coords).Cast())
					{
						GRAPHICS::ADD_DECAL((int)DecalTypes::splatters_paint,
							coords.x,
							coords.y,
							coords.z,
							0,  //true
							0,  //true
							-1, //true
							0,
							1.f,
							0.f,  // always 0
							0.5f, //size x
							0.4f, //size y
							color.r,
							color.g,
							color.b,
							color.a,
							-1,
							true,
							false,
							false);
					}
				}
			}
			break;
		}
		default: break;
		}
	}
}