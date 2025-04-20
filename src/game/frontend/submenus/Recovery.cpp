#include "Recovery.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/features/recovery/GiveVehicleReward.hpp"
#include "Recovery/StatEditor.hpp"
#include "Recovery/Transactions.hpp"
#include "Recovery/HeistModifier.hpp"

namespace YimMenu::Submenus
{
	Recovery::Recovery() :
	    Submenu::Submenu("Recovery")
	{
		auto shopping = std::make_shared<Category>("Shopping");
		auto missions = std::make_shared<Category>("Missions");
		auto nightClub = std::make_shared<Category>("Nightclub");
		auto arcade = std::make_shared<Category>("Arcade");
		auto vehiclesGroup = std::make_shared<Group>("Vehicles");
		auto generalGroup = std::make_shared<Group>("General");

		auto nightClubGroup = std::make_shared<Group>("NightclubSafe");
		auto arcadeGroup = std::make_shared<Group>("ArcadeSafe");


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

		nightClubGroup->AddItem(std::make_shared<BoolCommandItem>("nightclubsafe"_J));

		arcadeGroup->AddItem(std::make_shared<BoolCommandItem>("arcadesafe"_J));

		shopping->AddItem(vehiclesGroup);

		nightClub->AddItem(nightClubGroup);
		arcade->AddItem(arcadeGroup);
		missions->AddItem(generalGroup);
		AddCategory(std::move(shopping));
		AddCategory(std::move(missions));
		AddCategory(std::move(nightClub));
		AddCategory(std::move(arcade));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
		AddCategory(BuildHeistModifierMenu());
	}
}