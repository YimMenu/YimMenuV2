#include "Debug.hpp"

#include "Debug/Misc.hpp"
#include "Debug/Globals.hpp"
#include "Debug/Locals.hpp"
#include "Debug/Scripts.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu::Submenus
{
	Debug::Debug() :
	    Submenu::Submenu("Debug")
	{
		AddCategory(BuildMiscMenu());
		AddCategory(BuildGlobalsMenu());
		AddCategory(BuildLocalsMenu());
		AddCategory(BuildScriptsMenu());
	}
}