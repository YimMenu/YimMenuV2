#include "PatternScanner.hpp"

#include "Module.hpp"
#include "ModuleMgr.hpp"
#include "core/backend/PatternCache.hpp"

#include <future>

namespace YimMenu
{
	PatternScanner::PatternScanner(const Module* module) :
	    m_Module(module),
	    m_Patterns()
	{
	}

	bool PatternScanner::Scan()
	{
		if (!m_Module || !m_Module->Valid())
			return false;

		bool scanSuccess = true;

		if (!ModuleMgr.IsManualMapped())
		{
			std::vector<std::future<bool>> jobs;
			for (const auto& [pattern, func] : m_Patterns)
			{
				jobs.emplace_back(std::async(&PatternScanner::ScanInternal, this, pattern, func));
			}

			for (auto& job : jobs)
			{
				job.wait();

				if (scanSuccess)
					scanSuccess = job.get();
			}
		}
		else
		{
			// spawning threads seems to throw STATUS_THREADPOOL_FREE_LIBRARY_ON_COMPLETION_FAILED when manual mapping
			for (const auto& [pattern, func] : m_Patterns)
				scanSuccess = scanSuccess && PatternScanner::ScanInternal(pattern, func);
		}

		return scanSuccess;
	}

	bool PatternScanner::ScanInternal(const IPattern* pattern, PatternFunc func) const
	{
		const auto signature = pattern->Signature();

		if (PatternCache::IsInitialized())
		{
			auto offset = PatternCache::GetCachedOffset(pattern->Hash().Update(m_Module->Size()));
			if (offset.has_value())
			{
				LOGF(INFO, "Using cached pattern [{}] : [{:X}] [Hash(): {:X}]", pattern->Name(), m_Module->Base() + offset.value(), pattern->Hash().Update(m_Module->Size()).m_Hash);
				std::invoke(func, m_Module->Base() + offset.value());
				return true;
			}
		}

		for (auto i = m_Module->Base(); i < m_Module->End(); ++i)
		{
			if (signature.size() + i > m_Module->End())
				break;

			const auto instruction = reinterpret_cast<std::uint8_t*>(i);
			bool found = true;
			for (std::size_t instructionIdx = 0; instructionIdx < signature.size(); ++instructionIdx)
			{
				if (signature[instructionIdx] && signature[instructionIdx].value() != instruction[instructionIdx])
				{
					found = false;
				}
			}

			if (found)
			{
				LOG(INFO) << "Found pattern [" << pattern->Name() << "] : [" << HEX(i) << "]";

				std::invoke(func, i);

				if (PatternCache::IsInitialized())
				{
					PatternCache::UpdateCachedOffset(pattern->Hash().Update(m_Module->Size()), i - m_Module->Base());
				}

				return true;
			}
		}

		LOG(WARNING) << "Failed to find pattern [" << pattern->Name() << "]";
		return false;
	}
}