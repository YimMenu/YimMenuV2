#include "Recovery.hpp"

#include "Recovery/HeistModifier.hpp"
#include "Recovery/StatEditor.hpp"
#include "Recovery/Transactions.hpp"
#include "game/features/recovery/GiveVehicleReward.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu::Submenus
{
	Recovery::Recovery() :
	    Submenu::Submenu("Recovery")
	{
		auto shopping  = std::make_shared<Category>("Shopping");
		auto missions  = std::make_shared<Category>("Missions");
		auto nightClub = std::make_shared<Category>("Nightclub");
		auto arcade    = std::make_shared<Category>("Arcade");
		auto casino    = std::make_shared<Category>("Casino");
		auto rp        = std::make_shared<Category>("RP");

		auto vehiclesGroup  = std::make_shared<Group>("Vehicles");
		auto generalGroup   = std::make_shared<Group>("General");
		auto nightClubGroup = std::make_shared<Group>("NightclubSafe");
		auto arcadeGroup    = std::make_shared<Group>("ArcadeSafe");
		auto casinoGroup    = std::make_shared<Group>("CasinoRigSlotMachines");
		auto rpGroup        = std::make_shared<Group>("RP");


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

		casinoGroup->AddItem(std::make_shared<BoolCommandItem>("casinomanipulaterigslotmachines"_J));

		rpGroup->AddItem(std::make_shared<IntCommandItem>("rpmultiplierinput"_J));
		rpGroup->AddItem(std::make_shared<CommandItem>("rpmultiplier"_J));

		shopping->AddItem(vehiclesGroup);

		nightClub->AddItem(nightClubGroup);
		arcade->AddItem(arcadeGroup);
		missions->AddItem(generalGroup);
		casino->AddItem(casinoGroup);
		rp->AddItem(rpGroup);
		AddCategory(std::move(shopping));
		AddCategory(std::move(missions));
		AddCategory(std::move(nightClub));
		AddCategory(std::move(arcade));
		AddCategory(std::move(rp));
		AddCategory(std::move(casino));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildTransactionsMenu());
		AddCategory(BuildHeistModifierMenu());
	}
}