#pragma once
#include "core/util/Joaat.hpp"

#include <backends/imgui_impl_dx12.h>
#include <comdef.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <functional>
#include <map>
#include <windows.h>
#include <wrl/client.h>


#define REL(o)       \
	o->Release();    \
	if (o)           \
	{                \
		o = nullptr; \
	}

namespace YimMenu
{
	using namespace Microsoft::WRL;
	using RendererCallBack = std::function<void()>;
	using WindowProcedureCallback = std::function<void(HWND, UINT, WPARAM, LPARAM)>;

	struct FrameContext
	{
		ID3D12CommandAllocator* CommandAllocator;
		ID3D12Resource* Resource;
		D3D12_CPU_DESCRIPTOR_HANDLE Descriptor;
		UINT64 FenceValue;
	};

	struct ExampleDescriptorHeapAllocator
	{
		ID3D12DescriptorHeap* Heap = nullptr;
		D3D12_DESCRIPTOR_HEAP_TYPE HeapType = D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES;
		D3D12_CPU_DESCRIPTOR_HANDLE HeapStartCpu;
		D3D12_GPU_DESCRIPTOR_HANDLE HeapStartGpu;
		UINT HeapHandleIncrement;
		ImVector<int> FreeIndices;

		void Create(ID3D12Device* device, ID3D12DescriptorHeap* heap)
		{
			IM_ASSERT(Heap == nullptr && FreeIndices.empty());
			Heap = heap;
			D3D12_DESCRIPTOR_HEAP_DESC desc = heap->GetDesc();
			HeapType = desc.Type;
			HeapStartCpu = Heap->GetCPUDescriptorHandleForHeapStart();
			HeapStartGpu = Heap->GetGPUDescriptorHandleForHeapStart();
			HeapHandleIncrement = device->GetDescriptorHandleIncrementSize(HeapType);
			FreeIndices.reserve((int)desc.NumDescriptors);
			for (int n = desc.NumDescriptors; n > 0; n--)
				FreeIndices.push_back(n - 1);
		}
		void Destroy()
		{
			Heap = nullptr;
			FreeIndices.clear();
		}
		void Alloc(D3D12_CPU_DESCRIPTOR_HANDLE* out_cpu_desc_handle, D3D12_GPU_DESCRIPTOR_HANDLE* out_gpu_desc_handle)
		{
			IM_ASSERT(FreeIndices.Size > 0);
			int idx = FreeIndices.back();
			FreeIndices.pop_back();
			out_cpu_desc_handle->ptr = HeapStartCpu.ptr + (idx * HeapHandleIncrement);
			out_gpu_desc_handle->ptr = HeapStartGpu.ptr + (idx * HeapHandleIncrement);
		}
		void Free(D3D12_CPU_DESCRIPTOR_HANDLE out_cpu_desc_handle, D3D12_GPU_DESCRIPTOR_HANDLE out_gpu_desc_handle)
		{
			int cpu_idx = (int)((out_cpu_desc_handle.ptr - HeapStartCpu.ptr) / HeapHandleIncrement);
			int gpu_idx = (int)((out_gpu_desc_handle.ptr - HeapStartGpu.ptr) / HeapHandleIncrement);
			IM_ASSERT(cpu_idx == gpu_idx);
			FreeIndices.push_back(cpu_idx);
		}
	};

	class Renderer final
	{
	private:
		Renderer();

	public:
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		static void Destroy()
		{
			GetInstance().DestroyImpl();
		}
		static bool Init()
		{
			return GetInstance().InitImpl();
		}

		/**
		 * @brief Add a callback function to draw using ImGui
		 * 
		 * @param callback Callback function
		 * @param priority Low values will be drawn before higher values.
		 * @return true Successfully added callback.
		 * @return false Duplicate render priority was given.
		 */
		static bool AddRendererCallBack(RendererCallBack&& callback, std::uint32_t priority)
		{
			return GetInstance().AddRendererCallBackImpl(std::move(callback), priority);
		}
		/**
		 * @brief Add a callback function to handle Windows WindowProcedure
		 * 
		 * @param callback Callback function
		 */
		static void AddWindowProcedureCallback(WindowProcedureCallback&& callback)
		{
			GetInstance().AddWindowProcedureCallbackImpl(std::move(callback));
		}

		static void DX12OnPresent()
		{
			GetInstance().DX12OnPresentImpl();
		}

		static LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
		{
			return GetInstance().WndProcImpl(hwnd, msg, wparam, lparam);
		}

		static void WaitForLastFrame();
		static void WaitForNextFrame();

		static void DX12PreResize();
		static void DX12PostResize();

		static bool IsResizing()
		{
			return GetInstance().m_Resizing;
		}

		static void SetResizing(const bool& status)
		{
			GetInstance().m_Resizing = status;
		}

		static void Resize(float scale)
		{
			GetInstance().ResizeImpl(scale);
		}

		static void SetFontsUpdated()
		{
			GetInstance().m_FontsUpdated = true;
		}

		static void SetSafeToRender()
		{
			GetInstance().m_SafeToRender = true;
		}

	private:
		static void DX12NewFrame();
		static void DX12EndFrame();

	private:
		void DestroyImpl();
		bool InitImpl();

		bool InitDX12();

		void ResizeImpl(float scale);

		bool AddRendererCallBackImpl(RendererCallBack&& callback, std::uint32_t priority);
		void AddWindowProcedureCallbackImpl(WindowProcedureCallback&& callback);

		void DX12OnPresentImpl();

		LRESULT WndProcImpl(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		static Renderer& GetInstance()
		{
			static Renderer i{};

			return i;
		}

	public:
		ExampleDescriptorHeapAllocator m_HeapAllocator;

	private:
		bool m_Initialized;
		bool m_Resizing;
		bool m_SafeToRender;

		// Shared
		ImFontAtlas m_FontAtlas;

		//DX12
		std::vector<FrameContext> m_FrameContext;

		DXGI_SWAP_CHAIN_DESC m_SwapChainDesc;
		ComPtr<IDXGISwapChain1> m_GameSwapChain;
		ComPtr<IDXGISwapChain3> m_SwapChain;
		ComPtr<ID3D12Device> m_Device;
		ComPtr<ID3D12CommandQueue> m_CommandQueue;
		ComPtr<ID3D12CommandAllocator> m_CommandAllocator;
		ComPtr<ID3D12GraphicsCommandList> m_CommandList;
		ComPtr<ID3D12DescriptorHeap> m_BackbufferDescriptorHeap;
		ComPtr<ID3D12DescriptorHeap> m_DescriptorHeap;

		ComPtr<ID3D12Fence> m_Fence;
		HANDLE m_FenceEvent{};
		UINT64 m_FenceLastSignaledValue{};
		HANDLE m_SwapchainWaitableObject{};
		UINT64 m_FrameIndex{};

		bool m_FontsUpdated;

	private:
		//Other
		std::map<joaat_t, RendererCallBack> m_RendererCallBacks;
		std::vector<WindowProcedureCallback> m_WindowProcedureCallbacks;
	};
}

// Make our linker aware of the ImGui WndProcHandler
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);