#include "World.hpp"
#include <game/frontend/items/Items.hpp>

namespace YimMenu::Submenus
{
	World::World() :
	    Submenu::Submenu("World")
	{
		auto mainGroup = std::make_shared<Category>("Spawners");
		auto spawnGroup = std::make_shared<Group>("Vehicle");
		auto modsGroup  = std::make_shared<Group>("Modifications");

		spawnGroup->AddItem(std::make_shared<StringCommandItem>("vehmodelname"_J));
		spawnGroup->AddItem(std::make_shared<BoolCommandItem>("spawninvehicle"_J));
		spawnGroup->AddItem(std::make_shared<BoolCommandItem>("spawnupgraded"_J));
		spawnGroup->AddItem(std::make_shared<BoolCommandItem>("usecustomlicenseplate"_J));
		spawnGroup->AddItem(std::make_shared<ConditionalItem>("usecustomlicenseplate"_J, std::make_shared<StringCommandItem>("customlicenseplate"_J)));
		spawnGroup->AddItem(std::make_shared<CommandItem>("spawnvehicle"_J));

		modsGroup->AddItem(std::make_shared<BoolCommandItem>("lsccustomsbypass"_J));

		mainGroup->AddItem(spawnGroup);
		mainGroup->AddItem(modsGroup); 

		AddCategory(std::move(mainGroup));
	}
};