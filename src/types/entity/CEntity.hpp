#pragma once

#include "fwEntity.hpp"

#include <cstdint>

class CEntityDrawHandler;

class CEntity : public rage::fwEntity
{
public:
	virtual void* _0x120() = 0;            // implemented only by CPed
	virtual void UpdatePositionImpl() = 0; // 0x128
	virtual void _0x130() = 0;
	virtual void _0x138(void*) = 0;
	virtual void _0x140() = 0;
	virtual void _0x148(int) = 0;
	virtual bool _0x150() = 0;
	virtual CEntityDrawHandler* CreateDrawHandler() = 0; // 0x158
	virtual int GetTypeFlags() = 0;                      // 0x160
	virtual int GetTypeFlags2() = 0;                     // 0x168
	virtual bool _0x170() = 0;                           // implemented only by CPickup
	virtual bool _0x178() = 0;
	virtual void _0x180(bool) = 0;
	virtual bool _0x188() = 0;
	virtual bool _0x190() = 0;
	virtual void ClearDecals() = 0;                           // 0x198
	virtual void GetModelBounds(rage::fvector3* bounds) = 0;  // 0x1A0
	virtual void GetModelBounds2(rage::fvector3* bounds) = 0; // 0x1A8
	virtual float GetBoundingBoxSize() = 0;                   // 0x1B0
	virtual float _0x1B8(void*) = 0;
	virtual float _0x1C0(void*) = 0;
	virtual rage::fvector3* _0x1C8() = 0;
	virtual rage::fvector3* GetCameraOffset() = 0;               // 0x1D0
	virtual void GetCameraBasePosition(rage::fvector3* pos) = 0; // 0x1D8
	virtual bool _0x1E0() = 0;
	virtual bool Update() = 0; // 0x1E8 always returns true
	virtual bool _0x1F0() = 0;
	virtual void Warp(rage::fvector3* pos, float heading, bool) = 0; // 0x1F8

	uint32_t m_flags_3; //0x00C0
	uint32_t m_flags_4; //0x00C4
	uint32_t dwordC8;
	uint32_t dwordCC;
};
static_assert(sizeof(CEntity) == 0xD0);