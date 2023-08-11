#include "core/hooking/DetourHook.hpp"
#include "core/renderer/Renderer.hpp"
#include "game/hooks/Hooks.hpp"


namespace YimMenu
{
	LRESULT Window::WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
	{
		if (g_Running)
			Renderer::WndProc(hwnd, umsg, wparam, lparam);

		if (umsg == WM_KEYUP && wparam == VK_DELETE) // fallback to unload
			g_Running = false;

		return BaseHook::Get<Window::WndProc, DetourHook<WNDPROC>>()->Original()(hwnd, umsg, wparam, lparam);
	}
}