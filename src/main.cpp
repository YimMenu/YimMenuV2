#include "common.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/HotkeySystem.hpp"
#include "core/settings/Settings.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/hooking/Hooking.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/renderer/Renderer.hpp"
#include "game/backend/Players.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/frontend/GUI.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu
{
	DWORD Main(void*)
	{
		const auto documents = std::filesystem::path(std::getenv("appdata")) / "YimMenuV2";
		FileMgr::Init(documents);

		LogHelper::Init("YimMenuV2", FileMgr::GetProjectFile("./cout.log"));

		g_HotkeySystem.RegisterCommands();
		Settings::Initialize(FileMgr::GetProjectFile("./settings.json"));

		if (!ModuleMgr.LoadModules())
			goto EARLY_UNLOAD;

		if (!Pointers.Init())
			goto EARLY_UNLOAD;

		if (!Renderer::Init())
			goto EARLY_UNLOAD;

		Players::Init();

		Hooking::Init();

		ScriptMgr::Init();
		LOG(INFO) << "ScriptMgr initialized";

		GUI::Init();

		ScriptMgr::AddScript(std::make_unique<Script>(&NativeHooks::RunScript)); // runs once
		ScriptMgr::AddScript(std::make_unique<Script>(&Self::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&GUI::RunScript));
		FiberPool::Init(5);
		ScriptMgr::AddScript(std::make_unique<Script>(&HotkeySystem::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&Commands::RunScript));

		Notifications::Show("YimMenuV2", "Loaded succesfully", NotificationType::Success);

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

	DisableThreadLibraryCalls(dllInstance);

	if (reason == DLL_PROCESS_ATTACH)
	{
		g_DllInstance = dllInstance;

		g_MainThread = CreateThread(nullptr, 0, Main, nullptr, 0, &g_MainThreadId);
	}
	return true;
}