#include "Renderer.hpp"

#include "core/memory/ModuleMgr.hpp"
#include "core/memory/PatternScanner.hpp"
#include "game/frontend/GUI.hpp"
#include "game/frontend/Menu.hpp"
#include "game/pointers/Pointers.hpp"

#include <backends/imgui_impl_dx12.h>
#include <backends/imgui_impl_win32.h>
#include <imgui.h>


namespace YimMenu
{
	Renderer::Renderer() :
	    m_Initialized(false),
	    m_Resizing(false),
	    m_FontsUpdated(false),
		m_SafeToRender(false)
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::DestroyImpl()
	{
		if (!m_Initialized)
			return;

		// TODO: we aren't destroying resources properly
		ImGui_ImplWin32_Shutdown();


		WaitForLastFrame();
		ImGui_ImplDX12_InvalidateDeviceObjects();

		for (size_t i{}; i != GetInstance().m_SwapChainDesc.BufferCount; ++i)
		{
			REL(GetInstance().m_FrameContext[i].Resource);
		}

		ImGui_ImplDX12_Shutdown();

		ImGui::DestroyContext();

#if 0
		// manually destroy the allocators we created for the rest of the frame contexts
		for (size_t i = 1; i < m_SwapChainDesc.BufferCount; ++i)
			if (m_FrameContext[i].CommandAllocator)
				m_FrameContext[i].CommandAllocator->Release();
#endif
	}

	bool Renderer::InitDX12()
	{
		if (!Pointers.SwapChain)
		{
			LOG(WARNING) << "SwapChain pointer is invalid!";

			return false;
		}

		if (!Pointers.CommandQueue)
		{
			LOG(WARNING) << "CommandQueue pointer is invalid!";

			return false;
		}

		//This is required. In order to stop ComPtr from releasing the original pointer, we create a new ComPtr with the ptr as the intializer. (The '=' operator uses swap which releases the object passed into it)
		if (m_GameSwapChain = ComPtr<IDXGISwapChain1>(*Pointers.SwapChain); !m_GameSwapChain.Get())
		{
			LOG(WARNING) << "Dereferenced SwapChain pointer is invalid!";

			return false;
		}

		if (m_CommandQueue = ComPtr<ID3D12CommandQueue>(*Pointers.CommandQueue); !m_CommandQueue.Get())
		{
			LOG(WARNING) << "Dereferenced CommandQueue pointer is invalid!";

			return false;
		}

		m_GameSwapChain.As(&m_SwapChain); //We need GetCurrentBackBufferIndex from IDXGISwapChain3

		if (const auto result = m_SwapChain->GetDevice(__uuidof(ID3D12Device), reinterpret_cast<void**>(m_Device.GetAddressOf())); result < 0)
		{
			LOG(WARNING) << "Failed to get D3D Device with result: [" << result << "]";

			return false;
		}

		if (const auto result = m_SwapChain->GetDesc(&m_SwapChainDesc); result < 0)
		{
			LOG(WARNING) << "Failed to get SwapChain Description with result: [" << result << "]";

			return false;
		}

		if (const auto result = m_Device->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(ID3D12Fence), (void**)m_Fence.GetAddressOf()); result < 0)
		{
			LOG(WARNING) << "Failed to create Fence with result: [" << result << "]";

			return false;
		}

		if (const auto result = m_FenceEvent = CreateEventA(nullptr, FALSE, FALSE, nullptr); !result)
		{
			LOG(WARNING) << "Failed to create Fence Event!";

			return false;
		}

		m_FrameContext.resize(m_SwapChainDesc.BufferCount);

		D3D12_DESCRIPTOR_HEAP_DESC DescriptorDesc{D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, m_SwapChainDesc.BufferCount, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE};
		if (const auto result =
		        m_Device->CreateDescriptorHeap(&DescriptorDesc, __uuidof(ID3D12DescriptorHeap), (void**)m_DescriptorHeap.GetAddressOf());
		    result < 0)
		{
			LOG(WARNING) << "Failed to create Descriptor Heap with result: [" << result << "]";

			return false;
		}

