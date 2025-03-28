#pragma once

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

		bool m_ShouldRunScript = false;

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