#include "Debug.hpp"

#include "Debug/Globals.hpp"
#include "Debug/Locals.hpp"
//#include "Debug/Scripts.hpp"
#include "Debug/Misc.hpp"

#include "game/frontend/items/Items.hpp"



namespace YimMenu::Submenus
{
	Debug::Debug() :
	    Submenu::Submenu("Debug")
	{
		AddCategory(BuildGlobalsMenu());
		AddCategory(BuildLocalsMenu());
		AddCategory(BuildMiscMenu());
	}
}