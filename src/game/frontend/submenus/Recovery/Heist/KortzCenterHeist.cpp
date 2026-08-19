#include "KortzCenterHeist.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderKortzCenterHeistMenu()
	{
		auto tab   = std::make_shared<TabItem>("Kortz Center Heist");

		auto target    = std::make_shared<Group>("Primary Target", 1);
		auto general   = std::make_shared<Group>("General", 2);

		auto vehicles  = std::make_shared<CollapsingHeaderItem>("Vehicles");
		auto equipment = std::make_shared<CollapsingHeaderItem>("Equipment");
		auto intel     = std::make_shared<CollapsingHeaderItem>("Intel");

		auto action    = std::make_shared<Group>("", 1);

		target->AddItem(std::make_shared<ListCommandItem>("kortzcenterheistprimarytarget"_J));

		general->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistguardroutes"_J));
		general->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistglasscutter"_J));
		general->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistpowerdrills"_J));
		general->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistempcharges"_J));

		vehicles->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistcaracara"_J));
		vehicles->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistannihilator"_J));
		vehicles->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistmanchez"_J));
		vehicles->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistcaracaraprep"_J));
		vehicles->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistannihilatorprep"_J));
		vehicles->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistmanchezprep"_J));

		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisthazmat"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheiststaffkeycard"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisttacticalequip"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisthackingdevice"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistaccesscode"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistunmarkedweapons"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistguardshipments"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistprepemp"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistguardroutesprep"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistglasscutterprep"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistpowerdrillsprep"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistempchargesprep"_J));

		intel->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistscopeout"_J));
		intel->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistalphamail"_J));
		intel->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistscopesecondary"_J));
		intel->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistscopepoi"_J));

		auto inHeist = std::make_shared<Group>("In-Heist", 2);

		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistskipfingerprint"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistskipsignalnodes"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistskipdatacrack"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistautoenterpcaccesscode"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistcutglass"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistdisablelaser"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheisttakeprimary"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheisttakesecondary"_J));

		action->AddItem(std::make_shared<CommandItem>("kortzcenterheistsetup"_J));

		tab->AddItem(target);
		tab->AddItem(general);
		tab->AddItem(vehicles);
		tab->AddItem(equipment);
		tab->AddItem(intel);
		tab->AddItem(inHeist);
		tab->AddItem(action);

		return tab;
	}
}
