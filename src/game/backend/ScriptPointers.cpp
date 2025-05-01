#include "ScriptPointers.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "core/memory/ModuleMgr.hpp"

namespace YimMenu
{
	ScriptPointers::ScriptPointers() :
	    m_CacheFile(FileMgr::GetProjectFile("./scr_pointers.bin"))
	{
	}

	void ScriptPointers::InitImpl()
	{
		m_CacheFile.Load();
		if (m_CacheFile.UpToDate(ModuleMgr.Get("GTA5_Enhanced.exe"_J)->GetNtHeader()->FileHeader.TimeDateStamp))
		{
			Load();
		}
	}

	void ScriptPointers::CachePointerImpl(joaat_t nameHash, std::uint32_t address)
	{
		m_ScriptPointers.emplace(nameHash, address);
		Save();
	}

	std::uint32_t ScriptPointers::GetPointerImpl(joaat_t nameHash)
	{
		if (auto it = m_ScriptPointers.find(nameHash); it != m_ScriptPointers.end())
		{
			return it->second;
		}

		return 0;
	}

	void ScriptPointers::Save()
	{
		auto dataSize = sizeof(std::uint32_t) + sizeof(scrPointerSaveStruct) * m_ScriptPointers.size();
		auto data     = std::make_unique<uint8_t[]>(dataSize);
		auto dataPtr  = data.get();

		*(std::uint32_t*)dataPtr = m_ScriptPointers.size();
		dataPtr += sizeof(std::uint32_t);

		for (auto& [hash, val] : m_ScriptPointers)
		{
			auto saveStruct        = (scrPointerSaveStruct*)dataPtr;
			saveStruct->m_NameHash = hash;
			saveStruct->m_Address  = val;
			dataPtr += sizeof(scrPointerSaveStruct);
		}

		m_CacheFile.SetHeaderVersion(ModuleMgr.Get("GTA5_Enhanced.exe"_J)->GetNtHeader()->FileHeader.TimeDateStamp);
		m_CacheFile.SetData(std::move(data), dataSize);
		m_CacheFile.Write();
	}

	void ScriptPointers::Load()
	{
		auto data = m_CacheFile.Data();

		auto numPointers = *(std::uint32_t*)data;
		data += sizeof(std::uint32_t);

		for (int i = 0; i < numPointers; i++)
		{
			auto saveStruct = (scrPointerSaveStruct*)data;
			m_ScriptPointers.emplace(saveStruct->m_NameHash, saveStruct->m_Address);
			data += sizeof(scrPointerSaveStruct);
		}

		LOG(INFO) << "Loaded " << m_ScriptPointers.size() << " script pointers from cache.";
	}
}