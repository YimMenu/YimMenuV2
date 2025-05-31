#pragma once
#include "core/memory/PatternHash.hpp"

namespace YimMenu
{
	class PatternCache
	{
		bool m_Initialized;
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
			return GetInstance().m_Initialized;
		}

	private:
		static PatternCache& GetInstance()
		{
			static PatternCache Instance;
			return Instance;
		}

		void InitImpl();
		void UpdateImpl();
		std::optional<int> GetCachedOffsetImpl(PatternHash hash);
		void UpdateCachedOffsetImpl(PatternHash hash, int offset);
	};
}