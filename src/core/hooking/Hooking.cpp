#include "Hooking.hpp"

#include "BaseHook.hpp"
#include "DetourHook.hpp"
#include "VMTHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu
{
	Hooking::Hooking()
	{
		BaseHook::Add<Hooks::Window::WndProc>(new DetourHook("WndProc", Pointers.WndProc, Hooks::Window::WndProc));

		auto swapchain_vft = *reinterpret_cast<void***>(*Pointers.SwapChain);
		BaseHook::Add<Hooks::SwapChain::Present>(new DetourHook("Present", swapchain_vft[Hooks::SwapChain::VMTPresentIdx], Hooks::SwapChain::Present));
		BaseHook::Add<Hooks::SwapChain::ResizeBuffers>(new DetourHook("ResizeBuffers", swapchain_vft[Hooks::SwapChain::VMTResizeBuffersIdx], Hooks::SwapChain::ResizeBuffers));

		// BaseHook::Add<Hooks::Anticheat::QueueDependency>(new DetourHook("QueueDependency", Pointers.QueueDependency, Hooks::Anticheat::QueueDependency));
		BaseHook::Add<Hooks::Anticheat::PrepareMetricForSending>(new DetourHook("PrepareMetricForSending", Pointers.PrepareMetricForSending, Hooks::Anticheat::PrepareMetricForSending));
		BaseHook::Add<Hooks::Anticheat::GetThreadContext>(new DetourHook("GetThreadContext", reinterpret_cast<void*>(GetProcAddress(LoadLibraryA("kernel32.dll"), "GetThreadContext")), Hooks::Anticheat::GetThreadContext));
		BaseHook::Add<Hooks::Anticheat::HttpStartRequest>(new DetourHook("HttpStartRequest", Pointers.HttpStartRequest, Hooks::Anticheat::HttpStartRequest));
		BaseHook::Add<Hooks::Anticheat::BattlEyeServerProcessPlayerJoin>(new DetourHook("BattlEyeServerProcessPlayerJoin", Pointers.BattlEyeServerProcessPlayerJoin, Hooks::Anticheat::BattlEyeServerProcessPlayerJoin));
		BaseHook::Add<Hooks::Anticheat::GetAnticheatInitializedHash>(new DetourHook("GetAnticheatInitializedHash", Pointers.GetAnticheatInitializedHash, Hooks::Anticheat::GetAnticheatInitializedHash));
		BaseHook::Add<Hooks::Anticheat::GetAnticheatInitializedHash2>(new DetourHook("GetAnticheatInitializedHash2", Pointers.GetAnticheatInitializedHash2, Hooks::Anticheat::GetAnticheatInitializedHash2));

		BaseHook::Add<Hooks::Script::RunScriptThreads>(new DetourHook("RunScriptThreads", Pointers.RunScriptThreads, Hooks::Script::RunScriptThreads));
		BaseHook::Add<Hooks::Script::InitNativeTables>(new DetourHook("InitNativeTables", Pointers.InitNativeTables, Hooks::Script::InitNativeTables));
		BaseHook::Add<Hooks::Script::ScriptVM>(new DetourHook("ScriptVM", reinterpret_cast<void*>(Pointers.ScriptVM), Hooks::Script::ScriptVM));

		BaseHook::Add<Hooks::Info::AssignPhysicalIndex>(new DetourHook("AssignPhysicalIndex", Pointers.AssignPhysicalIndex, Hooks::Info::AssignPhysicalIndex));
		BaseHook::Add<Hooks::Info::NetworkPlayerMgrShutdown>(new DetourHook("NetworkPlayerMgrShutdown", Pointers.NetworkPlayerMgrShutdown, Hooks::Info::NetworkPlayerMgrShutdown));

		BaseHook::Add<Hooks::Network::ReceiveNetMessage>(new DetourHook("ReceiveNetMessage", Pointers.ReceiveNetMessage, Hooks::Network::ReceiveNetMessage));

		BaseHook::Add<Hooks::Spoofing::IsNodeInScope>(new DetourHook("IsNodeInScope", Pointers.IsNodeInScope, Hooks::Spoofing::IsNodeInScope));
		BaseHook::Add<Hooks::Spoofing::ShouldUseNodeCache>(new DetourHook("ShouldUseNodeCache", Pointers.ShouldUseNodeCache, Hooks::Spoofing::ShouldUseNodeCache));
		BaseHook::Add<Hooks::Spoofing::WriteNetArrayData>(new DetourHook("WriteNetArrayData", Pointers.WriteNetArrayData, Hooks::Spoofing::WriteNetArrayData));
		BaseHook::Add<Hooks::Spoofing::WriteNodeData>(new DetourHook("WriteNodeData", Pointers.WriteNodeData, Hooks::Spoofing::WriteNodeData));
		BaseHook::Add<Hooks::Spoofing::WriteSyncTree>(new DetourHook("WriteSyncTree", Pointers.WriteSyncTree, Hooks::Spoofing::WriteSyncTree));

		BaseHook::Add<Hooks::Network::GetPoolType>(new DetourHook("GetPoolType", Pointers.GetPoolType, Hooks::Network::GetPoolType));

		BaseHook::Add<Hooks::Matchmaking::MatchmakingAdvertise>(new DetourHook("MatchmakingAdvertise", Pointers.MatchmakingAdvertise, Hooks::Matchmaking::MatchmakingAdvertise));
		BaseHook::Add<Hooks::Matchmaking::MatchmakingSessionDetailSendResponse>(new DetourHook("MatchmakingSessionDetailSendResponse", Pointers.MatchmakingSessionDetailSendResponse, Hooks::Matchmaking::MatchmakingSessionDetailSendResponse));
		BaseHook::Add<Hooks::Matchmaking::MatchmakingUnadvertise>(new DetourHook("MatchmakingUnadvertise", Pointers.MatchmakingUnadvertise, Hooks::Matchmaking::MatchmakingUnadvertise));
		BaseHook::Add<Hooks::Matchmaking::MatchmakingUpdate>(new DetourHook("MatchmakingUpdate", Pointers.MatchmakingUpdate, Hooks::Matchmaking::MatchmakingUpdate));

		BaseHook::Add<Hooks::Misc::AssistedAimShouldReleaseEntity>(new DetourHook("AssistedAimShouldReleaseEntity", Pointers.AssistedAimShouldReleaseEntity, Hooks::Misc::AssistedAimShouldReleaseEntity));
	}

	Hooking::~Hooking()
	{
		DestroyImpl();
	}

	bool Hooking::Init()
	{
		return GetInstance().InitImpl();
	}

	void Hooking::Destroy()
	{
		GetInstance().DestroyImpl();
		BytePatches::RestoreAll();
	}

	bool Hooking::InitImpl()
	{
		BaseHook::EnableAll();
		m_MinHook.ApplyQueued();

		return true;
	}

	void Hooking::DestroyImpl()
	{
		BaseHook::DisableAll();
		m_MinHook.ApplyQueued();

		for (auto it : BaseHook::Hooks())
		{
			delete it;
		}
		BaseHook::Hooks().clear();
	}
}