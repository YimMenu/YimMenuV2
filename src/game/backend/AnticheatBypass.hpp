#pragma once

namespace YimMenu
{
	enum class FSLStatus
	{
		NotLoaded,
		Loaded_NoBypass,
		FSL_BypassEnabled
	};

	class AnticheatBypass
	{
	private:
		static AnticheatBypass& GetInstance()
		{
			static AnticheatBypass instance;
			return instance;
		}

		void RunScriptImpl();
		bool m_IsFSLLoaded     = false;
		bool m_BattlEyeRunning = false;

	public:
		static void RunScript()
		{
			GetInstance().RunScriptImpl();
		}

		static bool IsFSLLoaded()
		{
			return GetModuleHandleA("WINMM.dll") != nullptr;
		}

		static bool IsBattlEyeRunning()
		{
			return GetInstance().m_BattlEyeRunning;
		}

		static int GetFSLVersion()
		{
			using Fn     = int(__stdcall*)();
			HMODULE hMod = GetModuleHandleA("WINMM.dll");
			if (!hMod)
				return -1;
			auto fn = reinterpret_cast<Fn>(GetProcAddress(hMod, "LawnchairGetVersion"));
			return fn ? fn() : -1;
		}

		static bool IsLocalSavesEnabled()
		{
			using Fn     = bool(__stdcall*)();
			HMODULE hMod = GetModuleHandleA("WINMM.dll");
			if (!hMod)
				return false;
			auto fn = reinterpret_cast<Fn>(GetProcAddress(hMod, "LawnchairIsProvidingLocalSaves"));
			return fn ? fn() : false;
		}

		static bool IsBattleEyeBypassEnabled()
		{
			using Fn     = bool(__stdcall*)();
			HMODULE hMod = GetModuleHandleA("WINMM.dll");
			if (!hMod)
				return false;
			auto fn = reinterpret_cast<Fn>(GetProcAddress(hMod, "LawnchairIsProvidingBattlEyeBypass"));
			return fn ? fn() : false;
		}

		static FSLStatus GetFSLStatus()
		{
			if (!IsFSLLoaded())
				return FSLStatus::NotLoaded;

			if (IsBattleEyeBypassEnabled())
				return FSLStatus::FSL_BypassEnabled;

			return FSLStatus::Loaded_NoBypass;
		}
	};
}
