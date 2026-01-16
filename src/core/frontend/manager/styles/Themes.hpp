#pragma once

#include "core/frontend/manager/Category.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu
{
	// Forward declarations of each theme's render function, append when adding new themes
	extern void RenderClassicTheme();
	extern void RenderModernTheme();
	extern void RenderModernVTheme();
	extern void RenderModularTheme();
	extern void SetupStyle();
	extern void DefaultStyle();
}
