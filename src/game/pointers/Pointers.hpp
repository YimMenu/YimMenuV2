#pragma once
#include <d3d12.h>
#include <dxgi1_4.h>
#include <windows.h>
#include "types/script/scrNativeHandler.hpp"
#include "types/rage/ObfVar.hpp"
#include "core/memory/BytePatches.hpp"

namespace rage
{
	template<typename T>
	class atArray;
	class scrThread;
	class scrProgram;
	class netSyncTree;
	class netObject;
	class netConnectionManager;
	class netArrayMgr;
	class netEventMgr;
	class netCatalog;
	class netCatalogBaseItem;
	class fwBasePool;
	class fwVehiclePool;
	class rlSessionInfo;
	class rlGamerHandle;
	struct rlTaskStatus;
	class rlScTaskStatus;
	class rlSessionByGamerTaskResult;
	class rlQueryPresenceAttributesContext;
	class rlScGamerHandle;
	class rlQueryAccountsResult;
	class rlGetAvatarsContext;
	class rlGetAvatarsPlayerList;
	struct gameSkeleton;
}
class CPedFactory;
class CNetGamePlayer;
class CEntity;
class CNetworkObjectMgr;
class CNetworkPlayerMgr;
class PoolEncryption;
class CStatsMgr;
class CNetShopTransaction;
class CNetworkSession;
class CStatsMpCharacterMappingData;
class CAnticheatContext;

namespace YimMenu
{
	namespace Functions
	{
		using HandleToPtr = void* (*)(int handle);
		using PtrToHandle = int (*)(void* pointer);
		using GetNetPlayerFromPid = CNetGamePlayer* (*)(int id);
		using TriggerWeaponDamageEvent = void (*)(CEntity* source, CEntity* target, rage::fvector3* position, int hit_component, bool override_default_damage, int weapon_type, float override_damage, int tire_index, int suspension_index, int flags, uint32_t action_result_hash, int16_t action_result_id, int action_unk, bool hit_weapon, bool hit_weapon_ammo_attachment, bool silenced, bool unk, rage::fvector3* impact_direction);
		using GetSyncTreeForType = rage::netSyncTree* (*)(void* netObjMgr, uint16_t type);
		using MigrateObject = void (*)(CNetGamePlayer* player, rage::netObject* object, int type);
		using QueuePacket = void (*)(rage::netConnectionManager* mgr, int msg_id, void* data, int size, int flags, std::uint16_t* out_seq_id);
		using GetNetObjectById = rage::netObject* (*)(uint16_t id);
		using RequestControl = void (*)(rage::netObject* object);
		using EventAck = bool (*)(uintptr_t data, CNetGamePlayer* target_player, uint32_t event_index, uint32_t event_handled_bitset);
		using SendEventAck = void (*)(rage::netEventMgr* event_manager, CNetGamePlayer* source_player);
		using ScriptVM = int (*)(uint64_t* stack, int64_t** scr_globals, rage::scrProgram* program, void* ctx);
		using GetPackedStatData = void (*)(int index, int* row, bool* is_bool, bool* unk);
		using GetCatalogItem = rage::netCatalogBaseItem* (*)(rage::netCatalog * catalog, std::uint32_t* hash);
		using GetActiveBasket = CNetShopTransaction* (*)(void* mgr, int* out_txn_id);
		using JoinSessionByInfo = bool (*)(CNetworkSession* network, rage::rlSessionInfo* info, int unk, int flags, rage::rlGamerHandle* handles, int num_handles);
		using GetSessionByGamerHandle = bool (*)(int profile_index, rage::rlGamerHandle* handles, int num_handles, rage::rlSessionByGamerTaskResult* results, int num_results, bool* success, rage::rlTaskStatus* state);
		using GetPresenceAttributes = bool (*)(int profile_index, rage::rlScGamerHandle* handles, int num_handles, rage::rlQueryPresenceAttributesContext** contexts, int count, rage::rlScTaskStatus* state);
		using GetAvatars = bool (*)(rage::rlGetAvatarsContext* context, rage::rlGetAvatarsPlayerList* players);
		using AssistedAimFindNewTarget = bool (*)(__int64 a1);
	}

