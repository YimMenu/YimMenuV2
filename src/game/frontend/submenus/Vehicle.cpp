#include "Vehicle.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/frontend/submenus/Vehicle/SpawnVehicle.hpp"
#include "Vehicle/VehicleEditorCategory.hpp"
#include "Vehicle/PersistCarCategory.hpp"

namespace YimMenu::Submenus
{
	Vehicle::Vehicle() :
		Submenu::Submenu("Vehicle")
	{
		auto main = std::make_shared<Category>("Main");

		auto globals = std::make_shared<Group>("Globals");
		auto tools   = std::make_shared<Group>("Tools", 1);
		auto misc    = std::make_shared<Group>("Misc");

		globals->AddItem(std::make_shared<BoolCommandItem>("vehiclegodmode"_J, "Godmode"));
		globals->AddItem(std::make_shared<BoolCommandItem>("keepfixed"_J, "Keep Fixed"));
		globals->AddItem(std::make_shared<BoolCommandItem>("hornboost"_J));
		globals->AddItem(std::make_shared<BoolCommandItem>("modifyboostbehavior"_J));
		globals->AddItem(std::make_shared<ConditionalItem>("modifyboostbehavior"_J, std::make_shared<ListCommandItem>("boostbehavior"_J)));

		tools->AddItem(std::make_shared<CommandItem>("enterlastvehicle"_J));
		tools->AddItem(std::make_shared<CommandItem>("repairvehicle"_J));
		tools->AddItem(std::make_shared<CommandItem>("fixallvehicles"_J));
		tools->AddItem(std::make_shared<CommandItem>("callmechanic"_J));
		tools->AddItem(std::make_shared<CommandItem>("savepersonalvehicle"_J));

		misc->AddItem(std::make_shared<BoolCommandItem>("speedometer"_J));
		misc->AddItem(std::make_shared<BoolCommandItem>("seatbelt"_J));
		misc->AddItem(std::make_shared<BoolCommandItem>("allowhatsinvehicles"_J));
		misc->AddItem(std::make_shared<BoolCommandItem>("lsccustomsbypass"_J));
		misc->AddItem(std::make_shared<BoolCommandItem>("dlcvehicles"_J));

		main->AddItem(globals);
		main->AddItem(tools);
		main->AddItem(misc);

		AddCategory(std::move(main));
		AddCategory(BuildSpawnVehicleMenu());
		AddCategory(VehicleEditorCategory());
		AddCategory(PersistCarCategory());
	}
}