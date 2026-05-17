#include "OutfitEditor.hpp"

#include "core/frontend/manager/UIManager.hpp"
#include "game/backend/Self.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/gta/Natives.hpp"
#include "core/frontend/Notifications.hpp"

#include <random>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

// TODO: clean up more AI generated junk from this file

namespace YimMenu
{
	int GetMaxDrawable(int slot)
	{
		auto ped = Self::GetPed();
		return PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(static_cast<int>(ped.GetHandle()), slot);
	}

	int GetMaxTexture(int slot, int drawable)
	{
		auto ped = Self::GetPed();
		return PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(static_cast<int>(ped.GetHandle()), slot, drawable);
	}

	int GetMaxPropDrawable(int slot)
	{
		auto ped = Self::GetPed();
		return PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(static_cast<int>(ped.GetHandle()), slot);
	}

	int GetMaxPropTexture(int slot, int drawable)
	{
		auto ped = Self::GetPed();
		return PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(static_cast<int>(ped.GetHandle()), slot, drawable);
	}

	void GetOutfitSlot(int slot, int& drawable, int& texture)
	{
		auto ped = Self::GetPed();
		drawable = PED::GET_PED_DRAWABLE_VARIATION(static_cast<int>(ped.GetHandle()), slot);
		texture = PED::GET_PED_TEXTURE_VARIATION(static_cast<int>(ped.GetHandle()), slot);
	}

	void GetPropSlot(int slot, int& drawable, int& texture)
	{
		auto ped = Self::GetPed();
		drawable = PED::GET_PED_PROP_INDEX(static_cast<int>(ped.GetHandle()), slot, 0);
		if (drawable == -1)
		{
			drawable = 0;
			texture = 0;
			return;
		}
		texture = PED::GET_PED_PROP_TEXTURE_INDEX(static_cast<int>(ped.GetHandle()), slot);
	}

	void SetOutfitSlot(int slot, int drawable, int texture)
	{
		auto ped = Self::GetPed();
		PED::SET_PED_COMPONENT_VARIATION(static_cast<int>(ped.GetHandle()), slot, drawable, texture, 0);
	}

	void SetPropSlot(int slot, int drawable, int texture)
	{
		auto ped = Self::GetPed();
		PED::SET_PED_PROP_INDEX(static_cast<int>(ped.GetHandle()), slot, drawable, texture, true, 0);
	}


	static std::string GetSaveDirectory()
	{
		auto dir = std::filesystem::path(std::getenv("appdata")) / "YimMenuV2" / "Outfits";
		std::filesystem::create_directories(dir);
		return dir.string();
	}

	struct OutfitData
	{
		std::string name;
		std::vector<int> component_drawables;
		std::vector<int> component_textures;
		std::vector<int> prop_slots = {0, 1, 2, 6};
		std::vector<int> prop_drawables;
		std::vector<int> prop_textures;
	};

	static OutfitData GetCurrentOutfitData()
	{
		OutfitData outfit;
		outfit.component_drawables.resize(12);
		outfit.component_textures.resize(12);

		for (int slot = 0; slot < 12; slot++)
		{
			GetOutfitSlot(slot, outfit.component_drawables[slot], outfit.component_textures[slot]);
		}

		outfit.prop_drawables.resize(4);
		outfit.prop_textures.resize(4);
		for (int i = 0; i < 4; i++)
		{
			int slot = outfit.prop_slots[i];
			GetPropSlot(slot, outfit.prop_drawables[i], outfit.prop_textures[i]);
		}

		return outfit;
	}

	static void ApplyOutfitData(const OutfitData& outfit)
	{
		for (int slot = 0; slot < 12 && slot < outfit.component_drawables.size(); slot++)
		{
			if (outfit.component_drawables[slot] >= 0)
			{
				SetOutfitSlot(slot, outfit.component_drawables[slot], outfit.component_textures[slot]);
			}
		}

		for (int i = 0; i < outfit.prop_slots.size() && i < outfit.prop_drawables.size(); i++)
		{
			int slot = outfit.prop_slots[i];
			int drawable = outfit.prop_drawables[i];
			int texture = outfit.prop_textures[i];

			auto ped = Self::GetPed();
			if (drawable > 0)
			{
				PED::SET_PED_PROP_INDEX(static_cast<int>(ped.GetHandle()), slot, drawable, texture, true, 0);
			}
			else
			{
				PED::SET_PED_PROP_INDEX(static_cast<int>(ped.GetHandle()), slot, -1, 0, true, 0);
			}
		}
	}

