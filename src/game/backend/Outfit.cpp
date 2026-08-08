#include "Outfit.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/Notifications.hpp"
#include <fstream>
#include "core/util/Strings.hpp"

namespace YimMenu
{
	namespace Outfit
	{
		void OutfitEditor::CheckBoundsDrawable(ComponentData& item, const int lower)
		{
			if (item.drawable_id > item.drawable_id_max)
				item.drawable_id = item.drawable_id_max;
			if (item.drawable_id < lower)
				item.drawable_id = lower;
		}

		void OutfitEditor::CheckBoundsTexture(ComponentData& item, const int lower)
		{
			if (item.texture_id > item.texture_id_max)
				item.texture_id = item.texture_id_max;
			if (item.texture_id < lower)
				item.texture_id = lower;
		}

		void OutfitEditor::SetSelfOutfit(OutfitComponents components, OutfitProps props, bool applyHair)
		{
			for (auto t : components.items)
			{
				auto item = t.second;

				auto palette_var = item.palette_var;
				if (item.palette_var == -1)
					palette_var = PED::GET_PED_PALETTE_VARIATION(Self::GetPed().GetHandle(), t.first);

				if (!applyHair && t.first == 2)
					continue;

				PED::SET_PED_COMPONENT_VARIATION(Self::GetPed().GetHandle(), t.first, item.drawable_id, item.texture_id, palette_var);
			}

			PED::CLEAR_ALL_PED_PROPS(Self::GetPed().GetHandle(), 0);

			for (auto& t : props.items)
			{
				auto item = t.second;
				PED::SET_PED_PROP_INDEX(Self::GetPed().GetHandle(), t.first, item.drawable_id, item.texture_id, TRUE, 0);
			}
		}

		Folder OutfitEditor::CheckFolder(std::string folderName)
		{
			return FileMgr::GetProjectFolder("./saved_outfits/" + folderName);
		}

		void OutfitEditor::ApplyOutfitFromJson(std::string folderName, std::string fileName, bool applyHair)
		{
			const auto file = CheckFolder(folderName).GetFile(fileName).Path();

			if (!std::filesystem::exists(file))
			{
				Notifications::Show("Outfit", "File does not exist.", NotificationType::Error);
				return;
			}

			std::ifstream file_stream(file);
			nlohmann::json j;

			try
			{
				file_stream >> j;
			}
			catch (std::exception& e)
			{
				LOG(WARNING) << e.what();
			}
			file_stream.close();

			OutfitComponents components;
			OutfitProps props;

			if (j["model"] != Self::GetPed().GetModel())
			{
				Notifications::Show("Oufit", "Ped models different.", NotificationType::Error);
				return;
			}

			for (auto& item : j["components"].items())
			{
				std::stringstream ss(item.key());
				int id = 0;
				ss >> id;
				components.items[id].drawable_id = item.value()["drawable_id"];
				components.items[id].texture_id = item.value()["texture_id"];
				if (auto palette_var = item.value()["palette_var"]; !palette_var.is_null())
					components.items[id].palette_var = palette_var;
			}
			for (auto& item : j["props"].items())
			{
				std::stringstream ss(item.key());
				int id = 0;
				ss >> id;
				props.items[id].drawable_id = item.value()["drawable_id"];
				props.items[id].texture_id = item.value()["texture_id"];
			}

			SetSelfOutfit(components, props, applyHair);
		}

		void OutfitEditor::SaveOutfit(std::string fileName, std::string folder)
		{
			OutfitComponents components;
			OutfitProps props;

			nlohmann::json j;
			nlohmann::json j_components;
			nlohmann::json j_props;

			ReplaceString(fileName, ".", ""); // filename say "bob.." will throw relative path error from Folder::GetFile
			fileName += ".json";

			auto model = Self::GetPed().GetModel();
			auto ped = Self::GetPed().GetHandle();

			for (auto& item : components.items)
			{
				nlohmann::json tmp;
				tmp["drawable_id"] = PED::GET_PED_DRAWABLE_VARIATION(ped, item.first);
				tmp["texture_id"] = PED::GET_PED_TEXTURE_VARIATION(ped, item.first);
				tmp["palette_var"] = PED::GET_PED_PALETTE_VARIATION(ped, item.first);
				j_components[std::to_string(item.first)] = tmp;
			}

			for (auto& item : props.items)
			{
				nlohmann::json tmp;
				tmp["drawable_id"] = PED::GET_PED_PROP_INDEX(ped, item.first, 0);
				tmp["texture_id"] = PED::GET_PED_PROP_TEXTURE_INDEX(ped, item.first);
				j_props[std::to_string(item.first)] = tmp;
			}

			j["components"] = j_components;
			j["props"] = j_props;
			j["model"] = model;

			auto path = CheckFolder(folder).GetFile(fileName).Path();
			std::ofstream o(path);
			o << std::setw(4) << j << std::endl;
			o.close();
		}

		void OutfitEditor::RefreshList(std::string folderName, std::vector<std::string>& folders, std::vector<std::string>& files)
		{
			folders.clear();

			const auto file_path = CheckFolder();
			for (const auto& directory_entry : std::filesystem::directory_iterator(file_path.Path()))
				if (directory_entry.is_directory())
					folders.push_back(directory_entry.path().filename().generic_string());

			files.clear();

			const auto file_path2 = CheckFolder(folderName);
			for (const auto& directory_entry : std::filesystem::directory_iterator(file_path2.Path()))
				if (directory_entry.path().extension() == ".json")
					files.push_back(directory_entry.path().filename().generic_string());
		}

	}
}