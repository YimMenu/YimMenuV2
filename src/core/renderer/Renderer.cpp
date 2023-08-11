#include "Renderer.hpp"

#include "game/pointers/Pointers.hpp"

#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>
#include <imgui.h>

namespace YimMenu
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::DestroyImpl()
	{
		if (m_SwapChain && m_Device && m_DeviceContext)
		{
			ImGui_ImplDX11_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();
		}
	}

	bool Renderer::InitImpl()
	{
		if (!Pointers.SwapChain)
		{
			LOG(WARNING) << "SwapChain pointer is invalid!";

			return false;
		}

		if (m_SwapChain = *Pointers.SwapChain; !m_SwapChain)
		{
			LOG(WARNING) << "Dereferenced SwapChain pointer is invalid!";

			return false;
		}

		if (const auto result = m_SwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&m_Device)); result < 0)
		{
			LOG(WARNING) << "Failed to get D3D Device with result: [" << result << "]";

			return false;
		}
		m_Device->GetImmediateContext(&m_DeviceContext);

		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		// never returns false, useless to check return
		ImGui_ImplDX11_Init(m_Device, m_DeviceContext);
		ImGui_ImplWin32_Init(Pointers.Hwnd);

		LOG(INFO) << "Renderer has finished initializing.";
		return true;
	}

	bool Renderer::AddDXCallbackImpl(DXCallback&& callback, std::uint32_t priority)
	{
		return m_DXCallbacks.insert({priority, callback}).second;
	}

	void Renderer::AddWindowProcedureCallbackImpl(WindowProcedureCallback&& callback)
	{
		return m_WindowProcedureCallbacks.push_back(callback);
	}

	void Renderer::OnPresentImpl()
	{
		Renderer::NewFrame();
		for (const auto& callback : m_DXCallbacks | std::views::values)
			callback();
		Renderer::EndFrame();
	}

	LRESULT Renderer::WndProcImpl(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		for (const auto& callback : m_WindowProcedureCallbacks)
			callback(hwnd, msg, wparam, lparam);

		return ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
	}

	void Renderer::PreResize()
	{
		ImGui_ImplDX11_InvalidateDeviceObjects();
	}

	void Renderer::PostResize()
	{
		ImGui_ImplDX11_CreateDeviceObjects();
	}

	void Renderer::NewFrame()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void Renderer::EndFrame()
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
}