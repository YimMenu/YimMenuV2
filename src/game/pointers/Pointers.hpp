#pragma once
#include <d3d11.h>
#include <script/scrNativeHandler.hpp>
#include <windows.h>

namespace YimMenu
{
	namespace Functions
	{
		using GetNativeHandler = rage::scrNativeHandler (*)(void* registration_table, rage::scrNativeHash hash);
		using FixVectors       = void (*)(rage::scrNativeCallContext* call_ctx);
	}

	struct PointerData
	{
		IDXGISwapChain** SwapChain;
		HWND Hwnd;
		WNDPROC WndProc;
		std::int64_t** ScriptGlobals;
		void* NativeRegistrationTable;
		Functions::GetNativeHandler GetNativeHandler;
		Functions::FixVectors FixVectors;
	};

	struct Pointers : PointerData
	{
		bool Init();
	};

	inline YimMenu::Pointers Pointers;
}