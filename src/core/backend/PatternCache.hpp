#pragma once
#include "core/memory/PatternHash.hpp"

namespace YimMenu
{
	class PatternCache
	{
		std::atomic_bool m_Initialized;
		std::unordered_map<std::uint64_t, int> m_Data;
		std::mutex m_Mutex;

	public:
		PatternCache() :
		    m_Initialized(false)
		{
		}

		static void Init()
		{
			GetInstance().InitImpl();
		}

		static void Update()
		{
			GetInstance().UpdateImpl();
		}

		static std::optional<int> GetCachedOffset(PatternHash hash)
		{
			return GetInstance().GetCachedOffsetImpl(hash);
		}

		static void UpdateCachedOffset(PatternHash hash, int offset)
		{
			GetInstance().UpdateCachedOffsetImpl(hash, offset);
		}

		static bool IsInitialized()
		{
			return GetInstance().m_Initialized.load(std::memory_order_acquire);
		}

		static std::size_t GetEntryCount()
		{
			return GetInstance().GetEntryCountImpl();
		}

	private:
		static PatternCache& GetInstance()
		{
			static PatternCache Instance;
			return Instance;
		}

		void InitImpl();
		void UpdateImpl();
		std::size_t GetEntryCountImpl();
		std::optional<int> GetCachedOffsetImpl(PatternHash hash);
		void UpdateCachedOffsetImpl(PatternHash hash, int offset);
	};
}
