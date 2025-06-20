#include "Globals.hpp"
#include "DrawVariable.hpp"

// TODO: name compares are expensive, but this is way better than the old impl that reads the json file every frame

namespace YimMenu::Submenus
{
	static void SaveGlobal(SavedGlobal& globalObj)
	{
		for (auto& global : SavedVariables::GetSavedGlobals())
		{
			if (global.name == globalObj.name)
			{
				global = globalObj;
				SavedVariables::Save();
				return;
			}
		}

		SavedVariables::GetSavedGlobals().push_back(globalObj);
		SavedVariables::Save();
	}

	static void DeleteGlobal(SavedGlobal& globalObj)
	{
		std::erase_if(SavedVariables::GetSavedGlobals(), [&](SavedGlobal& g) {
			return g.name == globalObj.name;
		});
		SavedVariables::Save();
	}

	std::shared_ptr<Category> BuildGlobalsMenu()
	{
		auto globals = std::make_unique<Category>("Globals");

		auto editor = std::make_unique<Group>("Editor");
		auto saved = std::make_unique<Group>("Saved");

		static bool ensureVarsLoaded = ([] {
			SavedVariables::Init();
			return true;
		})();

		static char globalName[255]{};
		static SavedGlobal curGlobal{};

		editor->AddItem(std::make_unique<ImGuiItem>([] {
			DrawSavedVariable(curGlobal);
			DrawSavedVariableEdit(curGlobal, curGlobal.Read());
		}));

		saved->AddItem(std::make_unique<ImGuiItem>([] {
			if (ImGui::BeginListBox("##savedglobals", ImVec2(200, 200)))
			{
				for (auto& var : SavedVariables::GetSavedGlobals())
				{
					if (ImGui::Selectable(var.name.c_str(), var.name == curGlobal.name))
					{
						curGlobal = var;
						strncpy(globalName, var.name.c_str(), sizeof(globalName));
					}
				}
				ImGui::EndListBox();
			}
			ImGui::SameLine();
			if (ImGui::BeginListBox("##globalvalues", ImVec2(200, 200)))
			{
				for (auto& var : SavedVariables::GetSavedGlobals())
				{
					ImGui::PushID(var.name.c_str());
					DrawSavedVariablePreview(var, var.Read());
					ImGui::PopID();
				}
				ImGui::EndListBox();
			}

			ImGui::BeginGroup();

			ImGui::SetNextItemWidth(200.f);
			ImGui::InputTextWithHint("##global_name", "Name", globalName, sizeof(globalName));
			ImGui::SameLine();
			if (ImGui::Button("Save"))
			{
				curGlobal.name = globalName;
				SaveGlobal(curGlobal);
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete"))
			{
				curGlobal.name = globalName;
				DeleteGlobal(curGlobal);
				curGlobal = SavedGlobal();
			}

			ImGui::EndGroup();
		}));

		globals->AddItem(std::move(editor));
		globals->AddItem(std::move(saved));
		return globals;
	}
}