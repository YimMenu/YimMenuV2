#include "AnticheatBypass.hpp"

#include "core/backend/ScriptMgr.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/util/Joaat.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/gta/Natives.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu
{
	static bool CheckForFSL()
	{
		HMODULE hWinmm    = GetModuleHandleA("WINMM.dll");
		bool hasFakeWINMM = hWinmm && GetProcAddress(hWinmm, "LawnchairGetVersion");

		int versionCount = 0;
		for (auto& module : ModuleMgr.GetModules())
		{
			if (module.first == "version.dll"_J)
				versionCount++;
		}

		bool hasFakeVersionDLL = versionCount > 1;

		return hasFakeWINMM || hasFakeVersionDLL;
	}


	static int GetFSLVersion()
	{
		using GetVersionFn = int (*)();
		HMODULE hMod       = GetModuleHandleA("WINMM.dll");
		if (!hMod)
			return -1;

		auto fn = reinterpret_cast<GetVersionFn>(GetProcAddress(hMod, "LawnchairGetVersion"));
		return fn ? fn() : -1;
	}

	static bool IsLocalSavesEnabled()
	{
		using Fn     = bool (*)();
		HMODULE hMod = GetModuleHandleA("WINMM.dll");
		if (!hMod)
			return false;

		auto fn = reinterpret_cast<Fn>(GetProcAddress(hMod, "LawnchairIsProvidingLocalSaves"));
		return fn ? fn() : false;
	}

	static bool IsBattleEyeBypassEnabled()
	{
		using Fn     = bool (*)();
		HMODULE hMod = GetModuleHandleA("WINMM.dll");
		if (!hMod)
			return false;

		auto fn = reinterpret_cast<Fn>(GetProcAddress(hMod, "LawnchairIsProvidingBattleEyeBypass"));
		return fn ? fn() : false;
	}

	static void TransactionHook(rage::scrNativeCallContext* ctx)
	{
		if (ctx->GetArg<int>(3) == -50712147)
		{
			return ctx->SetReturnValue(FALSE);
		}
		return NativeInvoker::GetNativeHandler(NativeIndex::NET_GAMESERVER_BEGIN_SERVICE)(ctx);
	}

	void AnticheatBypass::RunScriptImpl()
	{
		NativeHooks::AddHook("shop_controller"_J, NativeIndex::NET_GAMESERVER_BEGIN_SERVICE, &TransactionHook);

		m_IsFSLLoaded = CheckForFSL();
		m_FSLVersion  = GetFSLVersion();
		m_LocalSaves  = IsLocalSavesEnabled();
		m_BEBypass    = IsBattleEyeBypassEnabled();

		m_BattlEyeRunning = (NETWORK::_NETWORK_GET_GAME_RESTART_REASON() == 0 && GetModuleHandleA("BEClient_x64.dll")) && !m_IsFSLLoaded;

		const char* mode = "Vanilla";

		if (m_BattlEyeRunning)
			mode = "Legit BattlEye";
		else if (m_IsFSLLoaded)
			mode = "FSL";

		LOGF(VERBOSE, "Anticheat Bypass Mode: {}", mode);
		LOGF(VERBOSE, "[FSL] Loaded: {} | Version: {} | Local Saves: {} | BE Bypass: {}", m_IsFSLLoaded ? "Yes" : "No", m_FSLVersion, m_LocalSaves ? "Enabled" : "Disabled", m_BEBypass ? "Enabled" : "Disabled");

		if (m_BattlEyeRunning)
		{
			LOGF(WARNING, "[Anticheat] If you are not using a real BattlEye bypass, exit immediately and disable BE!");
		}

		if (!m_IsFSLLoaded)
			Pointers.BattlEyeStatusUpdatePatch->Apply();

		while (true)
		{
			if (!m_IsFSLLoaded)
			{
				*Pointers.BERestartStatus = 0;
				*Pointers.NeedsBERestart  = false;
				*Pointers.IsBEBanned      = false;
			}

			ScriptMgr::Yield();
		}
	}
}
