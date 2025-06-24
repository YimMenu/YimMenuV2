#pragma once
#include <d3d11.h>

class CNetworkPlayerMgr;
class CNetGamePlayer;
class CProjectBaseSyncDataNode;
class CScriptedGameEvent;
class CBattlEyePlayerModifyInterface;
class CBattlEyePlayerModifyContext;

namespace rage
{
	class netConnectionManager;
	class netArrayHandler;
	class netEvent;
	class scrProgram;
	class netObject;
	class datBitBuffer;
	class JsonSerializer;
	class rlMetric;
	class rlSessionDetailMsg;
	class rlSessionInfo;
	struct rlTaskStatus;
}

class MatchmakingAttributes;
class MatchmakingId;

namespace YimMenu
{
	class Player;
}

namespace YimMenu::Hooks
{
	namespace SwapChain
	{
		constexpr auto VMTPresentIdx = 8;
		constexpr auto VMTResizeBuffersIdx = 13;
		extern HRESULT Present(IDXGISwapChain* that, UINT syncInterval, UINT flags);
		extern HRESULT ResizeBuffers(IDXGISwapChain* that, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
	}

	namespace Anticheat
	{
		extern void QueueDependency(__int64 a1);
		extern bool PrepareMetricForSending(rage::JsonSerializer* ser, void* a2, void* a3, rage::rlMetric* metric);
		extern BOOL GetThreadContext(HANDLE hThread, LPCONTEXT lpContext);
		extern void HttpStartRequest(void* request);
		extern bool BattlEyeServerProcessPlayerJoin(CBattlEyePlayerModifyInterface* server_iface, CBattlEyePlayerModifyContext* context);
		extern std::uint32_t GetAnticheatInitializedHash();
		extern std::uint32_t GetAnticheatInitializedHash2(void* ac_var, std::uint32_t seed);
	}

	namespace Matchmaking
	{
		extern bool MatchmakingAdvertise(int profile_index, int num_slots, int available_slots, MatchmakingAttributes* data, std::uint64_t session_id, rage::rlSessionInfo* info, MatchmakingId* out_id, rage::rlTaskStatus* status);
		extern bool MatchmakingUpdate(int profile_index, MatchmakingId* id, int num_slots, int available_slots, rage::rlSessionInfo* info, MatchmakingAttributes* data, rage::rlTaskStatus* status);
		extern bool MatchmakingUnadvertise(int profile_index, MatchmakingId* id, rage::rlTaskStatus* status);
		extern bool MatchmakingSessionDetailSendResponse(rage::netConnectionManager* mgr, void* request_frame, rage::rlSessionDetailMsg* msg);
	}

	namespace Info
	{
		extern void AssignPhysicalIndex(CNetworkPlayerMgr* mgr, CNetGamePlayer* player, std::uint8_t index);
		extern void NetworkPlayerMgrShutdown(CNetworkPlayerMgr* mgr);
	}

	namespace Script
	{
		extern bool RunScriptThreads(int ops_to_execute);
		extern void InitNativeTables(rage::scrProgram* program);
		extern int ScriptVM(uint64_t* stack, uint64_t** scr_globals, rage::scrProgram* program, void* ctx); // ctx = rage::scrThread::Context
	}

	namespace Spoofing
	{
		extern void WriteNodeData(CProjectBaseSyncDataNode* node, rage::netObject* object, rage::datBitBuffer* buffer, void* logger, bool update);
		extern bool ShouldUseNodeCache(void* node, int flags);
		extern bool IsNodeInScope(void* node, void* a2, std::uint8_t playerId, int flags, unsigned int a5, int a6);
		extern bool WriteSyncTree(void* tree, int type, int flags, rage::netObject* object, rage::datBitBuffer* buffer, int unk, void* a6, std::uint8_t player_id, void* a8);
		extern int WriteNetArrayData(rage::netArrayHandler* _this, CNetGamePlayer* target, rage::datBitBuffer* bit_buffer, uint16_t counter, uint32_t* elem_start, bool silent);
	}

	namespace Network
	{
		extern void ReceiveNetMessage(void* a1, rage::netConnectionManager* mgr, rage::netEvent* event);
		extern void ReceiveNetGameEvent(Player player, uint16_t event_id, uint32_t event_index, uint32_t event_handled_bits, rage::datBitBuffer& buffer);
		extern bool HandleScriptedGameEvent(Player player, CScriptedGameEvent& event);
		extern int GetPoolType();
	}

	namespace Window
	{
		extern LRESULT WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
	}

	namespace Misc
	{
		extern bool AssistedAimShouldReleaseEntity(__int64 a1);
	}
}