#pragma once
#include <chrono>
#include <unordered_set>

namespace YimMenu
{
	class PlayerData
	{
	public:
		bool m_IsModder{};
		bool m_RunFreemodeStateKick{};
		netSocketAddress m_InternalAddress{};
		netSocketAddress m_ExternalAddress{};
		bool m_HasAddresses{};
	};
}