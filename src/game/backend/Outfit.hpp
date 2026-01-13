#pragma once
#include "core/filemgr/FileMgr.hpp"
#include <unordered_map>

namespace YimMenu
{
	namespace Outfit
	{
		struct ComponentData
		{
			std::string label;
			int drawable_id = 0;
			int texture_id = 0;
			int palette_var = -1;
			int drawable_id_max = 0;
			int texture_id_max = 0;
		};

		struct OutfitComponents
		{
			std::unordered_map<int, ComponentData> items = {
			    {1, {"Mask"}},
			    {2, {"Hair"}},
			    {3, {"Torso"}},
			    {4, {"Leg"}},
			    {5, {"Bag"}},
			    {6, {"Shoe"}},
			    {7, {"Accessory"}},
			    {8, {"Undershirt"}},
			    {9, {"Kevlar/Armor"}},
			    {10, {"Decals"}},
			    {11, {"Tops"}}};
		};

		struct OutfitProps
		{
			std::unordered_map<int, ComponentData> items = {
			    {0, {"Hats"}},
			    {1, {"Glasses"}},
			    {2, {"Ears"}},
			    {6, {"Watches"}},
			    {7, {"Bracelets"}}};
		};

        class OutfitEditor {
            
            public: 

            static void SetSelfOutfit(OutfitComponents components, OutfitProps props, bool applyHair);

            // json
            static Folder CheckFolder(std::string folderName = "");
            static void ApplyOutfitFromJson(std::string folderName, std::string fileName, bool applyHair);
            static void SaveOutfit(std::string fileName, std::string folder);
			static void RefreshList(std::string folderName, std::vector<std::string>& folders, std::vector<std::string>& files);

            // check & fix bounds
            static void CheckBoundsDrawable(ComponentData& item, const int lower);
            static void CheckBoundsTexture(ComponentData& item, const int lower);
        };
	}
}