	struct PointerData
	{
		IDXGISwapChain1** SwapChain;
		ID3D12CommandQueue** CommandQueue;
		HWND* Hwnd;
		PVOID WndProc;
		std::uint32_t* ScreenResX;
		std::uint32_t* ScreenResY;
		const char* GameVersion;
		const char* OnlineVersion;
		rage::atArray<rage::scrThread*>* ScriptThreads;
		PVOID InitNativeTables;
		std::int64_t** ScriptGlobals;
		PVOID RunScriptThreads;
		Functions::HandleToPtr HandleToPtr;
		Functions::PtrToHandle PtrToHandle;
		CPedFactory** PedFactory;
		Functions::GetNetPlayerFromPid GetNetPlayerFromPid;
		bool* IsSessionStarted;
		PVOID AssignPhysicalIndex;
		PVOID NetworkPlayerMgrShutdown;
		Functions::TriggerWeaponDamageEvent TriggerWeaponDamageEvent;
		rage::scrProgram** ScriptPrograms;
		int* RegionCode;
		Functions::GetSyncTreeForType GetSyncTreeForType;
		CNetworkObjectMgr** NetworkObjectMgr;
		PVOID WriteNodeData;
		PVOID ShouldUseNodeCache;
		PVOID IsNodeInScope;
		PVOID WriteSyncTree;
		Functions::MigrateObject MigrateObject;
		CNetworkPlayerMgr** NetworkPlayerMgr;
		Functions::QueuePacket QueuePacket;
		Functions::GetNetObjectById GetNetObjectById;
		Functions::RequestControl RequestControl;
		BytePatch ModelSpawnBypass;
		BytePatch SpectatePatch; // used to patch the code that prevents you from spawning network objects when spectating
		BytePatch WorldModelSpawnBypass;
		PVOID ReceiveNetMessage;
		rage::netEventMgr** NetEventMgr;
		Functions::EventAck EventAck;
		Functions::SendEventAck SendEventAck;
		PVOID QueueDependency;
		PVOID SigScanMemory;
		Functions::ScriptVM ScriptVM;
		PVOID PrepareMetricForSending;
		int* BERestartStatus;
		bool* NeedsBERestart;
		bool* IsBEBanned;
		BytePatch BattlEyeStatusUpdatePatch;
		PVOID WriteNetArrayData;
		BytePatch NetArrayCachedDataPatch;
		rage::netArrayMgr** NetArrayMgr;
		CStatsMgr* StatsMgr;
		Functions::GetPackedStatData GetPackedStatData;
		rage::netCatalog* NetCatalog;
		Functions::GetCatalogItem GetCatalogItem;
		void** TransactionMgr;
		Functions::GetActiveBasket GetActiveBasket;
		PoolEncryption* PedPool;
		PoolEncryption* ObjectPool;
		rage::fwVehiclePool*** VehiclePool;
		PVOID HttpStartRequest;
		CNetworkSession** NetworkSession;
		Functions::JoinSessionByInfo JoinSessionByInfo;
		Functions::GetSessionByGamerHandle GetSessionByGamerHandle;
		Functions::GetPresenceAttributes GetPresenceAttributes;
		Functions::GetAvatars GetAvatars;
		std::uint32_t* NetworkTime;
		std::uint32_t* GameTimer;
		PVOID FormatIntCaller1;
		PVOID FormatIntCaller2;
		BytePatch ShouldNotTargetEntityPatch;
		BytePatch GetAssistedAimTypePatch;
		BytePatch GetLockOnPosPatch;
		BytePatch ShouldAllowDriverLockOnPatch;
		BytePatch AllowPausingInSessionPatch;
		PVOID GetPoolType;
		BytePatch SetJoinRequestPoolTypePatch;
		BytePatch HandleJoinRequestIgnorePoolPatch;
		CStatsMpCharacterMappingData* StatsMpCharacterMappingData;
		int* HasGTAPlus;
		PVOID BattlEyeServerProcessPlayerJoin;
		PVOID AssistedAimShouldReleaseEntity;
		Functions::AssistedAimFindNewTarget AssistedAimFindNewTarget;
		rage::gameSkeleton* GameSkeleton;
		PVOID Nullsub;
		rage::Obf32** AnticheatInitializedHash;
		PVOID GetAnticheatInitializedHash;
		PVOID GetAnticheatInitializedHash2;
		CAnticheatContext** AnticheatContext;
		BytePatch AbilityBarPatch;
		PVOID MatchmakingAdvertise;
		PVOID MatchmakingUpdate;
		PVOID MatchmakingUnadvertise;
		PVOID MatchmakingSessionDetailSendResponse;
	};

	struct Pointers : PointerData
	{
		bool Init();
		bool LateInit();
	};

	inline YimMenu::Pointers Pointers;
}