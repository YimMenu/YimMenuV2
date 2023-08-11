#pragma once
#include "util/Joaat.hpp"

#include <d3d11.h>
#include <functional>
#include <map>
#include <windows.h>

namespace YimMenu
{
	using DXCallback              = std::function<void()>;
	using WindowProcedureCallback = std::function<void(HWND, UINT, WPARAM, LPARAM)>;

	class Renderer final
	{
	private:
		Renderer();

	public:
		~Renderer();

		Renderer(const Renderer&)                = delete;
		Renderer(Renderer&&) noexcept            = delete;
		Renderer& operator=(const Renderer&)     = delete;
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
		static bool AddDXCallback(DXCallback&& callback, std::uint32_t priority)
		{
			return GetInstance().AddDXCallbackImpl(std::move(callback), priority);
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

		static void OnPresent()
		{
			GetInstance().OnPresentImpl();
		}
		static LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
		{
			return GetInstance().WndProcImpl(hwnd, msg, wparam, lparam);
		}

		static void PreResize();
		static void PostResize();

	private:
		static void NewFrame();
		static void EndFrame();

	private:
		void DestroyImpl();
		bool InitImpl();

		bool AddDXCallbackImpl(DXCallback&& callback, std::uint32_t priority);
		void AddWindowProcedureCallbackImpl(WindowProcedureCallback&& callback);

		void OnPresentImpl();
		LRESULT WndProcImpl(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		static Renderer& GetInstance()
		{
			static Renderer i{};

			return i;
		}

	private:
		ID3D11Device* m_Device;
		ID3D11DeviceContext* m_DeviceContext;
		IDXGISwapChain* m_SwapChain;

		std::map<joaat_t, DXCallback> m_DXCallbacks;
		std::vector<WindowProcedureCallback> m_WindowProcedureCallbacks;
	};
}

// Make our linker aware of the ImGui WndProcHandler
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);