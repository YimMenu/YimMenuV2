#include "core/commands/Command.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	bool GetBlipLocationOfType(Vector3& location, int sprite)
	{
		Blip blip = HUD::GET_CLOSEST_BLIP_INFO_ID(sprite);
		if (blip)
		{
			location = HUD::GET_BLIP_COORDS(blip);
			location.z += 1.0f;
			return true;
		}
		return false;
	}

	class TpToObjective : public Command
	{
		using Command::Command;


		virtual void OnCall() override
		{
			static const auto sprites = {1, 0, 2, 38, 143, 144, 145, 146, 161, 478, 501, 514, 521, 535, 536, 537, 538, 539, 540, 541, 542, 549, 556, 568, 615, 761, 762, 763, 764, 765, 780, 817, 842, 844, 845, 850};
			Vector3 location;
			for (const auto sprite : sprites)
			{
				if (GetBlipLocationOfType(location, sprite))
				{
					Self::GetPed().TeleportTo(location);
					return;
				}
			}
		}
	};

	static TpToObjective _TpToObjective{"tptoobjective", "Teleport to Objective", "Teleports you to the Objective"};
}
