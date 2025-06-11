#include "Stats.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Stats
{
	static void ConvertMPX(std::string& statName)
	{
		std::transform(statName.begin(), statName.end(), statName.begin(), ::tolower);
		if (statName.substr(0, 3) == "mpx")
			statName[2] = GetCharIndex() + '0';
	}

	int GetCharIndex()
	{
		int index{};
		STATS::STAT_GET_INT("MPPLY_LAST_MP_CHAR"_J, &index, -1);
		return index;
	}

	void SetInt(std::string statName, int value)
	{
		ConvertMPX(statName);
		STATS::STAT_SET_INT(Joaat(statName), value, TRUE);
	}

	void SetBool(std::string statName, bool value)
	{
		ConvertMPX(statName);
		STATS::STAT_SET_BOOL(Joaat(statName), value, TRUE);
	}

	void SetFloat(std::string statName, float value)
	{
		ConvertMPX(statName);
		STATS::STAT_SET_FLOAT(Joaat(statName), value, TRUE);
	}

	void SetDate(std::string statName, Date* value)
	{
		ConvertMPX(statName);
		STATS::STAT_SET_DATE(Joaat(statName), value, SCR_SIZEOF(Date), TRUE);
	}

	void SetString(std::string statName, const char* value)
	{
		ConvertMPX(statName);
		STATS::STAT_SET_STRING(Joaat(statName), value, TRUE);
	}

	int GetInt(std::string statName)
	{
		int value{};
		ConvertMPX(statName);
		STATS::STAT_GET_INT(Joaat(statName), &value, -1);
		return value;
	}

	bool GetBool(std::string statName)
	{
		BOOL value{};
		ConvertMPX(statName);
		STATS::STAT_GET_BOOL(Joaat(statName), &value, -1);
		return value;
	}

	float GetFloat(std::string statName)
	{
		float value{};
		ConvertMPX(statName);
		STATS::STAT_GET_FLOAT(Joaat(statName), &value, -1);
		return value;
	}

	Date GetDate(std::string statName)
	{
		Date value{};
		ConvertMPX(statName);
		STATS::STAT_GET_DATE(Joaat(statName), &value, SCR_SIZEOF(Date), -1);
		return value;
	}

	const char* GetString(std::string statName)
	{
		ConvertMPX(statName);
		return STATS::STAT_GET_STRING(Joaat(statName), -1); // The native is null-safe
	}

	void SetPackedBool(int index, bool value)
	{
		STATS::SET_PACKED_STAT_BOOL_CODE(index, value, -1);
	}

	void SetPackedInt(int index, int value)
	{
		STATS::SET_PACKED_STAT_INT_CODE(index, value, -1);
	}

	bool GetPackedBool(int index)
	{
		return STATS::GET_PACKED_STAT_BOOL_CODE(index, -1);
	}

	int GetPackedInt(int index)
	{
		return STATS::GET_PACKED_STAT_INT_CODE(index, -1);
	}
}