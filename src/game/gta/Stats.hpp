#pragma once
#include "core/util/Joaat.hpp"
#include "types/script/types.hpp"

namespace YimMenu::Stats
{
	extern int GetCharIndex();

	extern void SetInt(std::string statName, int value);
	extern void SetBool(std::string statName, bool value = true);
	extern void SetFloat(std::string statName, float value);
	extern void SetDate(std::string statName, Date* value);
	extern void SetString(std::string statName, const char* value);
	extern int GetInt(std::string statName);
	extern bool GetBool(std::string statName);
	extern float GetFloat(std::string statName);
	extern Date GetDate(std::string statName);
	extern const char* GetString(std::string statName);

	extern void SetPackedBool(int index, bool value);
	extern void SetPackedInt(int index, int value);
	extern bool GetPackedBool(int index);
	extern int GetPackedInt(int index);

	extern void SetMaskedBool(std::string statName, int bitIndex, bool value);
	extern void SetMaskedInt(std::string statName, int bitStart, int bitSize, int value);
	extern bool GetMaskedBool(std::string statName, int bitIndex);
	extern int GetMaskedInt(std::string statName, int bitIndex, int bitSize);

	//You can directly write/read all packed int/bool and uint64 statistics.
	extern void SetMaskedAll(std::string statName, uint64_t value);
	extern void SetMaskedAll(Hash hash, uint64_t value);
	uint64_t GetMaskedAll(Hash hash, int playerindex=-1);
	uint64_t GetMaskedAll(std::string statName, int playerindex = -1);
}