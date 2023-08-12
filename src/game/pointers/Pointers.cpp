#include "Pointers.hpp"

#include "core/memory/BytePatch.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/memory/PatternScanner.hpp"
#include "util/Joaat.hpp"

namespace YimMenu
{
	bool Pointers::Init()
	{
		const auto gta5 = ModuleMgr.Get("GTA5.exe"_J);
		if (!gta5)
		{
			LOG(FATAL) << "Could not find " << gta5->Name() << ", is this GTA5?";

			return false;
		}

		auto scanner = PatternScanner(gta5);

		constexpr auto swapchainPtrn = Pattern<"48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8">("IDXGISwapChain");
		scanner.Add(swapchainPtrn, [this](PointerCalculator ptr) {
			SwapChain = ptr.Add(3).Rip().As<IDXGISwapChain**>();
		});

		constexpr auto wndProcPtrn = Pattern<"48 8B C4 48 89 58 08 4C 89 48 20 55 56 57 41 54 41 55 41 56 41 57 48 8D 68 A1 48 81 EC F0">("WNDPROC");
		scanner.Add(wndProcPtrn, [this](PointerCalculator ptr) {
			WndProc = ptr.As<WNDPROC>();
		});

		constexpr auto debugTrap = Pattern<"48 83 EC 28 33 C9 FF 15 ? ? ? ? 45 33 C9">("DebugTrap");
		scanner.Add(debugTrap, [this](PointerCalculator ptr) {
			BytePatch::Make(ptr.As<void*>(), std::to_array({0xC3, 0x90, 0x90, 0x90}))->Apply();

			UnhookWindowsHookEx(*ptr.Add(45).Rip().As<HHOOK*>());
		});

		constexpr auto nativeHandlersPtrn = Pattern<"48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A">("NativeHandlers");
		scanner.Add(nativeHandlersPtrn, [this](PointerCalculator ptr) {
			NativeRegistrationTable = ptr.Add(3).Rip().As<void*>();
			GetNativeHandler        = ptr.Add(12).Rip().As<Functions::GetNativeHandler>();
		});

		constexpr auto fixVectorsPtrn = Pattern<"83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA">("FixVectors");
		scanner.Add(fixVectorsPtrn, [this](PointerCalculator ptr) {
			FixVectors = ptr.As<Functions::FixVectors>();
		});

		if (!scanner.Scan())
		{
			LOG(FATAL) << "Some patterns could not be found, unloading.";

			return false;
		}

		if (Hwnd = FindWindow("grcWindow", nullptr); !Hwnd)
		{
			LOG(FATAL) << "Failed to grab game window, unloading.";

			return false;
		}

		return true;
	}
}