#include "Hooking.hpp"

#include "BaseHook.hpp"
#include "DetourHook.hpp"
#include "VMTHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu
{
	Hooking::Hooking()
	{
		BaseHook::Add<Window::WndProc>(new DetourHook<void*>("WndProc", reinterpret_cast<void*>(Pointers.WndProc), reinterpret_cast<void*>(Window::WndProc)));

		auto swapchain = new VMTHook<SwapChain::VMTSize>("SwapChain", *Pointers.SwapChain);
		swapchain->Hook(SwapChain::VMTPresentIdx, SwapChain::Present);
		swapchain->Hook(SwapChain::VMTResizeBuffersIdx, SwapChain::ResizeBuffers);
		BaseHook::Add<SwapChain::Present>(swapchain);
	}

	Hooking::~Hooking()
	{
		DestroyImpl();
	}

	bool Hooking::Init()
	{
		return GetInstance().InitImpl();
	}

	void Hooking::Destroy()
	{
		GetInstance().DestroyImpl();
	}

	bool Hooking::InitImpl()
	{
		BaseHook::EnableAll();
		m_MinHook.ApplyQueued();

		return true;
	}

	void Hooking::DestroyImpl()
	{
		BaseHook::DisableAll();
		m_MinHook.ApplyQueued();

		for (auto it : BaseHook::Hooks())
		{
			delete it;
		}
		BaseHook::Hooks().clear();
	}
}