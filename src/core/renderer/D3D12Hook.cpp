#include "D3D12Hook.hpp"

namespace YimMenu
{
    static thread_local bool g_InsideCreateSwapchain = false;

    bool D3D12Hook::RawVtablePatch::Install(void** vtable, size_t index, void* newFn)
    {
        if (!vtable)
            return false;

        if (Installed)
            return true;

        Slot = &vtable[index];
        OriginalFn = *Slot;

        DWORD oldProtect{};
        if (!VirtualProtect(Slot, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect)) // we still need this in case the menu is injected very early
            return false;

        *Slot = newFn;

        VirtualProtect(Slot, sizeof(void*), oldProtect, &oldProtect);

        Installed = true;
        return true;
    }

    void D3D12Hook::RawVtablePatch::Uninstall()
    {
        if (!Installed || !Slot)
            return;

        DWORD oldProtect{};
        if (VirtualProtect(Slot, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect))
        {
            *Slot = OriginalFn;
            VirtualProtect(Slot, sizeof(void*), oldProtect, &oldProtect);
        }

        Installed = false;
        Slot = nullptr;
        OriginalFn = nullptr;
    }

    bool D3D12Hook::InitImpl()
    {
        std::scoped_lock hookLock{m_HookMutex};

        // SocialClubD3D12Renderer.dll's detours only fire on CreateSwapChain calls, not on
        // factory creation, so this shouldn't break SC's swapchain
        if (!m_FactoryVtable)
        {
            auto dxgiModule = LoadLibraryA("dxgi.dll");
            if (!dxgiModule)
            {
                LOGF(FATAL, "Failed to load dxgi.dll.");
                return false;
            }

            auto createDxgiFactory = reinterpret_cast<decltype(CreateDXGIFactory)*>(GetProcAddress(dxgiModule, "CreateDXGIFactory"));
            if (!createDxgiFactory)
            {
                LOGF(FATAL, "Failed to resolve CreateDXGIFactory.");
                return false;
            }

            IDXGIFactory4* factory = nullptr;
            if (FAILED(createDxgiFactory(IID_PPV_ARGS(&factory))))
            {
                LOGF(FATAL, "Failed to create DXGI factory.");
                return false;
            }

            m_FactoryVtable = *reinterpret_cast<void***>(factory);
            factory->Release();
        }

        // no dummy swapchain created, so SC's detour never fires
        if (!m_SwapchainVtable)
        {
            if (!Pointers.SwapChain || !*Pointers.SwapChain)
            {
                LOGF(FATAL, "SwapChain pointer is not yet valid.");
                return false;
            }

            m_SwapchainVtable = *reinterpret_cast<void***>(*Pointers.SwapChain);
        }

        InstallHooks();

        if (!m_Hooked)
            return false;

        LOGF(INFO, "D3D12 Hook initialized.");
        return true;
    }

    void D3D12Hook::DestroyImpl(bool unloading)
    {
        std::scoped_lock hookLock{m_HookMutex};

        if (unloading)
        {
            if (m_SwapchainVmt && m_SwapChain)
                m_SwapchainVmt->Disable();

            m_CreateSwapchainForHwndPatch.Uninstall();
        }

        // Without unloading the factory patch stays installed on purpose
        TeardownSwapchainHook();
        m_Hooked = false;
    }

    void D3D12Hook::TeardownSwapchainHook()
    {
        m_PresentPatch.Uninstall();
        m_CommandQueue.Reset();
        m_SwapChain = nullptr;
        m_Window = nullptr;
        m_IsPhase1 = true;
    }

    void D3D12Hook::InstallHooks()
    {
        TeardownSwapchainHook();

        if (!m_PresentPatch.Install(m_SwapchainVtable, 8, reinterpret_cast<void*>(&D3D12Hook::Present)))
        {
            LOGF(FATAL, "Failed to install the phase 1 Present vtable patch.");
            m_Hooked = false;
            return;
        }

        if (!m_CreateSwapchainForHwndPatch.Installed)
        {
            if (!m_CreateSwapchainForHwndPatch.Install(m_FactoryVtable, 15, reinterpret_cast<void*>(&D3D12Hook::CreateSwapChainForHwnd)))
                LOGF(FATAL, "Failed to install the CreateSwapChainForHwnd patch.");
        }

        m_Hooked = true;
    }

    void D3D12Hook::HookSwapchain(IDXGISwapChain3* swapChain)
    {
        m_PresentPatch.Uninstall();

        // The previous hook is intentionally never destroyed, VMTHook dtor would write the original vptr back into a
        // swapchain that FFX may have already freed, which would corrupt whatever is now at that address
        m_SwapchainVmt = new VMTHook("D3D12SwapChain", swapChain, 64); // should be enough
        m_SwapchainVmt->Hook(8, reinterpret_cast<void*>(&D3D12Hook::Present));
        m_SwapchainVmt->Hook(13, reinterpret_cast<void*>(&D3D12Hook::ResizeBuffers));
        m_SwapchainVmt->Enable();

        m_SwapChain = swapChain;
        m_IsPhase1 = false;
        m_Hooked = true;
    }

