#include "HeistModifier.hpp"
#include "Heist/ApartmentHeist.hpp"
#include "Heist/DiamondCasinoHeist.hpp"
#include "Heist/CayoPericoHeist.hpp"
#include "Heist/DoomsdayHeist.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildHeistModifierMenu()
	{
		auto menu        = std::make_shared<Category>("Heists");
		auto heistTabBar = std::make_shared<TabBarItem>("Heist Modifier");

		heistTabBar->AddItem(RenderApartmentHeistMenu());
		heistTabBar->AddItem(RenderDiamondCasinoHeistMenu());
		heistTabBar->AddItem(RenderCayoPericoHeistMenu());
		heistTabBar->AddItem(RenderDoomsdayHeistMenu());

		menu->AddItem(std::move(heistTabBar));

		return menu;
	}
}