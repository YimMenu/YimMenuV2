#pragma once
#include <cstdint>

namespace rage
{
	union rlPresenceAttributeValue
	{
		char m_StringValue[256];
		uint64_t m_IntValue;

		rlPresenceAttributeValue(const char* value)
		{
			strncpy(m_StringValue, value, sizeof(m_StringValue));
		}

		rlPresenceAttributeValue(std::uint64_t value)
		{
			m_IntValue = value;
		}
	};

	class rlQueryPresenceAttributesContext
	{
	public:
		enum class Type : std::uint32_t
		{
			INT = 1,
			STRING = 3
		};

		char m_Key[64]{};
		rlPresenceAttributeValue m_Value{(std::uint64_t)0};
		Type m_Type = Type::INT;

		rlQueryPresenceAttributesContext()
		{
		}

		rlQueryPresenceAttributesContext(std::string_view key, Type type, rlPresenceAttributeValue default_value)
		{
			strncpy(m_Key, key.data(), sizeof(m_Key));
			m_Type = type;
			m_Value = default_value;
		}
	}; //Size: 0x0148
	static_assert(sizeof(rage::rlQueryPresenceAttributesContext) == 0x148);
}