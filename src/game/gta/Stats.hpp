#pragma once
#include "core/util/Joaat.hpp"
#include "types/script/types.hpp"

namespace YimMenu::Stats
{
	extern int GetCharIndex();

	extern void SetInt(std::string statName, int value);
	extern void SetBool(std::string statName, bool value);
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
}