#include "PatternScanner.hpp"

#include "Module.hpp"

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

		std::vector<std::future<bool>> jobs;
		for (const auto& [pattern, func] : m_Patterns)
		{
			jobs.emplace_back(std::async(&PatternScanner::ScanInternal, this, pattern, func));
		}

		bool scanSuccess = true;
		for (auto& job : jobs)
		{
			job.wait();

			if (scanSuccess)
				scanSuccess = job.get();
		}
		if (!scanSuccess)
		{
			LOG(FATAL) << "Some patterns have not been found, continuing would be foolish.";
		}
		return scanSuccess;
	}

	bool PatternScanner::ScanInternal(const IPattern* pattern, PatternFunc func) const
	{
		const auto signature = pattern->Signature();

		for (auto i = m_Module->Base(); i < m_Module->End(); ++i)
		{
			if (signature.size() + i > m_Module->End())
				break;

			const auto instruction = reinterpret_cast<std::uint8_t*>(i);
			bool found             = true;
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

				return true;
			}
		}

		LOG(WARNING) << "Failed to find pattern [" << pattern->Name() << "]";
		return false;
	}
}