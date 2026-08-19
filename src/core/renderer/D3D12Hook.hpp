// Credits to:
// https://github.com/praydog/REFramework/blob/master/src/D3D12Hook.cpp
// https://github.com/praydog/REFramework/blob/master/src/D3D12Hook.hpp
#pragma once
#include "core/hooking/VMTHook.hpp"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl/client.h>

namespace YimMenu
{
    class D3D12Hook
    {
    public:
        static bool Init()
        {
            return GetInstance().InitImpl();
        }

        static bool Destroy(bool unloading = false)
        {
            return GetInstance().DestroyImpl(unloading);
        }

        static void OnPresent(std::function<void()> fn)
        {
            GetInstance().m_OnPresent = std::move(fn);
        }

        static void OnResizeBuffers(std::function<void()> fn)
        {
            GetInstance().m_OnResizeBuffers = std::move(fn);
        }

        static void OnDeviceReset(std::function<void()> fn)
        {
            GetInstance().m_OnDeviceReset = std::move(fn);
        }

        static ID3D12Device4* GetDevice()
        {
            return GetInstance().m_Device;
        }

        static IDXGISwapChain3* GetSwapChain()
        {
            return GetInstance().m_SwapChain;
        }

        static ID3D12CommandQueue* GetCommandQueue()
        {
            return GetInstance().m_CommandQueue;
        }

        static HWND GetWindow()
        {
            return GetInstance().m_Window;
        }

    private:
        // VMTHook clones the vtable per-instance (so hooking one object never
        // affects another), which is exactly the opposite of what phase 1 needs, so
        // this one raw patch is done by hand.
        struct RawVtablePatch
        {
            bool Install(void** vtable, size_t index, void* newFn);
            void Uninstall();

            template <typename T>
            T Original() const
            {
                return reinterpret_cast<T>(OriginalFn);
            }

            void** Slot = nullptr;
            void* OriginalFn = nullptr;
            bool Installed = false;
        };

        static D3D12Hook& GetInstance()
        {
            static D3D12Hook instance;
            return instance;
        }

        bool InitImpl();
        bool DestroyImpl(bool unloading);
        void InstallHooks();

        static HRESULT Present(IDXGISwapChain3* swapChain, UINT syncInterval, UINT flags, void* r9);
        static HRESULT ResizeBuffers(IDXGISwapChain3* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
        static HRESULT CreateSwapchain(IDXGIFactory4* factory, IUnknown* device, HWND hwnd, const DXGI_SWAP_CHAIN_DESC* desc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* pFullscreenDesc, IDXGIOutput* pRestrictToOutput, IDXGISwapChain** swapChain);

        std::function<void()> m_OnPresent = nullptr;
        std::function<void()> m_OnResizeBuffers = nullptr;
        std::function<void()> m_OnDeviceReset = nullptr;
        ID3D12Device4* m_Device = nullptr;
        ID3D12CommandQueue* m_CommandQueue = nullptr;
        IDXGISwapChain3* m_SwapChain = nullptr;
        HWND m_Window = nullptr;
        bool m_Hooked = false;
        bool m_IsPhase1 = true;
        uint32_t m_CommandQueueOffset = 0;
        void** m_FactoryVtable = nullptr;
        void** m_SwapchainVtable = nullptr;
        RawVtablePatch m_CreateSwapchainPatch = {};
        RawVtablePatch m_PresentPatch = {};
		std::unique_ptr<VMTHook> m_SwapchainVmt = {};
        std::recursive_mutex m_HookMutex = {};
    };
}