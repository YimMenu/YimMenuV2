#include "SpawnVehicle.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/data/Vehicles.hpp"
#include "game/gta/Vehicle.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Submenus
{
	static Vector3 GetVehicleSpawnLoc(joaat_t hash, bool spawnInside)
	{
		float y_offset = 0;

		if (Self::GetVehicle().IsValid())
		{
			Vector3 min, max, result;
			MISC::GET_MODEL_DIMENSIONS(hash, &min, &max);
			result   = max - min;
			y_offset = result.y;
		}
		else if (!spawnInside)
		{
			y_offset = 5.f;
		}

		return ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Self::GetPed().GetHandle(), 0.f, y_offset, 0.f);
	}

	std::shared_ptr<Category> BuildSpawnVehicleMenu()
	{
		auto menu = std::make_shared<Category>("Spawn");

		static std::vector<std::string> vehicleNames{};
		static std::vector<int> vehicleClasses{};
		static int selectedClass{-1};
		static bool spawnInside{};
		static bool spawnMaxed{};

		menu->AddItem(std::make_unique<ImGuiItem>([] {
			static bool init = [] {
				FiberPool::Push([] {
					std::unordered_map<std::string, int> nameCount;

					for (auto& veh : g_VehicleHashes)
					{
						std::string gxt     = VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(veh);
						std::string display = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(gxt.c_str());

						int& count            = nameCount[display == "NULL" ? gxt : display];
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

			const int visible  = std::min(10, static_cast<int>(vehicleNames.size()));
			const float height = visible * ImGui::GetTextLineHeightWithSpacing();
			if (ImGui::BeginListBox("##vehicles", {300.f, height}))
			{
				std::string lower = search;
				std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
				for (int veh = 0; veh < vehicleNames.size(); veh++)
				{
					if (vehicleNames[veh].empty())
						continue;

					auto hash      = g_VehicleHashes[veh];
					auto name      = vehicleNames[veh];
					auto lowerName = name;
					std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

					bool matchesSearch = lowerName.find(lower) != std::string::npos;
					bool matchesClass  = selectedClass == -1 || vehicleClasses[veh] == selectedClass;
					if (matchesSearch && matchesClass)
					{
						ImGui::PushID(hash);
						if (ImGui::Selectable(name.c_str()))
						{
							FiberPool::Push([hash] {
								auto handle = Vehicle::Create(hash, GetVehicleSpawnLoc(hash, spawnInside), Self::GetPed().GetHeading());

								if (spawnInside)
									Self::GetPed().SetInVehicle(handle);

								if (spawnMaxed)
									handle.Upgrade();
							});
						}
						ImGui::PopID();
					}
				}

				ImGui::EndListBox();
			}

			ImGui::Checkbox("Spawn Inside", &spawnInside);
			ImGui::SameLine();
			ImGui::Checkbox("Spawn Maxed", &spawnMaxed);
		}));

		return menu;
	}
}