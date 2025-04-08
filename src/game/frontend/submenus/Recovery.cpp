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
		auto money_ranks = std::make_shared<Category>("Money & Ranks");
		auto vehiclesGroup = std::make_shared<Group>("Vehicles");
		auto cayoGroup = std::make_shared<Group>("Cayo Perico");

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
		cayoGroup->AddItem(std::make_shared<CommandItem>("skipcayosetup"_J));
		cayoGroup->AddItem(std::make_shared<CommandItem>("skipcayocooldown"_J));


		money_ranks->AddItem(std::make_shared<StringCommandItem>("rankwanted"_J, "Rank Wanted"));
		money_ranks->AddItem(std::make_shared<CommandItem>("setrprank"_J, "Set Rank"));

		shopping->AddItem(vehiclesGroup);
		heist->AddItem(cayoGroup);
		AddCategory(std::move(shopping));
		AddCategory(std::move(money_ranks));
		AddCategory(std::move(heist));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
	}
}