		if (const auto result = m_Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
		        __uuidof(ID3D12CommandAllocator),
		        (void**)m_CommandAllocator.GetAddressOf());
		    result < 0)
		{
			LOG(WARNING) << "Failed to create primary Command Allocator with result: [" << result << "]";

			return false;
		}

		m_FrameContext[0].CommandAllocator = m_CommandAllocator.Get(); // set initial command allocator

		// create the rest of the allocators
		for (size_t i = 1; i < m_SwapChainDesc.BufferCount; ++i)
		{
			if (const auto result = m_Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&m_FrameContext[i].CommandAllocator); result < 0)
			{
				LOG(WARNING) << "Failed to create secondary Command Allocator with result: [" << result << "]";

				return false;
			}
		}

		if (const auto result = m_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_CommandAllocator.Get(), NULL, __uuidof(ID3D12GraphicsCommandList), (void**)m_CommandList.GetAddressOf()); result < 0)
		{
			LOG(WARNING) << "Failed to create Command List with result: [" << result << "]";

			return false;
		}

		if (const auto result = m_CommandList->Close(); result < 0)
		{
			LOG(WARNING) << "Failed to finalize the creation of Command List with result: [" << result << "]";

			return false;
		}

		D3D12_DESCRIPTOR_HEAP_DESC DescriptorBackbufferDesc{D3D12_DESCRIPTOR_HEAP_TYPE_RTV, m_SwapChainDesc.BufferCount, D3D12_DESCRIPTOR_HEAP_FLAG_NONE, 1};
		if (const auto result = m_Device->CreateDescriptorHeap(&DescriptorBackbufferDesc,
		        __uuidof(ID3D12DescriptorHeap),
		        (void**)m_BackbufferDescriptorHeap.GetAddressOf());
		    result < 0)
		{
			LOG(WARNING) << "Failed to create Backbuffer Descriptor Heap with result: [" << result << "]";

			return false;
		}

		const auto RTVDescriptorSize{m_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)};
		D3D12_CPU_DESCRIPTOR_HANDLE RTVHandle{m_BackbufferDescriptorHeap->GetCPUDescriptorHandleForHeapStart()};
		for (size_t i = 0; i < m_SwapChainDesc.BufferCount; ++i)
		{
			ComPtr<ID3D12Resource> BackBuffer{};
			m_FrameContext[i].Descriptor = RTVHandle;
			m_SwapChain->GetBuffer(i, __uuidof(ID3D12Resource), (void**)BackBuffer.GetAddressOf());
			m_Device->CreateRenderTargetView(BackBuffer.Get(), nullptr, RTVHandle);
			m_FrameContext[i].Resource = BackBuffer.Get();
			RTVHandle.ptr += RTVDescriptorSize;
		}

		m_HeapAllocator.Create(m_Device.Get(), m_DescriptorHeap.Get());

		// never returns false, useless to check return
		ImGui::CreateContext(&GetInstance().m_FontAtlas);
		ImGui_ImplWin32_Init(*Pointers.Hwnd);

		ImGui_ImplDX12_InitInfo init_info = {};
		init_info.Device = m_Device.Get();
		init_info.CommandQueue = m_CommandQueue.Get();
		init_info.NumFramesInFlight = m_SwapChainDesc.BufferCount;
		init_info.RTVFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
		init_info.DSVFormat = DXGI_FORMAT_UNKNOWN;
		// Allocating SRV descriptors (for textures) is up to the application, so we provide callbacks.
		// (current version of the backend will only allocate one descriptor, future versions will need to allocate more)
		init_info.SrvDescriptorHeap = m_DescriptorHeap.Get();
		init_info.SrvDescriptorAllocFn = [](ImGui_ImplDX12_InitInfo*, D3D12_CPU_DESCRIPTOR_HANDLE* out_cpu_handle, D3D12_GPU_DESCRIPTOR_HANDLE* out_gpu_handle) {
			return GetInstance().m_HeapAllocator.Alloc(out_cpu_handle, out_gpu_handle);
		};
		init_info.SrvDescriptorFreeFn = [](ImGui_ImplDX12_InitInfo*, D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle, D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle) {
			return GetInstance().m_HeapAllocator.Free(cpu_handle, gpu_handle);
		};
		ImGui_ImplDX12_Init(&init_info);

		ImGui::StyleColorsDark();

		LOG(INFO) << "DirectX 12 renderer has finished initializing.";
		m_Initialized = true;
		return true;
	}

	bool Renderer::InitImpl()
	{
		while (!*Pointers.Hwnd || !*Pointers.ScreenResX)
		{
			std::this_thread::sleep_for(1s);
		}

		LOG(INFO) << "Using DX12, clear shader cache if you're having issues.";
		return InitDX12();
	}

	bool Renderer::AddRendererCallBackImpl(RendererCallBack&& callback, std::uint32_t priority)
	{
		return m_RendererCallBacks.insert({priority, callback}).second;
	}

	void Renderer::AddWindowProcedureCallbackImpl(WindowProcedureCallback&& callback)
	{
		return m_WindowProcedureCallbacks.push_back(callback);
	}

	void Renderer::DX12OnPresentImpl()
	{
		if (!m_SafeToRender)
			return;

		Renderer::DX12NewFrame();
		for (const auto& callback : m_RendererCallBacks | std::views::values)
			callback();
		Renderer::DX12EndFrame();
	}

	LRESULT Renderer::WndProcImpl(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		for (const auto& callback : m_WindowProcedureCallbacks)
			callback(hwnd, msg, wparam, lparam);

		return ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
	}

	void Renderer::ResizeImpl(float scale)
	{
		DX12PreResize();

		if (scale != 1.0f)
			ImGui::GetStyle().ScaleAllSizes(scale);
		ImGui::GetStyle().MouseCursorScale = 1.0f;
		ImGui::GetIO().FontGlobalScale = scale;
		DX12PostResize();
	}

	void Renderer::WaitForLastFrame()
	{
		FrameContext FrameCtx = GetInstance().m_FrameContext[GetInstance().m_FrameIndex % GetInstance().m_SwapChainDesc.BufferCount];

		UINT64 FenceValue = FrameCtx.FenceValue;

		if (FenceValue == 0)
		{
			return;
		}

		FrameCtx.FenceValue = 0;

		if (GetInstance().m_Fence->GetCompletedValue() >= FenceValue)
		{
			return;
		}

		GetInstance().m_Fence->SetEventOnCompletion(FenceValue, GetInstance().m_FenceEvent);

		WaitForSingleObject(GetInstance().m_FenceEvent, INFINITE);
	}

	void Renderer::WaitForNextFrame()
	{
		UINT NextFrameIndex = GetInstance().m_FrameIndex + 1;
		GetInstance().m_FrameIndex = NextFrameIndex;

		HANDLE WaitableObjects[] = {GetInstance().m_SwapchainWaitableObject, nullptr};
		DWORD NumWaitableObjets = 1;

		FrameContext FrameCtx = GetInstance().m_FrameContext[NextFrameIndex % GetInstance().m_SwapChainDesc.BufferCount];
		UINT64 FenceValue = FrameCtx.FenceValue;
		if (FenceValue != 0) // means no fence was signaled
		{
			FrameCtx.FenceValue = 0;
			GetInstance().m_Fence->SetEventOnCompletion(FenceValue, GetInstance().m_FenceEvent);
			WaitableObjects[1] = GetInstance().m_FenceEvent;
			NumWaitableObjets = 2;
		}

		WaitForMultipleObjects(NumWaitableObjets, WaitableObjects, TRUE, INFINITE);
	}

	void Renderer::DX12PreResize()
	{
		SetResizing(true);

		WaitForLastFrame();

		ImGui_ImplDX12_InvalidateDeviceObjects();

		for (size_t i{}; i != GetInstance().m_SwapChainDesc.BufferCount; ++i)
		{
			REL(GetInstance().m_FrameContext[i].Resource);
		}
	}

	void Renderer::DX12PostResize()
	{
		//Recreate our pointers and ImGui's
		ImGui_ImplDX12_CreateDeviceObjects();
		const auto RTVDescriptorSize{GetInstance().m_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV)};
		D3D12_CPU_DESCRIPTOR_HANDLE RTVHandle{GetInstance().m_BackbufferDescriptorHeap->GetCPUDescriptorHandleForHeapStart()};
		for (size_t i{}; i != GetInstance().m_SwapChainDesc.BufferCount; ++i)
		{
			ComPtr<ID3D12Resource> BackBuffer{};
			GetInstance().m_FrameContext[i].Descriptor = RTVHandle;
			GetInstance().m_SwapChain->GetBuffer(i, __uuidof(ID3D12Resource), (void**)BackBuffer.GetAddressOf());
			GetInstance().m_Device->CreateRenderTargetView(BackBuffer.Get(), nullptr, RTVHandle);
			GetInstance().m_FrameContext[i].Resource = BackBuffer.Get();
			RTVHandle.ptr += RTVDescriptorSize;
		}

		SetResizing(false);
	}

	void Renderer::DX12NewFrame()
	{
		if (GetInstance().m_FontsUpdated)
		{
			DX12PreResize();
			DX12PostResize();
			GetInstance().m_FontsUpdated = false;
		}

		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void Renderer::DX12EndFrame()
	{
		WaitForNextFrame();

		FrameContext& CurrentFrameContext{GetInstance().m_FrameContext[GetInstance().m_SwapChain->GetCurrentBackBufferIndex()]};
		CurrentFrameContext.CommandAllocator->Reset();

		D3D12_RESOURCE_BARRIER Barrier{D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
		    D3D12_RESOURCE_BARRIER_FLAG_NONE,
		    {{CurrentFrameContext.Resource, D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET}}};
		GetInstance().m_CommandList->Reset(CurrentFrameContext.CommandAllocator, nullptr);
		GetInstance().m_CommandList->ResourceBarrier(1, &Barrier);
		GetInstance().m_CommandList->OMSetRenderTargets(1, &CurrentFrameContext.Descriptor, FALSE, nullptr);
		GetInstance().m_CommandList->SetDescriptorHeaps(1, GetInstance().m_DescriptorHeap.GetAddressOf());

		ImGui::Render();

		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), GetInstance().m_CommandList.Get());

		Barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
		Barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
		GetInstance().m_CommandList->ResourceBarrier(1, &Barrier);
		GetInstance().m_CommandList->Close();

		ID3D12CommandList* CommandLists[]{GetInstance().m_CommandList.Get()};
		GetInstance().m_CommandQueue->ExecuteCommandLists(_countof(CommandLists), CommandLists);

		UINT64 FenceValue = GetInstance().m_FenceLastSignaledValue + 1;
		GetInstance().m_CommandQueue->Signal(GetInstance().m_Fence.Get(), FenceValue);
		GetInstance().m_FenceLastSignaledValue = FenceValue;
		CurrentFrameContext.FenceValue = FenceValue;
	}
}