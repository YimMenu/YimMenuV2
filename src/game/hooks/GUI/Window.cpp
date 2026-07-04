#include "core/hooking/DetourHook.hpp"
#include "core/renderer/Renderer.hpp"
#include "game/hooks/Hooks.hpp"

namespace YimMenu::Hooks
{
	LRESULT Window::WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
	{
		if (g_Running)
		{
			if (Renderer::WndProc(hwnd, umsg, wparam, lparam))
			{
				// Block mouse button clicks when ImGui consumed them
				switch (umsg)
				{
				case WM_LBUTTONDOWN: case WM_LBUTTONUP:
				case WM_RBUTTONDOWN: case WM_RBUTTONUP:
				case WM_MBUTTONDOWN: case WM_MBUTTONUP:
				case WM_XBUTTONDOWN: case WM_XBUTTONUP:
					return TRUE;
				}
			}
		}

		return BaseHook::Get<Window::WndProc, DetourHook<WNDPROC>>()->Original()(hwnd, umsg, wparam, lparam);
	}
}