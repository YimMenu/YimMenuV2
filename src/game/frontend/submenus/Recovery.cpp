#include "Recovery.hpp"
#include "game/frontend/items/Items.hpp"
#include "Recovery/StatEditor.hpp"
#include "Recovery/Transactions.hpp"
#include "Recovery/HeistModifier.hpp"

namespace YimMenu::Submenus
{
	Recovery::Recovery() :
	    Submenu::Submenu("Recovery")
	{
		auto missions   = std::make_shared<Category>("Missions");
		auto businesses = std::make_shared<Category>("Businesses");

		auto missionsGeneralGroup   = std::make_shared<Group>("General");
		auto businessesGeneralGroup = std::make_shared<Group>("General");

		missionsGeneralGroup->AddItem(std::make_shared<BoolCommandItem>("playallmissionssolo"_J));
		missionsGeneralGroup->AddItem(std::make_shared<CommandItem>("forcelaunchheist"_J));

		businessesGeneralGroup->AddItem(std::make_shared<ListCommandItem>("businesssafe"_J));
		businessesGeneralGroup->AddItem(std::make_shared<CommandItem>("claimsafeearnings"_J));

		missions->AddItem(missionsGeneralGroup);
		businesses->AddItem(businessesGeneralGroup);
		AddCategory(std::move(missions));
		AddCategory(std::move(businesses));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
		AddCategory(BuildHeistModifierMenu());
	}
}