#include "Recovery.hpp"

#include "Recovery/StatEditor.hpp"
#include "Recovery/Transactions.hpp"
#include "game/features/recovery/GiveVehicleReward.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu::Submenus
{
	Recovery::Recovery() :
	    Submenu::Submenu("Recovery")
	{
		auto shopping          = std::make_shared<Category>("Shopping");
		auto vehiclesGroup     = std::make_shared<Group>("Vehicles");
		auto moneyMethodsGroup = std::make_shared<Group>("Money Methods");

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
		moneyMethodsGroup->AddItem(std::make_shared<CommandItem>("cayoperico"_J));
		moneyMethodsGroup->AddItem(std::make_shared<CommandItem>("cayopericoskip"_J));

		shopping->AddItem(vehiclesGroup);
		shopping->AddItem(moneyMethodsGroup);
		AddCategory(std::move(shopping));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
	}
}