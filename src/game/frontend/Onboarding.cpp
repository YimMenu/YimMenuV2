#include "Onboarding.hpp"
#include "GUI.hpp"
#include "core/translation/Translation.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/BoolCommand.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/pointers/Pointers.hpp"
#include <shellapi.h>

namespace YimMenu
{
	static BoolCommand _OnboardingComplete{"$onboardingcomplete", "", ""};

	void ProcessOnboarding()
	{
		if (_OnboardingComplete.GetState())
			return;

		static bool ensure_popup_open = [] {
			ImGui::OpenPopup(Translation::Tr("IMPORTANT! PLEASE READ!").c_str());
			GUI::SetOnboarding(true);
			return true;
		}();

		const auto window_size = ImVec2{700, 500};
		const auto window_position = ImVec2{(*Pointers.ScreenResX - window_size.x) / 2, (*Pointers.ScreenResY - window_size.y) / 2};

		ImGui::SetNextWindowSize(window_size, ImGuiCond_Once);
		ImGui::SetNextWindowPos(window_position, ImGuiCond_Once);

		if (ImGui::BeginPopupModal(Translation::Tr("IMPORTANT! PLEASE READ!").c_str(), nullptr, ImGuiWindowFlags_NoSavedSettings))
		{
			ImGui::TextWrapped("%s",
			    Translation::Tr(
			        "Welcome to YimMenuV2! You can press INSERT or Ctrl+\\ to open the menu. With the introduction of BattlEye, the ability to join and stay in public sessions has been severely limited. "
			        "You have an option to play only with other YimMenu users, or you can choose to connect to regular BattlEye-protected sessions. "
			        "You will automatically be kicked out of regular sessions in under three minutes, and you may be temporarily blacklisted from "
			        "joining for up to two days, even after re-enabling BattlEye")
			        .c_str());
			static int value = 0;
			ImGui::RadioButton(Translation::TrLabel("Play with YimMenu users").c_str(), &value, 0);
			ImGui::SameLine();
			ImGui::RadioButton(Translation::TrLabel("Play with everyone (Broken!)").c_str(), &value, 1);
			ImGui::TextWrapped("%s",
			    Translation::Tr(
			        "You can always change your choice by toggling Network > Spoofing > Join YimMenu-only Sessions. Our official repository is at "
			        "https://github.com/YimMenu/YimMenuV2. Make sure to only download the menu from GitHub to avoid malware. "
			        "You can use the repository to report bugs, suggest features, and contribute by making pull requests. We also have a "
			        "Matrix server that can be found at https://matrix.to/#/#yimmenu:matrix.org for faster communication with developers "
			        "and other users. Matrix is a free and open source alternative to Discord, and creating an account is safe and easy")
			        .c_str());
			if (ImGui::Button(Translation::TrLabel("Open GitHub").c_str()))
			{
				ShellExecuteA(NULL, "open", "https://github.com/YimMenu/YimMenuV2", NULL, NULL, SW_SHOWNORMAL);
			}
			ImGui::SameLine();
			if (ImGui::Button(Translation::TrLabel("Open Matrix server").c_str()))
			{
				ShellExecuteA(NULL, "open", "https://matrix.to/#/#yimmenu:matrix.org", NULL, NULL, SW_SHOWNORMAL);
			}
			ImGui::TextWrapped("%s",
			    Translation::Tr("Check for updates reguarly; we publish new builds every night. But most importantly, mess around and have fun with YimMenu!").c_str());
			if (ImGui::Button(Translation::TrLabel("Close").c_str()))
			{
				Commands::GetCommand<BoolCommand>("cheaterpool"_J)->SetState(!value);
				_OnboardingComplete.SetState(true);
				GUI::SetOnboarding(false);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
}