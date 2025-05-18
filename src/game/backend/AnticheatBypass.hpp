#pragma once

namespace YimMenu
{
	class AnticheatBypass
	{
	private:
		static AnticheatBypass& GetInstance()
		{
			static AnticheatBypass instance;
			return instance;
		}

		void RunScriptImpl();

		bool m_IsFSLLoaded = false;
		bool m_BattlEyeRunning = false;
		int m_FSLVersion          = -1;
		bool m_ProvidesLocalSaves = false;
		bool m_ProvidesBEBYPASS   = false;

	public:
		static void RunScript()
		{
			GetInstance().RunScriptImpl();
		}

		static bool IsFSLLoaded()
		{
			return GetInstance().m_IsFSLLoaded;
		}

		// actual battleye, as opposed to the FSL shim
		static bool IsBattlEyeRunning()
		{
			return GetInstance().m_BattlEyeRunning;
		}

		static int GetFSLVersion()
		{
			return GetInstance().m_FSLVersion;
		}

		static bool ProvidesLocalSaves()
		{
			return GetInstance().m_ProvidesLocalSaves;
		}

		static bool ProvidesBattlEyeBypass()
		{
			return GetInstance().m_ProvidesBEBYPASS;
		}
	};
}