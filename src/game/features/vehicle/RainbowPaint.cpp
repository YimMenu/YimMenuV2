#include "core/commands/BoolCommand.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/gta/Natives.hpp"
#include "game/backend/Self.hpp"
#include <chrono>

namespace YimMenu::Features
{
	static float red = 255.f, green = 0.f, blue = 0.f;   // start from full red

	enum class RainbowPaintType
	{
		Spasm = 0,
		Fade,
	};

	static std::vector<std::pair<int, const char*>> g_RainbowPaintTypeList = {
	    {0, "Spasm"},
	    {1, "Fade"},
	};

	struct RainbowPaintSettings
	{
		bool primary = true;                           // affect primary color
		bool secondary = false;			       // do not affect secondary paint
		int speed = 1;
		RainbowPaintType type = RainbowPaintType::Fade; // Default option is fade
	};

	static RainbowPaintSettings g_RainbowPaintSettings;

	static BoolCommand _RainbowPaintPrimary{
	    "rainbowpri",
	    "Vehicle RGB Paint Primary",
	    "Enable RGB rainbow paint on vehicle primary color",
	    g_RainbowPaintSettings.primary};

	static BoolCommand _RainbowPaintSecondary{
	    "rainbowsec",
	    "Vehicle RGB Paint Secondary",
	    "Enable RGB rainbow paint on vehicle secondary color",
	    g_RainbowPaintSettings.secondary};

	static IntCommand _RainbowPaintSpeed{
	    "rainbowspeed",
	    "Vehicle RGB Paint Speed",
	    "Speed of the rainbow paint cycling (1-10)",
	    g_RainbowPaintSettings.speed,
	    1,
	    10};

	static ListCommand _RainbowPaintType{
	    "rainbowtype",
	    "Vehicle Rainbow Paint Type",
	    "Type of rainbow paint effect",
	    g_RainbowPaintTypeList,
	    1}; // Uses fade by default

	class VehicleRainbowPaint : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		void OnTick() override
		{
			UpdateRainbowPaint();  // activates function found below
		}

		void UpdateRainbowPaint()
		{
			auto veh = Self::GetVehicle().GetHandle();
			if (!ENTITY::DOES_ENTITY_EXIST(veh))  //if player isn't sitting in a vehicle
				return; // do nothing

			RainbowPaintType type = static_cast<RainbowPaintType>(_RainbowPaintType.GetState());

			static std::chrono::system_clock::time_point last_rgb_run_time;
			static std::chrono::milliseconds delay = std::chrono::milliseconds(0);
			static bool ran = false;

			auto now = std::chrono::system_clock::now();

			if (type == RainbowPaintType::Spasm && last_rgb_run_time + delay < now)
			{
				red = static_cast<float>(rand() % 256);
				green = static_cast<float>(rand() % 256);
				blue = static_cast<float>(rand() % 256);

				delay = std::chrono::milliseconds(110 - (_RainbowPaintSpeed.GetState() * 10));     // the paint spazzes out
				last_rgb_run_time = now;
				ran = true;
			}
			else if (type == RainbowPaintType::Fade)                   // a great fade
			{
				if (ran)
				{
					red = 255.f;
					green = 0.f;
					blue = 0.f;
					ran = false;
				}

				int speed = _RainbowPaintSpeed.GetState();

				if (red > 0.f && blue == 0.f)
				{
					green += speed;
					red -= speed;
				}
				else if (green > 0.f && red == 0.f)
				{
					blue += speed;
					green -= speed;
				}
				else if (blue > 0.f && green == 0.f)
				{
					red += speed;
					blue -= speed;
				}

				red = std::clamp(red, 0.f, 255.f);
				green = std::clamp(green, 0.f, 255.f);
				blue = std::clamp(blue, 0.f, 255.f);
			}

			if (_RainbowPaintPrimary.GetState())
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, static_cast<int>(red), static_cast<int>(green), static_cast<int>(blue));         // checks state of settings toggled
			if (_RainbowPaintSecondary.GetState())
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, static_cast<int>(red), static_cast<int>(green), static_cast<int>(blue));
		}
	};

	static VehicleRainbowPaint _VehicleRainbowPaint{"rainbowpaint", "Vehicle Rainbow Paint", "Cycles vehicle colors through a rainbow effect."};
}
