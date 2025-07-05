#include "Pointers.hpp"

#include "core/backend/PatternCache.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/memory/PatternScanner.hpp"
#include "core/util/Joaat.hpp"
#include "types/rage/atArray.hpp"

namespace YimMenu
{
	// on some cracked game builds
	static bool IsSocialClubNeverGoingToLoad()
	{
		return Pointers.ScriptThreads && Pointers.ScriptThreads->size() != 0;
	}

	bool Pointers::Init()
	{
		PatternCache::Init();

		const auto gta5 = ModuleMgr.Get("GTA5_Enhanced.exe"_J);
		if (!gta5)
		{
			LOG(FATAL) << "Could not find GTA5_Enhanced.exe, is this GTA 5 Enhanced?";
			return false;
		}

		auto scanner = PatternScanner(gta5);

		constexpr auto swapchainPtrn = Pattern<"72 C7 EB 02 31 C0 8B 0D">("IDXGISwapChain");
		scanner.Add(swapchainPtrn, [this](PointerCalculator ptr) {
			CommandQueue = ptr.Add(0x1A).Add(3).Rip().As<ID3D12CommandQueue**>();
			SwapChain = ptr.Add(0x21).Add(3).Rip().As<IDXGISwapChain1**>();
		});

		constexpr auto wndProcPtrn = Pattern<"3D 85 00 00 00 0F 87 2D 02 00 00">("WndProc");
		scanner.Add(wndProcPtrn, [this](PointerCalculator ptr) {
			WndProc = ptr.Sub(0x4F).As<PVOID>();
		});

		constexpr auto hWndPtrn = Pattern<"E8 ? ? ? ? 84 C0 74 25 48 8B 0D">("HWND");
		scanner.Add(hWndPtrn, [this](PointerCalculator ptr) {
			Hwnd = ptr.Add(9).Add(3).Rip().As<HWND*>();
		});

		constexpr auto screenResPtrn = Pattern<"75 39 0F 57 C0 F3 0F 2A 05">("ScreenRes");
		scanner.Add(screenResPtrn, [this](PointerCalculator ptr) {
			ScreenResX = ptr.Add(0x5).Add(4).Rip().As<std::uint32_t*>();
			ScreenResY = ptr.Add(0x1E).Add(4).Rip().As<std::uint32_t*>();
		});

		constexpr auto versionPtrn = Pattern<"4C 8D 0D ? ? ? ? 48 8D 5C 24 ? 48 89 D9 48 89 FA">("Version");
		scanner.Add(versionPtrn, [this](PointerCalculator ptr) {
			GameVersion = ptr.Add(3).Rip().As<const char*>();
			OnlineVersion = ptr.Add(0x47).Add(3).Rip().As<const char*>();
		});

		constexpr auto scriptThreadsPtrn = Pattern<"48 8B 05 ? ? ? ? 48 89 34 F8 48 FF C7 48 39 FB 75 97">("ScriptThreads");
		scanner.Add(scriptThreadsPtrn, [this](PointerCalculator ptr) {
			ScriptThreads = ptr.Add(3).Rip().As<rage::atArray<rage::scrThread*>*>();
		});

		constexpr auto populateNativesPtrn = Pattern<"EB 2A 0F 1F 40 00 48 8B 54 17 10">("InitNativeTables");
		scanner.Add(populateNativesPtrn, [this](PointerCalculator ptr) {
			InitNativeTables = ptr.Sub(0x2A).As<PVOID>();
		});

		constexpr auto runScriptThreadsPtrn = Pattern<"BE 40 5D C6 00">("RunScriptThreads");
		scanner.Add(runScriptThreadsPtrn, [this](PointerCalculator ptr) {
			RunScriptThreads = ptr.Sub(0xA).As<PVOID>();
		});

		constexpr auto handlesAndPtrsPtrn = Pattern<"0F 1F 84 00 00 00 00 00 89 F8 0F 28 FE 41">("HandlesAndPtrs");
		scanner.Add(handlesAndPtrsPtrn, [this](PointerCalculator ptr) {
			HandleToPtr = ptr.Add(0x21).Add(1).Rip().As<Functions::HandleToPtr>();
			PtrToHandle = ptr.Sub(0xB).Add(1).Rip().As<Functions::PtrToHandle>();
		});

		constexpr auto pedFactoryPtrn = Pattern<"C7 40 30 03 00 00 00 48 8B 0D">("PedFactory");
		scanner.Add(pedFactoryPtrn, [this](PointerCalculator ptr) {
			PedFactory = ptr.Add(7).Add(3).Rip().As<CPedFactory**>();
		});

		constexpr auto getNetPlayerFromPidPtrn = Pattern<"83 FB 20 74 2A 89 D9">("GetNetPlayerFromPID");
		scanner.Add(getNetPlayerFromPidPtrn, [this](PointerCalculator ptr) {
			GetNetPlayerFromPid = ptr.Add(8).Rip().As<Functions::GetNetPlayerFromPid>();
		});

		constexpr auto isSessionStarted = Pattern<"0F B6 05 ? ? ? ? 0A 05 ? ? ? ? 75 2A">("IsSessionStarted");
		scanner.Add(isSessionStarted, [this](PointerCalculator addr) {
			IsSessionStarted = addr.Add(3).Rip().As<bool*>();
		});

		constexpr auto assignPhysicalIndexPtrn = Pattern<"41 8D 47 01 3C 20 0F 87 68 01 00 00">("AssignPhysicalIndex");
		scanner.Add(assignPhysicalIndexPtrn, [this](PointerCalculator ptr) {
			AssignPhysicalIndex = ptr.Sub(0x13).As<PVOID>();
		});

		constexpr auto networkPlayerManagerShutdownPtrn = Pattern<"84 C0 0F 84 88 00 00 00 4C 89 F9 E8">("NetworkPlayerMgrShutdown");
		scanner.Add(networkPlayerManagerShutdownPtrn, [this](PointerCalculator ptr) {
			NetworkPlayerMgrShutdown = ptr.Sub(0x1B).As<PVOID>();
		});

		constexpr auto scriptGlobalsPtrn = Pattern<"48 8B 8E B8 00 00 00 48 8D 15 ? ? ? ? 49 89 D8">("ScriptGlobals");
		scanner.Add(scriptGlobalsPtrn, [this](PointerCalculator ptr) {
			ScriptGlobals = ptr.Add(7).Add(3).Rip().As<std::int64_t**>();
		});

		constexpr auto sendNetworkDamagePtrn = Pattern<"0F B6 41 28 04 FE 3C 03 0F 87 EA">("SendNetworkDamage");
		scanner.Add(sendNetworkDamagePtrn, [this](PointerCalculator ptr) {
			TriggerWeaponDamageEvent = ptr.Sub(0x51).As<Functions::TriggerWeaponDamageEvent>();
		});

		constexpr auto scriptProgramsPtrn = Pattern<"48 C7 84 C8 D8 00 00 00 00 00 00 00">("ScriptPrograms");
		scanner.Add(scriptProgramsPtrn, [this](PointerCalculator ptr) {
			ScriptPrograms = ptr.Add(0x13).Add(3).Rip().Add(0xD8).As<rage::scrProgram**>();
		});

		constexpr auto regionCodePtrn = Pattern<"4C 8D 05 ? ? ? ? 48 89 F1 48 89 FA E8 ? ? ? ? 84 C0 74 3D">("RegionCode");
		scanner.Add(regionCodePtrn, [this](PointerCalculator ptr) {
			RegionCode = ptr.Add(3).Rip().As<int*>();
		});

		constexpr auto networkObjectMgrPtrn = Pattern<"41 83 7E FA 02 40 0F 9C C5 C1 E5 02">("NetworkObjectMgr&GetSyncTreeForType");
		scanner.Add(networkObjectMgrPtrn, [this](PointerCalculator ptr) {
			NetworkObjectMgr = ptr.Add(0xC).Add(3).Rip().As<CNetworkObjectMgr**>();
			GetSyncTreeForType = ptr.Add(0x13).Add(1).Rip().As<Functions::GetSyncTreeForType>();
		});

		constexpr auto writeNodeDataPtrn = Pattern<"48 8B 89 A8 00 00 00 48 8B 01 48 8B 40 10 48 FF E0">("WriteNodeData");
		scanner.Add(writeNodeDataPtrn, [this](PointerCalculator ptr) {
			WriteNodeData = ptr.As<PVOID>();
		});

		constexpr auto shouldUseNodeCachePtrn = Pattern<"83 FA 20 74 1D 48 89 CE">("ShouldUseNodeCache&Nullsub");
		scanner.Add(shouldUseNodeCachePtrn, [this](PointerCalculator ptr) {
			ShouldUseNodeCache = ptr.Sub(5).As<PVOID>();
			Nullsub = ptr.Add(0x29).As<PVOID>();
		});

		constexpr auto isNodeInScopePtrn = Pattern<"41 83 F9 02 74 22 48 8B 06">("IsNodeInScope");
		scanner.Add(isNodeInScopePtrn, [this](PointerCalculator ptr) {
			IsNodeInScope = ptr.Sub(0x26).As<PVOID>();
		});

		constexpr auto writeSyncTreePtrn = Pattern<"4D 89 CD 45 89 C6 41 89 D7 48 89 CF 8B 05 ? ? ? ? 65 48 8B 0C 25 58 00 00 00">("WriteSyncTree");
		scanner.Add(writeSyncTreePtrn, [this](PointerCalculator ptr) {
			WriteSyncTree = ptr.Sub(0x10).As<PVOID>();
		});

		constexpr auto migrateObjectPtrn = Pattern<"48 8B 96 D0 00 00 00 4C 89 F9 41 B8 03 00 00 00">("MigrateObject");
		scanner.Add(migrateObjectPtrn, [this](PointerCalculator ptr) {
			MigrateObject = ptr.Add(0x10).Add(1).Rip().As<Functions::MigrateObject>();
		});

		constexpr auto networkPlayerMgrPtrn = Pattern<"75 0E 48 8B 05 ? ? ? ? 48 8B 88 F0 00 00 00">("NetworkPlayerMgr");
		scanner.Add(networkPlayerMgrPtrn, [this](PointerCalculator ptr) {
			NetworkPlayerMgr = ptr.Add(2).Add(3).Rip().As<CNetworkPlayerMgr**>();
		});

		constexpr auto queuePacketPtrn = Pattern<"45 89 F1 E8 ? ? ? ? 84 C0 74 25">("QueuePacket");
		scanner.Add(queuePacketPtrn, [this](PointerCalculator ptr) {
			QueuePacket = ptr.Add(3).Add(1).Rip().As<Functions::QueuePacket>();
		});

		constexpr auto getNetObjectByIdPtrn = Pattern<"0F B7 4E 60 E8">("GetNetObjectById");
		scanner.Add(getNetObjectByIdPtrn, [this](PointerCalculator ptr) {
			GetNetObjectById = ptr.Add(4).Add(1).Rip().As<Functions::GetNetObjectById>();
		});

		constexpr auto requestControlPtrn = Pattern<"74 0A 48 89 F9 E8 ? ? ? ? 31 F6 89 F0 48 83 C4 20">("RequestControl");
		scanner.Add(requestControlPtrn, [this](PointerCalculator ptr) {
			RequestControl = ptr.Add(5).Add(1).Rip().As<Functions::RequestControl>();
		});

		constexpr auto spectatePatchPtrn = Pattern<"74 26 66 83 FF 0D 77 20 0F B7 C7">("SpectatePatch");
		scanner.Add(spectatePatchPtrn, [this](PointerCalculator ptr) {
			SpectatePatch = BytePatches::Add(ptr.As<std::uint8_t*>(), 0xEB);
		});

		constexpr auto modelSpawnBypassPtrn = Pattern<"E8 ? ? ? ? 48 8B 78 48">("ModelSpawnBypass");
		scanner.Add(modelSpawnBypassPtrn, [this](PointerCalculator ptr) {
			ModelSpawnBypass = BytePatches::Add(ptr.Add(1).Rip().Add(0x2B).As<std::uint8_t*>(), 0xEB);
		});

		constexpr auto worldModelSpawnBypassPtrn = Pattern<"4C 8B 2C 01 4D 85 ED 0F 84 ? ? ? ?">("WorldModelSpawnBypass");
		scanner.Add(worldModelSpawnBypassPtrn, [this](PointerCalculator ptr) {
			WorldModelSpawnBypass = BytePatches::Add(ptr.Add(4).As<void*>(), std::to_array<std::uint8_t>({0xEB, 0x12, 0x90}));
		});

		constexpr auto receiveNetMessagePtrn = Pattern<"48 81 C1 00 03 00 00 4C 89 E2">("ReceiveNetMessage");
		scanner.Add(receiveNetMessagePtrn, [this](PointerCalculator ptr) {
			ReceiveNetMessage = ptr.Add(0xD).Add(1).Rip().As<PVOID>();
		});

		constexpr auto netEventMgrPtrn = Pattern<"4C 8B 05 ? ? ? ? 44 0F B7 CA">("NetEventMgr");
		scanner.Add(netEventMgrPtrn, [this](PointerCalculator ptr) {
			NetEventMgr = ptr.Add(3).Rip().As<rage::netEventMgr**>();
		});

		constexpr auto sendEventAckPtrn = Pattern<"84 C0 75 ? 89 EE 49 8D AD">("SendEventAck");
		scanner.Add(sendEventAckPtrn, [this](PointerCalculator ptr) {
			EventAck = ptr.Sub(4).Rip().As<Functions::EventAck>();
			SendEventAck = ptr.Add(0x13).Add(1).Rip().As<Functions::SendEventAck>();
		});

		constexpr auto queueDependencyPtrn = Pattern<"0F 29 46 50 48 8D 05">("QueueDependency&SigScanMemory");
		scanner.Add(queueDependencyPtrn, [this](PointerCalculator ptr) {
			QueueDependency = ptr.Add(0x71).Add(1).Rip().As<PVOID>();
			SigScanMemory = ptr.Add(4).Add(3).Rip().As<PVOID>();
		});

		constexpr auto scriptVMPtrn = Pattern<"49 63 41 1C">("ScriptVM");
		scanner.Add(scriptVMPtrn, [this](PointerCalculator ptr) {
			ScriptVM = ptr.Sub(0x24).As<Functions::ScriptVM>();
		});

		constexpr auto prepareMetricForSendingPtrn = Pattern<"48 89 F9 FF 50 20 48 8D 15">("PrepareMetricForSending");
		scanner.Add(prepareMetricForSendingPtrn, [this](PointerCalculator ptr) {
			PrepareMetricForSending = ptr.Sub(0x26).As<PVOID>();
		});

		constexpr auto beDataPtrn = Pattern<"48 C7 05 ? ? ? ? 00 00 00 00 E8 ? ? ? ? 48 89 C1 E8 ? ? ? ? E8 ? ? ? ? BD 0A 00 00 00">("BEData");
		scanner.Add(beDataPtrn, [this](PointerCalculator ptr) {
			BERestartStatus = ptr.Add(3).Rip().Add(8).Add(4).As<int*>();
			NeedsBERestart = ptr.Add(3).Rip().Add(8).Add(4).Add(8).As<bool*>();
			IsBEBanned = ptr.Add(3).Rip().Add(8).Add(4).Add(8).Add(4).As<bool*>();
		});

		constexpr auto battlEyeStatusUpdatePatchPtrn = Pattern<"80 B9 92 0A 00 00 01">("BattlEyeStatusUpdatePatch");
		scanner.Add(battlEyeStatusUpdatePatchPtrn, [this](PointerCalculator ptr) {
			BattlEyeStatusUpdatePatch = BytePatches::Add(ptr.As<void*>(), 
				// since arxan obfuscated this subroutine, return mid-function instead
				// TODO: this might break in a later update
				std::to_array<std::uint8_t>({
					0x48, 0x83, 0xC4, 0x38, // add rsp, 38h
					0x5F,                   // pop rdi
					0x5E,                   // pop rsi
					0xC3                    // ret
				})
			);
		});

		constexpr auto writeNetArrayDataPtrn = Pattern<"0F 84 06 03 00 00 0F B6 83">("WriteNetArrayData");
		scanner.Add(writeNetArrayDataPtrn, [this](PointerCalculator ptr) {
			WriteNetArrayData = ptr.Sub(0x4E).As<PVOID>();
			NetArrayMgr = ptr.Sub(0x32).Add(3).As<rage::netArrayMgr**>();
		});

		constexpr auto netArrayCachedDataPatchPtrn = Pattern<"0F 84 64 FE FF FF FF">("NetArrayCachedDataPatch");
		scanner.Add(netArrayCachedDataPatchPtrn, [this](PointerCalculator ptr) {
			NetArrayCachedDataPatch = BytePatches::Add(ptr.As<void*>(), std::to_array<std::uint8_t>({0xE9, 0x65, 0xFE, 0xFF, 0xFF, 0x90}));
		});

		constexpr auto statsMgrPtrn = Pattern<"89 6C 24 28 48 8D 0D ? ? ? ? 48 8D">("CStatsMgr");
		scanner.Add(statsMgrPtrn, [this](PointerCalculator ptr) {
			StatsMgr = ptr.Add(4).Add(3).Rip().As<CStatsMgr*>();
		});

		constexpr auto getPackedStatDataPtrn = Pattern<"8D 81 37 FE FF FF">("GetPackedStatData");
		scanner.Add(getPackedStatDataPtrn, [this](PointerCalculator ptr) {
			GetPackedStatData = ptr.Sub(0xE).As<Functions::GetPackedStatData>();
		});

		constexpr auto getCatalogItemPtrn = Pattern<"0F 82 55 FF FF FF 44 89 7C 24 30">("NetCatalog&GetCatalogItem");
		scanner.Add(getCatalogItemPtrn, [this](PointerCalculator ptr) {
			NetCatalog = ptr.Add(0xB).Add(3).Rip().As<rage::netCatalog*>();
			GetCatalogItem = ptr.Add(0x17).Add(1).Rip().As<Functions::GetCatalogItem>();
		});

		constexpr auto transactionMgrPtrn = Pattern<"48 8B 05 ? ? ? ? 80 78 39 00 74 2D">("TransactionMgr");
		scanner.Add(transactionMgrPtrn, [this](PointerCalculator ptr) {
			TransactionMgr = ptr.Add(3).Rip().As<void**>();
		});

		constexpr auto getActiveBasketPtrn = Pattern<"48 8B 40 10 81 7B 0C AE A0 A9 04">("GetActiveBasket");
		scanner.Add(getActiveBasketPtrn, [this](PointerCalculator ptr) {
			GetActiveBasket = ptr.Sub(0x39).As<Functions::GetActiveBasket>();
		});

		constexpr auto pedPoolPtrn = Pattern<"80 79 4B 00 0F 84 F5 00 00 00 48 89 F1">("PedPool");
		scanner.Add(pedPoolPtrn, [this](PointerCalculator ptr) {
			PedPool = ptr.Add(0x18).Add(3).Rip().As<PoolEncryption*>();
		});

		constexpr auto vehiclePoolPtrn = Pattern<"48 83 78 18 0D">("VehiclePool");
		scanner.Add(vehiclePoolPtrn, [this](PointerCalculator ptr) {
			VehiclePool = ptr.Sub(0xA).Add(3).Rip().As<rage::fwVehiclePool***>();
		});

		constexpr auto objectPoolPtrn = Pattern<"48 8B 04 0A C3 0F B6 05">("ObjectPool");
		scanner.Add(objectPoolPtrn, [this](PointerCalculator ptr) {
			ObjectPool = ptr.Add(5).Add(3).Rip().As<PoolEncryption*>();
		});

		constexpr auto httpStartRequestPtrn = Pattern<"56 57 48 83 EC 28 48 89 CE 8B 81 ? ? ? ? FF C8 83 F8 04 0F 87">("HttpStartRequest");
		scanner.Add(httpStartRequestPtrn, [this](PointerCalculator ptr) {
			HttpStartRequest = ptr.As<PVOID>();
		});

		constexpr auto networkSessionPtrn = Pattern<"49 C7 86 F8 00 00 00 00 00 00 00 48 8B 05">("NetworkSession");
		scanner.Add(networkSessionPtrn, [this](PointerCalculator ptr) {
			NetworkSession = ptr.Add(0x17).Add(3).Rip().As<CNetworkSession**>();
		});

		constexpr auto joinSessionByInfoPtrn = Pattern<"B0 01 40 84 E9 0F 85 32 FD FF FF 48 89 F1">("JoinSessionByInfo");
		scanner.Add(joinSessionByInfoPtrn, [this](PointerCalculator ptr) {
			JoinSessionByInfo = ptr.Sub(0x7).Add(1).Rip().As<Functions::JoinSessionByInfo>();
		});

		constexpr auto getSessionByGamerHandle = Pattern<"48 C7 84 24 80 00 00 00 10 00 00 08">("GetSessionByGamerHandle");
		scanner.Add(getSessionByGamerHandle, [this](PointerCalculator ptr) {
			GetSessionByGamerHandle = ptr.Sub(0x4A).Add(1).Rip().As<Functions::GetSessionByGamerHandle>();
		});

		constexpr auto networkTimePtrn = Pattern<"89 05 ? ? ? ? 80 3D ? ? ? ? ? 0F 84 ? ? ? ? E9">("NetworkTime");
		scanner.Add(networkTimePtrn, [this](PointerCalculator ptr) {
			NetworkTime = ptr.Add(2).Rip().As<std::uint32_t*>();
		});

		constexpr auto gameTimerPtrn = Pattern<"3B 2D ? ? ? ? 76 ? 89 D9">("GameTimer");
		scanner.Add(gameTimerPtrn, [this](PointerCalculator ptr) {
			GameTimer = ptr.Add(2).Rip().As<std::uint32_t*>();
		});

		constexpr auto formatIntCaller1Ptrn = Pattern<"48 89 35 ? ? ? ? 48 8B 74 24">("FormatIntCaller1");
		scanner.Add(formatIntCaller1Ptrn, [this](PointerCalculator ptr) {
			FormatIntCaller1 = ptr.Add(0x5D).As<PVOID>();
		});

		constexpr auto formatIntCaller2Ptrn = Pattern<"48 B8 20 73 69 7A 65 3D 27 32 48 89 84 24">("FormatIntCaller2");
		scanner.Add(formatIntCaller2Ptrn, [this](PointerCalculator ptr) {
			FormatIntCaller2 = ptr.Sub(0x11).As<PVOID>();
		});

		constexpr auto shouldTargetEntityPatchPtrn = Pattern<"F6 80 A9 14 00 00 01">("ShouldNotTargetEntityPatch");
		scanner.Add(shouldTargetEntityPatchPtrn, [this](PointerCalculator ptr) {
			ShouldNotTargetEntityPatch = BytePatches::Add(ptr.Sub(0x53).As<void*>(), std::to_array<std::uint8_t>({0xB0, 0x00, 0xC3}));
		});

		constexpr auto getAssistedAimTypePatchPtrn = Pattern<"FF E0 48 8D 86">("GetAssistedAimTypePatch");
		scanner.Add(getAssistedAimTypePatchPtrn, [this](PointerCalculator ptr) {
			GetAssistedAimTypePatch = BytePatches::Add(ptr.Sub(0x15).As<void*>(), std::to_array<std::uint8_t>({0xBD, 0x01, 0x00, 0x00, 0x00}));
		});

		constexpr auto getLockOnPosPatchPtrn = Pattern<"0F 29 74 24 ? 48 89 D6 48 89 CF 48 8B 05">("GetLockOnPosPatch");
		scanner.Add(getLockOnPosPatchPtrn, [this](PointerCalculator ptr) {
			GetLockOnPosPatch = BytePatches::Add(ptr.Add(0x22).As<std::uint8_t*>(), 0xEB);
		});

		constexpr auto shouldAllowDriverLockOnPatchPtrn = Pattern<"75 ? 45 89 C7 49 89 CE">("ShouldAllowDriverLockOnPatch");
		scanner.Add(shouldAllowDriverLockOnPatchPtrn, [this](PointerCalculator ptr) {
			ShouldAllowDriverLockOnPatch = BytePatches::Add(ptr.Sub(0x2C).As<std::uint8_t*>(), std::to_array<std::uint8_t>({0xB0, 0x01, 0xC3}));
		});

		constexpr auto allowPausingInSessionPatchPtrn = Pattern<"80 88 ? ? ? ? ? EB ? E8">("AllowPausingInSessionPatch");
		scanner.Add(allowPausingInSessionPatchPtrn, [this](PointerCalculator ptr) {
			AllowPausingInSessionPatch = BytePatches::Add(ptr.Sub(0x1E).As<std::uint8_t*>(), 0xEB);
		});

		constexpr auto getPoolTypePtrn = Pattern<"BA CE 94 A6 ED E8">("GetPoolType");
		scanner.Add(getPoolTypePtrn, [this](PointerCalculator ptr) {
			GetPoolType = ptr.Sub(19).As<PVOID>();
		});

		constexpr auto setJoinRequestPoolTypePatchPtrn = Pattern<"89 86 ? ? ? ? E8 ? ? ? ? 89 C0">("SetJoinRequestPoolTypePatch");
		scanner.Add(setJoinRequestPoolTypePatchPtrn, [this](PointerCalculator ptr) {
			// MOV EAX, 0; 0 is the normal pool
			SetJoinRequestPoolTypePatch = BytePatches::Add(ptr.Sub(5).As<std::uint8_t*>(), std::to_array<std::uint8_t>({0xB8, 0x00, 0x00, 0x00, 0x00}));
		});

		constexpr auto handleJoinRequestIgnorePoolPatchPtrn = Pattern<"83 FD 05 ? ? ? 00 00 00 48 8B">("HandleJoinRequestIgnorePoolPatch");
		scanner.Add(handleJoinRequestIgnorePoolPatchPtrn, [this](PointerCalculator ptr) {
			HandleJoinRequestIgnorePoolPatch = BytePatches::Add(ptr.As<void*>(), std::to_array<std::uint8_t>({0x39, 0xC9, 0x90}));
		});

		constexpr auto statsMpCharacterMappingDataPtrn = Pattern<"48 8D 0D ? ? ? ? 89 F2 0F 28 74 24 ? 48 83 C4 38">("CStatsMpCharacterMappingData");
		scanner.Add(statsMpCharacterMappingDataPtrn, [this](PointerCalculator ptr) {
			StatsMpCharacterMappingData = ptr.Add(3).Rip().As<CStatsMpCharacterMappingData*>();
		});

		static constexpr auto scMembershipStuffPtrn = Pattern<"48 8D 15 ? ? ? ? 41 B8 18 02 00 00 E8">("ScMembershipStuff");
		scanner.Add(scMembershipStuffPtrn, [this](PointerCalculator addr) {
			HasGTAPlus = addr.Add(3).Rip().As<int*>();
		});

		constexpr auto battlEyeServerProcessPlayerJoinPtrn = Pattern<"41 57 41 56 41 55 41 54 56 57 55 53 48 83 EC 48 48 89 D3 48 89 CE E9">("BattlEyeServerProcessPlayerJoin");
		scanner.Add(battlEyeServerProcessPlayerJoinPtrn, [this](PointerCalculator ptr) {
			BattlEyeServerProcessPlayerJoin = ptr.As<PVOID>();
		});

		constexpr auto assistedAimShouldReleaseEntityPtrn = Pattern<"80 7F 28 04 75 6A">("AssistedAimShouldReleaseEntity");
		scanner.Add(assistedAimShouldReleaseEntityPtrn, [this](PointerCalculator ptr) {
			AssistedAimShouldReleaseEntity = ptr.Sub(0xF).As<PVOID>();
		});

		constexpr auto assistedAimFindNewTargetPtrn = Pattern<"0F 84 C9 00 00 00 48 89 CE 48 89 F9">("AssistedAimFindNewTarget");
		scanner.Add(assistedAimFindNewTargetPtrn, [this](PointerCalculator ptr) {
			AssistedAimFindNewTarget = ptr.Sub(0x33).As<Functions::AssistedAimFindNewTarget>();
		});

		constexpr auto gameSkeletonPtrn = Pattern<"0F B6 C0 8D 14 00 83 C2 02">("GameSkeleton");
		scanner.Add(gameSkeletonPtrn, [this](PointerCalculator ptr) {
			GameSkeleton = ptr.Add(0x9).Add(3).Rip().As<rage::gameSkeleton*>();
		});

		constexpr auto anticheatInitializedHashPtrn = Pattern<"89 9E C8 00 00 00 48 8B 0D ? ? ? ? 48 85 C9 74 46">("AnticheatInitializedHash&GetAnticheatInitializedHash");
		scanner.Add(anticheatInitializedHashPtrn, [this](PointerCalculator ptr) {
			AnticheatInitializedHash = ptr.Add(9).Rip().As<rage::Obf32**>();
			GetAnticheatInitializedHash = ptr.Add(0x13).Rip().As<PVOID>();
		});

		constexpr auto anticheatContextPtrn = Pattern<"48 8D BB 70 0A 00 00 4C 8D 35 ? ? ? ? 66 90">("AnticheatContext");
		scanner.Add(anticheatContextPtrn, [this](PointerCalculator ptr) {
			AnticheatContext = ptr.Sub(0x12).Add(3).Rip().As<CAnticheatContext**>();
		});

		constexpr auto getAnticheatInitializedHash2Ptrn = Pattern<"89 9E E8 00 00 00 89 C2 E8 ? ? ? ? 69">("GetAnticheatInitializedHash2");
		scanner.Add(getAnticheatInitializedHash2Ptrn, [this](PointerCalculator ptr) {
			GetAnticheatInitializedHash2 = ptr.Add(0x9).Rip().As<PVOID>();
		});

		constexpr auto abilityBarPatchPtrn = Pattern<"75 39 48 85 F6 74 1A 48 89 F1 E8">("AbilityBarPatch");
		scanner.Add(abilityBarPatchPtrn, [this](PointerCalculator ptr) {
			AbilityBarPatch = BytePatches::Add(ptr.As<std::uint16_t*>(), 0x9090);
		});

		static constexpr auto doMatchmakingAdvertisePtrn = Pattern<"C7 47 30 01 00 00 00 E9 92">("MatchmakingAdvertise");
		scanner.Add(doMatchmakingAdvertisePtrn, [this](PointerCalculator addr) {
			MatchmakingAdvertise = addr.Sub(0xC).Rip().As<PVOID>();
		});

		static constexpr auto doMatchmakingUpdatePtrn = Pattern<"C7 47 30 02 00 00 00 EB 7A">("MatchmakingUpdate");
		scanner.Add(doMatchmakingUpdatePtrn, [this](PointerCalculator addr) {
			MatchmakingUpdate = addr.Sub(0x8).Rip().As<PVOID>();
		});

		static constexpr auto doMatchmakingUnadvertisePtrn = Pattern<"C7 86 C8 01 00 00 04 00 00 00">("MatchmakingUnadvertise");
		scanner.Add(doMatchmakingUnadvertisePtrn, [this](PointerCalculator addr) {
			MatchmakingUnadvertise = addr.Sub(0xC).Rip().As<PVOID>();
		});

		static constexpr auto matchmakingSessionDetailSendResponsePtrn = Pattern<"48 B8 01 00 00 00 0D 00 00 00">("SessionDetailSendResponse");
		scanner.Add(matchmakingSessionDetailSendResponsePtrn, [this](PointerCalculator addr) {
			MatchmakingSessionDetailSendResponse = addr.Add(0x2F).Rip().As<PVOID>();
		});

		if (!scanner.Scan())
		{
			LOG(FATAL) << "Some patterns could not be found, unloading.";
			return false;
		}

		PatternCache::Update();
		return true;
	}

