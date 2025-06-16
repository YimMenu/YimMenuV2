#include "CGameScriptId.hpp"
#include "types/rage/datBitBuffer.hpp"

void CGameScriptId::Deserialize(rage::datBitBuffer& buffer)
{
	m_Hash = buffer.Read<uint32_t>(32);
	m_Timestamp = buffer.Read<uint32_t>(32);

	bool has_position_hash = buffer.Read<bool>(1);
	if (has_position_hash)
	{
		m_PositionHash = buffer.Read<uint32_t>(32);
	}
	else
	{
		m_PositionHash = 0;
	}

	bool has_instance_id = buffer.Read<bool>(1);
	if (has_instance_id)
	{
		m_InstanceId = buffer.Read<int32_t>(8);
	}
	else
	{
		m_InstanceId = -1;
	}
}