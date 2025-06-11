#include "ScriptPointers.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "core/memory/ModuleMgr.hpp"

namespace YimMenu
{
	ScriptPointers::ScriptPointers() :
	    m_CacheFile(FileMgr::GetProjectFile("./scr_pointers.bin"), 2)
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

	void ScriptPointers::CachePointerImpl(joaat_t scriptHash, joaat_t nameHash, std::uint32_t address)
	{
		if (auto it = m_ScriptPointers.find(scriptHash); it != m_ScriptPointers.end())
			it->second.emplace(nameHash, address);
		else
		{
			m_ScriptPointers.emplace(scriptHash, std::unordered_map<joaat_t, std::uint32_t>({{nameHash, address}}));
		}
		Save();
	}

	std::uint32_t ScriptPointers::GetPointerImpl(joaat_t scriptHash, joaat_t nameHash)
	{
		if (auto it = m_ScriptPointers.find(scriptHash); it != m_ScriptPointers.end())
		{
			if (auto it2 = it->second.find(nameHash); it2 != it->second.end())
			{
				return it2->second;
			}
		}

		return 0;
	}

	void ScriptPointers::Save()
	{
		std::vector<scrPointerSaveStruct> savedPointers;

		for (auto& [script, ptrs] : m_ScriptPointers)
		{
			for (auto& [hash, val] : ptrs)
			{
				scrPointerSaveStruct saveStruct;
				saveStruct.m_NameHash = hash;
				saveStruct.m_Address = val;
				saveStruct.m_ScriptHash = script;
				savedPointers.push_back(saveStruct);
			}
		}

		auto dataSize = sizeof(std::uint32_t) + sizeof(scrPointerSaveStruct) * savedPointers.size();
		auto data = std::make_unique<uint8_t[]>(dataSize);
		auto dataPtr = data.get();

		*(std::uint32_t*)dataPtr = savedPointers.size();
		dataPtr += sizeof(std::uint32_t);
		memcpy(dataPtr, savedPointers.data(), sizeof(scrPointerSaveStruct) * savedPointers.size());

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
			if (auto it = m_ScriptPointers.find(saveStruct->m_ScriptHash); it != m_ScriptPointers.end())
				it->second.emplace(saveStruct->m_NameHash, saveStruct->m_Address);
			else
			{
				m_ScriptPointers.emplace(saveStruct->m_ScriptHash, std::unordered_map<joaat_t, std::uint32_t>({{saveStruct->m_NameHash, saveStruct->m_Address}}));
			}
			data += sizeof(scrPointerSaveStruct);
		}

		LOG(INFO) << "Loaded " << m_ScriptPointers.size() << " script pointers from cache.";
	}
}