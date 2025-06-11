#include "Locals.hpp"
#include "DrawVariable.hpp"
#include "game/gta/Scripts.hpp"
#include "types/script/scrThread.hpp"

namespace YimMenu::Submenus
{
	static void SaveLocal(SavedLocal& localObj)
	{
		for (auto& local : SavedVariables::GetSavedLocals())
		{
			if (local.name == localObj.name && local.script == localObj.script)
			{
				local = localObj;
				SavedVariables::Save();
				return;
			}
		}

		SavedVariables::GetSavedLocals().push_back(localObj);
		SavedVariables::Save();
	}

	static void DeleteLocal(SavedLocal& localObj)
	{
		std::erase_if(SavedVariables::GetSavedLocals(), [&](SavedLocal& g) {
			return g.name == localObj.name && g.script == localObj.script;
		});
		SavedVariables::Save();
	}

	std::shared_ptr<Category> BuildLocalsMenu()
	{
		auto locals = std::make_unique<Category>("Locals");

		auto editor = std::make_unique<Group>("Editor");
		auto saved = std::make_unique<Group>("Saved");

		static bool ensureVarsLoaded = ([] {
			SavedVariables::Init();
			return true;
		})();

		static char scriptName[255]{};
		static char localName[255]{};
		static SavedLocal curLocal{};
		static rage::scrThread* curThread = nullptr;

		editor->AddItem(std::make_unique<ImGuiItem>([] {
			ImGui::SetNextItemWidth(200.f);
			ImGui::InputText("Script", scriptName, sizeof(scriptName));

			curThread = Scripts::FindScriptThread(Joaat(scriptName));
			if (!curThread)
				return ImGui::TextDisabled("Invalid");

			DrawSavedVariable(curLocal);
			DrawSavedVariableEdit(curLocal, curLocal.Read(curThread));
		}));

		saved->AddItem(std::make_unique<ImGuiItem>([] {
			if (!curThread)
				return ImGui::TextDisabled("Invalid");

			auto scriptIdf = curThread->m_ScriptHash;
			if (scriptIdf != curLocal.script)
			{
				curLocal = SavedLocal();
				curLocal.script = scriptIdf;
			}

			if (ImGui::BeginListBox("##savedlocals", ImVec2(200, 200)))
			{
				for (auto& var : SavedVariables::GetSavedLocals())
				{
					if (var.script != scriptIdf)
						continue;

					if (ImGui::Selectable(var.name.c_str(), var.name == curLocal.name))
					{
						curLocal = var;
						strncpy(localName, var.name.c_str(), sizeof(localName));
					}
				}
				ImGui::EndListBox();
			}
			ImGui::SameLine();
			if (ImGui::BeginListBox("##localvalues", ImVec2(200, 200)))
			{
				for (auto& var : SavedVariables::GetSavedLocals())
				{
					if (var.script != scriptIdf)
						continue;

					DrawSavedVariablePreview(var, var.Read(curThread));
				}
				ImGui::EndListBox();
			}

			ImGui::BeginGroup();

			ImGui::SetNextItemWidth(200.f);
			ImGui::InputText("##localname", localName, sizeof(localName));
			ImGui::SameLine();
			if (ImGui::Button("Save"))
			{
				curLocal.name = localName;
				SaveLocal(curLocal);
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete"))
			{
				curLocal.name = localName;
				DeleteLocal(curLocal);
				curLocal = SavedLocal();
			}

			ImGui::EndGroup();
		}));

		locals->AddItem(std::move(editor));
		locals->AddItem(std::move(saved));
		return locals;
	}
}