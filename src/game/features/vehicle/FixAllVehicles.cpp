#include "core/commands/Command.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/PersonalVehicles.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu::Features
{
	class FixAllVehicles : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			int count = 0;
			for (const auto& it : PersonalVehicles::GetPersonalVehicles())
			{
				const auto& personalVeh = it.second;
				if (personalVeh->Repair())
					count++;
			}

			if (count > 0)
				Notifications::Show("Fix All Vehicles", std::format("{} vehicles fixed.", count), NotificationType::Success);
			else
				Notifications::Show("Fix All Vehicles", "No vehicles to fix.");
		}
	};

	static FixAllVehicles _FixAllVehicles{"fixallvehicles", "Fix All Vehicles", "Fixes all of your destroyed personal vehicles."};
}