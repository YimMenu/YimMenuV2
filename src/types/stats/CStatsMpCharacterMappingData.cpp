#include "CStatsMpCharacterMappingData.hpp"

int CStatsMpCharacterMappingData::GetStatCount(Type type)
{
	if (type < Type::Int || type > Type::BoolAward)
		return 0;

	return m_Data[(int)type].size();
}

int CStatsMpCharacterMappingData::GetStatHash(Type type, int index, int slot)
{
	if (type < Type::Int || type > Type::BoolAward)
		return 0;

	if (index < 0 || index >= m_Data[(int)type].size())
		return 0;

	if (slot < 0 || slot > 1)
		return 0;

	return slot ? m_Data[(int)type][index].m_Slot1Hash : m_Data[(int)type][index].m_Slot0Hash;
}