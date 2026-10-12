#include "Renderer.hpp"
#include "D3D12Hook.hpp"
#include "core/frontend/manager/styles/Themes.hpp"
#include "game/frontend/Menu.hpp"
#include <backends/imgui_impl_dx12.h>
#include <backends/imgui_impl_win32.h>
#include <imgui.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

namespace YimMenu
{
    void Renderer::InitImpl()
    {
        D3D12Hook::OnPresent([this] {
            if (!m_Initialized)
            {
                if (!InitInternal())
                    return;
            }

            Render();
        });

        D3D12Hook::OnResizeBuffers([this] {
            Resize();
        });

        D3D12Hook::OnDeviceReset([this] {
			Destroy();
        });
    }

    bool Renderer::InitInternal()
    {
        auto swapChain = D3D12Hook::GetSwapChain();
        auto queue = D3D12Hook::GetCommandQueue();
        auto window = D3D12Hook::GetWindow();
        if (!swapChain || !queue || !window)
        {
			//LOGF(FATAL, "Invalid D3D12Hook data.");
            return false;
        }

        DXGI_SWAP_CHAIN_DESC desc{};
        ComPtr<ID3D12Device> device{};
        if (FAILED(swapChain->GetDesc(&desc)) || FAILED(swapChain->GetDevice(IID_PPV_ARGS(&device))))
            return false;

        UINT bufferCount = desc.BufferCount > 0 ? desc.BufferCount : 3;

        m_Device = device;
        m_Queue = queue;
        m_RtvFormat = desc.BufferDesc.Format;

        if (!CreateDeviceObjects(device.Get(), bufferCount))
        {
            LOGF(FATAL, "Failed to create device objects.");
            ReleaseDeviceObjects();
            return false;
        }

        CreateRenderTargets(swapChain);

        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        ImGui::StyleColorsDark();

        ImGui_ImplWin32_Init(window);

        ImGui_ImplDX12_InitInfo initInfo{};
        initInfo.Device = device.Get();
        initInfo.CommandQueue = queue;
        initInfo.NumFramesInFlight = static_cast<int>(bufferCount);
        initInfo.RTVFormat = m_RtvFormat != DXGI_FORMAT_UNKNOWN ? m_RtvFormat : DXGI_FORMAT_R8G8B8A8_UNORM;
        initInfo.DSVFormat = DXGI_FORMAT_UNKNOWN;
        initInfo.SrvDescriptorHeap = m_SrvHeap.Get();
        initInfo.UserData = &m_SrvAllocator;
        initInfo.SrvDescriptorAllocFn = [](ImGui_ImplDX12_InitInfo* info, D3D12_CPU_DESCRIPTOR_HANDLE* outCpu, D3D12_GPU_DESCRIPTOR_HANDLE* outGpu) {
            static_cast<SrvHeapAllocator*>(info->UserData)->Alloc(outCpu, outGpu);
        };
        initInfo.SrvDescriptorFreeFn = [](ImGui_ImplDX12_InitInfo* info, D3D12_CPU_DESCRIPTOR_HANDLE cpu, D3D12_GPU_DESCRIPTOR_HANDLE gpu) {
            static_cast<SrvHeapAllocator*>(info->UserData)->Free(cpu, gpu);
        };

        if (!ImGui_ImplDX12_Init(&initInfo))
        {
            LOGF(FATAL, "ImGui_ImplDX12_Init failed.");

            ImGui_ImplWin32_Shutdown();
            ImGui::DestroyContext();

            ReleaseRenderTargets();
            ReleaseDeviceObjects();
            return false;
        }

        Menu::SetupFonts();
        SetupStyle();
        GUI::ToggleMouse();

        {
            std::scoped_lock lock{m_WndProcMutex};
            m_Initialized = true;
        }

        LOGF(INFO, "Renderer initialized.");
        return true;
    }

    void Renderer::DestroyImpl()
    {
        if (m_Initialized || m_DeviceObjectsValid)
        {
            bool wasInitialized = m_Initialized;

            // waits for the GPU on our own queue before anything below is freed
            ReleaseRenderTargets();

            {
                std::scoped_lock lock{m_WndProcMutex};

                m_Initialized = false;

                if (wasInitialized)
                {
                    ImGui_ImplDX12_Shutdown();
                    ImGui_ImplWin32_Shutdown();
                    ImGui::DestroyContext();
                }
            }

            ReleaseDeviceObjects();
        }
    }

