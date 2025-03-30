#pragma once
#include <cstdint>
#include "types/rage/vector.hpp"
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPhysicalAttachDataNode : CSyncDataNodeInfrequent
{
public:
    bool m_IsAttached; //0x00C0
    bool unk_00C1; //0x00C1
    uint16_t m_Attachedto; //0x00C2
    char pad_00C4[12]; //0x00C4
    rage::fvector3 m_Offset; //0x00D0
    rage::fvector4 m_Orientation; //0x00E0
    rage::fvector3 m_ParentOffset; //0x00F0
    uint16_t m_OtherAttachBone; //0x0100
    uint16_t m_AttachBone; //0x0102
    uint32_t m_AttachFlags; //0x0104
    bool m_AllowInitialSeparation; //0x0108
    char pad_00109[3]; //0x0109
    float unk_010C; //0x010C
    float unk_0110; //0x0110
    bool unk_0114; //0x0114
    bool unk_0115; //0x0115
    bool m_IsCargoVehicle; //0x0116
}; //Size: 0x0120
static_assert(sizeof(CPhysicalAttachDataNode) == 0x120);