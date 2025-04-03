#include "Menu.hpp"

#include "core/commands/Commands.hpp"
#include "core/frontend/manager/UIManager.hpp"
#include "core/renderer/Renderer.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/frontend/fonts/Fonts.hpp"
#include "game/pointers/Pointers.hpp"
#include "submenus/Self.hpp"
#include "submenus/Teleport.hpp"
#include "submenus/Network.hpp"
#include "submenus/Players.hpp"
#include "submenus/Recovery.hpp"
#include "submenus/Settings.hpp"
#include "submenus/Debug.hpp"
#include "submenus/World.hpp"

namespace YimMenu
{
	void Menu::Init()
	{
		// Arguably the only place this file should be edited at for more menus
		UIManager::AddSubmenu(std::make_shared<Submenus::Self>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Teleport>());
		UIManager::AddSubmenu(std::make_shared<Submenus::World>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Network>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Players>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Recovery>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Settings>());
		UIManager::AddSubmenu(std::make_shared<Submenus::Debug>());

		Renderer::AddRendererCallBack(
		    [&] {
			    if (!GUI::IsOpen())
				    return;

			    ImGui::PushFont(Menu::Font::g_DefaultFont);
			    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImU32(ImColor(15, 15, 15)));

			    ImGui::SetNextWindowSize(ImVec2((*Pointers.ScreenResX / 2.5), (*Pointers.ScreenResY / 2.5)), ImGuiCond_Once);
			    if (ImGui::Begin("YimMenuV2", nullptr, ImGuiWindowFlags_NoDecoration))
			    {
				    //ImGui::BeginDisabled(*Pointers.IsSessionStarted);
				    if (ImGui::Button("Unload", ImVec2(120, 0)))
				    {
					    if (true)
					    {
						    FiberPool::Push([] {
							    Commands::Shutdown();
							    g_Running = false;
						    });
					    }
					    else
					    {
						    g_Running = false;
					    }
				    }
				    //ImGui::EndDisabled();

				    UIManager::Draw();
			    }
			    ImGui::End();

			    ImGui::PopStyleColor();
			    ImGui::PopFont();
		    },
		    -1);
	}

	void Menu::SetupStyle()
	{
		ImGuiStyle& style = ImGui::GetStyle();

		// Text colors
		style.Colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.70f, 1.00f);

		// Window backgrounds
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.08f, 0.15f, 1.00f);  // Dark blue background
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.10f, 0.18f, 1.00f);   // Slightly lighter blue
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.05f, 0.06f, 0.12f, 0.95f);   // Darker blue

		// Borders and frames
		style.Colors[ImGuiCol_Border] = ImVec4(0.20f, 0.25f, 0.39f, 0.25f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.15f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.25f, 0.40f, 1.00f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.30f, 0.47f, 1.00f);

		// Buttons
		style.Colors[ImGuiCol_Button] = ImVec4(0.15f, 0.20f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 0.25f, 0.45f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 0.30f, 0.55f, 1.00f);

		// Title bars
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.10f, 0.18f, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.12f, 0.22f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.07f, 0.15f, 1.00f);

		// Tabs
		style.Colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.20f, 0.35f, 0.85f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.20f, 0.25f, 0.45f, 0.85f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.25f, 0.30f, 0.55f, 1.00f);

		// Headers
		style.Colors[ImGuiCol_Header] = ImVec4(0.15f, 0.20f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.20f, 0.25f, 0.45f, 1.00f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.30f, 0.55f, 1.00f);

		// Plots
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.50f, 0.80f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.50f, 0.60f, 0.90f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.50f, 0.80f, 1.00f);

		style.GrabRounding = style.FrameRounding = style.ChildRounding = style.WindowRounding = 8.0f;
	}

	void Menu::SetupFonts()
	{
		auto& IO = ImGui::GetIO();
		ImFontConfig FontCfg{};
		FontCfg.FontDataOwnedByAtlas = false;

		Menu::Font::g_DefaultFont = IO.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Fonts::MainFont), sizeof(Fonts::MainFont), Menu::Font::g_DefaultFontSize, &FontCfg);
		Menu::Font::g_OptionsFont = IO.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Fonts::MainFont), sizeof(Fonts::MainFont), Menu::Font::g_OptionsFontSize, &FontCfg);
		Menu::Font::g_ChildTitleFont = IO.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Fonts::MainFont), sizeof(Fonts::MainFont), Menu::Font::g_ChildTitleFontSize, &FontCfg);
		Menu::Font::g_ChatFont = IO.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Fonts::MainFont), sizeof(Fonts::MainFont), Menu::Font::g_ChatFontSize, &FontCfg);
		Menu::Font::g_OverlayFont = IO.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Fonts::MainFont), sizeof(Fonts::MainFont), Menu::Font::g_OverlayFontSize, &FontCfg);
		UIManager::SetOptionsFont(Menu::Font::g_OptionsFont);
	}
}
