#include "World.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu::Submenus
{
	World::World() :
	    Submenu::Submenu("World")
	{
		auto main          = std::make_shared<Category>("Main");
		auto spawnersGroup = std::make_shared<Category>("Spawners");
		auto iplsGroup     = std::make_shared<Category>("IPLs");
	
		auto killPeds = std::make_shared<Group>("Kill", 1);
		killPeds->AddItem(std::make_shared<CommandItem>("killallpeds"_J));
		killPeds->AddItem(std::make_shared<CommandItem>("killallenemies"_J));
		auto deleteOpts = std::make_shared<Group>("Delete", 1);
		deleteOpts->AddItem(std::make_shared<CommandItem>("delpeds"_J));
		deleteOpts->AddItem(std::make_shared<CommandItem>("delvehs"_J));
		deleteOpts->AddItem(std::make_shared<CommandItem>("delobjs"_J));
		auto bringOpts = std::make_shared<Group>("Bring", 1);
		bringOpts->AddItem(std::make_shared<CommandItem>("bringpeds"_J));
		bringOpts->AddItem(std::make_shared<CommandItem>("bringvehs"_J));
		bringOpts->AddItem(std::make_shared<CommandItem>("bringobjs"_J));
		
		auto weatherOpts = std::make_shared<Group>("Weather", 1);
		weatherOpts->AddItem(std::make_shared<ListCommandItem>("weather"_J));
		weatherOpts->AddItem(std::make_shared<ConditionalItem>("forceweather"_J, std::make_shared<CommandItem>("setweather"_J), true));
		weatherOpts->AddItem(std::make_shared<BoolCommandItem>("forceweather"_J));

		auto otherOpts = std::make_shared<Group>("Other", 1);
		otherOpts->AddItem(std::make_shared<BoolCommandItem>("pedsignore"_J));
		otherOpts->AddItem(std::make_shared<BoolCommandItem>("PedRiotMode"_J));
		otherOpts->AddItem(std::make_shared<BoolCommandItem>("CopsDispatch"_J));

		main->AddItem(std::move(killPeds));
		main->AddItem(std::move(deleteOpts));
		main->AddItem(std::move(bringOpts));
		main->AddItem(std::move(weatherOpts));
		main->AddItem(std::move(otherOpts));

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




		AddCategory(std::move(main));
		AddCategory(std::move(spawnersGroup));
		AddCategory(std::move(iplsGroup));
	}
};