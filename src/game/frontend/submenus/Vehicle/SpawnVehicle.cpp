#include "SpawnVehicle.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/PersonalVehicles.hpp"
#include "game/gta/data/Vehicles.hpp"
#include "game/gta/Natives.hpp"
#include "game/features/vehicle/VehiclePreview.hpp"

namespace YimMenu::Submenus
{
	static BoolCommand spawnInsideVehicle{"spawninsideveh", "Spawn Inside", "Spawn inside the vehicle."};
	static BoolCommand spawnVehicleMaxed{"spawnvehmaxed", "Spawn Maxed", "Spawn the vehicle maxed."};
	static BoolCommand spawnInsidePersonalVehicle{"spawninsidepv", "Spawn Inside", "Spawn inside the personal vehicle."};
	static BoolCommand spawnClonePersonalVehicle{"spawnclonepv", "Spawn Clone", "Spawn a clone of the persone vehicle."};

	// Track hover state for preview
	static int s_HoveredVehicleIndex = -1;
	static int s_HoveredPersonalVehicleIndex = -1;

	std::shared_ptr<TabItem> RenderSpawnNewVehicle()
	{
		auto tab = std::make_shared<TabItem>("New Vehicle");

		auto spawn = std::make_shared<Group>("Spawn");
		auto settings = std::make_shared<Group>("Settings");
		auto previewSettings = std::make_shared<Group>("Preview");

		static std::vector<std::string> vehicleNames{};
		static std::vector<int> vehicleClasses{};
		static int selectedClass{-1};

		spawn->AddItem(std::make_unique<ImGuiItem>([] {
			static bool init = [] {
				FiberPool::Push([] {
					std::unordered_map<std::string, int> nameCount;

					for (auto& veh : g_VehicleHashes)
					{
						std::string gxt = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(veh);
						std::string display = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(gxt.c_str());

						int& count = nameCount[display == "NULL" ? gxt : display];
						std::string finalName = display == "NULL" ? gxt : display;
						if (count > 0)
						{
							finalName += " " + std::to_string(count + 1);
						}
						++count;

						std::string maker = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MAKE_NAME_FROM_VEHICLE_MODEL(veh));
						if (maker != "NULL")
						{
							finalName = maker + " " + finalName;
						}

						vehicleNames.push_back(finalName);

						int id = VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(veh);
						vehicleClasses.push_back(id);
					}
				});

				return true;
			}();

			static char search[64];
			ImGui::SetNextItemWidth(300.f);
			ImGui::InputTextWithHint("Name", "Search", search, sizeof(search));

			ImGui::SetNextItemWidth(300.f);
			if (ImGui::BeginCombo("Class", selectedClass == -1 ? "All" : g_VehicleClassNames[selectedClass]))
			{
				if (ImGui::Selectable("All", selectedClass == -1))
				{
					selectedClass = -1;
				}

				for (int i = 0; i < g_VehicleClassNames.size(); i++)
				{
					if (ImGui::Selectable(g_VehicleClassNames[i], selectedClass == i))
					{
						selectedClass = i;
					}
				}

				ImGui::EndCombo();
			}

			const int visible = std::min(20, static_cast<int>(vehicleNames.size()));
			const float height = visible * ImGui::GetTextLineHeightWithSpacing();
			if (ImGui::BeginListBox("##vehicles", {300.f, height}))
			{
				if (vehicleNames.empty())
				{
					ImGui::Text("Natives not cached yet.");
				}
				else
				{
					std::string lower = search;
					std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
					for (int veh = 0; veh < vehicleNames.size(); veh++)
					{
						auto hash = g_VehicleHashes[veh];
						auto name = vehicleNames[veh];
						auto lowerName = name;
						std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

						bool matchesSearch = lowerName.find(lower) != std::string::npos;
						bool matchesClass = selectedClass == -1 || vehicleClasses[veh] == selectedClass;
						if (matchesSearch && matchesClass)
						{
							ImGui::PushID(hash);

							// Handle click for spawning
							if (ImGui::Selectable(name.c_str()))
							{
								// Hide preview when actually spawning
								VehiclePreview::Get().HidePreview();
								s_HoveredVehicleIndex = -1;

								FiberPool::Push([hash] {
									auto handle = Vehicle::Create(hash, Vehicle::GetSpawnLocRelToPed(Self::GetPed().GetHandle(), hash), Self::GetPed().GetHeading());

									if (spawnInsideVehicle.GetState())
										Self::GetPed().SetInVehicle(handle);

									if (spawnVehicleMaxed.GetState())
										handle.Upgrade();
								});
							}

							// Handle hover for preview (after item is rendered)
							bool isHovered = ImGui::IsItemHovered();
							if (isHovered && s_HoveredVehicleIndex != veh && VehiclePreview::Get().IsPreviewEnabled())
							{
								s_HoveredVehicleIndex = veh;
								VehiclePreview::Get().ShowPreview(hash, name);
							}
							else if (!isHovered && s_HoveredVehicleIndex == veh)
							{
								s_HoveredVehicleIndex = -1;
								VehiclePreview::Get().HidePreview();
							}

							ImGui::PopID();
						}
					}
				}

				ImGui::EndListBox();
			}
		}));

		// Add preview settings to settings category
		settings->AddItem(std::make_shared<BoolCommandItem>("spawninsideveh"_J));
		settings->AddItem(std::make_shared<BoolCommandItem>("spawnvehmaxed"_J));
		