	static void SaveOutfitToFile(const std::string& name)
	{
		try
		{
			auto outfit = GetCurrentOutfitData();
			nlohmann::json j;
			j["name"] = name;
			j["component_drawables"] = outfit.component_drawables;
			j["component_textures"] = outfit.component_textures;
			j["prop_slots"] = outfit.prop_slots;
			j["prop_drawables"] = outfit.prop_drawables;
			j["prop_textures"] = outfit.prop_textures;

			std::string filename = GetSaveDirectory() + "/" + name + ".json";
			std::ofstream file(filename);
			file << j.dump(4);

			Notifications::Show("Outfit Editor", "Saved outfit: " + name, NotificationType::Success);
		}
		catch (const std::exception& e)
		{
			Notifications::Show("Outfit Editor", "Failed to save outfit", NotificationType::Error);
		}
	}

	static bool LoadOutfitFromFile(const std::string& name)
	{
		try
		{
			std::string filename = GetSaveDirectory() + "/" + name;
			if (!filename.ends_with(".json"))
				filename += ".json";

			std::ifstream file(filename);
			if (!file.is_open())
				return false;

			nlohmann::json j;
			file >> j;

			OutfitData outfit;
			outfit.name = j.value("name", name);
			outfit.component_drawables = j.value("component_drawables", std::vector<int>(12, 0));
			outfit.component_textures = j.value("component_textures", std::vector<int>(12, 0));
			outfit.prop_slots = j.value("prop_slots", std::vector<int>{0, 1, 2, 6});
			outfit.prop_drawables = j.value("prop_drawables", std::vector<int>(4, 0));
			outfit.prop_textures = j.value("prop_textures", std::vector<int>(4, 0));

			ApplyOutfitData(outfit);
			Notifications::Show("Outfit Editor", "Loaded outfit: " + outfit.name, NotificationType::Success);
			return true;
		}
		catch (const std::exception& e)
		{
			Notifications::Show("Outfit Editor", "Failed to load outfit", NotificationType::Error);
			return false;
		}
	}

	static std::vector<std::string> GetSavedOutfits()
	{
		std::vector<std::string> outfits;
		try
		{
			for (const auto& entry : std::filesystem::directory_iterator(GetSaveDirectory()))
			{
				if (entry.path().extension() == ".json")
				{
					outfits.push_back(entry.path().stem().string());
				}
			}
		}
		catch (...)
		{
		}
		return outfits;
	}

	static bool DeleteOutfitFile(const std::string& name)
	{
		try
		{
			std::string filename = GetSaveDirectory() + "/" + name + ".json";
			bool result = std::filesystem::remove(filename);
			if (result)
			{
				Notifications::Show("Outfit Editor", "Deleted outfit: " + name, NotificationType::Success);
			}
			return result;
		}
		catch (...)
		{
			return false;
		}
	}

	// Helper function for underlined text
	static void TextUnderlined(const char* text)
	{
		ImGui::Text("%s", text);
		ImVec2 min = ImGui::GetItemRectMin();
		ImVec2 max = ImGui::GetItemRectMax();
		min.y = max.y;
		ImGui::GetWindowDrawList()->AddLine(min, max, ImGui::GetColorU32(ImGui::GetStyle().Colors[ImGuiCol_Text]));
	}

	static void TextUnderlinedAt(const char* text, float y)
	{
		auto old_cursor = ImGui::GetCursorPos();
		ImGui::SetCursorPosY(y);
		TextUnderlined(text);
		ImGui::SetCursorPos(old_cursor);
	}