	bool Pointers::LateInit()
	{
		auto sc = ModuleMgr.Get("socialclub.dll"_J);
		while (!sc)
		{
			LOG(WARNING) << "Waiting for socialclub.dll";
			std::this_thread::sleep_for(1s);

			if (IsSocialClubNeverGoingToLoad())
			{
				LOG(WARNING) << "Timed out checking for socialclub.dll";
				return false;
			}

			ModuleMgr.LoadModules();
			sc = ModuleMgr.Get("socialclub.dll"_J);
		}

		auto scanner = PatternScanner(sc);

		constexpr auto getPresenceAttributesPtrn = Pattern<"48 8B C4 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 54 41 56 41 57 48 83 EC 40 33 DB 49">("GetPresenceAttributes");
		scanner.Add(getPresenceAttributesPtrn, [this](PointerCalculator ptr) {
			GetPresenceAttributes = ptr.As<Functions::GetPresenceAttributes>();
		});

		constexpr auto numHandlesPatchPtrn = Pattern<"83 FD 20 0F 87 54 02 00 00">("NumHandlesPatch");
		scanner.Add(numHandlesPatchPtrn, [this](PointerCalculator ptr) {
			BytePatches::Add(ptr.Add(2).As<std::uint8_t*>(), 100)->Apply(); // change handle limit to 100
		});

		constexpr auto readAttributePatchPtrn = Pattern<"75 70 EB 23">("ReadAttributesPatch");
		scanner.Add(readAttributePatchPtrn, [this](PointerCalculator ptr) {
			BytePatches::Add(ptr.As<void*>(), std::to_array<std::uint8_t>({0x90, 0x90}))->Apply();
		});

		constexpr auto readAttributePatch2Ptrn = Pattern<"32 C0 EB ? C7 83">("ReadAttributesPatch2");
		scanner.Add(readAttributePatch2Ptrn, [this](PointerCalculator ptr) {
			BytePatches::Add(ptr.As<void*>(), std::to_array<std::uint8_t>({0xB0, 0x01}))->Apply();
		});

		constexpr auto getAvatarsPtrn = Pattern<"89 4E 7C 48 8B CE E8 ? ? ? ? 84 C0">("GetAvatars");
		scanner.Add(getAvatarsPtrn, [this](PointerCalculator ptr) {
			GetAvatars = ptr.Add(6).Add(1).Rip().As<Functions::GetAvatars>();
		});

		if (!scanner.Scan())
		{
			LOG(WARNING) << "Some socialclub patterns could not be found";
			return false;
		}

		PatternCache::Update();
		return true;
	}
}