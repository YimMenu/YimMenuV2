#pragma once
#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl/client.h>

namespace YimMenu
{
    class Renderer
    {
    public:
	    using RendererCallback = std::function<void()>;
	    using WindowProcedureCallback = std::function<void(HWND, UINT, WPARAM, LPARAM)>;

        static void Init()
        {
            GetInstance().InitImpl();
        }

        static void Destroy()
        {
            GetInstance().DestroyImpl();
        }

	    static void AddRendererCallback(RendererCallback&& callback, uint32_t priority)
        {
            GetInstance().m_RendererCallbacks.insert({priority, callback});
        }

        static void AddWindowProcedureCallback(WindowProcedureCallback&& callback)
        {
            GetInstance().m_WindowProcedureCallbacks.push_back(callback);
        }

		static bool IsInitialized()
		{
			return GetInstance().m_Initialized;
		}

		static void SetSafeToRender()
		{
			GetInstance().m_SafeToRender = true;
		}

		static void SetFontsUpdated()
		{
			GetInstance().m_FontsUpdated = true;
		}

    private:
        template <typename T>
        using ComPtr = Microsoft::WRL::ComPtr<T>;

        struct SrvHeapAllocator
        {
            void Init(ID3D12Device* device, ID3D12DescriptorHeap* heap);
            void Alloc(D3D12_CPU_DESCRIPTOR_HANDLE* outCpu, D3D12_GPU_DESCRIPTOR_HANDLE* outGpu);
            void Free(D3D12_CPU_DESCRIPTOR_HANDLE cpu, D3D12_GPU_DESCRIPTOR_HANDLE gpu);

            ID3D12DescriptorHeap* Heap = nullptr;
            UINT DescriptorSize = 0;
            D3D12_CPU_DESCRIPTOR_HANDLE HeapStartCpu = {};
            D3D12_GPU_DESCRIPTOR_HANDLE HeapStartGpu = {};
            std::vector<int> FreeIndices = {};
        };

        struct FrameContext
        {
            ComPtr<ID3D12CommandAllocator> Allocator = {};
            UINT64 FenceValue = 0;
        };

        static Renderer& GetInstance()
        {
            static Renderer instance;
            return instance;
        }

        void InitImpl();
        void DestroyImpl();
        bool InitInternal();
        void Render();
        void Resize();
        bool CreateDeviceObjects(ID3D12Device* device, ID3D12CommandQueue* queue, UINT bufferCount);
        void CreateRenderTargets(IDXGISwapChain3* swapChain);
        void ReleaseRenderTargets();
        void InvalidateDeviceObjects();

        static LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

        bool m_Initialized = false;
        bool m_DeviceObjectsValid = false;
		bool m_SafeToRender = false;
		bool m_FontsUpdated = false;
        HWND m_Window = nullptr;
        WNDPROC m_OriginalWndProc = nullptr;
        ComPtr<ID3D12DescriptorHeap> m_RtvHeap = {};
        ComPtr<ID3D12DescriptorHeap> m_SrvHeap = {};
        SrvHeapAllocator m_SrvAllocator = {};
        std::vector<FrameContext> m_FrameContexts = {};
        std::vector<ComPtr<ID3D12Resource>> m_BackBuffers = {};
        std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> m_RtvHandles = {};
        UINT m_BufferCount = 0;
        ComPtr<ID3D12GraphicsCommandList> m_CommandList = {};
        ComPtr<ID3D12Fence> m_Fence = {};
        HANDLE m_FenceEvent = nullptr;
        UINT64 m_FenceValue = 0;
        std::map<uint32_t, RendererCallback> m_RendererCallbacks;
        std::vector<WindowProcedureCallback> m_WindowProcedureCallbacks;
    };
}