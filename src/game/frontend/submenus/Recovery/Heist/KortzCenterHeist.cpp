#include "KortzCenterHeist.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderKortzCenterHeistMenu()
	{
		auto tab   = std::make_shared<TabItem>("Kortz Center Heist");

		auto target    = std::make_shared<Group>("Primary Target", 1);
		auto intel   = std::make_shared<Group>("Intel", 2);

		auto vehicles  = std::make_shared<CollapsingHeaderItem>("Vehicles");
		auto equipment = std::make_shared<CollapsingHeaderItem>("Equipment");
		auto optinalPrep     = std::make_shared<CollapsingHeaderItem>("Optinal Prep Work");

		auto action    = std::make_shared<Group>("", 1);

		auto inHeist = std::make_shared<Group>("Misc", 3);

		target->AddItem(std::make_shared<ListCommandItem>("kortzcenterheistprimarytarget"_J));

		intel->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistscopeout"_J));
		intel->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistscopesecondary"_J));
		intel->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistscopepoi"_J));
		intel->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistweakguards"_J));
		intel->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisthardmode"_J));

		
		vehicles->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistcaracara"_J));
		vehicles->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistannihilator"_J));
		vehicles->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistmanchez"_J));
		vehicles->AddItem(std::make_shared<ListCommandItem>("kortzcenterheistmanchezcolor"_J));
		
		
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisthazmat"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistmanholekey"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistalphamail"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheiststaffkeycard"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisttacticalequip"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistunmarkedweapons"_J));
		equipment->AddItem(std::make_shared<ListCommandItem>("kortzcenterheistloadouttype"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistaccesscode"_J));
		equipment->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisthackingdevice"_J));

		optinalPrep->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistguardshipments"_J));
		optinalPrep->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistguardroutes"_J));
		optinalPrep->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistglasscutter"_J));
		optinalPrep->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistpowerdrills"_J));
		optinalPrep->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistempcharges"_J));
		optinalPrep->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistprepemp"_J));
		optinalPrep->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistguardroutesprep"_J));
		optinalPrep->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistglasscutterprep"_J));
		optinalPrep->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistpowerdrillsprep"_J));

		action->AddItem(std::make_shared<CommandItem>("kortzcenterheistsetup"_J));


		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistskipfingerprint"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistskipsignalnodes"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistskipdatacrack"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistenteraccesscode"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistcutglass"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistdisablelaser"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheisttakeprimary"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheisttakesecondary"_J));



		tab->AddItem(target);
		tab->AddItem(intel);
		tab->AddItem(equipment);
		tab->AddItem(vehicles);
		tab->AddItem(optinalPrep);
		tab->AddItem(action);
		tab->AddItem(inHeist);

		return tab;
	}
}