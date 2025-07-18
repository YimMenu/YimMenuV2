#pragma once

namespace YimMenu
{
	struct Color
	{
		float r;
		float g;
		float b;
		float a;

		Color(float red = 0.f, float green = 0.f, float blue = 0.f, float alpha = 255.f) :
			r(red),
			g(green),
			b(blue),
			a(alpha)
		{
		}

		Color(ImVec4 color) :
			r(color.x),
			g(color.y),
			b(color.z),
			a(color.w)
		{
		}
	};
	
	enum class RainbowColorStyle
	{
		Fade,
		Spasm
	};

	inline void RainbowColor(Color& color, int speed = 1, RainbowColorStyle type = RainbowColorStyle::Fade)
	{
		static bool firstInit = true;
		static std::chrono::system_clock::time_point lastRunTime;

		if (type == RainbowColorStyle::Spasm)
		{
			auto delay = std::chrono::milliseconds(std::max(10, 1010 - (speed * 100)));

			if (lastRunTime + delay < std::chrono::system_clock::now())
			{
				color.r = rand() % 256;
				color.g = rand() % 256;
				color.b = rand() % 256;

				lastRunTime = std::chrono::system_clock::now();
				firstInit = true;
			}
		}

		if (type == RainbowColorStyle::Fade)
		{
			if (firstInit)
			{
				color.r   = 255;
				color.g   = 0;
				color.b   = 0;
				firstInit = false;
			}

			if (color.r > 0 && color.b == 0)
			{
				color.g += speed;
				color.r -= speed;
			}
			if (color.g > 0 && color.r == 0)
			{
				color.b += speed;
				color.g -= speed;
			}
			if (color.b > 0 && color.g == 0)
			{
				color.r += speed;
				color.b -= speed;
			}
			color.r = std::clamp(color.r, 0.f, 255.f);
			color.g = std::clamp(color.g, 0.f, 255.f);
			color.b = std::clamp(color.b, 0.f, 255.f);
		}
	}
}