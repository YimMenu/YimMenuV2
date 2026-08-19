#pragma once

namespace YimMenu
{
	class GUI final
	{
	public:
		static void Init()
		{
			GetInstance().InitImpl();
		}

		static bool IsOpen()
		{
			return GetInstance().m_IsOpen;
		}

		static void Toggle()
		{
			GetInstance().m_IsOpen ^= true;
		}

		static bool IsUsingKeyboard()
		{
			return ImGui::GetIO().WantTextInput;
		}

		static void RunScript()
		{
			GetInstance().RunScriptImpl();
		}

		static void SetOnboarding(bool state)
		{
			GetInstance().SetOnboardingImpl(state);
		}

		static bool IsOnboarding()
		{
			return GetInstance().m_Onboarding;
		}

		static void ToggleMouse();

	private:
		void WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		void InitImpl();
		void SetOnboardingImpl(bool state);
		void RunScriptImpl();

		static GUI& GetInstance()
		{
			static GUI i{};

			return i;
		}

		bool m_IsOpen;
		bool m_Onboarding;
	};
}