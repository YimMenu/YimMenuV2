#include "Vehicle.hpp"
#include <game/frontend/items/Items.hpp>


namespace YimMenu::Submenus
{
	Vehicle::Vehicle() :
		Submenu("Vehicle")
	{
		auto mainGroup  = std::make_shared<Category>("Spawners");
		auto spawnGroup = std::make_shared<Group>("Vehicle");

		spawnGroup->AddItem(std::make_shared<StringCommandItem>("vehmodelname"_J));
		spawnGroup->AddItem(std::make_shared<BoolCommandItem>("spawninvehicle"_J));
		spawnGroup->AddItem(std::make_shared<BoolCommandItem>("spawnupgraded"_J));
		spawnGroup->AddItem(std::make_shared<BoolCommandItem>("usecustomlicenseplate"_J));
		spawnGroup->AddItem(std::make_shared<ConditionalItem>("usecustomlicenseplate"_J, std::make_shared<StringCommandItem>("customlicenseplate"_J)));
		spawnGroup->AddItem(std::make_shared<CommandItem>("spawnvehicle"_J));

		spawnGroup->AddItem(std::make_shared<BoolCommandItem>("lsccustomsbypass"_J));

		mainGroup->AddItem(spawnGroup);

		AddCategory(std::move(mainGroup));
		auto vehicleaddons             = std::make_shared<Category>("Vehicleaddons");
		auto vehicleGlobalsGroup = std::make_shared<Group>("Globals");
		auto vehicleMiscGroup    = std::make_shared<Group>("Misc");

		vehicleGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("vehiclegodmode"_J, "Godmode"));
		vehicleGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("keepfixed"_J, "Keep Fixed"));
		vehicleGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("hornboost"_J));
		vehicleGlobalsGroup->AddItem(std::make_shared<CommandItem>("repairvehicle"_J));


		vehicleMiscGroup->AddItem(std::make_shared<BoolCommandItem>("speedometer"_J));

		vehicleaddons->AddItem(vehicleGlobalsGroup);
		vehicleaddons->AddItem(vehicleMiscGroup);
		AddCategory(std::move(vehicleaddons));
	}
};