	std::shared_ptr<Category> CreateOutfitsMenu()
	{
		auto category = std::make_shared<Category>("Outfit Editor");

		category->AddItem(std::make_shared<ImGuiItem>([] {
			if (!NativeInvoker::AreHandlersCached())
				return ImGui::TextDisabled("Natives not cached yet");

			auto ped = Self::GetPed();

			if (!ped)
				return ImGui::TextDisabled("Player ped not found");

			if (ImGui::BeginTabBar("OutfitEditorTabs", ImGuiTabBarFlags_None))
			{
				if (ImGui::BeginTabItem("Editor"))
				{
					// Create two columns layout
					const float windowWidth = ImGui::GetContentRegionAvail().x;
					const float columnWidth = windowWidth * 0.5f;
					const float inputWidth = 120.0f; // Minimal width for number input

					ImGui::Columns(2, "OutfitColumns", false);
					ImGui::SetColumnWidth(0, columnWidth);

					// Components section (Left column)

					float header_y = ImGui::GetCursorPosY();

					TextUnderlined("Components");
					const struct
					{
						const char* name;
						int slot;
					} componentSlots[] = {{"Top", 11}, {"Undershirt", 8}, {"Legs", 4}, {"Feet", 6}, {"Accessories", 7}, {"Bags", 5}, {"Mask", 1}, {"Gloves", 3}, {"Decals", 10}, {"Armor", 9}};

					bool first_iter = true;
					for (const auto& component : componentSlots)
					{
						ImGui::PushID(component.slot);

						int drawable, texture;
						GetOutfitSlot(component.slot, drawable, texture);

						ImGui::Text("%s", component.name);
						ImGui::SameLine();

						ImGui::SetCursorPosX(columnWidth - inputWidth * 2 - 10);

						ImGui::PushItemWidth(inputWidth);
						if (first_iter)
							TextUnderlinedAt("Drawable", header_y);
						if (ImGui::InputInt("##{}drawable", &drawable))
						{
							drawable = std::clamp(drawable, 0, GetMaxDrawable(component.slot) - 1);
							SetOutfitSlot(component.slot, drawable, texture);
						}
						ImGui::SameLine();
						if (first_iter)
					TextUnderlinedAt("Texture", header_y); // TODO: this heading is slightly misaligned and I'm not sure why (caused by the above SameLine?)
						if (ImGui::InputInt("##{}texture", &texture))
						{
							texture = std::clamp(texture, 0, GetMaxTexture(component.slot, drawable) - 1);
							SetOutfitSlot(component.slot, drawable, texture);
						}
						ImGui::PopItemWidth();
						ImGui::PopID();

						first_iter = false;
					}

					// Props section (Right column)
					ImGui::NextColumn();
					TextUnderlined("Props");

					const struct
					{
						const char* name;
						int slot;
					} propSlots[] = {{"Hats", 0}, {"Glasses", 1}, {"Ears", 2}, {"Watches", 6}};

					first_iter = true;
					for (const auto& prop : propSlots)
					{
						ImGui::PushID(prop.slot);

						int drawable, texture;
						GetPropSlot(prop.slot, drawable, texture);

						ImGui::Text("%s", prop.name);
						ImGui::SameLine();

						ImGui::SetCursorPosX(columnWidth + (columnWidth - inputWidth * 2 - 10));

						ImGui::PushItemWidth(inputWidth);
						if (first_iter)
							TextUnderlinedAt("Drawable", header_y);
						if (ImGui::InputInt("##pdrawable", &drawable))
						{
							drawable = std::clamp(drawable, 0, GetMaxPropDrawable(prop.slot) - 1);
							SetPropSlot(prop.slot, drawable, texture);
						}
						ImGui::SameLine();
						if (first_iter)
							TextUnderlinedAt("Texture", header_y);
						if (ImGui::InputInt("##ptexture", &texture))
						{
							texture = std::clamp(texture, 0, GetMaxPropTexture(prop.slot, drawable) - 1);
							SetPropSlot(prop.slot, drawable, texture);
						}
						ImGui::PopItemWidth();
						ImGui::PopID();

						first_iter = false;
					}

					ImGui::Columns(1);

					if (ImGui::Button("Randomize Outfit"))
					{
						std::random_device rd;
						std::mt19937 gen(rd());

				// Randomize components
						for (int i = 0; i < 12; ++i)
						{
							int maxDrawable = GetMaxDrawable(i);
							if (maxDrawable > 0)
							{
								int drawable = std::uniform_int_distribution<>(0, maxDrawable - 1)(gen);
								int maxTexture = GetMaxTexture(i, drawable);
								int texture = maxTexture > 0 ? std::uniform_int_distribution<>(0, maxTexture - 1)(gen) : 0;
								SetOutfitSlot(i, drawable, texture);
							}
						}

				// Randomize props
						for (int i : {0, 1, 2, 6, 7})
						{
							int maxDrawable = GetMaxPropDrawable(i);
							if (maxDrawable > 0)
							{
								int drawable = std::uniform_int_distribution<>(0, maxDrawable - 1)(gen);
								int maxTexture = GetMaxPropTexture(i, drawable);
								int texture = maxTexture > 0 ? std::uniform_int_distribution<>(0, maxTexture - 1)(gen) : 0;
								SetPropSlot(i, drawable, texture);
							}
						}
					}

					ImGui::EndTabItem();
				}

				if (ImGui::BeginTabItem("Save/Load"))
				{
					static char outfitName[64] = "";
					static int selectedOutfitIndex = -1;
					static std::vector<std::string> outfitsCache;

					// Refresh outfit list button
					if (ImGui::Button("Refresh List", ImVec2(150, 0)))
					{
						outfitsCache = GetSavedOutfits();
						if (selectedOutfitIndex >= (int)outfitsCache.size())
							selectedOutfitIndex = -1;
					}

					ImGui::SameLine();
					ImGui::TextDisabled("(Outfits saved in %%appdata%%/YimMenuV2/Outfits/)");

					ImGui::Spacing();
					ImGui::Separator();

					// Save Section
					ImGui::Text("Save Current Outfit");
					ImGui::Separator();
					ImGui::InputText("Outfit Name", outfitName, sizeof(outfitName));
					if (ImGui::Button("Save Outfit", ImVec2(200, 0)) && strlen(outfitName) > 0)
					{
						SaveOutfitToFile(outfitName);
						memset(outfitName, 0, sizeof(outfitName));
						outfitsCache = GetSavedOutfits(); // Refresh the list after saving
					}

					ImGui::Spacing();
					ImGui::Spacing();
					ImGui::Separator();

					// Load Section with Dropdown
					ImGui::Text("Load Saved Outfit");
					ImGui::Separator();

					// Refresh cache if empty
					if (outfitsCache.empty())
						outfitsCache = GetSavedOutfits();

					if (outfitsCache.empty())
					{
						ImGui::TextDisabled("No saved outfits found. Save an outfit first!");
					}
					else
					{
						// Dropdown Combo
						const char* preview = (selectedOutfitIndex >= 0 && selectedOutfitIndex < (int)outfitsCache.size()) ? outfitsCache[selectedOutfitIndex].c_str() : "Select an outfit...";

						if (ImGui::BeginCombo("##OutfitDropdown", preview))
						{
							for (int i = 0; i < (int)outfitsCache.size(); i++)
							{
								bool is_selected = (selectedOutfitIndex == i);
								if (ImGui::Selectable(outfitsCache[i].c_str(), is_selected))
								{
									selectedOutfitIndex = i;
								}
								if (is_selected)
									ImGui::SetItemDefaultFocus();
							}
							ImGui::EndCombo();
						}

						ImGui::Spacing();

						// Load button
						if (ImGui::Button("Load Selected Outfit", ImVec2(200, 0)) && selectedOutfitIndex >= 0)
						{
							LoadOutfitFromFile(outfitsCache[selectedOutfitIndex]);
						}

						ImGui::SameLine();

						// Delete button
						if (ImGui::Button("Delete Selected Outfit", ImVec2(200, 0)) && selectedOutfitIndex >= 0)
						{
							DeleteOutfitFile(outfitsCache[selectedOutfitIndex]);
							outfitsCache = GetSavedOutfits(); // Refresh after deletion
							if (selectedOutfitIndex >= (int)outfitsCache.size())
								selectedOutfitIndex = -1;
						}
					}

					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
		}));

		return category;
	}
}