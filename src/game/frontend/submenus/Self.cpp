#include "Self.hpp"

#include "core/util/Joaat.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu::Submenus
{
	Self::Self() :
	    Submenu::Submenu("Self")
	{
		auto main          = std::make_shared<Category>("Main");
		auto globalsGroup  = std::make_shared<Group>("Globals");
		auto movementGroup = std::make_shared<Group>("Movement");
		auto wantedGroup = std::make_shared<Group>("Wanted");
		auto toolsGroup    = std::make_shared<Group>("Tools");

		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("godmode"_J));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("invis"_J));
		movementGroup->AddItem(std::make_shared<ConditionalItem>("invis"_J, std::make_shared<BoolCommandItem>("localvis"_J)));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("otr"_J));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("noragdoll"_J));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("noidlekick"_J));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("unlimitedoxygen"_J));

		auto clearWanted = std::make_shared<Group>("", 1);
		clearWanted->AddItem(std::make_shared<ConditionalItem>("neverwanted"_J, std::make_shared<CommandItem>("clearwanted"_J), true));
		clearWanted->AddItem(std::make_shared<BoolCommandItem>("neverwanted"_J));
		auto setWanted = std::make_shared<Group>("", 1);
		setWanted->AddItem(std::make_shared<IntCommandItem>("wantedslider"_J, "Level"));
		setWanted->AddItem(std::make_shared<ConditionalItem>("freezewanted"_J, std::make_shared<CommandItem>("setwanted"_J), true));
		setWanted->AddItem(std::make_shared<BoolCommandItem>("freezewanted"_J));
		wantedGroup->AddItem(std::make_shared<ConditionalItem>("freezewanted"_J, clearWanted, true));
		wantedGroup->AddItem(std::make_shared<ConditionalItem>("neverwanted"_J, setWanted, true));

		toolsGroup->AddItem(std::make_shared<CommandItem>("skipcutscene"_J));
		toolsGroup->AddItem(std::make_shared<CommandItem>("suicide"_J));
		toolsGroup->AddItem(std::make_shared<CommandItem>("heal"_J));
		toolsGroup->AddItem(std::make_shared<CommandItem>("cleardamage"_J));
		toolsGroup->AddItem(std::make_shared<CommandItem>("fillinventory"_J));
		
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("standonvehicles"_J));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("disableactionmode"_J));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("superrun"_J));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("superjump"_J));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("noclip"_J));
		movementGroup->AddItem(std::make_shared<ConditionalItem>("noclip"_J, std::make_shared<FloatCommandItem>("noclipspeed"_J)));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("freecam"_J));
		movementGroup->AddItem(std::make_shared<ConditionalItem>("freecam"_J, std::make_shared<FloatCommandItem>("freecamspeed"_J)));

		main->AddItem(globalsGroup);
		main->AddItem(wantedGroup);
		main->AddItem(toolsGroup);
		main->AddItem(movementGroup);
		AddCategory(std::move(main));

		auto weapons             = std::make_shared<Category>("Weapons");
		auto weaponsGlobalsGroup = std::make_shared<Group>("Globals");

		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("infiniteammo"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("infiniteclip"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("rapidfire"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("infiniteparachutes"_J));
		weaponsGlobalsGroup->AddItem(std::make_shared<CommandItem>("giveallweapons"_J));

		weapons->AddItem(weaponsGlobalsGroup);
		AddCategory(std::move(weapons));

		auto vehicle = std::make_shared<Category>("Vehicle");
		auto vehicleGlobalsGroup = std::make_shared<Group>("Globals");
		auto vehicleMiscGroup = std::make_shared<Group>("Misc");

		vehicleGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("vehiclegodmode"_J, "Godmode"));
		vehicleGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("keepfixed"_J, "Keep Fixed"));
		vehicleGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("hornboost"_J));
		vehicleGlobalsGroup->AddItem(std::make_shared<BoolCommandItem>("modifyboostbehavior"_J));
		vehicleGlobalsGroup->AddItem(std::make_shared<ConditionalItem>("modifyboostbehavior"_J, std::make_shared<ListCommandItem>("boostbehavior"_J)));
		vehicleGlobalsGroup->AddItem(std::make_shared<CommandItem>("repairvehicle"_J));
		vehicleGlobalsGroup->AddItem(std::make_shared<CommandItem>("enterlastvehicle"_J));

		vehicleMiscGroup->AddItem(std::make_shared<BoolCommandItem>("speedometer"_J));
		vehicleMiscGroup->AddItem(std::make_shared<BoolCommandItem>("seatbelt"_J));
		vehicleMiscGroup->AddItem(std::make_shared<BoolCommandItem>("allowhatsinvehicles"_J));

		vehicle->AddItem(vehicleGlobalsGroup);
		vehicle->AddItem(vehicleMiscGroup);
		AddCategory(std::move(vehicle));
	}
}
