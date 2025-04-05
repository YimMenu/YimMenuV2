#include "core/backend/FiberPool.hpp"
#include "core/commands/Command.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/gta/Natives.hpp"
#include "types/stats/CStatsMgr.hpp"

namespace YimMenu::Features
{
	class CayoPericoOptimizer : public Command
	{
	public:
		CayoPericoOptimizer(const std::string& name, const std::string& description, const std::string& detailedDescription) :
		    Command(name, description, detailedDescription)
		{
		}

	private:
		struct StatInfo
		{
			std::string m_Name;
			std::uint32_t m_NameHash;
			bool m_Normalized = false;
			sStatData* m_Data = nullptr;

			bool IsValid()
			{
				return m_Data != nullptr;
			}
		};

		union StatValue {
			float m_AsFloat;
			int m_AsInt;
			bool m_AsBool;
			std::uint64_t m_AsU64;
			char m_AsString[12];
		};

		static StatInfo GetStatInfo(const char* name_str)
		{
			StatInfo name{};
			auto len = strlen(name_str);

			if (len > 1 && name_str[0] == '$')
			{
				name_str++;
				len--;
				name.m_Normalized = true;
			}

			name.m_Name = name_str;

			if (len > 3 && tolower(name_str[0]) == 'm' && tolower(name_str[1]) == 'p' && tolower(name_str[2]) == 'x')
			{
				if (auto last_char = Pointers.StatsMgr->GetStat("MPPLY_LAST_MP_CHAR"_J))
				{
					name.m_Name[2]    = '0' + last_char->GetInt();
					name.m_Normalized = true;
				}
			}

			name.m_NameHash = Joaat(name.m_Name);
			name.m_Data     = Pointers.StatsMgr->GetStat(name.m_NameHash);

			if (name.m_Data == nullptr && len > 3 && (tolower(name_str[0]) != 'm' || tolower(name_str[1]) != 'p' || !(tolower(name_str[2]) == '0' || tolower(name_str[2]) == '1')))
			{
				auto last_char   = Pointers.StatsMgr->GetStat("MPPLY_LAST_MP_CHAR"_J);
				auto char_index  = last_char ? last_char->GetInt() : 0;
				auto char_prefix = char_index == 0 ? "MP0_" : "MP1_";
				auto new_hash    = Joaat(char_prefix + name.m_Name);
				auto new_stat    = Pointers.StatsMgr->GetStat(new_hash);

				if (new_stat)
				{
					name.m_Name       = char_prefix + name.m_Name;
					name.m_NameHash   = new_hash;
					name.m_Data       = new_stat;
					name.m_Normalized = true;
				}
			}

			return name;
		}

		static void WriteStat(std::uint32_t hash, StatValue& value, sStatData* data)
		{
			switch (data->GetType())
			{
			case sStatData::Type::_BOOL: STATS::STAT_SET_BOOL(hash, value.m_AsBool, true); break;
			case sStatData::Type::FLOAT: STATS::STAT_SET_FLOAT(hash, value.m_AsFloat, true); return;
			case sStatData::Type::INT:
			case sStatData::Type::UINT32:
			case sStatData::Type::UINT16:
			case sStatData::Type::UINT8: STATS::STAT_SET_INT(hash, value.m_AsInt, true); return;
			case sStatData::Type::INT64: data->SetInt64(value.m_AsU64); return;
			case sStatData::Type::UINT64:
				STATS::STAT_SET_MASKED_INT(hash, (std::uint32_t)value.m_AsU64, 0, 32, true);
				STATS::STAT_SET_MASKED_INT(hash, (std::uint32_t)(value.m_AsU64 >> 32), 32, 32, true);
				return;
			case sStatData::Type::STRING: STATS::STAT_SET_STRING(hash, value.m_AsString, true); return;
			default: return;
			}
		}

