#include "DiamondCasinoHeist.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderDiamondCasinoHeistMenu()
	{
		auto tab = std::make_shared<TabItem>("Diamond Casino Heist");

		auto cuts = std::make_shared<Group>("Heist Cuts", 2);
		auto setups = std::make_shared<Group>("Heist Setups");
		auto loots = std::make_shared<Group>("Loots", 2);
		auto misc = std::make_shared<Group>("Misc", 1);

		cuts->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistcut1"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistcut3"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistcut2"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistcut4"_J));
		cuts->AddItem(std::make_shared<CommandItem>("diamondcasinoheistforceready"_J));
		cuts->AddItem(std::make_shared<CommandItem>("diamondcasinoheistsetcuts"_J));

		auto gunmanAndDriver = std::make_shared<Group>("", 2);
		gunmanAndDriver->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistgunman"_J));
		gunmanAndDriver->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistdriver"_J));
		gunmanAndDriver->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistweapon"_J));
		gunmanAndDriver->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistvehicle"_J));

		setups->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistdifficulty"_J));
		setups->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistprimarytarget"_J));
		setups->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheistapproach"_J));
		setups->AddItem(std::move(gunmanAndDriver));
		setups->AddItem(std::make_shared<ListCommandItem>("diamondcasinoheisthacker"_J));
		setups->AddItem(std::make_shared<CommandItem>("diamondcasinoheistsetup"_J));

		loots->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistpotentialtake"_J));
		loots->AddItem(std::make_shared<IntCommandItem>("diamondcasinoheistactualtake"_J));
		loots->AddItem(std::make_shared<CommandItem>("diamondcasinoheistsetpotentialtake"_J, "Set##potentialtake"));
		loots->AddItem(std::make_shared<CommandItem>("diamondcasinoheistsetactualtake"_J, "Set##actualtake"));

		misc->AddItem(std::make_shared<CommandItem>("diamondcasinoheistskiphacking"_J));
		misc->AddItem(std::make_shared<CommandItem>("diamondcasinoheistskipdrilling"_J));
		misc->AddItem(std::make_shared<CommandItem>("diamondcasinoheistinstantfinish"_J));

		tab->AddItem(cuts);
		tab->AddItem(setups);
		tab->AddItem(loots);
		tab->AddItem(misc);

		return tab;
	}
}