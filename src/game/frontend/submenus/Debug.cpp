#include "Debug.hpp"

#include "Debug/Misc.hpp"
#include "Debug/Globals.hpp"
#include "Debug/Locals.hpp"
#include "Debug/Scripts.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu::Submenus
{
	Debug::Debug() :
		#define ICON_FA_ARROW_RIGHT "\xef\x84\xa0"
	    Submenu::Submenu("Debug", ICON_FA_ARROW_RIGHT)
	{
		AddCategory(BuildMiscMenu());
		AddCategory(BuildGlobalsMenu());
		AddCategory(BuildLocalsMenu());
		AddCategory(BuildScriptsMenu());
	}
}