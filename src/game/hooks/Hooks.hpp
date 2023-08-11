#pragma once
#include <d3d11.h>

namespace YimMenu
{
	namespace SwapChain
	{
		constexpr auto VMTPresentIdx       = 8;
		constexpr auto VMTResizeBuffersIdx = 13;
		constexpr auto VMTSize             = 19;
		extern HRESULT Present(IDXGISwapChain* that, UINT syncInterval, UINT flags);
		extern HRESULT ResizeBuffers(IDXGISwapChain* that, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
	}

	namespace Window
	{
		extern LRESULT WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
	}
}