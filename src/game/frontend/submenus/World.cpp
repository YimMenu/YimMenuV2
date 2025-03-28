#include "World.hpp"
#include <game/frontend/items/Items.hpp>

namespace YimMenu::Submenus
{
	World::World() :
	    Submenu::Submenu("World")
	{
		auto spawnersGroup = std::make_shared<Category>("Spawners");
		auto iplsGroup     = std::make_shared<Category>("IPLs");

		auto spawnGroup = std::make_shared<Group>("Vehicle");
		auto modsGroup  = std::make_shared<Group>("Modifications");

		spawnGroup->AddItem(std::make_shared<StringCommandItem>("vehmodelname"_J));
		spawnGroup->AddItem(std::make_shared<BoolCommandItem>("spawninvehicle"_J));
		spawnGroup->AddItem(std::make_shared<BoolCommandItem>("spawnupgraded"_J));
		spawnGroup->AddItem(std::make_shared<BoolCommandItem>("usecustomlicenseplate"_J));
		spawnGroup->AddItem(std::make_shared<ConditionalItem>("usecustomlicenseplate"_J, std::make_shared<StringCommandItem>("customlicenseplate"_J)));
		spawnGroup->AddItem(std::make_shared<CommandItem>("spawnvehicle"_J));

		modsGroup->AddItem(std::make_shared<BoolCommandItem>("lsccustomsbypass"_J));

		spawnersGroup->AddItem(spawnGroup);
		spawnersGroup->AddItem(modsGroup);

		iplsGroup->AddItem(std::make_shared<ListCommandItem>("iplselector"_J));
		iplsGroup->AddItem(std::make_shared<CommandItem>("loadipl"_J));
		iplsGroup->AddItem(std::make_shared<CommandItem>("unloadipl"_J));
		iplsGroup->AddItem(std::make_shared<CommandItem>("ipltp"_J));

		AddCategory(std::move(spawnersGroup));
		AddCategory(std::move(iplsGroup));
	}
};