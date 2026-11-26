#include "KortzCenterHeist.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderKortzCenterHeistMenu()
	{
		auto tab = std::make_shared<TabItem>("Kortz Center Heist");

		auto target = std::make_shared<Group>("Primary Target", 1);
		auto setups = std::make_shared<Group>("Heist Setups", 5);
		auto action = std::make_shared<Group>("", 1);
		auto inHeist = std::make_shared<Group>("Misc", 3);

		target->AddItem(std::make_shared<ListCommandItem>("kortzcenterheistprimarytarget"_J));

		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisthardmode"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheiststaffkeycard"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisttacticalequip"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistalphamail"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisthazmat"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistunmarkedweapons"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistmanchez"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistcaracara"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistannihilator"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistguardshipments"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistguardroutes"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistglasscutter"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistpowerdrills"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistempcharges"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistaccesscode"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheisthackingdevice"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistscopeout"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistscopesecondary"_J));
		setups->AddItem(std::make_shared<BoolCommandItem>("kortzcenterheistscopepoi"_J));

		action->AddItem(std::make_shared<CommandItem>("kortzcenterheistsetup"_J));

		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistskipfingerprint"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistskipsignalnodes"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistskipdatacrack"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistautoenterpcaccesscode"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistcutglass"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistdisablelaser"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheistdisablecameras"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheisttakeprimary"_J));
		inHeist->AddItem(std::make_shared<CommandItem>("kortzcenterheisttakesecondary"_J));

		tab->AddItem(target);
		tab->AddItem(setups);
		tab->AddItem(action);
		tab->AddItem(inHeist);

		return tab;
	}
}