		// Add preview controls to preview category
		previewSettings->AddItem(std::make_shared<BoolCommandItem>("enablevehiclepreview"_J));
		previewSettings->AddItem(std::make_shared<FloatCommandItem>("previewrotationspeed"_J));
		previewSettings->AddItem(std::make_shared<IntCommandItem>("previewalpha"_J));

		tab->AddItem(spawn);
		tab->AddItem(settings);
		tab->AddItem(previewSettings);
		return tab;
	}

	std::shared_ptr<TabItem> RenderSpawnPersonalVehicle()
	{
		auto tab = std::make_shared<TabItem>("Personal Vehicle");

		auto spawn = std::make_shared<Group>("Spawn");
		auto settings = std::make_shared<Group>("Settings");
		auto previewSettings = std::make_shared<Group>("Preview");

		static std::string selectedGarageStr{""};

		spawn->AddItem(std::make_unique<ImGuiItem>([] {
			if (!*Pointers.IsSessionStarted)
				return ImGui::TextDisabled("Join GTA Online.");

			PersonalVehicles::Update();

			static char search[64];
			ImGui::SetNextItemWidth(300.f);
			ImGui::InputTextWithHint("Name", "Search", search, sizeof(search));

			ImGui::SetNextItemWidth(300.f);
			if (ImGui::BeginCombo("Garage", selectedGarageStr.empty() ? "All" : selectedGarageStr.c_str()))
			{
				if (ImGui::Selectable("All", selectedGarageStr.empty()))
				{
					selectedGarageStr.clear();
				}
				for (auto garage : PersonalVehicles::GetGarages())
				{
					if (ImGui::Selectable(garage.c_str(), garage == selectedGarageStr))
					{
						selectedGarageStr = garage;
					}
				}

				ImGui::EndCombo();
			}

			const int visible = std::min(20, static_cast<int>(PersonalVehicles::GetPersonalVehicles().size()));
			const float height = visible * ImGui::GetTextLineHeightWithSpacing();
			if (ImGui::BeginListBox("##personalvehicles", {300.f, height}))
			{
				if (PersonalVehicles::GetPersonalVehicles().empty())
				{
					ImGui::Text("Stats not loaded yet.");
				}
				else
				{
					std::string lowerSearch = search;
					std::transform(lowerSearch.begin(), lowerSearch.end(), lowerSearch.begin(), tolower);
					int currentIndex = 0;
					for (const auto& it : PersonalVehicles::GetPersonalVehicles())
					{
						const auto& label = it.first;
						const auto& personalVeh = it.second;

						auto lowerName = label;
						std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

						bool matchesSearch = lowerName.find(lowerSearch) != std::string::npos;
						bool matchesGarage = selectedGarageStr.empty() || personalVeh->GetGarage() == selectedGarageStr;
						if (matchesSearch && matchesGarage)
						{
							ImGui::PushID(personalVeh->GetId());

							// Handle click for spawning
							if (ImGui::Selectable(label.c_str()))
							{
								// Hide preview when actually spawning
								VehiclePreview::Get().HidePreview();
								s_HoveredPersonalVehicleIndex = -1;
								
								FiberPool::Push([&personalVeh] {
									if (spawnClonePersonalVehicle.GetState())
									{
										auto coords  = Vehicle::GetSpawnLocRelToPed(Self::GetPed().GetHandle(), personalVeh->GetModel());
										auto heading = Self::GetPed().GetHeading();
										auto handle  = personalVeh->Clone(coords, heading);
										
										if (spawnInsidePersonalVehicle.GetState())
											Self::GetPed().SetInVehicle(handle);
									}
									else
									{
										if (!personalVeh->Request(spawnInsidePersonalVehicle.GetState()))
											Notifications::Show("Spawn Personal Vehicle", "Failed to spawn Personal Vehicle.", NotificationType::Error);
									}
								});
							}

							// Handle hover for preview (after item is rendered)
							bool isHovered = ImGui::IsItemHovered();
							if (isHovered && s_HoveredPersonalVehicleIndex != currentIndex && VehiclePreview::Get().IsPreviewEnabled())
							{
								s_HoveredPersonalVehicleIndex = currentIndex;
								VehiclePreview::Get().ShowPreview(personalVeh->GetModel(), label);
							}
							else if (!isHovered && s_HoveredPersonalVehicleIndex == currentIndex)
							{
								s_HoveredPersonalVehicleIndex = -1;
								VehiclePreview::Get().HidePreview();
							}

							ImGui::PopID();
						}
						currentIndex++;
					}
				}

				ImGui::EndListBox();
			}
		}));

		settings->AddItem(std::make_shared<BoolCommandItem>("spawninsidepv"_J));
		settings->AddItem(std::make_shared<BoolCommandItem>("spawnclonepv"_J));
		
		// Add preview controls to preview category (shared with new vehicle tab)
		previewSettings->AddItem(std::make_shared<BoolCommandItem>("enablevehiclepreview"_J));
		previewSettings->AddItem(std::make_shared<FloatCommandItem>("previewrotationspeed"_J));
		previewSettings->AddItem(std::make_shared<IntCommandItem>("previewalpha"_J));

		tab->AddItem(spawn);
		tab->AddItem(settings);
		tab->AddItem(previewSettings);
		return tab;
	}

	std::shared_ptr<Category> BuildSpawnVehicleMenu()
	{
		auto menu = std::make_shared<Category>("Spawn");

		auto tabBar = std::make_shared<TabBarItem>("Spawn");

		tabBar->AddItem(RenderSpawnNewVehicle());
		tabBar->AddItem(RenderSpawnPersonalVehicle());

		menu->AddItem(std::move(tabBar));

		return menu;
	}
}