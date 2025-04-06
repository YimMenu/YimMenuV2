#include "game/pointers/Pointers.hpp"
#include "game/gta/Natives.hpp"
#include "types/stats/CStatsMgr.hpp"
#include <core/util/Joaat.hpp>

namespace YimMenu::StatsEditor
{
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

	StatInfo GetStatInfo(const char* name_str)
	{
		StatInfo name{};
		auto len = strlen(name_str);

		// not sure why people do this
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
			// stat names without a character prefix
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
	void WriteStat(std::uint32_t hash, StatValue& value, sStatData* data)
	{
		switch (data->GetType())
		{
		case sStatData::Type::_BOOL: STATS::STAT_SET_BOOL(hash, value.m_AsBool, true); break;
		case sStatData::Type::FLOAT: STATS::STAT_SET_FLOAT(hash, value.m_AsFloat, true); return;
		case sStatData::Type::INT:
		case sStatData::Type::UINT32:
		case sStatData::Type::UINT16:
		case sStatData::Type::UINT8: STATS::STAT_SET_INT(hash, value.m_AsInt, true); return;
		case sStatData::Type::INT64:
			data->SetInt64(value.m_AsU64); // TODO this isn't a good idea! natives can't set this
			return;
		case sStatData::Type::UINT64:
			STATS::STAT_SET_MASKED_INT(hash, (std::uint32_t)value.m_AsU64, 0, 32, true);
			STATS::STAT_SET_MASKED_INT(hash, (std::uint32_t)(value.m_AsU64 >> 32), 32, 32, true);
			return;
		case sStatData::Type::STRING: STATS::STAT_SET_STRING(hash, value.m_AsString, true); return;
		default: return; // data type not supported
		}
	}
	void ReadStat(StatValue& value, sStatData* data)
	{
		memset(&value, 0, sizeof(StatValue));

		switch (data->GetType())
		{
		case sStatData::Type::_BOOL: value.m_AsBool = data->GetBool(); return;
		case sStatData::Type::FLOAT: value.m_AsFloat = data->GetFloat(); return;
		case sStatData::Type::INT:
		case sStatData::Type::UINT32:
		case sStatData::Type::UINT16:
		case sStatData::Type::UINT8: value.m_AsInt = data->GetInt(); return;
		case sStatData::Type::INT64: value.m_AsU64 = data->GetInt64(); return;
		case sStatData::Type::UINT64: value.m_AsU64 = data->GetUInt64(); return;
		case sStatData::Type::STRING: strncpy(value.m_AsString, data->GetString(), sizeof(value.m_AsString)); return;
		default: return; // data type not supported
		}
	}

	bool SetStatInt(const std::string& name, int value)
	{
		auto stat = GetStatInfo(name.c_str());
		if (!stat.IsValid())
			return false;

		StatValue val{};
		val.m_AsInt = value;
		WriteStat(stat.m_NameHash, val, stat.m_Data);
		return true;
	}

	int GetStatInt(const std::string& name)
	{
		auto stat = GetStatInfo(name.c_str());
		if (!stat.IsValid())
			return 0;

		StatValue val{};
		ReadStat(val, stat.m_Data);
		return val.m_AsInt;
	}
}