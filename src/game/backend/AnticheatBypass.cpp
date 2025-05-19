#include "AnticheatBypass.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/util/Joaat.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/gta/Natives.hpp"


using FnGetVersion = int(*)();
using FnLocalSaves = bool(*)();
using FnBattlEyeBypass = bool(*)();

namespace YimMenu
{
	static bool CheckForFSL()
	{
		int num_versions = 0;
		for (auto& module : ModuleMgr.GetModules())
			if (module.first == "WINMM.dll"_J)
				num_versions++;

		return num_versions > 1;
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
		m_BattlEyeRunning = (NETWORK::_NETWORK_GET_GAME_RESTART_REASON() == 0 && GetModuleHandleA("BEClient_x64.dll")) && !m_IsFSLLoaded;

		const char* mode = "Vanilla";

		if (m_BattlEyeRunning)
			mode = "Legit BattlEye";
		else if (m_IsFSLLoaded)
			mode = "FSL";
	
		LOGF(VERBOSE, "Anticheat bypass mode: {}", mode);

		if (m_IsFSLLoaded)
		{
			HMODULE hFSL = GetModuleHandleA("WINMM.dll");
			if (hFSL)
			{
				auto LawnchairGetVersion = reinterpret_cast<FnGetVersion>(GetProcAddress(hFSL, "LawnchairGetVersion"));
				auto LawnchairIsProvidingLocalSaves = reinterpret_cast<FnLocalSaves>(GetProcAddress(hFSL, "LawnchairIsProvidingLocalSaves"));
				auto LawnchairIsProvidingBattlEyeBypass = reinterpret_cast<FnBattlEyeBypass>(GetProcAddress(hFSL, "LawnchairIsProvidingBattlEyeBypass"));

				if (LawnchairGetVersion && LawnchairIsProvidingLocalSaves && LawnchairIsProvidingBattlEyeBypass)
				{
					m_FSLVersion         = LawnchairGetVersion();
					m_FSLProvidesLocalSaves = LawnchairIsProvidingLocalSaves();
					m_FSLProvidesBEBypass   = LawnchairIsProvidingBattlEyeBypass();

					LOGF(VERBOSE, "FSL Version: {}", m_FSLVersion);
					LOGF(VERBOSE, "FSL Local Saves: {}", m_FSLProvidesLocalSaves ? "Enabled" : "Disabled");
					LOGF(VERBOSE, "FSL BE Bypass: {}", m_FSLProvidesBEBypass ? "Enabled" : "Disabled");
				}
				else
				{
					LOGF(WARNING, "FSL detected but required exports were missing.");
				}
			}
		}

		if (m_BattlEyeRunning)
			LOGF(WARNING, "If you are not running an actual BattlEye bypass, exit the game immediately and ensure that BE is properly disabled");

		if (!m_IsFSLLoaded)
			Pointers.BattlEyeStatusUpdatePatch->Apply();

		while (true)
		{
			if (!m_IsFSLLoaded)
			{
				*Pointers.BERestartStatus = 0;
				*Pointers.NeedsBERestart = false;
				*Pointers.IsBEBanned = false;
			}
			ScriptMgr::Yield();
		}
	}
}