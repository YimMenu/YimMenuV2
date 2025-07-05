#include "common.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/HotkeySystem.hpp"
#include "core/settings/Settings.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/hooking/Hooking.hpp"
#include "core/hooking/CallHook.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/renderer/Renderer.hpp"
#include "core/util/Wine.hpp"
#include "core/scripting/LuaManager.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/backend/Players.hpp"
#include "game/backend/SavedLocations.hpp"
#include "game/backend/SavedPlayers.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/backend/Tunables.hpp"
#include "game/backend/ScriptPointers.hpp"
#include "game/frontend/GUI.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/features/vehicle/SavePersonalVehicle.hpp"
#include "game/features/self/OpenGunLocker.hpp"
#include "game/features/recovery/DailyActivities.hpp"

namespace YimMenu
{
	DWORD Main(void*)
	{
		const auto documents = std::filesystem::path(std::getenv("appdata")) / "YimMenuV2";
		FileMgr::Init(documents);

		LogHelper::Init("YimMenuV2", FileMgr::GetProjectFile("./cout.log"));

		LOGF(INFO, "Welcome to YimMenuV2! Build date: {} at {}", __DATE__, __TIME__);

		g_HotkeySystem.RegisterCommands();
		SavedLocations::FetchSavedLocations();
		Settings::Initialize(FileMgr::GetProjectFile("./settings.json"));

		if (!ModuleMgr.LoadModules())
			goto EARLY_UNLOAD;

		if (ModuleMgr.IsManualMapped())
			LOGF(WARNING, "Manual mapping detected, switch to normal injection if you're having issues");

		if (!Pointers.Init())
			goto EARLY_UNLOAD;

		AnticheatBypass::RunOnStartup();

		if (!Renderer::Init())
			goto EARLY_UNLOAD;

		Players::Init();

		Hooking::Init();

		ScriptMgr::Init();
		LOG(INFO) << "ScriptMgr initialized";

		ScriptPointers::Init();

		GUI::Init();

		ScriptMgr::AddScript(std::make_unique<Script>(&NativeHooks::RunScript)); // runs once
		ScriptMgr::AddScript(std::make_unique<Script>(&Tunables::RunScript));    // runs once
		ScriptMgr::AddScript(std::make_unique<Script>(&AnticheatBypass::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&Self::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&GUI::RunScript));
		FiberPool::Init(16);
		ScriptMgr::AddScript(std::make_unique<Script>(&LuaManager::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&HotkeySystem::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&Commands::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&Features::SavePersonalVehicle::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&Features::OpenGunLocker::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&Features::OpenStreetDealerMenu::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&SavedPlayers::RunScript));

		if (!Pointers.LateInit())
			LOG(WARNING) << "Socialclub patterns failed to load";

		Notifications::Show("YimMenuV2", "Loaded succesfully", NotificationType::Success);

		if (InWine().value_or(false))
		    LOG(INFO) << "Running in Wine!";

		while (g_Running)
		{
			Settings::Tick();
			std::this_thread::yield();
		}

		LOG(INFO) << "Unloading";
		NativeHooks::Destroy();
		FiberPool::Destroy();
		ScriptMgr::Destroy();
		Hooking::Destroy();
		CallSiteHook::Destroy();

	EARLY_UNLOAD:
		g_Running = false;
		Renderer::Destroy();
		LogHelper::Destroy();

		CloseHandle(g_MainThread);
		FreeLibraryAndExitThread(g_DllInstance, EXIT_SUCCESS);

		return EXIT_SUCCESS;
	}
}

BOOL WINAPI DllMain(HINSTANCE dllInstance, DWORD reason, void*)
{
	using namespace YimMenu;

	if (dllInstance)
		DisableThreadLibraryCalls(dllInstance);

	if (reason == DLL_PROCESS_ATTACH)
	{
		g_DllInstance = dllInstance;

		g_MainThread = CreateThread(nullptr, 0, Main, nullptr, 0, &g_MainThreadId);
	}
	return true;
}