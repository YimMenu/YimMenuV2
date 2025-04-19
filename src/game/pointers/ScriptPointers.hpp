#pragma once
#include "core/util/Joaat.hpp"
#include "core/filemgr/CacheFile.hpp"
#include "core/memory/Pattern.hpp"

namespace rage
{
	class scrProgram;
}

namespace YimMenu
{
#pragma pack(push, 1)
	struct scrPointerSaveStruct
	{
		joaat_t m_Hash;
		std::uint32_t m_Address;
	};
#pragma pack(pop)

	class ScriptPointers
	{
	public:
		class ScriptPointer
		{
		public:
			rage::scrProgram* m_Program;
			std::uint32_t m_Address;

		public:
			ScriptPointer() = default;
			ScriptPointer(rage::scrProgram* program);
			ScriptPointer(rage::scrProgram* program, std::uint32_t address);

			ScriptPointer Add(std::uint32_t offset);
			ScriptPointer Sub(std::uint32_t offset);
			ScriptPointer Rip();
			ScriptPointer Scan(SimplePattern pattern);

			template<typename T>
			T As()
			{
				return (T)m_Address;
			}
		};

		ScriptPointers();

		static void RunScript()
		{
			GetInstance().RunScriptImpl();
		}

		static void AddPointer(joaat_t hash, std::uint32_t address)
		{
			GetInstance().m_ScriptPointers.emplace(hash, address);
		}

		static std::uint32_t GetPointer(joaat_t hash)
		{
			if (auto it = GetInstance().m_ScriptPointers.find(hash); it != GetInstance().m_ScriptPointers.end())
			{
				return it->second;
			}

			return 0;
		}

	private:
		static ScriptPointers& GetInstance()
		{
			static ScriptPointers instance;
			return instance;
		}

		void RunScriptImpl();
		void Save();
		void Load();

		CacheFile m_CacheFile;
		std::unordered_map<joaat_t, std::uint32_t> m_ScriptPointers{};
	};

	using scrPtr = ScriptPointers::ScriptPointer;
}