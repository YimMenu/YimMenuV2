#pragma once

namespace rage
{
	class scrThread;
}

namespace YimMenu::Features
{
	class SavePersonalVehicle
	{
		static SavePersonalVehicle& GetInstance()
		{
			static SavePersonalVehicle instance;
			return instance;
		}

		void RunScriptImpl();

		bool m_ShouldRunScript = false;
		bool m_StartedByUs = false;
		rage::scrThread* m_Thread = nullptr;

	public:
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