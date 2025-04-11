#pragma once
#include "types/rage/RTTI.hpp"

namespace rage
{
	class rlGamerInfo;
}
class CNonPhysicalPlayerData;

namespace rage
{
#pragma pack(push, 8)
	class netPlayer
	{
	public:
		DEFINE_RAGE_RTTI(netPlayer);

		virtual void Reset() = 0;
		virtual bool IsPhysical() = 0;
		virtual const char* GetName() = 0;
		virtual std::uint64_t GetHostToken() = 0;
		virtual void UpdatePermissions() = 0; // dev status, comm perms, etc.
		virtual bool IsHost() = 0;
		virtual rage::rlGamerInfo* GetGamerInfo() = 0;
		virtual void UpdateUnk() = 0; // force updates a player ped data node

		inline bool IsLocal() const
		{
			return (m_Flags & 1) != 0;
		}

	    int m_AccountId;                                 //0x0008
		int64_t m_RockstarId;                            //0x0010
		char pad_0018[0x38];                             //0x0018 voice chat stuff
		CNonPhysicalPlayerData* m_NonPhysicalPlayer;     //0x0050
		uint32_t m_MessageId;                            //0x0058
		char pad_005C[4];                                //0x005C
		uint8_t m_ActiveIndex;                           //0x0060
		uint8_t m_PlayerIndex;                           //0x0061
		char pad_0062[0x6E];                             //0x0062
		uint8_t m_Flags;                                 //0x00D0
		char pad_0091[0xF];                              //0x00D1
	}; //Size: 0x00A0
	static_assert(sizeof(netPlayer) == 0xE0);
#pragma pack(pop)
}