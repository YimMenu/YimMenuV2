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

		bool m_IsFSLLoaded     = false;
		int m_FSLVersion       = -1;
		bool m_LocalSaves      = false;
		bool m_BEBypass        = false;
		bool m_BattlEyeRunning = false;

	public:
		static void RunScript()
		{
			GetInstance().RunScriptImpl();
		}

		static bool IsFSLLoaded()
		{
			return GetInstance().m_IsFSLLoaded;
		}

		static bool IsBattlEyeRunning()
		{
			return GetInstance().m_BattlEyeRunning;
		}

		static int GetFSLVersion()
		{
			return GetInstance().m_FSLVersion;
		}

		static bool IsLocalSavesEnabled()
		{
			return GetInstance().m_LocalSaves;
		}

		static bool IsBattleEyeBypassEnabled()
		{
			return GetInstance().m_BEBypass;
		}
	};
}
