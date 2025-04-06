#pragma once
#include "core/frontend/manager/Category.hpp"
#include "game/frontend/items/Items.hpp"
#include <string>

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildStatEditorMenu();
	// API publique
	bool SetStatInt(const std::string& name, int value);
	int GetStatInt(const std::string& name);
}