#include "PatternCache.hpp"

#include "core/filemgr/FileMgr.hpp"

namespace YimMenu
{
	namespace
	{
		constexpr std::uint32_t CacheMagic = 0x32434D59; // YMC2
		constexpr std::uint32_t CacheVersion = 1;
		constexpr std::uint32_t MaxCacheEntries = 100'000;

		struct CacheHeader
		{
			std::uint32_t m_Magic;
			std::uint32_t m_Version;
			std::uint32_t m_EntryCount;
			std::uint32_t m_Reserved;
		};

		struct CacheEntry
		{
			std::uint64_t m_Hash;
			std::int32_t m_Offset;
			std::uint32_t m_Reserved;
		};
	}

	std::optional<int> PatternCache::GetCachedOffsetImpl(PatternHash hash)
	{
		std::lock_guard lock(m_Mutex);
		if (auto it = m_Data.find(hash.GetHash()); it != m_Data.end())
			return it->second;

		return std::nullopt;
	}

	void PatternCache::UpdateCachedOffsetImpl(PatternHash hash, int offset)
	{
		std::lock_guard lock(m_Mutex);
		m_Data[hash.GetHash()] = offset;
	}

	void PatternCache::InitImpl()
	{
		std::lock_guard lock(m_Mutex);
		m_Data.clear();

		auto file = FileMgr::GetProjectFile("./pattern_cache.bin");
		if (file.Exists())
		{
			std::ifstream stream(file.Path(), std::ios_base::binary);
			CacheHeader header{};
			if (stream.read(reinterpret_cast<char*>(&header), sizeof(header))
				&& header.m_Magic == CacheMagic
				&& header.m_Version == CacheVersion
				&& header.m_EntryCount <= MaxCacheEntries)
			{
				for (std::uint32_t i = 0; i < header.m_EntryCount; ++i)
				{
					CacheEntry entry{};
					if (!stream.read(reinterpret_cast<char*>(&entry), sizeof(entry)))
					{
						LOG(WARNING) << "Pattern cache is truncated; discarding cached offsets";
						m_Data.clear();
						break;
					}
					m_Data.insert_or_assign(entry.m_Hash, entry.m_Offset);
				}
			}
			else
			{
				LOG(WARNING) << "Pattern cache has an unsupported or corrupt header; rebuilding it";
			}
		}

		m_Initialized.store(true, std::memory_order_release);
	}

	void PatternCache::UpdateImpl()
	{
		std::lock_guard lock(m_Mutex);

		auto file = FileMgr::GetProjectFile("./pattern_cache.bin");
		auto temporary = file.Path();
		temporary += ".tmp";
		std::ofstream stream(temporary, std::ios_base::binary | std::ios_base::trunc);
		if (!stream)
		{
			LOG(WARNING) << "Failed to open the temporary pattern cache";
			return;
		}

		const CacheHeader header{CacheMagic, CacheVersion, static_cast<std::uint32_t>(m_Data.size()), 0};
		stream.write(reinterpret_cast<const char*>(&header), sizeof(header));
		for (const auto& [hash, offset] : m_Data)
		{
			const CacheEntry entry{hash, offset, 0};
			stream.write(reinterpret_cast<const char*>(&entry), sizeof(entry));
		}
		stream.flush();
		if (!stream)
		{
			LOG(WARNING) << "Failed to write the temporary pattern cache";
			stream.close();
			std::error_code ec;
			std::filesystem::remove(temporary, ec);
			return;
		}
		stream.close();

		if (!MoveFileExW(temporary.c_str(), file.Path().c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
		{
			LOGF(WARNING, "Failed to replace the pattern cache: error {}", GetLastError());
			std::error_code ec;
			std::filesystem::remove(temporary, ec);
		}
	}

	std::size_t PatternCache::GetEntryCountImpl()
	{
		std::lock_guard lock(m_Mutex);
		return m_Data.size();
	}
}
