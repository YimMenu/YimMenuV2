#pragma once
#include "core/util/Joaat.hpp"
#include "core/filemgr/CacheFile.hpp"

namespace YimMenu
{
#pragma pack(push, 1)
	struct scrPointerSaveStruct
	{
		joaat_t m_NameHash;
		joaat_t m_ScriptHash;
		std::uint32_t m_Address;
	};
#pragma pack(pop)

	class ScriptPointers
	{
		static ScriptPointers& GetInstance()
		{
			static ScriptPointers instance;
			return instance;
		}

		void InitImpl();
		void CachePointerImpl(joaat_t scriptHash, joaat_t nameHash, std::uint32_t address);
		std::uint32_t GetPointerImpl(joaat_t scriptHash, joaat_t nameHash);
		void Save();
		void Load();

		CacheFile m_CacheFile;
		std::unordered_map<joaat_t, std::unordered_map<joaat_t, std::uint32_t>> m_ScriptPointers{};

	public:
		ScriptPointers();

		static void Init()
		{
			GetInstance().InitImpl();
		}

		static void CachePointer(joaat_t scriptHash, joaat_t nameHash, std::uint32_t address)
		{
			GetInstance().CachePointerImpl(scriptHash, nameHash, address);
		}

		static std::uint32_t GetPointer(joaat_t scriptHash, joaat_t nameHash)
		{
			return GetInstance().GetPointerImpl(scriptHash, nameHash);
		}
	};
}