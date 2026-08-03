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

	void SetMaskedBool(std::string statName, int bitIndex, bool value)
	{
		ConvertMPX(statName);
		STATS::STAT_SET_MASKED_INT(Joaat(statName), value, bitIndex, 1, true);
	}

	void SetMaskedInt(std::string statName, int bitStart, int bitSize, int value)
	{
		ConvertMPX(statName);
		STATS::STAT_SET_MASKED_INT(Joaat(statName), value, bitStart, bitSize, true);
	}

	bool GetMaskedBool(std::string statName, int bitIndex)
	{
		int value{};
		ConvertMPX(statName);
		STATS::STAT_GET_MASKED_INT(Joaat(statName), &value, bitIndex, 1, -1);
		return value != 0;
	}

	int GetMaskedInt(std::string statName, int bitIndex, int bitSize)
	{
		int value{};
		ConvertMPX(statName);
		STATS::STAT_GET_MASKED_INT(Joaat(statName), &value, bitIndex, bitSize, -1);
		return value;
	}


	void Stats::SetMaskedAll(Hash hash, uint64_t value)
	{
		uint64_t uint64_value = value;
		int part0 = uint64_value & 0xFFFFu;
		int part1 = (uint64_value >> 16) & 0xFFFFu;
		int part2 = (uint64_value >> 32) & 0xFFFFu;
		int part3 = (uint64_value >> 48) & 0xFFFFu;
		// The second input parameter is of type int. Using -1 will cause the entire data to overflow
		//so you have to split the 64-bit data into 4 parts to write it.
		STATS::STAT_SET_MASKED_INT(hash, part0, 0, 16, true);  //bit0-bit15
		STATS::STAT_SET_MASKED_INT(hash, part1, 16, 16, true); //bit16-bit31
		STATS::STAT_SET_MASKED_INT(hash, part2, 32, 16, true); //bit32-bit47
		STATS::STAT_SET_MASKED_INT(hash, part3, 48, 16, true); //bit48-bit63
	}

	void Stats::SetMaskedAll(std::string statName, uint64_t value)
	{
		ConvertMPX(statName);
		uint64_t uint64_value = value;
		int part0 = uint64_value & 0xFFFFu;
		int part1 = (uint64_value >> 16) & 0xFFFFu;
		int part2 = (uint64_value >> 32) & 0xFFFFu;
		int part3 = (uint64_value >> 48) & 0xFFFFu;
		
		auto hash = Joaat(statName);
		STATS::STAT_SET_MASKED_INT(hash, part0, 0, 16, true);  //bit0-bit15
		STATS::STAT_SET_MASKED_INT(hash, part1, 16, 16, true); //bit16-bit31
		STATS::STAT_SET_MASKED_INT(hash, part2, 32, 16, true); //bit32-bit47
		STATS::STAT_SET_MASKED_INT(hash, part3, 48, 16, true); //bit48-bit63
	}

	uint64_t GetMaskedAll(Hash hash, int playerindex)
	{
		int part0 = 0, part1 = 0, part2 = 0, part3 = 0;
		STATS::STAT_GET_MASKED_INT(hash, &part0, 0, 16, playerindex);
		STATS::STAT_GET_MASKED_INT(hash, &part1, 16, 16, playerindex);
		STATS::STAT_GET_MASKED_INT(hash, &part2, 32, 16, playerindex);
		STATS::STAT_GET_MASKED_INT(hash, &part3, 48, 16, playerindex);
		uint64_t value = (static_cast<uint64_t>(part3) << 48) | (static_cast<uint64_t>(part2) << 32) | (static_cast<uint64_t>(part1) << 16) | part0;
		return value;
	}

	uint64_t GetMaskedAll(std::string statName, int playerindex)
	{
		Hash hash = Joaat(statName);
		int part0 = 0, part1 = 0, part2 = 0, part3 = 0;
		STATS::STAT_GET_MASKED_INT(hash, &part0, 0, 16, playerindex);
		STATS::STAT_GET_MASKED_INT(hash, &part1, 16, 16, playerindex);
		STATS::STAT_GET_MASKED_INT(hash, &part2, 32, 16, playerindex);
		STATS::STAT_GET_MASKED_INT(hash, &part3, 48, 16, playerindex);
		uint64_t value = (static_cast<uint64_t>(part3) << 48) | (static_cast<uint64_t>(part2) << 32) | (static_cast<uint64_t>(part1) << 16) | part0;
		return value;
	}

}