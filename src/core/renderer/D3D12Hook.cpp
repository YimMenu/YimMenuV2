#include "D3D12Hook.hpp"

namespace YimMenu
{
    static thread_local bool g_InsideD3d12Hook = false;

    bool D3D12Hook::RawVtablePatch::Install(void** vtable, size_t index, void* newFn)
    {
        if (!vtable)
            return false;

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

        g_InsideD3d12Hook = true;
        struct Restore
        {
            ~Restore()
            {
                g_InsideD3d12Hook = false;
            }
        } restore{};

        // if this is a rehook after a swapchain recreation
        if (m_CommandQueueOffset != 0 && m_SwapchainVtable && m_FactoryVtable)
        {
            LOGF(INFO, "Re-initializing via previously discovered vtables.");

            InstallHooks();
            return m_Hooked;
        }

        IDXGISwapChain1* swapChain1 = nullptr;
        IDXGISwapChain3* swapChain = nullptr;
        ID3D12Device* device = nullptr;

        const D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
        DXGI_SWAP_CHAIN_DESC1 swapChainDesc1{};
        swapChainDesc1.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        swapChainDesc1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc1.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        swapChainDesc1.BufferCount = 2;
        swapChainDesc1.SampleDesc.Count = 1;
        swapChainDesc1.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED;
        swapChainDesc1.Width = 1;
        swapChainDesc1.Height = 1;

        auto d3d12Module = LoadLibraryA("d3d12.dll");
        if (!d3d12Module)
        {
            LOGF(FATAL, "Failed to load d3d12.dll.");
            return false;
        }

        auto d3d12CreateDevice = reinterpret_cast<decltype(D3D12CreateDevice)*>(GetProcAddress(d3d12Module, "D3D12CreateDevice"));
        if (!d3d12CreateDevice)
        {
            LOGF(FATAL, "Failed to resolve D3D12CreateDevice.");
            return false;
        }

        bool deviceCreated = !FAILED(d3d12CreateDevice(nullptr, featureLevel, IID_PPV_ARGS(&device)));
        if (!deviceCreated)
        {
            LOGF(FATAL, "Failed to create dummy D3D12 device.");
            return false;
        }

        auto dxgiModule = LoadLibraryA("dxgi.dll");
        if (!dxgiModule)
        {
            LOGF(FATAL, "Failed to load dxgi.dll.");
            device->Release();
            return false;
        }

        auto createDxgiFactory = reinterpret_cast<decltype(CreateDXGIFactory)*>(GetProcAddress(dxgiModule, "CreateDXGIFactory"));
        if (!createDxgiFactory)
        {
            LOGF(FATAL, "Failed to resolve CreateDXGIFactory.");
            device->Release();
            return false;
        }

        IDXGIFactory4* factory = nullptr;
        if (FAILED(createDxgiFactory(IID_PPV_ARGS(&factory))))
        {
            LOGF(FATAL, "Failed to create the dummy DXGI factory.");
            device->Release();
            return false;
        }

        D3D12_COMMAND_QUEUE_DESC queueDesc{};
        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

        ID3D12CommandQueue* commandQueue = nullptr;
        if (FAILED(device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue))))
        {
            LOGF(FATAL, "Failed to create the dummy command queue.");
            factory->Release();
            device->Release();
            return false;
        }

        HWND hwnd = nullptr;
        WNDCLASSEXA wc{};

        auto initDummyWindow = [&]() {
            wc.cbSize = sizeof(WNDCLASSEXA);
            wc.style = CS_HREDRAW | CS_VREDRAW;
            wc.lpfnWndProc = DefWindowProcA;
            wc.hInstance = GetModuleHandleA(nullptr);
            wc.lpszClassName = "YimMenuDummyWindow";

            RegisterClassExA(&wc);
            hwnd = CreateWindowA(wc.lpszClassName, "YimMenu Dummy Window", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, nullptr, nullptr, wc.hInstance, nullptr);

            swapChainDesc1.BufferCount = 3;
            swapChainDesc1.Width = 0;
            swapChainDesc1.Height = 0;
            swapChainDesc1.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            swapChainDesc1.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
            swapChainDesc1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc1.SampleDesc.Count = 1;
            swapChainDesc1.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
            swapChainDesc1.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
            swapChainDesc1.Scaling = DXGI_SCALING_STRETCH;
        };

        const std::vector<std::function<bool()>> swapchainAttempts{
            [&]() {
                return !FAILED(factory->CreateSwapChainForComposition(commandQueue, &swapChainDesc1, nullptr, &swapChain1));
            },
            [&]() {
                initDummyWindow();
                return !FAILED(factory->CreateSwapChainForHwnd(commandQueue, hwnd, &swapChainDesc1, nullptr, nullptr, &swapChain1));
            },
            [&]() {
                return !FAILED(factory->CreateSwapChainForHwnd(commandQueue, GetDesktopWindow(), &swapChainDesc1, nullptr, nullptr, &swapChain1));
            },
        };

        bool anySucceeded = false;
        for (size_t i = 0; i < swapchainAttempts.size(); i++)
        {
            try
            {
                if (swapchainAttempts[i]())
                {
                    LOGF(INFO, "Created dummy swapchain via attempt {}.", i);
                    anySucceeded = true;
                    break;
                }
            }
            catch (const std::exception& e)
            {
                LOGF(FATAL, "Dummy swapchain attempt {} threw: {}", i, e.what());
            }
            catch (...)
            {
                LOGF(FATAL, "Dummy swapchain attempt {} threw an unknown exception.", i);
            }
        }

        auto cleanupDummyWindow = [&]() {
            if (hwnd)
                DestroyWindow(hwnd);
            if (wc.lpszClassName)
                UnregisterClassA(wc.lpszClassName, wc.hInstance);
        };

        if (!anySucceeded)
        {
            LOGF(FATAL, "Failed to create a dummy swapchain via any method.");
            cleanupDummyWindow();
            commandQueue->Release();
            factory->Release();
            device->Release();
            return false;
        }

        if (FAILED(swapChain1->QueryInterface(IID_PPV_ARGS(&swapChain))))
        {
            LOGF(FATAL, "Failed to query IDXGISwapChain3 from the dummy swapchain.");
            cleanupDummyWindow();
            swapChain1->Release();
            commandQueue->Release();
            factory->Release();
            device->Release();
            return false;
        }

        m_CommandQueueOffset = 0;

        for (uint32_t i = 0; i < 512 * sizeof(void*); i += sizeof(void*))
        {
            auto base = reinterpret_cast<uintptr_t>(swapChain1) + i;
            if (IsBadReadPtr(reinterpret_cast<void*>(base), sizeof(void*)))
                break;

            if (*reinterpret_cast<ID3D12CommandQueue**>(base) == commandQueue)
            {
                m_CommandQueueOffset = i;
                LOGF(INFO, "Found command queue offset at {:#x}.", i);
                break;
            }
        }

        auto targetSwapchain = swapChain;

        if (m_CommandQueueOffset == 0)
		{
			bool shouldBreak = false;
			for (uint32_t base = 0; base < 512 * sizeof(void*) && !shouldBreak; base += sizeof(void*))
			{
				auto preScanBase = reinterpret_cast<uintptr_t>(swapChain1) + base;
				if (IsBadReadPtr(reinterpret_cast<void*>(preScanBase), sizeof(void*)))
					break;

				auto scanBase = *reinterpret_cast<uintptr_t*>(preScanBase);
				if (scanBase == 0 || IsBadReadPtr(reinterpret_cast<void*>(scanBase), sizeof(void*)))
					continue;

				for (uint32_t i = 0; i < 512 * sizeof(void*); i += sizeof(void*))
				{
					auto preData = scanBase + i;
					if (IsBadReadPtr(reinterpret_cast<void*>(preData), sizeof(void*)))
						break;

					if (*reinterpret_cast<ID3D12CommandQueue**>(preData) == commandQueue)
					{
						targetSwapchain = reinterpret_cast<IDXGISwapChain3*>(scanBase);
						m_CommandQueueOffset = i;
						shouldBreak = true;

						LOGF(INFO, "Found nested command queue offset at {:#x}.", i);
						break;
					}
				}
			}
		}

        if (m_CommandQueueOffset == 0)
        {
            LOGF(FATAL, "Failed to find the command queue offset.");
            cleanupDummyWindow();
            swapChain->Release();
            swapChain1->Release();
            commandQueue->Release();
            factory->Release();
            device->Release();
            return false;
        }

        m_SwapchainVtable = *reinterpret_cast<void***>(targetSwapchain);
        m_FactoryVtable = *reinterpret_cast<void***>(factory);
        InstallHooks();

        commandQueue->Release();
        swapChain1->Release();
        swapChain->Release();
        device->Release();
        factory->Release();
        cleanupDummyWindow();

        if (!m_Hooked)
            return false;

        LOGF(INFO, "D3D12 Hook initialized.");
        return true;
    }

    bool D3D12Hook::DestroyImpl(bool unloading)
    {
        std::scoped_lock hookLock{m_HookMutex};

        if (!m_Hooked)
            return true;

        m_PresentPatch.Uninstall();
        m_SwapchainVmt.reset();

		if (unloading)
			m_CreateSwapchainPatch.Uninstall();

        m_Hooked = false;
        m_IsPhase1 = true;

        return true;
    }

    void D3D12Hook::InstallHooks()
    {
        m_PresentPatch.Uninstall();
        m_SwapchainVmt.reset();

        m_IsPhase1 = true;

        if (!m_PresentPatch.Install(m_SwapchainVtable, 8, reinterpret_cast<void*>(&D3D12Hook::Present)))
        {
            LOGF(FATAL, "Failed to install the phase 1 Present vtable patch.");
            m_Hooked = false;
            return;
        }

        if (!m_CreateSwapchainPatch.Installed)
        {
            if (!m_CreateSwapchainPatch.Install(m_FactoryVtable, 15, reinterpret_cast<void*>(&D3D12Hook::CreateSwapchain)))
                LOGF(FATAL, "Failed to install the CreateSwapChain patch.");
        }

        m_Hooked = true;
    }

    HRESULT D3D12Hook::Present(IDXGISwapChain3* swapChain, UINT syncInterval, UINT flags, void* r9)
    {
        std::scoped_lock hookLock{GetInstance().m_HookMutex};

        auto presentFn = GetInstance().m_IsPhase1 ? GetInstance().m_PresentPatch.Original<decltype(&D3D12Hook::Present)>() : GetInstance().m_SwapchainVmt->Original<decltype(&D3D12Hook::Present)>(8);

        HWND swapchainWnd = nullptr;
        {
            DXGI_SWAP_CHAIN_DESC swapchainDesc{};
            if (SUCCEEDED(swapChain->GetDesc(&swapchainDesc)))
                swapchainWnd = swapchainDesc.OutputWindow;
        }

        if (!GetInstance().m_IsPhase1 && swapChain != GetInstance().m_SwapChain)
            return presentFn(swapChain, syncInterval, flags, r9);

        if (GetInstance().m_IsPhase1) // caught the real present, switch to per instance vmt hook
        {
            GetInstance().m_PresentPatch.Uninstall();

            GetInstance().m_SwapchainVmt = std::make_unique<VMTHook>("D3D12SwapChain", swapChain, 64); // should be enough
			GetInstance().m_SwapchainVmt->Hook(8, reinterpret_cast<void*>(&D3D12Hook::Present));
			GetInstance().m_SwapchainVmt->Hook(13, reinterpret_cast<void*>(&D3D12Hook::ResizeBuffers));
			GetInstance().m_SwapchainVmt->Enable();

            GetInstance().m_IsPhase1 = false;
			presentFn = GetInstance().m_SwapchainVmt->Original<decltype(&D3D12Hook::Present)>(8);
        }

        GetInstance().m_Window = swapchainWnd;
        GetInstance().m_SwapChain = swapChain;

        {
            Microsoft::WRL::ComPtr<ID3D12Device4> tempDevice{};
            swapChain->GetDevice(IID_PPV_ARGS(&tempDevice));
            GetInstance().m_Device = tempDevice.Get();
        }

        GetInstance().m_CommandQueue = *reinterpret_cast<ID3D12CommandQueue**>(reinterpret_cast<uintptr_t>(swapChain) + GetInstance().m_CommandQueueOffset);

        if (GetInstance().m_OnPresent)
            GetInstance().m_OnPresent();

        return presentFn(swapChain, syncInterval, flags, r9);
    }

    HRESULT D3D12Hook::ResizeBuffers(IDXGISwapChain3* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
    {
        std::scoped_lock hookLock{GetInstance().m_HookMutex};

        auto resizeBuffersFn = GetInstance().m_SwapchainVmt->Original<decltype(&D3D12Hook::ResizeBuffers)>(13);

        if (GetInstance().m_OnResizeBuffers)
            GetInstance().m_OnResizeBuffers();

        return resizeBuffersFn(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
    }

    HRESULT D3D12Hook::CreateSwapchain(IDXGIFactory4* factory, IUnknown* device, HWND hwnd, const DXGI_SWAP_CHAIN_DESC* desc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain** swapChain)
    {
        auto createSwapChainFn = GetInstance().m_CreateSwapchainPatch.Original<decltype(&D3D12Hook::CreateSwapchain)>();

        if (g_InsideD3d12Hook)
            return createSwapChainFn(factory, device, hwnd, desc, pFullscreenDesc, pRestrictToOutput, swapChain);

        LOGF(INFO, "CreateSwapChain called, a new swapchain is being created.");

        std::scoped_lock hookLock{GetInstance().m_HookMutex};

        bool wasHooked = GetInstance().m_Hooked;

        if (wasHooked)
        {
            if (GetInstance().m_OnDeviceReset)
                GetInstance().m_OnDeviceReset();

            GetInstance().Destroy();
        }

        if (wasHooked)
            GetInstance().Init();

        return createSwapChainFn(factory, device, hwnd, desc, pFullscreenDesc, pRestrictToOutput, swapChain);
    }
}