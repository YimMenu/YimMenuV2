#pragma once
#include "core/frontend/manager/Category.hpp"

namespace YimMenu
{
	std::shared_ptr<Category> CreateOutfitsMenu();

	void SaveCurrentOutfit(const std::string& name);
	bool LoadOutfit(const std::string& name);
	std::vector<std::string> GetSavedOutfits();
	bool DeleteOutfit(const std::string& name);
	void ExportOutfitToClipboard();
	bool ImportOutfitFromClipboard();
}