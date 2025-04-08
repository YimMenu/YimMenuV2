#include "Recovery.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/features/recovery/GiveVehicleReward.hpp"
#include "Recovery/StatEditor.hpp"
#include "Recovery/Transactions.hpp"

namespace YimMenu::Submenus
{
	Recovery::Recovery() :
	    Submenu::Submenu("Recovery")
	{
		auto shopping = std::make_shared<Category>("Shopping");
		auto heist = std::make_shared<Category>("Heists");
		auto vehiclesGroup = std::make_shared<Group>("Vehicles");
		auto heistGroup = std::make_shared<Group>("Heist");

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
		heistGroup->AddItem(std::make_shared<CommandItem>("skipcayosetup"_J));
		heistGroup->AddItem(std::make_shared<CommandItem>("skipcayocooldown"_J));

		shopping->AddItem(vehiclesGroup);
		heist->AddItem(heistGroup);
		AddCategory(std::move(shopping));
		AddCategory(std::move(heist));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
	}
}