#include "Vehicle.hpp"
#include <game/frontend/items/Items.hpp>

namespace YimMenu::Submenus
{
	Vehicle::Vehicle() :
	    Submenu::Submenu("Vehicle")
	{
		auto mainGroup = std::make_shared<Category>("Main");
		auto spawnGroup = std::make_shared<Group>("Spawn");

		spawnGroup->AddItem(std::make_shared<StringCommandItem>("vehmodelname"_J));
		spawnGroup->AddItem(std::make_shared<BoolCommandItem>("spawninvehicle"_J));
		spawnGroup->AddItem(std::make_shared<BoolCommandItem>("spawnupgraded"_J));
		spawnGroup->AddItem(std::make_shared<CommandItem>("spawnvehicle"_J));

		mainGroup->AddItem(spawnGroup);

		AddCategory(std::move(mainGroup));
	}
};