		void ApplyStat(const char* statName, int statValue)
		{
			StatInfo statInfo = GetStatInfo(statName);

			if (!statInfo.IsValid())
			{
				LOG(WARNING) << "Stat not found: " << statName;
				return;
			}

			StatValue value{};

			switch (statInfo.m_Data->GetType())
			{
			case sStatData::Type::INT:
			case sStatData::Type::UINT32:
			case sStatData::Type::UINT16:
			case sStatData::Type::UINT8: value.m_AsInt = statValue; break;
			case sStatData::Type::INT64:
			case sStatData::Type::UINT64: value.m_AsU64 = statValue; break;
			case sStatData::Type::FLOAT: value.m_AsFloat = static_cast<float>(statValue); break;
			case sStatData::Type::_BOOL: value.m_AsBool = statValue != 0; break;
			default: LOG(WARNING) << "Unsupported stat type for: " << statName; return;
			}

			WriteStat(statInfo.m_NameHash, value, statInfo.m_Data);
			LOG(INFO) << "Modified: " << statName << " = " << statValue;
		}

	public:
		// Change Execute() to OnCall() to correctly override the base class method
		virtual void OnCall() override
		{
			FiberPool::Push([this] {
				// Set optimal Cayo Perico heist settings
				ApplyStat("MP0_H4CNF_BS_GEN", 131071);
				ApplyStat("MP0_H4CNF_BS_ENTR", 63);
				ApplyStat("MP0_H4CNF_BS_ABIL", 63);
				ApplyStat("MP0_H4CNF_WEAPONS", 2);
				ApplyStat("MP0_H4CNF_WEP_DISRP", 3);
				ApplyStat("MP0_H4CNF_ARM_DISRP", 3);
				ApplyStat("MP0_H4CNF_HEL_DISRP", 3);
				ApplyStat("MP0_H4CNF_TARGET", 5);
				ApplyStat("MP0_H4CNF_TROJAN", 4);
				ApplyStat("MP0_H4CNF_APPROACH", -1);
				ApplyStat("MP0_H4LOOT_CASH_I", 0);
				ApplyStat("MP0_H4LOOT_CASH_C", 0);
				ApplyStat("MP0_H4LOOT_WEED_I", 0);
				ApplyStat("MP0_H4LOOT_WEED_C", 0);
				ApplyStat("MP0_H4LOOT_COKE_I", 0);
				ApplyStat("MP0_H4LOOT_COKE_C", 0);
				ApplyStat("MP0_H4LOOT_GOLD_I", -1);
				ApplyStat("MP0_H4LOOT_GOLD_C", -1);
				ApplyStat("MP0_H4LOOT_PAINT", -1);
				ApplyStat("MP0_H4_PROGRESS", 131055);
				ApplyStat("MP0_H4LOOT_CASH_I_SCOPED", 0);
				ApplyStat("MP0_H4LOOT_CASH_C_SCOPED", 0);
				ApplyStat("MP0_H4LOOT_WEED_I_SCOPED", 0);
				ApplyStat("MP0_H4LOOT_WEED_C_SCOPED", 0);
				ApplyStat("MP0_H4LOOT_COKE_I_SCOPED", 0);
				ApplyStat("MP0_H4LOOT_COKE_C_SCOPED", 0);
				ApplyStat("MP0_H4LOOT_GOLD_I_SCOPED", -1);
				ApplyStat("MP0_H4LOOT_GOLD_C_SCOPED", -1);
				ApplyStat("MP0_H4LOOT_PAINT_SCOPED", -1);
				ApplyStat("MP0_H4_MISSIONS", 65535);
				ApplyStat("MP0_H4_PLAYTHROUGH_STATUS", 40000);

				LOG(INFO) << "Cayo Perico heist stats optimized!";
				// Replace NOTIFY with appropriate notification function from your codebase
			});
		}
	};

	static CayoPericoOptimizer g_cayo_perico_optimizer{"cayoperico", "Cayo Perico Optimizer", "Optimizes Cayo Perico heist stats for maximum rewards with panther statue and gold loot."};
}