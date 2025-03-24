#pragma once
#include <d3d11.h>

class CNetworkPlayerMgr;
class CNetGamePlayer;
class CProjectBaseSyncDataNode;
namespace rage
{
	class netConnectionManager;
	class netEvent;
	class scrProgram;
	class netObject;
	class datBitBuffer;
}

namespace YimMenu
{
	class Player;
}

namespace YimMenu::Hooks
{
	namespace SwapChain
	{
		constexpr auto VMTPresentIdx       = 8;
		constexpr auto VMTResizeBuffersIdx = 13;
		extern HRESULT Present(IDXGISwapChain* that, UINT syncInterval, UINT flags);
		extern HRESULT ResizeBuffers(IDXGISwapChain* that, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
	}

	namespace Info
	{
		extern void AssignPhysicalIndex(CNetworkPlayerMgr* mgr, CNetGamePlayer* player, std::uint8_t index);
	}

	namespace Script
	{
		extern bool RunScriptThreads(int ops_to_execute);
		extern void InitNativeTables(rage::scrProgram* program);
	}

	namespace Spoofing
	{
		extern void WriteNodeData(CProjectBaseSyncDataNode* node, rage::netObject* object, rage::datBitBuffer* buffer, void* logger, bool update);
		extern bool ShouldUseNodeCache(void* node, int flags);
		extern bool IsNodeInScope(void* node, void* a2, std::uint8_t playerId, int flags, unsigned int a5, int a6);
		extern bool WriteSyncTree(void* tree, int type, int flags, rage::netObject* object, rage::datBitBuffer* buffer, int unk, void* a6, std::uint8_t player_id, void* a8);
	}

	namespace Network
	{
		extern void ReceiveNetMessage(void* a1, rage::netConnectionManager* mgr, rage::netEvent* event);
		extern void ReceiveEvent(YimMenu::Player& player, uint16_t event_id, uint32_t event_index, uint32_t event_handled_bitset, rage::datBitBuffer& buffer);
		extern bool HandleScriptedGameEvent(YimMenu::Player& player, int64_t* args, uint32_t args_size);
	}

	namespace Window
	{
		extern LRESULT WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
	}
}