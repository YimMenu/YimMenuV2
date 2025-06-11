#include "CacheFile.hpp"

namespace YimMenu
{
	CacheFile::CacheFile(File cacheFile) :
	    m_CacheFile(cacheFile),
	    m_Data(nullptr),
	    m_CacheVersion(0),
	    m_CacheHeader()
	{
	}

	CacheFile::CacheFile(File cacheFile, std::uint32_t cacheVersion) :
	    m_CacheFile(cacheFile),
	    m_Data(nullptr),
	    m_CacheVersion(cacheVersion),
	    m_CacheHeader()
	{
	}

	void CacheFile::Free()
	{
		m_Data.reset();
	}

	bool CacheFile::Load()
	{
		if (!m_CacheFile.Exists())
			return false;
		if (m_Data)
			return true;

		auto file = std::ifstream(m_CacheFile.Path(), std::ios::binary);

		file.read(reinterpret_cast<char*>(&m_CacheHeader), sizeof(m_CacheHeader));

		m_Data = std::make_unique<uint8_t[]>(m_CacheHeader.m_DataSize);
		file.read(reinterpret_cast<char*>(m_Data.get()), m_CacheHeader.m_DataSize);

		file.close();
		return true;
	}

	bool CacheFile::Write() const
	{
		if (!m_Data)
			return false;

		auto file = std::ofstream(m_CacheFile.Path(), std::ios::binary);

		file.write(reinterpret_cast<const char*>(&m_CacheHeader), sizeof(m_CacheHeader));
		file.write(reinterpret_cast<const char*>(m_Data.get()), m_CacheHeader.m_DataSize);
		file.close();

		return true;
	}

	std::uint8_t* CacheFile::Data() const
	{
		return m_Data.get();
	}

	std::uint64_t CacheFile::DataSize() const
	{
		return m_CacheHeader.m_DataSize;
	}

	bool CacheFile::UpToDate(std::uint32_t fileVersion) const
	{
		if (!m_Data)
			return false;

		return m_CacheVersion == m_CacheHeader.m_CacheVersion && fileVersion == m_CacheHeader.m_FileVersion;
	}

	void CacheFile::SetData(cacheData&& data, std::uint64_t dataSize)
	{
		m_Data.swap(data);
		m_CacheHeader.m_DataSize = dataSize;
	}

	void CacheFile::SetHeaderVersion(std::uint32_t fileVersion)
	{
		m_CacheHeader.m_CacheVersion = m_CacheVersion;
		m_CacheHeader.m_FileVersion = fileVersion;
	}

	void CacheFile::SetCacheVersion(std::uint32_t cacheVersion)
	{
		m_CacheVersion = cacheVersion;
	}
}