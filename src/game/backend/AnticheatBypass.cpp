#include "AnticheatBypass.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/util/Joaat.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/gta/Natives.hpp"
#include "types/rage/gameSkeleton.hpp"
#include "types/anticheat/CAnticheatContext.hpp"
#include "types/game_files/CGameDataHash.hpp"

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

	static void NopGameSkeletonElement(rage::gameSkeletonUpdateElement* element)
	{
		// TODO: small memory leak
		// Hey rockstar if you keep up with this I'll make you integrity check everything until you can't anymore, please grow a brain and realize that this is futile
		// and kills performance if you're the host
		auto vtable = *reinterpret_cast<void***>(element);
		if (vtable[1] == Pointers.Nullsub)
			return; // already nopped

		auto new_vtable = new void*[3];
		memcpy(new_vtable, vtable, sizeof(void*) * 3);
		new_vtable[1] = Pointers.Nullsub;
		*reinterpret_cast<void***>(element) = new_vtable;
	}

	static void DefuseSigscanner()
	{
		bool patched = false;
		for (auto mode = Pointers.GameSkeleton->m_UpdateModes; mode; mode = mode->m_Next)
		{
			for (auto update_node = mode->m_Head; update_node; update_node = update_node->m_Next)
			{
				if (update_node->m_Hash != "Common Main"_J)
					continue;

				auto group = reinterpret_cast<rage::gameSkeletonUpdateGroup*>(update_node);

				for (auto group_child_node = group->m_Head; group_child_node; group_child_node = group_child_node->m_Next)
				{
					// TamperActions is a leftover from the old AC, but still useful to block anyway
					if (group_child_node->m_Hash != 0xA0F39FB6 && group_child_node->m_Hash != "TamperActions"_J)
						continue;
					patched = true;

					NopGameSkeletonElement(reinterpret_cast<rage::gameSkeletonUpdateElement*>(group_child_node));
				}
				break;
			}
		}


		if (patched)
		{
			LOGF(VERBOSE, "DefuseSigscanner: Patched out the sigscanner");
		}
		else
		{
			LOGF(WARNING, "DefuseSigscanner: Failed to patch the sigscanner");
		}
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
		DefuseSigscanner();
		
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