    bool D3D12Hook::PrepareForSwapchainCreation()
    {
        std::scoped_lock hookLock{m_HookMutex};

        if (!m_Hooked)
            return false;

        if (m_OnDeviceReset)
            m_OnDeviceReset();

        TeardownSwapchainHook();
        m_Hooked = false;
        return true;
    }

    void D3D12Hook::FinishSwapchainCreation(IUnknown* device, IUnknown* newSwapchain, HRESULT hr)
    {
        std::scoped_lock hookLock{m_HookMutex};

        Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue{};
        Microsoft::WRL::ComPtr<IDXGISwapChain3> swapChain3{};

        if (SUCCEEDED(hr))
        {
            if (device)
                device->QueryInterface(IID_PPV_ARGS(&queue));
            if (newSwapchain)
                newSwapchain->QueryInterface(IID_PPV_ARGS(&swapChain3));
        }

        if (queue && swapChain3)
        {
            m_CommandQueue = queue;
            HookSwapchain(swapChain3.Get());
            LOGF(INFO, "New swapchain hooked.");
        }
        else
        {
            // Creation failed, or this was not a D3D12 swapchain, fall back to phase 1
            LOGF(INFO, "CreateSwapChain finished without a usable D3D12 swapchain, falling back to phase 1.");
            InstallHooks();
        }
    }

    HRESULT D3D12Hook::Present(IDXGISwapChain3* swapChain, UINT syncInterval, UINT flags, void* r9)
    {
        decltype(&D3D12Hook::Present) presentFn = nullptr;
        bool ours = true;

        {
            std::scoped_lock hookLock{GetInstance().m_HookMutex};

            if (GetInstance().m_IsPhase1)
            {
                presentFn = GetInstance().m_PresentPatch.Original<decltype(&D3D12Hook::Present)>();
                if (!presentFn)
                    return DXGI_ERROR_INVALID_CALL;

                // the shared vtable can be hit by swapchains that aren't d3d12 ones
                Microsoft::WRL::ComPtr<ID3D12Device> probe{};
                if (FAILED(swapChain->GetDevice(IID_PPV_ARGS(&probe))))
                {
                    ours = false;
                }
                else
                {
                    LOGF(INFO, "Phase 1 caught swapchain {}, switching to per-instance hook.", static_cast<void*>(swapChain));
                    GetInstance().HookSwapchain(swapChain);
                    presentFn = GetInstance().m_SwapchainVmt->Original<decltype(&D3D12Hook::Present)>(8);
                }
            }
            else
            {
                presentFn = GetInstance().m_SwapchainVmt ? GetInstance().m_SwapchainVmt->Original<decltype(&D3D12Hook::Present)>(8) : nullptr;
                if (!presentFn)
                    return DXGI_ERROR_INVALID_CALL;

                ours = (swapChain == GetInstance().m_SwapChain);
            }

            if (ours)
            {
                DXGI_SWAP_CHAIN_DESC swapchainDesc{};
                if (SUCCEEDED(swapChain->GetDesc(&swapchainDesc)))
                    GetInstance().m_Window = swapchainDesc.OutputWindow;

                GetInstance().m_SwapChain = swapChain;

                if (GetInstance().m_OnPresent)
                    GetInstance().m_OnPresent();
            }
        }

        return presentFn(swapChain, syncInterval, flags, r9);
    }

    HRESULT D3D12Hook::ResizeBuffers(IDXGISwapChain3* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
    {
        std::scoped_lock hookLock{GetInstance().m_HookMutex};

        auto resizeBuffersFn = GetInstance().m_SwapchainVmt ? GetInstance().m_SwapchainVmt->Original<decltype(&D3D12Hook::ResizeBuffers)>(13) : nullptr;
        if (!resizeBuffersFn)
            return DXGI_ERROR_INVALID_CALL;

        if (swapChain == GetInstance().m_SwapChain && GetInstance().m_OnResizeBuffers)
            GetInstance().m_OnResizeBuffers();

        return resizeBuffersFn(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
    }

    HRESULT D3D12Hook::CreateSwapChainForHwnd(IDXGIFactory2* factory, IUnknown* device, HWND hwnd, const DXGI_SWAP_CHAIN_DESC1* desc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain1** swapChain)
    {
        auto createSwapChainFn = GetInstance().m_CreateSwapchainForHwndPatch.Original<decltype(&D3D12Hook::CreateSwapChainForHwnd)>();

        if (g_InsideCreateSwapchain)
            return createSwapChainFn(factory, device, hwnd, desc, pFullscreenDesc, pRestrictToOutput, swapChain);

        g_InsideCreateSwapchain = true;

        bool wasHooked = GetInstance().PrepareForSwapchainCreation();

        HRESULT hr = createSwapChainFn(factory, device, hwnd, desc, pFullscreenDesc, pRestrictToOutput, swapChain);

        if (wasHooked)
            GetInstance().FinishSwapchainCreation(device, (SUCCEEDED(hr) && swapChain) ? *swapChain : nullptr, hr);

        g_InsideCreateSwapchain = false;
        return hr;
    }
}