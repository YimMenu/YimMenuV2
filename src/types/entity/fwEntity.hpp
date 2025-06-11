#pragma once


#include "../rage/RTTI.hpp"
#include "../rage/fwExtensibleBase.hpp"
#include "../rage/vector.hpp"

#include <cstdint>

class CMoveObjectPooledObject;
class CNavigation;

namespace rage
{
	class fwDynamicEntityComponent;
	class crmtRequestPose;
	class crmtRequestIk;
	class crFrameFilter;
	class fwAudEntity;
	class fwDrawData;

	class fwEntity : public fwExtensibleBase
	{
	public:
		DEFINE_RAGE_RTTI(rage::fwEntity);

		virtual void* _0x38(void*, void*) = 0;
		virtual void AddExtension(void* extension) = 0; // 0x40
		virtual void _0x48() = 0;                       // not implemented
		virtual void _0x50() = 0;                       // only implemented by CEntityBatch
		virtual void _0x58() = 0;
		virtual void SetModelInfo(std::uint16_t* model_index) = 0; // 0x60
		virtual void _0x68(int, vector4*) = 0;
		virtual void* _0x70(int) = 0;
		virtual CNavigation* GetNavigation() = 0;                // 0x78
		virtual CMoveObjectPooledObject* CreateMoveObject() = 0; // 0x80
		virtual std::uint32_t* GetType() = 0;                    // 0x88
		virtual void _0x90() = 0;
		virtual float _0x98() = 0;
		virtual bool TryRequestInverseKinematics(rage::crmtRequestPose* pose, rage::crmtRequestIk* ik) = 0; // 0xA0 implemented only by CPed
		virtual bool TryRequestFacialAnims(void*) = 0;                                                      // 0xA8 implemented only by CPed
		virtual void* _0xB0() = 0;
		virtual std::uint8_t _0xB8() = 0;                  // implemented only by CPed
		virtual rage::crFrameFilter* GetFrameFilter() = 0; // 0xC0
		virtual rage::fwAudEntity* GetEntityAudio() = 0;   // 0xC8
		virtual void _0xD0() = 0;
		virtual void SetTransform(matrix44* matrix, bool update_pos) = 0;  // 0xD8
		virtual void SetTransform2(matrix44* matrix, bool update_pos) = 0; // 0xE0
		virtual void SetPosition(fvector4* pos, bool update_pos) = 0;      // 0xE8
		virtual void SetHeading(float heading, bool update_pos) = 0;       // 0xF0
		virtual void SetEntityTypeFlags() = 0;                             // 0xF8
		virtual void _0x100() = 0;                                         // not implemented
		virtual void UpdatePhysics(CNavigation* navigation) = 0;           // 0x108
		virtual void UpdatePhysics2(CNavigation* navigation) = 0;          // 0x110
		virtual void UpdatePosition() = 0;                                 // 0x118

		enum class Flags
		{
			IS_VISIBLE = (1 << 0)
		};

		enum class Type : std::uint8_t
		{
			VEHICLE = 3,
			PED,
			OBJECT
		};

		class CBaseModelInfo* m_ModelInfo;                              //0x0020
		Type m_Type;                                                    //0x0028
		char gap29;                                                     //0x0029
		uint16_t gap2A;                                                 //0x002A
		uint32_t m_Flags;                                               //0x002D
		class CNavigation* m_Navigation;                                //0x0030
		uint16_t gap38;                                                 //0x0038
		uint16_t gap3A;                                                 //0x003A
		uint32_t gap3C;                                                 //0x003C
		class rage::fwDynamicEntityComponent* m_DynamicEntityComponent; //0x0040 (stores attachments and stuff)
		class rage::fwDrawData* m_DrawData;                             //0x0048
		class rage::fwDynamicEntityComponent* gap50;                    //0x0050
		uint64_t gap58;                                                 //0x0058
		matrix44 m_Transform;                                           //0x0060
		rage::fwEntity* m_RenderFocusEntity;                            //0x00A0
		uint32_t m_RenderFocusDistance;                                 //0x00A8
		uint32_t m_Flags2;                                              //0x00AC
		uint32_t m_ShadowFlags;                                         //0x00B0
		char gapB4[4];                                                  //0x00B4
		std::uint8_t byteB8;                                            //0x00B8

		rage::fvector3* GetPosition()
		{
			return reinterpret_cast<rage::fvector3*>(&m_Transform.rows[3]);
		}

		bool IsVehicle() const
		{
			return m_Type == Type::VEHICLE;
		}

		bool IsPed() const
		{
			return m_Type == Type::PED;
		}

		bool IsObject() const
		{
			return m_Type == Type::OBJECT;
		}
	};
	static_assert(sizeof(fwEntity) == 0xC0);
}