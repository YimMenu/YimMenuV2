#include "AnticheatBypass.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/util/Joaat.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/gta/Natives.hpp"
#include "types/anticheat/CAnticheatContext.hpp"

using FnGetVersion = int (*)();
using FnLocalSaves = bool (*)();
using FnBattlEyeBypass = bool (*)();

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

	void AnticheatBypass::RunOnStartupImpl()
	{
		bool loaded_late = false;

		if (!*Pointers.AnticheatInitializedHash)
		{
			*Pointers.AnticheatInitializedHash = new rage::Obf32; // this doesn't get freed so we don't have to use the game allocator
			(*Pointers.AnticheatInitializedHash)->setData(0x124EA49D);
		}
		else
		{
			(*Pointers.AnticheatInitializedHash)->setData(0x124EA49D);
			loaded_late = true;
		}
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
			Module* FSL = nullptr;
			for (auto& module : ModuleMgr.GetModules())
				if (module.first == "WINMM.dll"_J && module.second->IsExported("LawnchairGetVersion"))
					FSL = module.second.get();

			if (FSL)
			{
				auto LawnchairGetVersion = FSL->GetExport<FnGetVersion>("LawnchairGetVersion");
				auto LawnchairIsProvidingLocalSaves = FSL->GetExport<FnLocalSaves>("LawnchairIsProvidingLocalSaves");
				auto LawnchairIsProvidingBattlEyeBypass = FSL->GetExport<FnBattlEyeBypass>("LawnchairIsProvidingBattlEyeBypass");

				if (LawnchairGetVersion && LawnchairIsProvidingLocalSaves && LawnchairIsProvidingBattlEyeBypass)
				{
					m_FSLVersion = LawnchairGetVersion();
					m_FSLProvidesLocalSaves = LawnchairIsProvidingLocalSaves();
					m_FSLProvidesBEBypass = LawnchairIsProvidingBattlEyeBypass();

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

		if (!m_FSLProvidesBEBypass && !m_BattlEyeRunning)
			Pointers.BattlEyeStatusUpdatePatch->Apply();

		while (true)
		{
			if (!m_FSLProvidesBEBypass && !m_BattlEyeRunning)
			{
				*Pointers.BERestartStatus = 0;
				*Pointers.NeedsBERestart = false;
				*Pointers.IsBEBanned = false;
			}
			ScriptMgr::Yield();
		}
	}
}
