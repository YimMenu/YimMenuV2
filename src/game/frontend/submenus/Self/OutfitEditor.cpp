#include "OutfitEditor.hpp"
#include "game/frontend/items/Items.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/backend/Outfit.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "core/util/Strings.hpp"
#include "misc/cpp/imgui_stdlib.h"

namespace YimMenu
{
	class OutfitEditorMenu
	{
		Outfit::OutfitComponents components{};
		Outfit::OutfitProps props{};
		std::vector<std::string> folders{}, files{};
		std::string folder{}, file{};
		char outfitName[64]{}, newFolder[50]{};

	public:
		// refreshes the outfit editor data to current ped outfit
		void RefreshStats()
		{
			auto ped = Self::GetPed().GetHandle();
			for (auto& t : components.items)
			{
				auto& item = t.second;
				item.drawable_id = PED::GET_PED_DRAWABLE_VARIATION(ped, t.first);
				item.drawable_id_max = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, t.first) - 1;
				item.texture_id = PED::GET_PED_TEXTURE_VARIATION(ped, t.first);
				item.texture_id_max = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, t.first, item.drawable_id) - 1;
			}

			for (auto& t : props.items)
			{
				auto& item = t.second;
				item.drawable_id = PED::GET_PED_PROP_INDEX(ped, t.first, 0);
				item.drawable_id_max = PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(ped, t.first) - 1;
				item.texture_id = PED::GET_PED_PROP_TEXTURE_INDEX(ped, t.first);
				item.texture_id_max = PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(ped, t.first, item.drawable_id) - 1;
			}
		}

		void RenderComponents()
		{
			ImGui::BeginGroup();
			for (auto& t : components.items)
			{
				auto& item = t.second;
				ImGui::SetNextItemWidth(120);
				if (ImGui::InputInt(std::format("{} [0,{}]##1", item.label, item.drawable_id_max).c_str(), &item.drawable_id))
				{
					Outfit::OutfitEditor::CheckBoundsDrawable(item, 0);
					FiberPool::Push([id = t.first, item, this] {
						PED::SET_PED_COMPONENT_VARIATION(Self::GetPed().GetHandle(), id, item.drawable_id, 0, PED::GET_PED_PALETTE_VARIATION(Self::GetPed().GetHandle(), id));
						RefreshStats();
					});
				}
			}
			ImGui::EndGroup();
		}

		void RenderComponentsTextures()
		{
			ImGui::BeginGroup();
			for (auto& t : components.items)
			{
				auto& item = t.second;
				ImGui::SetNextItemWidth(120);
				if (ImGui::InputInt(std::format("{} TEX [0,{}]##2", item.label, item.texture_id_max).c_str(), &item.texture_id))
				{
					Outfit::OutfitEditor::CheckBoundsTexture(item, 0);
					FiberPool::Push([id = t.first, item, this] {
						PED::SET_PED_COMPONENT_VARIATION(Self::GetPed().GetHandle(), id, item.drawable_id, item.texture_id, PED::GET_PED_PALETTE_VARIATION(Self::GetPed().GetHandle(), id));
						RefreshStats();
					});
				}
			}
			ImGui::EndGroup();
		}

		void RenderProps()
		{
			for (auto& t : props.items)
			{
				auto& item = t.second;
				ImGui::SetNextItemWidth(120);
				if (ImGui::InputInt(std::format("{} [0,{}]##3", item.label, item.drawable_id_max).c_str(), &item.drawable_id))
				{
					Outfit::OutfitEditor::CheckBoundsDrawable(item, -1);
					FiberPool::Push([id = t.first, item, this] {
						if (item.drawable_id == -1)
							PED::CLEAR_PED_PROP(Self::GetPed().GetHandle(), id, 1);
						else
							PED::SET_PED_PROP_INDEX(Self::GetPed().GetHandle(), id, item.drawable_id, 0, TRUE, 0);
						RefreshStats();
					});
				}
			}
		}

		void RenderPropsTextures()
		{
			for (auto& t : props.items)
			{
				auto& item = t.second;
				ImGui::SetNextItemWidth(120);
				if (ImGui::InputInt(std::format("{} TEX [0,{}]##4", item.label, item.texture_id_max).c_str(), &item.texture_id))
				{
					Outfit::OutfitEditor::CheckBoundsTexture(item, -1);
					FiberPool::Push([id = t.first, item, this] {
						PED::SET_PED_PROP_INDEX(Self::GetPed().GetHandle(), id, item.drawable_id, item.texture_id, TRUE, 0);
						RefreshStats();
					});
				}
			}
		}

		void RenderOutfitList()
		{
			ImGui::BeginGroup();
			{
				// folders
				ImGui::SetNextItemWidth(300.f);
				if (ImGui::BeginCombo("", folder.empty() ? "Root" : folder.c_str()))
				{
					if (ImGui::Selectable("Root", folder == ""))
					{
						folder.clear();
						FiberPool::Push([this] {
							Outfit::OutfitEditor::RefreshList(folder, folders, files);
						});
					}

					for (std::string folderName : folders)
						if (ImGui::Selectable(folderName.c_str(), folder == folderName))
						{
							folder = folderName;
							FiberPool::Push([this] {
								Outfit::OutfitEditor::RefreshList(folder, folders, files);
							});
						}

					ImGui::EndCombo();
				}

				// files
				static std::string search;
				ImGui::SetNextItemWidth(300);
				if (ImGui::InputTextWithHint("###outfitname", "Search", &search))
					std::transform(search.begin(), search.end(), search.begin(), tolower);
				if (ImGui::BeginListBox("##saved_outfits", ImVec2(300, 300)))
				{
					for (const auto& pair : files)
					{
						std::string pair_lower = pair;
						std::transform(pair_lower.begin(), pair_lower.end(), pair_lower.begin(), tolower);
						if (pair_lower.contains(search))
						{
							auto fileName = pair.c_str();
							if (ImGui::Selectable(fileName, file == pair, ImGuiSelectableFlags_AllowItemOverlap))
								file = pair;
						}
					}
					ImGui::EndListBox();
				}
			}
			ImGui::EndGroup();
		}

		void RenderSaveButton(bool saveToNewFolder)
		{
			if (ImGui::Button("Save Outfit"))
				FiberPool::Push([saveToNewFolder, this] {
					std::string fileName = TrimString(outfitName);
					strcpy(outfitName, "");

					if (!fileName.size())
					{
						Notifications::Show("Outfit", "Filename empty!", NotificationType::Warning);
						return;
					}

					Outfit::OutfitEditor::SaveOutfit(fileName, folder);

					if (saveToNewFolder)
					{
						folder = newFolder; // set current folder to newly created folder
						strcpy(newFolder, "");
					}

					Outfit::OutfitEditor::RefreshList(folder, folders, files);
				});
		};

		void RenderOutfitListControls()
		{
			ImGui::BeginGroup();
			{
				if (ImGui::Button("Refresh list"))
					FiberPool::Push([this] {
						Outfit::OutfitEditor::RefreshList(folder, folders, files);
					});
				ImGui::Spacing();
				static bool applyHair = false;
				ImGui::Checkbox("Apply hair", &applyHair);
				ImGui::Spacing();
				if (ImGui::Button("Apply Selected Outfit"))
					FiberPool::Push([this] {
						Outfit::OutfitEditor::ApplyOutfitFromJson(folder, file, applyHair);
						applyHair = false; // reset everytime
						RefreshStats();
					});

				ImGui::Spacing();

				// save outfit
				ImGui::Text("Outfit Name");
				ImGui::SameLine();
				ImGui::SetNextItemWidth(250);
				ImGui::InputText("##filename", outfitName, IM_ARRAYSIZE(outfitName));

				if (folder.empty())
				{
					ImGui::Text("Folder Name");
					ImGui::SameLine();
					ImGui::SetNextItemWidth(250);
					ImGui::InputText("##foldername", newFolder, IM_ARRAYSIZE(newFolder));
					RenderSaveButton(true);
				}
				else
					RenderSaveButton(false);
			}
			ImGui::EndGroup();
		}
	};

	std::shared_ptr<Category> CreateOutfitsMenu()
	{
		static OutfitEditorMenu editor{};
		auto category = std::make_shared<Category>("Outfit Editor");

		category->AddItem(std::make_shared<ImGuiItem>([] {
			if (ImGui::Button("Refresh Stats"))
				FiberPool::Push([] {
					editor.RefreshStats();
				});
			ImGui::SameLine();
			if (ImGui::Button("Randomize Outfit"))
				FiberPool::Push([] {
					Self::GetPed().RandomizeOutfit2();
				});

			editor.RenderComponents();
			ImGui::SameLine();
			editor.RenderComponentsTextures();
			ImGui::SameLine();
			ImGui::BeginGroup();
			{
				editor.RenderProps();
				ImGui::Spacing();
				editor.RenderPropsTextures();
			}
			ImGui::EndGroup();

			ImGui::Spacing();

			editor.RenderOutfitList();
			ImGui::SameLine();
			editor.RenderOutfitListControls();
		}));

		return category;
	}
}
