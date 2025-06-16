#pragma once

#include "../rage/RTTI.hpp"
#include <cstdint>

class CDynamicEntity;
namespace rage
{
	class netObject
	{
	public:
		enum class Type : std::uint16_t
		{
			AUTOMOBILE,
			BIKE,
			BOAT,
			DOOR,
			HELI,
			OBJECT,
			PED,
			PICKUP,
			PICKUP_PLACEMENT,
			PLANE,
			SUBMARINE,
			PLAYER,
			TRAILER,
			TRAIN,
			GLASS_PANE,      // new in Enhanced, but doesn't actually seem to have a sync tree associated with it
			MAX = GLASS_PANE // for compatibility
		};

		Type m_ObjectType;           //0x0008
		int16_t m_ObjectId;          //0x000A
		char pad_000C[61];           //0x000C
		int8_t m_OwnerId;            //0x0049
		int8_t m_NextOwnerId;        //0x004A
		bool m_IsRemote;             //0x004B
		uint16_t m_Flags;            //0x004C
		uint16_t m_Flags2;           //0x004E
		class CObject* m_GameObject; //0x0050
		char pad_0058[48];           //0x0058
		uint32_t m_OwnershipToken;   //0x0088

		DEFINE_RAGE_RTTI(rage::netObject);

		inline bool IsVehicle() const
		{
			return m_ObjectType == Type::AUTOMOBILE || m_ObjectType == Type::BIKE || m_ObjectType == Type::BOAT || m_ObjectType == Type::HELI || m_ObjectType == Type::PLANE || m_ObjectType == Type::SUBMARINE || m_ObjectType == Type::TRAILER;
		}
	}; //Size: 0x008C
	static_assert(sizeof(netObject) == 0x90);
}