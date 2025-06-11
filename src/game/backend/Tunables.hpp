#pragma once
#include "core/util/Joaat.hpp"
#include "core/filemgr/CacheFile.hpp"
#include "game/gta/ScriptGlobal.hpp"

namespace YimMenu
{
	constexpr int TUNABLE_BASE_ADDRESS = 0x40001;

#pragma pack(push, 1)
	struct TunableSaveStruct
	{
		joaat_t m_Hash;
		std::uint32_t m_Offset;
	};
#pragma pack(pop)

	class Tunables
	{
		static Tunables& GetInstance()
		{
			static Tunables instance;
			return instance;
		}

		bool m_Initialized = false;
		bool m_Loading = false;
		bool m_ScriptStarted = false;
		CacheFile m_CacheFile;
		std::unordered_map<joaat_t, int> m_Tunables{};
		std::unique_ptr<uint64_t[]> m_TunablesBackup;
		int m_NumTunables = 0;
		int m_CurrentJunkVal = 0x1000000;
		std::unordered_map<int, joaat_t> m_JunkValues{};

		void RunScriptImpl();
		void Save();
		void Load();

	public:
		Tunables();

		static void RunScript()
		{
			GetInstance().RunScriptImpl();
		}

		static bool CachingTunables()
		{
			return GetInstance().m_ScriptStarted;
		}

		static bool Initialized()
		{
			return GetInstance().m_Initialized;
		}

		static void AddJunkValue(int value, joaat_t hash)
		{
			GetInstance().m_JunkValues.emplace(value, hash);
		}

		static int GetCurrentJunkVal()
		{
			return GetInstance().m_CurrentJunkVal;
		}

		static int IncrementJunkVal()
		{
			return GetInstance().m_CurrentJunkVal++;
		}

		static std::optional<ScriptGlobal> GetTunable(joaat_t hash)
		{
			if (auto it = GetInstance().m_Tunables.find(hash); it != GetInstance().m_Tunables.end())
			{
				if (ScriptGlobal(it->second).CanAccess())
					return ScriptGlobal(it->second);
			}

			return std::nullopt;
		}
	};

	class Tunable
	{
		joaat_t m_Hash;
		std::optional<ScriptGlobal> m_Global;

	public:
		constexpr Tunable(joaat_t hash) :
		    m_Hash(hash),
		    m_Global(std::nullopt)
		{
		}

		bool IsReady();

		// make sure to call IsReady before accessing tunables
		template<typename T>
		T Get()
		{
			return *m_Global->As<T*>();
		}

		// make sure to call IsReady before accessing tunables
		template<typename T>
		void Set(T new_value)
		{
			*m_Global->As<T*>() = new_value;
		}
	};
}