#include "Self.hpp"

#include "core/util/Joaat.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu::Features
{
	// BoolCommand _RecoveryEnabled("recoveryenabled", "Recovery Enabled", "Is the recovery feature enabled");
}

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
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("otr"_J));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("noragdoll"_J));

		auto clearWanted = std::make_shared<Group>("", 1);
		clearWanted->AddItem(std::make_shared<ConditionalItem>("neverwanted"_J, std::make_shared<CommandItem>("clearwanted"_J), true));
		clearWanted->AddItem(std::make_shared<BoolCommandItem>("neverwanted"_J));
		auto setWanted = std::make_shared<Group>("", 1);
		setWanted->AddItem(std::make_shared<IntCommandItem>("wantedslider"_J, "Level"));
		setWanted->AddItem(std::make_shared<ConditionalItem>("freezewanted"_J, std::make_shared<CommandItem>("setwanted"_J), true));
		setWanted->AddItem(std::make_shared<BoolCommandItem>("freezewanted"_J));
		wantedGroup->AddItem(std::make_shared<ConditionalItem>("freezewanted"_J, clearWanted, true));
		wantedGroup->AddItem(std::make_shared<ConditionalItem>("neverwanted"_J, setWanted, true));

		toolsGroup->AddItem(std::make_shared<CommandItem>("suicide"_J));

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

	

		
	}
}
