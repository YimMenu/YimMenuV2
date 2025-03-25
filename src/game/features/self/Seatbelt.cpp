#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Natives.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class Seatbelt : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;
		
		static constexpr int VEHICLE_KNOCK_OFF_NEVER	= 1;
		static constexpr int VEHICLE_KNOCK_OFF_DEFAULT	= 0;

		virtual void OnTick() override
		{
			auto handle = Self::GetPed().GetHandle();

			PED::SET_PED_CONFIG_FLAG(handle, 32, false);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(handle, VEHICLE_KNOCK_OFF_NEVER);
		}

		virtual void OnDisable() override
		{
			auto handle = Self::GetPed().GetHandle();

			PED::SET_PED_CONFIG_FLAG(handle, 32, true);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(handle, VEHICLE_KNOCK_OFF_DEFAULT);
		}
	};

	static Seatbelt _Seatbelt{"seatbelt", "Seatbelt", "Prevents you from falling out of vehicles."};
};