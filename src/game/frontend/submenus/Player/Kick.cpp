#include "Toxic.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildKickMenu()
	{
		auto menu = std::make_shared<Category>("Kick");

		auto kicks = std::make_shared<Group>("Kicks");
		kicks->AddItem(std::make_shared<PlayerCommandItem>("hkick"_J));
		kicks->AddItem(std::make_shared<PlayerCommandItem>("shkick"_J));
		kicks->AddItem(std::make_shared<PlayerCommandItem>("endkick"_J));
		kicks->AddItem(std::make_shared<PlayerCommandItem>("nfkick"_J));

		auto other = std::make_shared<Group>("Other");
		other->AddItem(std::make_shared<PlayerCommandItem>("blackscreen"_J));

		menu->AddItem(kicks);
		menu->AddItem(other);

		return menu;
	}
}