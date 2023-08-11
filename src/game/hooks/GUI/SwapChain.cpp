#include "core/hooking/VMTHook.hpp"
#include "core/renderer/Renderer.hpp"
#include "game/hooks/Hooks.hpp"

namespace YimMenu
{
	HRESULT SwapChain::Present(IDXGISwapChain* that, UINT syncInterval, UINT flags)
	{
		if (g_Running)
		{
			Renderer::OnPresent();
		}
		return BaseHook::Get<SwapChain::Present, VMTHook<SwapChain::VMTSize>>()->Original<decltype(&Present)>(SwapChain::VMTPresentIdx)(that, syncInterval, flags);
	}

	HRESULT SwapChain::ResizeBuffers(IDXGISwapChain* that, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
	{
		if (g_Running)
		{
			Renderer::PreResize();
			const auto result = BaseHook::Get<SwapChain::Present, VMTHook<SwapChain::VMTSize>>()->Original<decltype(&ResizeBuffers)>(SwapChain::VMTResizeBuffersIdx)(that, bufferCount, width, height, newFormat, swapChainFlags);
			Renderer::PostResize();
			return result;
		}
		return BaseHook::Get<SwapChain::Present, VMTHook<SwapChain::VMTSize>>()->Original<decltype(&ResizeBuffers)>(SwapChain::VMTResizeBuffersIdx)(that, bufferCount, width, height, newFormat, swapChainFlags);
	}
}