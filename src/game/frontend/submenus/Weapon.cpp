#include "Weapon.hpp"

#include <game/frontend/items/Items.hpp>


namespace YimMenu::Submenus
{
	Weapon::Weapon() :
	    Submenu("Weapons")
	{
		auto weapons             = std::make_shared<Category>("Weapons");
		auto weaponsGlobalsGroup = std::make_shared<Group>("Globals");

		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("infiniteammo"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("infiniteclip"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("rapidfire"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<CommandItem>("giveallweapons"_J));

		weapons->AddItem(weaponsGlobalsGroup);
		AddCategory(std::move(weapons));
	}
};