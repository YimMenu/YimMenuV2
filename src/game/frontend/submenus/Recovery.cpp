#include "Recovery.hpp"
#include "Recovery/HeistModifier.hpp"
#include "Recovery/StatEditor.hpp"
#include "Recovery/Transactions.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu::Submenus
{
	Recovery::Recovery() :
	    Submenu::Submenu("Recovery")
	{
		auto missions = std::make_shared<Category>("Missions");
		auto casino   = std::make_shared<Category>("Casino");

		auto generalGroup = std::make_shared<Group>("General");
		auto casinoGroup  = std::make_shared<Group>("CasinoRigSlotMachines");


		generalGroup->AddItem(std::make_shared<BoolCommandItem>("playallmissionssolo"_J));
		generalGroup->AddItem(std::make_shared<CommandItem>("forcelaunchheist"_J));
		generalGroup->AddItem(std::make_shared<IntCommandItem>("rpmultiplierinput"_J));
		generalGroup->AddItem(std::make_shared<CommandItem>("rpmultiplier"_J));

		casinoGroup->AddItem(std::make_shared<BoolCommandItem>("casinomanipulaterigslotmachines"_J));

		missions->AddItem(generalGroup);
		casino->AddItem(casinoGroup);

		AddCategory(std::move(missions));
		AddCategory(std::move(casino));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
		AddCategory(BuildHeistModifierMenu());
	}
}