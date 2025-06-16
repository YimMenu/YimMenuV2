#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Natives.hpp"
#include "game/backend/Self.hpp"
#include "types/ped/PedConfigFlag.hpp"

namespace YimMenu::Features
{
	class Seatbelt : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		static constexpr int VEHICLE_KNOCK_OFF_NEVER = 1;
		static constexpr int VEHICLE_KNOCK_OFF_DEFAULT = 0;

		virtual void OnTick() override
		{
			if (auto ped = Self::GetPed())
			{
				ped.SetConfigFlag(PedConfigFlag::WillFlyThroughWindscreen, false);
				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(Self::GetPed().GetHandle(), VEHICLE_KNOCK_OFF_NEVER);
			}
		}

		virtual void OnDisable() override
		{
			if (auto ped = Self::GetPed())
			{
				ped.SetConfigFlag(PedConfigFlag::WillFlyThroughWindscreen, true);
				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(Self::GetPed().GetHandle(), VEHICLE_KNOCK_OFF_DEFAULT);
			}
		}
	};

	static Seatbelt _Seatbelt{"seatbelt", "Seatbelt", "Prevents you from falling out of vehicles."};
};