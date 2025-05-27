#include "core/commands/Command.hpp"
#include "core/frontend/Notifications.hpp"
#include "types/script/globals/MPSV.hpp"

namespace YimMenu::Features
{
	class FixAllVehicles : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (auto mpsv = MPSV::Get())
			{
				int count = 0;
				for (int i = 0; i < *(int*)mpsv; i++)
				{
					if (mpsv->Entries[i].PersonalVehicleFlags.IsSet(1) && mpsv->Entries[i].PersonalVehicleFlags.IsSet(2))
					{
						mpsv->Entries[i].PersonalVehicleFlags.Clear(1);
						mpsv->Entries[i].PersonalVehicleFlags.Clear(6);
						mpsv->Entries[i].PersonalVehicleFlags.Clear(16);
						mpsv->Entries[i].PersonalVehicleFlags.Set(0);
						mpsv->Entries[i].PersonalVehicleFlags.Set(11);
						count++;
					}
				}

				if (count > 0)
					Notifications::Show("Fix All Vehicles", std::format("{} vehicles fixed.", count), NotificationType::Success);
				else
					Notifications::Show("Fix All Vehicles", "No vehicles to fix.");
			}
		}
	};

	static FixAllVehicles _FixAllVehicles{"fixallvehicles", "Fix All Vehicles", "Fixes all of your destroyed personal vehicles."};
}