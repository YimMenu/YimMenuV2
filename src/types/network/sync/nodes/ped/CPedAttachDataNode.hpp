#pragma once
#include <cstdint>
#include "types/rage/vector.hpp"
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPedAttachDataNode : CSyncDataNodeInfrequent
{
public:
    rage::fvector3 m_Offset; //0x00C0
    rage::fvector4 m_Orientation; //0x00D0
    uint16_t m_AttachedTo; //0x00E0
    uint16_t m_AttachmentBone; //0x00E2
    uint32_t m_AttachmentFlags; //0x00E4
    float m_Heading; //0x00E8
    float m_Heading2; //0x00EC
    bool m_IsAttached; //0x00F0
    bool unk_00F1; //0x00F1
};
static_assert(sizeof(CPedAttachDataNode) == 0x100);