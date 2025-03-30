#pragma once
#include "types/rage/RTTI.hpp"

class CNetGamePlayer;

namespace rage
{
	class datBitBuffer;
	// this one is a pain to reverse
	class netArrayIdentifierBase
	{
		DEFINE_RAGE_RTTI(netArrayIdentifierBase);

		virtual void Initialize(CNetGamePlayer* player) = 0;           // 0x38
		virtual void Deserialize(rage::datBitBuffer* buffer) = 0;      // 0x40
		virtual void Serialize(rage::datBitBuffer* buffer) = 0;        // 0x48
		virtual int CalculateSize() = 0;                               // 0x50
		virtual const char* _0x58() = 0;                               // 0x58 (always returns an empty string)
		virtual bool IsEqual(rage::netArrayIdentifierBase* other) = 0; // 0x60
		virtual CNetGamePlayer* GetOwner() = 0;                        // 0x68
		virtual void SetOwner(CNetGamePlayer* new_owner) = 0;          // 0x70
		virtual int GetUnkId() = 0;                                    // 0x78
		virtual int GetUnkIdSize() = 0;                                // 0x80 (zero for script host identifiers)

		CNetGamePlayer* m_Owner; // 0x8
		int m_UnkId;             // 0x10 
	};
	static_assert(sizeof(netArrayIdentifierBase) == 0x18);
}