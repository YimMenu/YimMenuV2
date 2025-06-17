#pragma once
#include "game/frontend/GUI.hpp"

namespace YimMenu::Menu
{
	extern void Init();
	extern void SetupStyle();
	extern void SetupFonts();

	namespace Font
	{
		inline ImFont* g_DefaultFont = nullptr;
		inline float g_DefaultFontSize = 19.0f;

		inline ImFont* g_OptionsFont = nullptr;
		inline float g_OptionsFontSize = 17.0f;

		inline ImFont* g_ChildTitleFont = nullptr;
		inline float g_ChildTitleFontSize = 14.5f;

		inline ImFont* g_ChatFont = nullptr;
		inline float g_ChatFontSize = 24.0f;

		inline ImFont* g_OverlayFont = nullptr;
		inline float g_OverlayFontSize = 30.0f;

		inline ImFont* g_AwesomeFont = nullptr;
		inline float g_AwesomeFontSize = 30.0f;
	}
}