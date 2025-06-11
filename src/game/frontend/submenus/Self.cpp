#include "Self.hpp"

#include "core/util/Joaat.hpp"
#include "game/frontend/items/Items.hpp"
#include "Self/OutfitEditor.hpp"
#include "Self/Weapons.hpp"

namespace YimMenu::Submenus
{
	Self::Self() :
	    Submenu::Submenu("Self")
	{
		auto main = std::make_shared<Category>("Main");
		auto globalsGroup = std::make_shared<Group>("Globals");
		auto movementGroup = std::make_shared<Group>("Movement");
		auto toolsGroup = std::make_shared<Group>("Tools", 2);
		auto wantedGroup = std::make_shared<Group>("Wanted");

		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("godmode"_J));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("invis"_J));
		movementGroup->AddItem(std::make_shared<ConditionalItem>("invis"_J, std::make_shared<BoolCommandItem>("localvis"_J)));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("otr"_J));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("noragdoll"_J));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("noidlekick"_J));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("unlimitedoxygen"_J));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("formatmoney"_J));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("mobileradio"_J));
		globalsGroup->AddItem(std::make_shared<BoolCommandItem>("keepplayerclean"_J));

		toolsGroup->AddItem(std::make_shared<CommandItem>("skipcutscene"_J));
		toolsGroup->AddItem(std::make_shared<CommandItem>("skipconversation"_J));
		toolsGroup->AddItem(std::make_shared<CommandItem>("suicide"_J));
		toolsGroup->AddItem(std::make_shared<CommandItem>("heal"_J));
		toolsGroup->AddItem(std::make_shared<CommandItem>("cleardamage"_J));
		toolsGroup->AddItem(std::make_shared<CommandItem>("fillinventory"_J));
		toolsGroup->AddItem(std::make_shared<CommandItem>("openwardrobe"_J));

		auto clearWanted = std::make_shared<Group>("", 1);
		clearWanted->AddItem(std::make_shared<ConditionalItem>("neverwanted"_J, std::make_shared<CommandItem>("clearwanted"_J), true));
		clearWanted->AddItem(std::make_shared<BoolCommandItem>("neverwanted"_J));
		auto setWanted = std::make_shared<Group>("", 1);
		setWanted->AddItem(std::make_shared<IntCommandItem>("wantedslider"_J, "Level"));
		setWanted->AddItem(std::make_shared<ConditionalItem>("freezewanted"_J, std::make_shared<CommandItem>("setwanted"_J), true));
		setWanted->AddItem(std::make_shared<BoolCommandItem>("freezewanted"_J));
		wantedGroup->AddItem(std::make_shared<ConditionalItem>("freezewanted"_J, clearWanted, true));
		wantedGroup->AddItem(std::make_shared<ConditionalItem>("neverwanted"_J, setWanted, true));

		movementGroup->AddItem(std::make_shared<BoolCommandItem>("standonvehicles"_J));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("disableactionmode"_J));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("superrun"_J));
		movementGroup->AddItem(std::make_shared<ConditionalItem>("superrun"_J, std::make_shared<FloatCommandItem>("moverateoverride"_J, std::nullopt, false)));
		movementGroup->AddItem(std::make_shared<ConditionalItem>("superrun"_J, std::make_shared<FloatCommandItem>("runsprintswimmultiplier"_J, std::nullopt, false)));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("superjump"_J));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("noclip"_J));
		movementGroup->AddItem(std::make_shared<ConditionalItem>("noclip"_J, std::make_shared<FloatCommandItem>("noclipspeed"_J)));
		movementGroup->AddItem(std::make_shared<BoolCommandItem>("freecam"_J));
		movementGroup->AddItem(std::make_shared<ConditionalItem>("freecam"_J, std::make_shared<FloatCommandItem>("freecamspeed"_J)));

		main->AddItem(globalsGroup);
		main->AddItem(toolsGroup);
		main->AddItem(wantedGroup);
		main->AddItem(movementGroup);
		AddCategory(std::move(main));

		AddCategory(BuildWeaponsMenu());

		auto outfitEditorCategory = YimMenu::CreateOutfitsMenu();
		AddCategory(std::move(outfitEditorCategory));
	}
}