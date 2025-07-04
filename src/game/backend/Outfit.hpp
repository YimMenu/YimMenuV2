#pragma once
#include "core/filemgr/FileMgr.hpp"

namespace YimMenu
{
	namespace Outfit
	{
		struct Component
		{
			int id;
			std::string label;
			int drawable_id = 0;
			int texture_id = 0;
			int palette_var = -1;
			int drawable_id_max = 0;
			int texture_id_max = 0;
		};

		struct OutfitComponents
		{
			std::unordered_map<int, Component> items = {
			    {1, {1, "Mask"}},
			    {2, {2, "Hair"}},
			    {3, {3, "Torso"}},
			    {4, {4, "Leg"}},
			    {5, {5, "Bag"}},
			    {6, {6, "Shoe"}},
			    {7, {7, "Accessory"}},
			    {8, {8, "Undershirt"}},
			    {9, {9, "Kevlar/Armor"}},
			    {10, {10, "Decals"}},
			    {11, {11, "Tops"}}};
		};

		struct OutfitProps
		{
			std::unordered_map<int, Component> items = {
			    {0, {0, "Hats"}},
			    {1, {1, "Glasses"}},
			    {2, {2, "Ears"}},
			    {6, {6, "Watches"}},
			    {7, {7, "Bracelets"}}};
		};

        class OutfitEditor {
            
            public: 

            static void SetSelfOutfit(OutfitComponents components, OutfitProps props);

            // json
            static Folder CheckFolder(std::string folder_name = "");
            static void ApplyOutfitFromJson(std::string folder_name, std::string file_name);
            static void SaveOutfit(std::string filename, std::string folder);
			static void RefreshList(std::string folder_name, std::vector<std::string>& folders, std::vector<std::string>& files);

            // check & fix bounds
            static void CheckBoundsDrawable(Component& item, const int lower);
            static void CheckBoundsTexture(Component& item, const int lower);

        };
	}
}