#include "core/frontend/manager/UIManager.hpp"
#include "GUI.hpp"
#include "Menu.hpp"
#include "ESP.hpp"
#include "Overlay.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/renderer/Renderer.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/frontend/ChatDisplay.hpp"
#include "game/gta/Natives.hpp"
#include "types/pad/ControllerInputs.hpp"

namespace YimMenu
{
	GUI::GUI() :
	    m_IsOpen(false)
	{
		Menu::SetupFonts();
		Menu::SetupStyle();
		Menu::Init();

		Renderer::AddWindowProcedureCallback([this](HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			GUI::WndProc(hwnd, msg, wparam, lparam);
		});

		Renderer::AddRendererCallBack(
		    [&] {
			    Notifications::Draw();
		    },
		    -2);
		Renderer::AddRendererCallBack(
		    [&] {
			    ESP::Draw();
		    },
		    -3);
		Renderer::AddRendererCallBack(
		    [&] {
			    ChatDisplay::Draw();
		    },
		    -5);
		Renderer::AddRendererCallBack(
		    [&] {
			    Overlay::Draw();
		    },
		    -6);

		Renderer::SetSafeToRender();
	}

	GUI::~GUI()
	{
	}

	void GUI::ToggleMouse()
	{
		auto& io = ImGui::GetIO();
		io.MouseDrawCursor = GUI::IsOpen() || GUI::IsOnboarding();
		GUI::IsOpen() || GUI::IsOnboarding() 
			? io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse :
			  io.ConfigFlags |= ImGuiConfigFlags_NoMouse;
	}

	void GUI::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (msg == WM_KEYUP 
			&& (wparam == VK_INSERT || (wparam == VK_OEM_5 && (GetKeyState(VK_CONTROL) & 0x8000) != 0)))
		{
			// Persist and restore the cursor position between menu instances
			static POINT CursorCoords{};
			if (m_IsOpen)
			{
				GetCursorPos(&CursorCoords);
			}
			else if (CursorCoords.x + CursorCoords.y)
			{
				SetCursorPos(CursorCoords.x, CursorCoords.y);
			}
			if (!GUI::IsOnboarding())
				Toggle();
			ToggleMouse(); 
		}
	}
	
	void GUI::SetOnboardingImpl(bool state)
	{
		m_Onboarding = state;
		ToggleMouse();
	}

	void GUI::RunScriptImpl()
	{
		while (g_Running)
		{
			if (GUI::IsOpen())
			{
				if (UIManager::ShowingContentWindow())
				{
					if (GUI::IsUsingKeyboard() && PAD::IS_USING_KEYBOARD_AND_MOUSE(0))
					{
						PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
					}
					else
					{
						static constexpr ControllerInputs controls[] = {ControllerInputs::INPUT_LOOK_LR, ControllerInputs::INPUT_LOOK_UD, ControllerInputs::INPUT_ATTACK, ControllerInputs::INPUT_AIM, ControllerInputs::INPUT_DUCK, ControllerInputs::INPUT_SELECT_WEAPON, ControllerInputs::INPUT_VEH_AIM, ControllerInputs::INPUT_VEH_ATTACK, ControllerInputs::INPUT_VEH_ATTACK2, ControllerInputs::INPUT_VEH_NEXT_RADIO, ControllerInputs::INPUT_VEH_PASSENGER_AIM, ControllerInputs::INPUT_VEH_PASSENGER_ATTACK, ControllerInputs::INPUT_VEH_SELECT_NEXT_WEAPON, ControllerInputs::INPUT_VEH_SELECT_PREV_WEAPON, ControllerInputs::INPUT_VEH_MOUSE_CONTROL_OVERRIDE, ControllerInputs::INPUT_MELEE_ATTACK_ALTERNATE, ControllerInputs::INPUT_FRONTEND_Y, ControllerInputs::INPUT_ATTACK2, ControllerInputs::INPUT_PREV_WEAPON, ControllerInputs::INPUT_NEXT_WEAPON, ControllerInputs::INPUT_VEH_DRIVE_LOOK, ControllerInputs::INPUT_VEH_DRIVE_LOOK2};

						for (const auto& control : controls)
							PAD::DISABLE_CONTROL_ACTION(0, static_cast<int>(control), true);
					}
				}
			}

			ScriptMgr::Yield();
		}
	}
}