#pragma once
#include "core/util/Joaat.hpp"
#include "types/network/netObject.hpp"

// Credits to Aure7138

namespace YimMenu
{
	struct SyncNodeId
	{
		joaat_t id;
		const char* name;

		constexpr SyncNodeId()
		{
			id = 0;
			name = "INVALID NODE ID!";
		}

		template<size_t N>
		constexpr SyncNodeId(char const (&pp)[N])
		{
			id = Joaat(pp);
			name = pp;
		}

		// implicit conversion
		constexpr operator joaat_t() const
		{
			return id;
		}
	};

	// Sync Node Virtual Function Table address to all sync node identifiers that also have that vft address.
	using SyncNodeVftToIds = std::unordered_map<uint64_t, SyncNodeId>;

	// Sync Tree node array index to node identifier.
	using SyncTreeNodeArrayIndexToNodeId = std::vector<SyncNodeId>;

	struct SyncNodeFinder
	{
		static constexpr size_t sm_SyncTreeCount = size_t(rage::netObject::Type::MAX);

		SyncNodeVftToIds m_SyncNodeMap;
		std::array<SyncTreeNodeArrayIndexToNodeId, sm_SyncTreeCount> m_SyncTreeNodeIdsMap;
		std::vector<SyncNodeId> m_GlobalNodeIds;

		SyncNodeFinder();
	};

	class Nodes
	{
	private:
		SyncNodeFinder m_Finder;
		bool m_Initialized = false;
		std::mutex m_InitMutex;

		SyncNodeId& FindImpl(uintptr_t addr);
		void InitImpl();

		static Nodes& GetInstance()
		{
			static Nodes Instance;
			return Instance;
		}

	public:
		static void Init()
		{
			std::lock_guard guard(GetInstance().m_InitMutex);
			if (!GetInstance().m_Initialized)
				GetInstance().InitImpl();
		}

		static void Reset()
		{
			std::lock_guard guard(GetInstance().m_InitMutex);
			GetInstance().m_Finder.m_SyncNodeMap = {};
			GetInstance().m_Finder.m_GlobalNodeIds = {};
			GetInstance().m_Initialized = false;
		}

		static bool IsInitialized()
		{
			return GetInstance().m_Initialized;
		}

		static SyncNodeId& Find(uintptr_t addr)
		{
			return GetInstance().FindImpl(addr);
		}

		static std::vector<SyncNodeId>& GetAllNodeIds()
		{
			return GetInstance().m_Finder.m_GlobalNodeIds;
		}
	};
}

namespace std
{
	template<>
	struct hash<YimMenu::SyncNodeId>
	{
		size_t operator()(const YimMenu::SyncNodeId& x) const
		{
			return x.id;
		}
	};
}