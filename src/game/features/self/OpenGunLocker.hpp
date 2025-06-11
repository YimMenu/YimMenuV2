#pragma once

namespace rage
{
	class scrThread;
}

namespace YimMenu::Features
{
	class OpenGunLocker
	{
		static OpenGunLocker& GetInstance()
		{
			static OpenGunLocker instance;
			return instance;
		}

		rage::scrThread* m_Thread = nullptr;
		bool m_ShouldRunScript = false;

		void RunScriptImpl();

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