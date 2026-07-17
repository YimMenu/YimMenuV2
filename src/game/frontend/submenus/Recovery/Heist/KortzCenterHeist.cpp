#include "KortzCenterHeist.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderKortzCenterHeistMenu()
	{
		auto tab = std::make_shared<TabItem>("Kortz Center Heist");

		auto target    = std::make_shared<Group>("Primary Target", 1);
		auto general   = std::make_shared<Group>("General", 2);
		auto preps     = std::make_shared<Group>("Prep Work", 2);
		auto scoping   = std::make_shared<Group>("Scoping", 2);
		auto action    = std::make_shared<Group>("", 1);

		target->AddItem(std::make_shared<ListCommandItem>("kortzcenterheistprimarytarget"_J));

		general->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistguardroutes"_J));
		general->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistglasscutter"_J));
		general->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistpowerdrills"_J));
		general->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistempcharges"_J));

		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistscopeout"_J));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistalphamail"_J));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisthazmat"_J));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheiststaffkeycard"_J));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisttacticalequip"_J));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisthackingdevice"_J));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistaccesscode"_J));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistunmarkedweapons"_J));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistcaracara"_J));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistannihilator"_J));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistmanchez"_J));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistprepemp"_J));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistguardshipments"_J));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistguardroutesprep"_J));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistglasscutterprep"_J));
		preps->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistpowerdrillsprep"_J));

		scoping->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistscopesecondary"_J));
		scoping->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistscopepoi"_J));

		action->AddItem(std::make_shared<CommandItem>("kortzcenterheistsetup"_J, "Setup##kortz"));

		tab->AddItem(target);
		tab->AddItem(general);
		tab->AddItem(preps);
		tab->AddItem(scoping);
		tab->AddItem(action);

		return tab;
	}
}
