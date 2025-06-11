#pragma once
#include "types/rage/atArray.hpp"

class CStatsMpCharacterMappingData
{
public:
	enum class Type
	{
		Int,
		Float,
		Bool,
		String,
		TextLabel,
		Date,
		Vector,
		UserId,
		IntAward,
		FloatAward,
		BoolAward
	};

	struct MappingData
	{
		char m_Pad[8];
		std::int32_t m_Slot0Hash;
		std::int32_t m_Slot1Hash;
	};

	char m_Pad[8];
	rage::atArray<MappingData> m_Data[11];

	// Should we move these to gta/Stats instead?
	int GetStatCount(Type type);
	int GetStatHash(Type type, int index, int slot);
};