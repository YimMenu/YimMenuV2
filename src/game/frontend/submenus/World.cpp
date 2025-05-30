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

		auto timeGroup = std::make_shared<Group>("Time Control");

		timeGroup->AddItem(std::make_shared<IntCommandItem>("networktimehour"_J, "Hour"));
		timeGroup->AddItem(std::make_shared<IntCommandItem>("networktimeminute"_J, "Minute"));
		timeGroup->AddItem(std::make_shared<IntCommandItem>("networktimesecond"_J, "Second"));

		timeGroup->AddItem(std::make_shared<CommandItem>("setnetworktime"_J, "Set"));
		timeGroup->AddItem(std::make_shared<BoolCommandItem>("freezenetworktime"_J, "Freeze"));

		auto otherOpts = std::make_shared<Group>("Other", 1);
		otherOpts->AddItem(std::make_shared<BoolCommandItem>("pedsignore"_J));
		otherOpts->AddItem(std::make_shared<BoolCommandItem>("PedRiotMode"_J));
		otherOpts->AddItem(std::make_shared<BoolCommandItem>("CopsDispatch"_J));

		main->AddItem(std::move(killPeds));
		main->AddItem(std::move(deleteOpts));
		main->AddItem(std::move(bringOpts));
		main->AddItem(std::move(weatherOpts));
		main->AddItem(std::move(otherOpts));
		main->AddItem(timeGroup);

		auto spawnVehicle = std::make_shared<Group>("Vehicle");
		spawnVehicle->AddItem(std::make_shared<StringCommandItem>("vehmodelname"_J));
		spawnVehicle->AddItem(std::make_shared<CommandItem>("spawnvehicle"_J));

		auto spawnPed = std::make_shared<Group>("Ped");
		spawnPed->AddItem(std::make_shared<StringCommandItem>("pedmodelname"_J));
		spawnPed->AddItem(std::make_shared<CommandItem>("spawnped"_J));

		auto spawnObject = std::make_shared<Group>("Object");
		spawnObject->AddItem(std::make_shared<StringCommandItem>("objectmodelname"_J));
		spawnObject->AddItem(std::make_shared<CommandItem>("spawnobject"_J));

		spawnersGroup->AddItem(spawnVehicle);
		spawnersGroup->AddItem(spawnPed);
		spawnersGroup->AddItem(spawnObject);

		iplsGroup->AddItem(std::make_shared<ListCommandItem>("iplselector"_J));
		iplsGroup->AddItem(std::make_shared<CommandItem>("loadipl"_J));
		iplsGroup->AddItem(std::make_shared<CommandItem>("unloadipl"_J));
		iplsGroup->AddItem(std::make_shared<CommandItem>("ipltp"_J));

		AddCategory(std::move(main));
		AddCategory(std::move(spawnersGroup));
		AddCategory(std::move(iplsGroup));
	}
};