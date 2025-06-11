#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "types/pad/ControllerInputs.hpp"

namespace YimMenu::Features
{
	class HornBoost : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		static constexpr float horn_boost_speed_default = 10.f;
		static constexpr float horn_boost_speed_max = 200.f;
		static constexpr float horn_boost_speed_increment = 0.3f;

		float m_HornBoostSpeed = horn_boost_speed_default;

		virtual void OnTick() override
		{
			auto veh = Self::GetVehicle();

			if (!veh)
			{
				m_HornBoostSpeed = horn_boost_speed_default;
				return;
			}

			if (PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HORN))
				m_HornBoostSpeed = veh.GetSpeed();

			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HORN))
			{
				if (m_HornBoostSpeed < horn_boost_speed_max)
					m_HornBoostSpeed += horn_boost_speed_increment;

				const auto velocity = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh.GetHandle(), 0.f, m_HornBoostSpeed, 0.f) - veh.GetPosition();
				veh.SetVelocity(Vector3(velocity));
			}
			else if (PAD::IS_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_VEH_HORN))
				m_HornBoostSpeed = horn_boost_speed_default;
		}
	};

	static HornBoost _HornBoost{"hornboost", "Horn Boost", "Makes the vehicle boost when you hold the horn"};
}