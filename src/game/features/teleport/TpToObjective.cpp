#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "types/blip/BlipSprite.hpp"

namespace YimMenu::Features
{
	static bool GetBlipLocationOfType(Vector3& location, int sprite)
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
			static constexpr BlipSprite sprites[] = {BlipSprite::RADAR_LEVEL, BlipSprite::RADAR_HIGHER, BlipSprite::RADAR_LOWER, BlipSprite::RADAR_OBJECTIVE_BLUE, BlipSprite::RADAR_OBJECTIVE_GREEN, BlipSprite::RADAR_OBJECTIVE_RED, BlipSprite::RADAR_OBJECTIVE_YELLOW, BlipSprite::RADAR_CONTRABAND, BlipSprite::RADAR_TARGET_A, BlipSprite::RADAR_TARGET_B, BlipSprite::RADAR_TARGET_C, BlipSprite::RADAR_TARGET_D, BlipSprite::RADAR_TARGET_E, BlipSprite::RADAR_TARGET_F, BlipSprite::RADAR_TARGET_G, BlipSprite::RADAR_TARGET_H, BlipSprite::RADAR_PICKUP_MACHINEGUN};
			Vector3 location;
			for (const auto sprite : sprites)
			{
				if (GetBlipLocationOfType(location, static_cast<int>(sprite)))
				{
					Self::GetPed().TeleportTo(location);
					return;
				}
			}
		}
	};

	static TpToObjective _TpToObjective{"tptoobjective", "Teleport to Objective", "Teleports you to the Objective"};
}
