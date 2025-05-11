#include "core/commands/Command.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class TpToObjective : public Command
	{
		using Command::Command;

		bool GetBlipLocationOfType(Vector3& location, int sprite)
		{
			Blip blip = HUD::GET_CLOSEST_BLIP_INFO_ID(sprite);
			if (blip)
			{
				location = HUD::GET_BLIP_COORDS(blip);
				return true;
			}
			return false;
		}

		virtual void OnCall() override
		{
			static const auto sprites = { 1, 0, 2, 38, 143, 144, 145, 146, 535, 536, 537, 538, 539, 540, 541, 542, 556, 568, 615, 760, 780, 817, 842 };
			Vector3 location;
			for (const auto sprite : sprites)
			{
				if (GetBlipLocationOfType(location, sprite))
				{
					Self::GetPed().TeleportTo(location);
					Notifications::Show("Teleporting to Objective", "Teleported to the objective.", NotificationType::Success, 5000);
					return;
				}
			}
			Notifications::Show("Teleporting to Objective", "No objective found.", NotificationType::Error, 5000);
		}
	};

	static TpToObjective _TpToObjective{"tptoobjective", "Teleport to Objective", "Teleports you to the Objective"};
}