    void Renderer::Render()
    {
        auto swapChain = D3D12Hook::GetSwapChain();
        if (!swapChain || !m_Queue || !m_Device)
            return;

        if (FAILED(m_Device->GetDeviceRemovedReason()))
            return;

        if (!m_SafeToRender)
            return;

        const UINT index = swapChain->GetCurrentBackBufferIndex();
        if (index >= m_FrameContexts.size() || index >= m_BackBuffers.size() || index >= m_RtvHandles.size())
            return;

        // if a resize happened, our cached backbuffer resources are stale, refresh them
        {
            ComPtr<ID3D12Resource> currentAtIndex{};
            if (m_BackBuffers[index] == nullptr || (SUCCEEDED(swapChain->GetBuffer(index, IID_PPV_ARGS(&currentAtIndex))) && currentAtIndex.Get() != m_BackBuffers[index].Get()))
                CreateRenderTargets(swapChain);
        }

        if (!m_BackBuffers[index])
            return;

        if (m_FontsUpdated)
        {
            WaitForGpu(2000);
            ImGui_ImplDX12_InvalidateDeviceObjects();
            ImGui_ImplDX12_CreateDeviceObjects();
            m_FontsUpdated = false;
        }

        auto& frame = m_FrameContexts[index];

        // wait for the GPU to be done with this frame context's allocator before reusing it
        if (m_Fence->GetCompletedValue() < frame.FenceValue)
        {
            if (FAILED(m_Fence->SetEventOnCompletion(frame.FenceValue, m_FenceEvent)) || WaitForSingleObject(m_FenceEvent, 5000) != WAIT_OBJECT_0)
                return;
        }

        if (FAILED(frame.Allocator->Reset()))
            return;

        if (FAILED(m_CommandList->Reset(frame.Allocator.Get(), nullptr)))
            return;

        D3D12_RESOURCE_BARRIER toRt{};
        toRt.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        toRt.Transition.pResource = m_BackBuffers[index].Get();
        toRt.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
        toRt.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
        toRt.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
        m_CommandList->ResourceBarrier(1, &toRt);

        m_CommandList->OMSetRenderTargets(1, &m_RtvHandles[index], FALSE, nullptr);
        ID3D12DescriptorHeap* heaps[] = {m_SrvHeap.Get()};
        m_CommandList->SetDescriptorHeaps(1, heaps);

        ImGui_ImplDX12_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        for (const auto& callback : m_RendererCallbacks | std::views::values)
            callback();

        ImGui::Render();

        ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), m_CommandList.Get());

        D3D12_RESOURCE_BARRIER toPresent{};
        toPresent.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        toPresent.Transition.pResource = m_BackBuffers[index].Get();
        toPresent.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
        toPresent.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
        toPresent.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
        m_CommandList->ResourceBarrier(1, &toPresent);

        // never submit a list that failed to record
        if (FAILED(m_CommandList->Close()))
            return;

        ID3D12CommandList* lists[] = {m_CommandList.Get()};
        m_Queue->ExecuteCommandLists(1, lists);

        const UINT64 value = m_FenceValue + 1;
        if (SUCCEEDED(m_Queue->Signal(m_Fence.Get(), value)))
        {
            m_FenceValue = value;
            frame.FenceValue = value;
        }
    }

    void Renderer::Resize()
    {
        if (!m_Initialized)
            return;

        ReleaseRenderTargets();
    }

    bool Renderer::CreateDeviceObjects(ID3D12Device* device, UINT bufferCount)
    {
        m_BufferCount = bufferCount;

        D3D12_DESCRIPTOR_HEAP_DESC rtvDesc{};
        rtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtvDesc.NumDescriptors = bufferCount;
        rtvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

        if (FAILED(device->CreateDescriptorHeap(&rtvDesc, IID_PPV_ARGS(&m_RtvHeap))))
            return false;

        D3D12_DESCRIPTOR_HEAP_DESC srvDesc{};
        srvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        srvDesc.NumDescriptors = 64;
        srvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

        if (FAILED(device->CreateDescriptorHeap(&srvDesc, IID_PPV_ARGS(&m_SrvHeap))))
            return false;

        m_SrvAllocator.Init(device, m_SrvHeap.Get());

        auto rtvIncrement = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        auto rtvStart = m_RtvHeap->GetCPUDescriptorHandleForHeapStart();

        m_FrameContexts.clear();
        m_RtvHandles.clear();
        m_BackBuffers.clear();
        m_FrameContexts.resize(bufferCount);
        m_RtvHandles.resize(bufferCount);
        m_BackBuffers.resize(bufferCount);

        for (UINT i = 0; i < bufferCount; i++)
        {
            if (FAILED(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_FrameContexts[i].Allocator))))
                return false;

            m_RtvHandles[i] = {rtvStart.ptr + static_cast<SIZE_T>(i) * rtvIncrement};
        }

        if (FAILED(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_FrameContexts[0].Allocator.Get(), nullptr, IID_PPV_ARGS(&m_CommandList))))
            return false;

        m_CommandList->Close();

        if (FAILED(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_Fence))))
            return false;

        m_FenceValue = 0;
        m_FenceEvent = CreateEventA(nullptr, FALSE, FALSE, nullptr);
        if (!m_FenceEvent)
            return false;

        m_DeviceObjectsValid = true;
        return true;
    }

    void Renderer::ReleaseDeviceObjects()
    {
        if (m_FenceEvent)
        {
            CloseHandle(m_FenceEvent);
            m_FenceEvent = nullptr;
        }

        m_FrameContexts.clear();
        m_BackBuffers.clear();
        m_RtvHandles.clear();
        m_CommandList.Reset();
        m_Fence.Reset();
        m_RtvHeap.Reset();
        m_SrvHeap.Reset();
        m_Queue.Reset();
        m_Device.Reset();

        m_FenceValue = 0;
        m_BufferCount = 0;
        m_DeviceObjectsValid = false;
    }

    void Renderer::CreateRenderTargets(IDXGISwapChain3* swapChain)
    {
        ComPtr<ID3D12Device> owningDevice{};
        if (FAILED(swapChain->GetDevice(IID_PPV_ARGS(&owningDevice))))
            return;

        for (UINT i = 0; i < m_BufferCount && i < m_BackBuffers.size(); ++i)
        {
            if (FAILED(swapChain->GetBuffer(i, IID_PPV_ARGS(&m_BackBuffers[i]))))
                continue;

            owningDevice->CreateRenderTargetView(m_BackBuffers[i].Get(), nullptr, m_RtvHandles[i]);
        }
    }

    void Renderer::WaitForGpu(DWORD timeoutMs)
    {
        if (!m_Fence || !m_FenceEvent || !m_Queue)
            return;

        const UINT64 value = m_FenceValue + 1;
        if (FAILED(m_Queue->Signal(m_Fence.Get(), value)))
            return;

        m_FenceValue = value;

        if (m_Fence->GetCompletedValue() < value)
        {
            if (SUCCEEDED(m_Fence->SetEventOnCompletion(value, m_FenceEvent)))
                WaitForSingleObject(m_FenceEvent, timeoutMs);
        }
    }

    void Renderer::ReleaseRenderTargets()
    {
        WaitForGpu(2000);

        for (auto& bb : m_BackBuffers)
            bb.Reset();
    }

    void Renderer::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        std::scoped_lock lock{GetInstance().m_WndProcMutex};

        if (!GetInstance().m_Initialized)
            return;

        for (const auto& callback : GetInstance().m_WindowProcedureCallbacks)
            callback(hwnd, msg, wparam, lparam);

        ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
    }

    void Renderer::SrvHeapAllocator::Init(ID3D12Device* device, ID3D12DescriptorHeap* srvHeap)
    {
        DescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
        HeapStartCpu = srvHeap->GetCPUDescriptorHandleForHeapStart();
        HeapStartGpu = srvHeap->GetGPUDescriptorHandleForHeapStart();

        FreeIndices.clear();
        FreeIndices.reserve(64);
        for (int i = 64 - 1; i >= 0; --i)
            FreeIndices.push_back(i);
    }

    void Renderer::SrvHeapAllocator::Alloc(D3D12_CPU_DESCRIPTOR_HANDLE* outCpu, D3D12_GPU_DESCRIPTOR_HANDLE* outGpu)
    {
        if (FreeIndices.empty())
        {
            LOGF(FATAL, "SRV heap exhausted.");
            *outCpu = HeapStartCpu;
            *outGpu = HeapStartGpu;
            return;
        }

        int index = FreeIndices.back();
        FreeIndices.pop_back();

        outCpu->ptr = HeapStartCpu.ptr + static_cast<SIZE_T>(index) * DescriptorSize;
        outGpu->ptr = HeapStartGpu.ptr + static_cast<UINT64>(index) * DescriptorSize;
    }

    void Renderer::SrvHeapAllocator::Free(D3D12_CPU_DESCRIPTOR_HANDLE cpu, D3D12_GPU_DESCRIPTOR_HANDLE gpu)
    {
        int index = static_cast<int>((cpu.ptr - HeapStartCpu.ptr) / DescriptorSize);
        FreeIndices.push_back(index);
    }
}