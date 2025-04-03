#pragma once
#include "File.hpp"

namespace YimMenu
{
	using cacheData = std::unique_ptr<uint8_t[]>;

	class CacheHeader final
	{
	public:
		std::uint32_t m_CacheVersion;
		std::uint32_t m_FileVersion;
		std::uint64_t m_DataSize;
	};

	class CacheFile final
	{
		File m_CacheFile;
		std::uint32_t m_CacheVersion;
		CacheHeader m_CacheHeader;
		cacheData m_Data;

	public:
		CacheFile() = delete;
		CacheFile(File cacheFile);
		CacheFile(File cacheFile, std::uint32_t cacheVersion);

		void Free();
		bool Load();
		bool Write() const;
		std::uint8_t* Data() const;
		std::uint64_t DataSize() const;

		bool UpToDate(std::uint32_t fileVersion) const;
		void SetData(cacheData&& data, std::uint64_t dataSize);
		void SetHeaderVersion(std::uint32_t fileVersion);
		void SetCacheVersion(std::uint32_t cacheVersion);
	};
}