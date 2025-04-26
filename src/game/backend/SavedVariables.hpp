#pragma once

namespace rage
{
	class scrThread;
}

namespace YimMenu
{
	enum class VariableType
	{
		INT,
		INT64,
		BITSET,
		BOOL,
		FLOAT,
		VECTOR,
		STRING
	};

	struct VariableAppendage
	{
		enum class Type
		{
			OFFSET,
			PLAYER_ID
		};

		Type type;
		int offset;
		int size;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(VariableAppendage, type, offset, size);
	};

	struct SavedVariableBase
	{
		std::string name;
		std::uint32_t base;
		std::vector<VariableAppendage> appendages;
		VariableType type;

		std::uint32_t CalculateOffset();
	};

	struct SavedLocal : public SavedVariableBase
	{
		std::uint32_t script;
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(SavedLocal, name, base, appendages, type, script);

		void* Read(rage::scrThread* thread);
	};

	struct SavedGlobal : public SavedVariableBase
	{
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(SavedGlobal, name, base, appendages, type);

		void* Read();
	};

	class SavedVariables
	{
		std::vector<SavedGlobal> m_SavedGlobals{};
		std::vector<SavedLocal> m_SavedLocals{};
		std::atomic_bool m_Initialized = false;

	public:
		static std::vector<SavedGlobal>& GetSavedGlobals()
		{
			return GetInstance().m_SavedGlobals;
		}

		static std::vector<SavedLocal>& GetSavedLocals()
		{
			return GetInstance().m_SavedLocals;
		}

		static void Init()
		{
			GetInstance().InitImpl();
		}

		static void Save()
		{
			GetInstance().SaveImpl();
		}

	private:
		static SavedVariables& GetInstance()
		{
			static SavedVariables instance;
			return instance;
		}

		void InitImpl();
		void SaveImpl();
	};
}