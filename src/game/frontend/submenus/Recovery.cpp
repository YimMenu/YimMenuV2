#include "Recovery.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/features/recovery/GiveVehicleReward.hpp"
#include "game/features/self/UnlockAllChameleonsColors.cpp"
#include "Recovery/StatEditor.hpp"
#include "Recovery/Transactions.hpp"

namespace YimMenu::Submenus
{
	Recovery::Recovery() :
	    Submenu::Submenu("Recovery")
	{
		auto shopping = std::make_shared<Category>("Shopping");
		auto missions = std::make_shared<Category>("Missions");
		auto unlockalls = std::make_shared<Category>("Recoverys");
		auto vehiclesGroup = std::make_shared<Group>("Vehicles");
		auto generalGroup = std::make_shared<Group>("General");
		auto cayoPericoGroup = std::make_shared<Group>("Cayo Perico");
		auto Recoveryss      = std::make_shared<Group>("Recovery");

		Recoveryss->AddItem(std::make_shared<CommandItem>("UnlockChameleons"_J));
		
		vehiclesGroup->AddItem(std::make_shared<BoolCommandItem>("dlcvehicles"_J));

		vehiclesGroup->AddItem(std::make_unique<ImGuiItem>([] {
			if (ImGui::Button("Save This Vehicle as Personal Vehicle"))
			{
				if (GiveVehicleReward::IsSafeToRunScript())
				{
					GiveVehicleReward::SetShouldRunScript(true);
				}
			}
		}));

		generalGroup->AddItem(std::make_shared<BoolCommandItem>("playallmissionssolo"_J));
		generalGroup->AddItem(std::make_shared<CommandItem>("forcelaunchheist"_J));

		cayoPericoGroup->AddItem(std::make_shared<CommandItem>("skipcayosetup"_J));
		cayoPericoGroup->AddItem(std::make_shared<CommandItem>("skipcayocooldown"_J));

		shopping->AddItem(vehiclesGroup);
		missions->AddItem(generalGroup);
		missions->AddItem(cayoPericoGroup);
		unlockalls->AddItem(Recoveryss);
		AddCategory(std::move(unlockalls));
		AddCategory(std::move(shopping));
		AddCategory(std::move(missions));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
	}
}
