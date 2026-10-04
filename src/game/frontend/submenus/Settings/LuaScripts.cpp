#include "LuaScripts.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/scripting/LuaManager.hpp"
#include "core/frontend/widgets/imgui_colors.h"
#include "core/filemgr/FileMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include <shellapi.h>

namespace YimMenu::Submenus
{
	static std::string GetScriptLabel(std::string_view path, bool disabled = false)
	{
		static const auto root = std::filesystem::canonical(FileMgr::GetProjectFolder("./scripts").Path());
		auto relative = std::filesystem::path(path).lexically_normal().lexically_relative(root);
		if (relative.empty() || *relative.begin() == "..")
			relative = std::filesystem::path(path).filename();
		if (disabled && *relative.begin() == "disabled")
			relative = relative.lexically_relative("disabled");
		return relative.generic_string();
	}

	static void DrawLoadedScript(std::shared_ptr<LuaScript>& script, std::shared_ptr<LuaScript>& selected_script)
	{
		auto label = GetScriptLabel(script->GetPath());
		if (script->GetLoadState() == LuaScript::LoadState::PAUSED)
			label += " (Paused)";
		ImGui::PushID(script->GetPath().data());
		if (ImGui::Selectable(label.c_str(), script == selected_script))
			selected_script = script;
		ImGui::PopID();
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("%s", script->GetLoadState() == LuaScript::LoadState::PAUSED ? "Paused. Select this script to resume it." : script->GetPath().data());
	}

	std::shared_ptr<Category> BuildLuaScriptsMenu()
	{
		auto menu = std::make_shared<Category>("Lua Scripts");

		static std::shared_ptr<LuaScript> selectedScript;

		menu->AddItem(std::make_unique<ImGuiItem>([] {
			ImGui::BeginGroup();
			const float height = 15 * ImGui::GetTextLineHeightWithSpacing();
			ImGui::TextUnformatted("Enabled");
			if (ImGui::BeginListBox("##enabledluascripts", {300.f, height}))
			{
				LuaManager::ForAllLoadedScripts([](std::shared_ptr<LuaScript>& script) {
					if (!LuaManager::IsIncludeScript(std::filesystem::path(script->GetPath())) && script->GetLoadState() != LuaScript::LoadState::UNLOADED)
						DrawLoadedScript(script, selectedScript);
				});
				ImGui::EndListBox();
			}
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::TextUnformatted("Disabled");
			if (ImGui::BeginListBox("##disabledluascripts", {300.f, height}))
			{
				static std::optional<std::string> loadingScript;

				ImGui::PushStyleColor(ImGuiCol_Text, ImGui::Colors::Gray.Value);
				LuaManager::ForAllUnloadedScripts([](LuaManager::UnloadedScript& script) {
					if (LuaManager::IsIncludeScript(std::filesystem::path(script.m_Path)))
						return;
					auto label = GetScriptLabel(script.m_Path, true);
					ImGui::PushID(script.m_Path.c_str());
					if (ImGui::Selectable(label.c_str(), false))
					{
						loadingScript = script.m_Path;
					}
					ImGui::PopID();

					if (ImGui::IsItemHovered())
					{
						ImGui::SetTooltip("Click to enable this script");
					}
				});
				ImGui::PopStyleColor();

				if (loadingScript)
				{
					LuaManager::LoadScript(*loadingScript);
					loadingScript = std::nullopt;
				}

				ImGui::EndListBox();
			}
			ImGui::EndGroup();

			if (ImGui::Button("Open Lua Scripts Folder"))
			{
				auto folder = std::filesystem::canonical(FileMgr::GetProjectFolder("./scripts").Path());
				auto result = ShellExecuteW(nullptr, L"open", folder.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
				if (reinterpret_cast<std::intptr_t>(result) <= 32)
					Notifications::Show("Lua Scripts", "Unable to open the scripts folder", NotificationType::Error);
			}

			ImGui::BeginGroup();
			if (selectedScript && (selectedScript->GetLoadState() == LuaScript::LoadState::UNLOADED || LuaManager::IsIncludeScript(std::filesystem::path(selectedScript->GetPath()))))
				selectedScript.reset();

			if (selectedScript)
			{
				auto label = GetScriptLabel(selectedScript->GetPath());
				ImGui::Text("%s", label.c_str());

				bool paused = selectedScript->GetLoadState() == LuaScript::LoadState::PAUSED;
				bool running = selectedScript->IsRunning();
				ImGui::BeginDisabled(!paused && !running);
				if (ImGui::Button(paused ? "Resume" : "Pause"))
				{
					FiberPool::Push([script = selectedScript, paused] {
						if (paused)
							script->Resume();
						else
							script->Pause();
					});
				}
				ImGui::EndDisabled();
				ImGui::SameLine();
				ImGui::BeginDisabled(!running);
				if (ImGui::Button("Reload"))
				{
					FiberPool::Push([script = selectedScript] {
						script->Reload();
					});
				}
				ImGui::SameLine();
				if (ImGui::Button("Disable"))
				{
					LuaManager::DisableScript(std::string(selectedScript->GetPath()));
				}
				ImGui::EndDisabled();
			}
			ImGui::EndGroup();
		}));

		return menu;
	}
}
