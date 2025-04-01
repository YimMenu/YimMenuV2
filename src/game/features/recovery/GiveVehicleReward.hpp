#pragma once

namespace rage
{
	class scrThread;
}

namespace YimMenu
{
	class GiveVehicleReward
	{
		static GiveVehicleReward& GetInstance()
		{
			static GiveVehicleReward instance;
			return instance;
		}

		void RunScriptImpl();

		bool m_ShouldRunScript    = false;
		bool m_StartedByUs        = false;
		rage::scrThread* m_Thread = nullptr;

	public:
		static bool IsSafeToRunScript();

		static void RunScript()
		{
			GetInstance().RunScriptImpl();
		}

		static void SetShouldRunScript(bool run)
		{
			GetInstance().m_ShouldRunScript = run;
		}
	};
}