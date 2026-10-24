#include "SavedVehicles.hpp"
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

	namespace
	{
		// Get rid of the ".json" file extension so keep the saved car list a little cleaner
		std::string GetDisplayName(const std::string& fileName)
		{
			constexpr std::string_view extension = ".json";
			if (fileName.size() > extension.size() && std::string_view(fileName).ends_with(extension))
				return fileName.substr(0, fileName.size() - extension.size());

			return fileName;
		}

		std::string ToLower(std::string value)
		{
			std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
				return static_cast<char>(std::tolower(c));
			});
			return value;
		}
	}

	std::shared_ptr<Category> BuildSavedVehiclesMenu()
	{
		static std::string folder{}, file{};
		static std::vector<std::string> folders{}, files{};
		static std::string vehicleFileNameInput{}, newFolder{}, search{};

		auto persistCar = std::make_shared<Category>("Saved Vehicles");

		persistCar->AddItem(std::make_shared<BoolCommandItem>("spawninsidesavedveh"_J));

		persistCar->AddItem(std::make_unique<ImGuiItem>([] {
			// Remove the need to refresh the list manually when the tab is opened
			static int lastDrawnFrame = -1;
			const int currentFrame = ImGui::GetFrameCount();
			const bool justOpened = (currentFrame != lastDrawnFrame + 1);
			lastDrawnFrame = currentFrame;

			if (justOpened)
				FiberPool::Push([] {
					SavedVehicles::RefreshList(folder, folders, files);
				});

			auto vehicle = Self::GetVehicle();
			const bool inVehicle = vehicle.IsValid();

			ImGui::SetNextItemWidth(240.f);
			if (ImGui::BeginCombo("Folder", folder.empty() ? "Root" : folder.c_str()))
			{
				if (ImGui::Selectable("Root", folder.empty()))
				{
					folder.clear();
					FiberPool::Push([] {
						SavedVehicles::RefreshList(folder, folders, files);
					});
				}

				for (const auto& folderName : folders)
				{
					if (ImGui::Selectable(folderName.c_str(), folder == folderName))
					{
						folder = folderName;
						FiberPool::Push([] {
							SavedVehicles::RefreshList(folder, folders, files);
						});
					}
				}

				ImGui::EndCombo();
			}

			ImGui::SameLine();
			if (ImGui::Button("Refresh List"))
				FiberPool::Push([] {
					SavedVehicles::RefreshList(folder, folders, files);
				});

			ImGui::SameLine();
			ImGui::TextDisabled("%d saved", static_cast<int>(files.size()));

			ImGui::Spacing();

			const float rowHeight = ImGui::GetTextLineHeightWithSpacing();
			const float minPaneHeight = 8.f * rowHeight + ImGui::GetFrameHeightWithSpacing() * 2.5f;
			const float paneHeight = std::max(ImGui::GetContentRegionAvail().y, minPaneHeight); // Since we can resize the YimMenu window, it's best to scale the panel height to the available Y-space
			constexpr float listWidth = 340.f;

			// Browser frame
			if (ImGui::BeginChild("##saved_vehicles_list_pane", ImVec2(listWidth, paneHeight)))
			{
				ImGui::SeparatorText("Saved Vehicles");

				ImGui::SetNextItemWidth(-FLT_MIN);
				ImGui::InputTextWithHint("##veh_search", "Search", &search);

				const std::string searchLower = ToLower(search);

				if (ImGui::BeginListBox("##saved_vehs", ImVec2(-FLT_MIN, -FLT_MIN)))
				{
					bool anyVisible = false;

					for (const auto& fileName : files)
					{
						const std::string displayName = GetDisplayName(fileName);

						if (!searchLower.empty() && !ToLower(displayName).contains(searchLower))
							continue;

						anyVisible = true;

						ImGui::PushID(fileName.c_str());
						if (ImGui::Selectable(displayName.c_str(), file == fileName))
						{
							file = fileName;

							// With this change we're going to spawn immediately without asking for a yes/no confirmation
							FiberPool::Push([selectedFolder = folder, selectedFile = fileName] {
								SavedVehicles::Load(selectedFolder, selectedFile, spawnInsideSavedVehicle.GetState());
							});
						}
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Click to spawn %s", displayName.c_str());
						ImGui::PopID();
					}

					if (!anyVisible)
						ImGui::TextDisabled(files.empty() ? "  No saved vehicles in this folder." : "  No matches."); // Provide some feedback to the user so they're not just seeing an empty panel without explanation

					ImGui::EndListBox();
				}
			}
			ImGui::EndChild();

			ImGui::SameLine();

			if (ImGui::BeginChild("##saved_vehicles_save_pane", ImVec2(0.f, paneHeight)))
			{
				ImGui::SeparatorText("Save Current Vehicle");

				if (!inVehicle)
				{
					ImGui::TextDisabled("Get into a vehicle to save it.");
				}
				else
				{
					const bool savingToNewFolder = folder.empty();

					ImGui::Text("File Name");
					ImGui::SetNextItemWidth(250.f);
					ImGui::InputTextWithHint("##vehiclefilename", "Name this vehicle", &vehicleFileNameInput);

					if (savingToNewFolder)
					{
						ImGui::Text("Folder Name");
						ImGui::SetNextItemWidth(250.f);
						ImGui::InputTextWithHint("##foldername", "Leave empty for Root", &newFolder);
					}

					ImGui::Spacing();

					if (ImGui::Button("Save"))
					{
						const std::string fileName = TrimString(vehicleFileNameInput);

						if (fileName.empty())
						{
							Notifications::Show("Saved Vehicles", "Filename empty!", NotificationType::Warning);
						}
						else
						{
							const std::string targetFolder = savingToNewFolder ? newFolder : folder;

							vehicleFileNameInput.clear();

							if (savingToNewFolder)
							{
								folder = newFolder; // jump to the folder we just saved into
								newFolder.clear();
							}

							FiberPool::Push([targetFolder, fileName] {
								SavedVehicles::Save(targetFolder, fileName);
								SavedVehicles::RefreshList(folder, folders, files);
							});
						}
					}

					ImGui::SameLine();
					if (ImGui::Button("Populate Name"))
						FiberPool::Push([] {
							vehicleFileNameInput = Self::GetVehicle().GetFullName();
						});
				}

				if (!file.empty())
				{
					ImGui::Spacing();
					ImGui::SeparatorText("Last Spawned");
					ImGui::TextWrapped("%s", GetDisplayName(file).c_str());
				}
			}
			ImGui::EndChild();
		}));

		return persistCar;
	}
}
