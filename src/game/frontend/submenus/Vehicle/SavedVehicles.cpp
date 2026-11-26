#include "SavedVehicles.hpp"
#include "core/translation/Translation.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/util/Strings.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/SavedVehicles.hpp"
#include "game/gta/Vehicle.hpp"
#include "misc/cpp/imgui_stdlib.h"

namespace YimMenu::Submenus
{
	static BoolCommand spawnInsideSavedVehicle{"spawninsidesavedveh", "Spawn Inside", "Spawn inside the vehicle."};

	std::shared_ptr<Category> BuildSavedVehiclesMenu()
	{
		static std::string folder{}, file{};
		static std::vector<std::string> folders{}, files{};
		static char vehicle_file_name_input[64]{};
		static char newFolder[50]{};

		auto persistCar = std::make_shared<Category>("Saved Vehicles");

		persistCar->AddItem(std::make_shared<BoolCommandItem>("spawninsidesavedveh"_J));

		persistCar->AddItem(std::make_unique<ImGuiItem>([] {
			static auto drawSaveVehicleButton = [](bool saveToNewFolder) {
				if (!Self::GetVehicle() || !Self::GetVehicle().IsValid())
					return;

				if (ImGui::Button(Translation::TrLabel("Save").c_str()))
					FiberPool::Push([saveToNewFolder] {
						std::string fileName = TrimString(vehicle_file_name_input);
						strcpy(vehicle_file_name_input, "");

						if (!fileName.size())
						{
							Notifications::Show("Saved Vehicles", "Filename empty!", NotificationType::Warning);
							return;
						}

						SavedVehicles::Save(saveToNewFolder ? newFolder : folder, fileName);

						if (saveToNewFolder)
						{
							folder = newFolder; // set current folder to newly created folder
							strcpy(newFolder, "");
						}

						SavedVehicles::RefreshList(folder, folders, files);
					});
				ImGui::SameLine();
				if (ImGui::Button(Translation::TrLabel("Populate Name").c_str()))
					FiberPool::Push([] {
						std::string name = Self::GetVehicle().GetFullName();
						strcpy(vehicle_file_name_input, name.c_str());
					});
			};

			if (ImGui::Button(Translation::TrLabel("Refresh List").c_str()))
				FiberPool::Push([] {
					SavedVehicles::RefreshList(folder, folders, files);
				});

			ImGui::SetNextItemWidth(300.f);
			const auto root_label = Translation::Tr("Root");
			auto folder_display = folder.empty() ? root_label.c_str() : folder.c_str();
			if (ImGui::BeginCombo(Translation::TrLabel("Folder").c_str(), folder_display))
			{
				if (ImGui::Selectable(Translation::TrLabel("Root").c_str(), folder == ""))
				{
					folder.clear();
					FiberPool::Push([] {
						SavedVehicles::RefreshList(folder, folders, files);
					});
				}

				for (std::string folder_name : folders)
					if (ImGui::Selectable(folder_name.c_str(), folder == folder_name))
					{
						folder = folder_name;
						FiberPool::Push([] {
							SavedVehicles::RefreshList(folder, folders, files);
						});
					}

				ImGui::EndCombo();
			}

			static bool open_modal = false;
			static std::string search;

			ImGui::SetNextItemWidth(300);
			if (ImGui::InputTextWithHint("###veh_name", Translation::Tr("Search").c_str(), &search))
				std::transform(search.begin(), search.end(), search.begin(), tolower);

			ImGui::Text("%s", Translation::Tr("Saved Vehicles").c_str());

			static const auto over_30 = (30 * ImGui::GetTextLineHeightWithSpacing() + 2);
			const auto box_height = files.size() <= 30 ? (files.size() * ImGui::GetTextLineHeightWithSpacing() + 2) : over_30;
			ImGui::SetNextItemWidth(250);
			if (ImGui::BeginListBox("##saved_vehs", ImVec2(300, box_height)))
			{
				for (const auto& pair : files)
				{
					std::string pair_lower = pair;
					std::transform(pair_lower.begin(), pair_lower.end(), pair_lower.begin(), tolower);
					if (pair_lower.contains(search))
					{
						auto file_name = pair.c_str();
						if (ImGui::Selectable(file_name, file == pair, ImGuiSelectableFlags_AllowItemOverlap))
						{
							file = pair;
							open_modal = true;
						}
					}
				}
				ImGui::EndListBox();
			}
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				ImGui::Text("%s", Translation::Tr("File Name").c_str());
				ImGui::SetNextItemWidth(250);
				ImGui::InputText("##vehiclefilename", vehicle_file_name_input, IM_ARRAYSIZE(vehicle_file_name_input));

				if (folder.empty())
				{
					ImGui::Text("%s", Translation::Tr("Folder Name").c_str());
					ImGui::SetNextItemWidth(250);
					ImGui::InputText("##foldername", newFolder, IM_ARRAYSIZE(newFolder));
					drawSaveVehicleButton(true);
				}
				else
					drawSaveVehicleButton(false);
			}
			ImGui::EndGroup();

			if (open_modal)
				ImGui::OpenPopup("##spawncarmodel2");
			if (ImGui::BeginPopupModal("##spawncarmodel2", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove))
			{
				ImGui::Text(Translation::Tr("Are you sure you want to spawn %s").c_str(), file.c_str());
				ImGui::Spacing();
				if (ImGui::Button(Translation::TrLabel("Yes").c_str()))
				{
					FiberPool::Push([] {
						SavedVehicles::Load(folder, file, spawnInsideSavedVehicle.GetState());
					});
					open_modal = false;
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button(Translation::TrLabel("No").c_str()))
				{
					open_modal = false;
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
		}));

		return persistCar;
	}
}
