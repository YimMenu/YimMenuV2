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
		auto missions   = std::make_shared<Category>("Missions");
		auto businesses = std::make_shared<Category>("Businesses");
		auto casino     = std::make_shared<Category>("Casino");

		auto generalGroup  = std::make_shared<Group>("General");
		auto businessGroup = std::make_shared<Group>("General");
		auto casinoGroup   = std::make_shared<Group>("Slot Machines");

		generalGroup->AddItem(std::make_shared<BoolCommandItem>("playallmissionssolo"_J));
		generalGroup->AddItem(std::make_shared<CommandItem>("forcelaunchheist"_J));
		generalGroup->AddItem(std::make_shared<BoolCommandItem>("unlockgtaplus"_J));

		generalGroup->AddItem(std::make_shared<BoolCommandItem>("override_rp_multiplier"_J));
        generalGroup->AddItem(std::make_shared<ConditionalItem>("override_rp_multiplier"_J, std::make_shared<FloatCommandItem>("rp_multiplier_input"_J)));

        generalGroup->AddItem(std::make_shared<BoolCommandItem>("override_cash_multiplier"_J));
        generalGroup->AddItem(std::make_shared<ConditionalItem>("override_cash_multiplier"_J, std::make_shared<FloatCommandItem>("cash_multiplier_input"_J)));

        generalGroup->AddItem(std::make_shared<BoolCommandItem>("override_cm_rp_multiplier"_J));
        generalGroup->AddItem(std::make_shared<ConditionalItem>("override_cm_rp_multiplier"_J, std::make_shared<FloatCommandItem>("cm_rp_multiplier_input"_J)));

        generalGroup->AddItem(std::make_shared<BoolCommandItem>("override_cm_cash_multiplier"_J));
        generalGroup->AddItem(std::make_shared<ConditionalItem>("override_cm_cash_multiplier"_J, std::make_shared<FloatCommandItem>("cm_cash_multiplier_input"_J)));

		businessGroup->AddItem(std::make_shared<ListCommandItem>("businesssafe"_J));
		businessGroup->AddItem(std::make_shared<CommandItem>("claimsafeearnings"_J));

		casinoGroup->AddItem(std::make_shared<BoolCommandItem>("casinomanipulaterigslotmachines"_J));

		missions->AddItem(generalGroup);
		businesses->AddItem(businessGroup);
		casino->AddItem(casinoGroup);

		AddCategory(std::move(missions));
		AddCategory(std::move(businesses));
		AddCategory(std::move(casino));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
		AddCategory(BuildHeistModifierMenu());
	}
}
