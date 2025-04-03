#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

#include <cstdint>

class CPedGameStateDataNode : CSyncDataNodeInfrequent
{
public:
	uint8_t m_WeaponComponentSomething[12]; //0x00C0
	uint32_t m_WeaponComponentHash[12];     //0x00CC
	uint32_t m_GadgetHash[3];               //0x00FC
	uint32_t unk_0108;                      //0x0108
	uint32_t unk_010C;                      //0x010C
	uint32_t unk_0110;                      //0x0110
	float unk_0114;                         //0x0114
	float unk_0118;                         //0x0118
	float unk_011C;                         //0x011C
	bool unk_0120;                          //0x0120
	uint32_t m_ArrestState;                 //0x0124
	uint32_t m_DeathState;                  //0x0128
	uint32_t m_WeaponHash;                  //0x012C
	uint32_t m_NumWeaponComponents;         //0x0130
	uint32_t m_NumEquippedGadgets;          //0x0134
	uint32_t m_VehicleSeat;                 //0x0138
	uint32_t m_ActionModeOverride;          //0x013C
	uint32_t unk_0140;                      //0x0140
	uint16_t m_VehicleId;                   //0x0144
	uint16_t m_MountId;                     //0x0146
	uint16_t m_CustodianId;                 //0x0148
	uint16_t unk_014A;                      //0x014A
	uint8_t new_014C;                       //0x014C  -- added b3258
	uint8_t m_TintIndex;                    //0x014D
	char pad_014E;                          //0x014E
	uint8_t unk_014F;                       //0x014F
	bool m_IsHandcuffed;                    //0x0150
	bool m_CanPerformArrest;                //0x0151
	bool m_CanPerformUncuff;                //0x0152
	bool m_CanBeArrested;                   //0x0153
	bool m_IsInCustody;                     //0x0154
	char pad_0155;                          //0x0155
	bool m_WeaponExists;                    //0x0156
	bool m_WeaponVisible;                   //0x0157
	bool m_WeaponHasAmmo;                   //0x0158
	bool m_WeaponAttachLeft;                //0x0159
	char pad_015A;                          //0x015A
	bool m_InSeat;                          //0x015B
	bool m_InVehicle;                       //0x015C
	bool m_OnMount;                         //0x015D
	bool m_HasCustodianOrArrestFlags;       //0x015E
	char pad_015F;                          //0x015F
	bool m_ActionModeEnabled;               //0x0160
	bool m_StealthModeEnabled;              //0x0161
	bool unk_0162;                          //0x0162
	bool unk_0163;                          //0x0163
	bool unk_0164;                          //0x0164
	bool unk_0165;                          //0x0165
	bool unk_0166;                          //0x0166
	bool unk_0167;                          //0x0167
	bool unk_0168;                          //0x0168
	bool unk_0169;                          //0x0169
	bool unk_016A;                          //0x016A
	bool unk_016B;                          //0x016B
	bool unk_016C;                          //0x016C
	bool unk_016D;                          //0x016D
	bool unk_016E;                          //0x016E
	bool unk_016F;                          //0x016F
	bool unk_0170;                          //0x0170
	bool unk_0171;                          //0x0171
	bool unk_0172;                          //0x0172
	bool unk_0173;                          //0x0173
	bool unk_0174;                          //0x0174
	bool unk_0175;                          //0x0175
	bool unk_0176;                          //0x0176
	bool unk_0177;                          //0x0177
	bool m_0x178;                           //0x0178 -- added b3407
	bool m_0x179;                           //0x0179 -- added b3407
}; //Size: 0x0180
static_assert(sizeof(CPedGameStateDataNode) == 0x180);