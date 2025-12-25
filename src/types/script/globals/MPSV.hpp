#pragma once
#include "types/script/types.hpp"

enum class ePersonalVehicleFlags
{
	TRIGGER_SPAWN_TOGGLE = 0,
	DESTROYED = 1,
	HAS_INSURANCE = 2,
	UNK0 = 3,
	IMPOUNDED = 6,
	UNK1 = 10,
	SPAWN_AT_MORS_MUTUAL = 11,
	UNK2 = 16
};

struct MPSV_Entry
{
	SCR_INT NumberPlateTextIndex;              // 0 (SET/GET_VEHICLE_NUMBER_PLATE_TEXT)
	TEXT_LABEL_15 NumberPlateText;             // 1
	SCR_INT Colours1;                          // 5 (SET/GET_VEHICLE_COLOURS)
	SCR_INT Colours2;                          // 6
	SCR_INT ExtraColours1;                     // 7 (SET/GET_VEHICLE_EXTRA_COLOURS)
	SCR_INT ExtraColours2;                     // 8
	SCR_ARRAY<uint64_t, 49> ModTypes;          // 9 (SET/GET_VEHICLE_MOD)
	SCR_ARRAY<uint64_t, 2> ModVariation;       // 59 (GET_VEHICLE_MOD_VARIATION)
	SCR_INT TyreSmokeR;                        // 62 (SET/GET_VEHICLE_TYRE_SMOKE_COLOR)
	SCR_INT TyreSmokeG;                        // 63
	SCR_INT TyreSmokeB;                        // 64
	SCR_INT WindowTint;                        // 65 (SET/GET_VEHICLE_WINDOW_TINT)
	SCR_HASH VehicleModel;                     // 66
	SCR_INT Livery;                            // 67 (SET/GET_VEHICLE_LIVERY)
	SCR_INT ConvertibleRoofState;              // 68 (GET_CONVERTIBLE_ROOF_STATE)
	SCR_INT WheelType;                         // 69 (SET/GET_VEHICLE_WHEEL_TYPE)
	SCR_INT DoorLockStatus;                    // 70 (GET_VEHICLE_DOOR_LOCK_STATUS)
	SCR_INT CustomPrimaryColourR;              // 71 (SET/GET_VEHICLE_CUSTOM_PRIMARY_COLOUR)
	SCR_INT CustomPrimaryColourG;              // 72
	SCR_INT CustomPrimaryColourB;              // 73
	SCR_INT NeonColourR;                       // 74 (SET/GET_VEHICLE_NEON_COLOUR)
	SCR_INT NeonColourG;                       // 75
	SCR_INT NeonColourB;                       // 76
	SCR_BITSET<uint64_t> Flags1;               // 77
	SCR_HASH HornHash;                         // 78 (OVERRIDE_VEH_HORN)
	SCR_INT HornSoundIndex;                    // 79 (SET/GET_VEHICLE_HORN_SOUND_INDEX)
	SCR_FLOAT EnveffScale;                     // 80 (SET/GET_VEHICLE_ENVEFF_SCALE)
	GAMER_HANDLE GamerHandle;                  // 81
	SCR_BOOL IsPersonalVehicle;                // 94 (this actually seems to be an int)
	SCR_BITSET<uint64_t> Flags2;               // 95
	SCR_INT PersonalVehicleSlot;               // 96 (DECOR_GET_INT(veParam0, "PV_Slot"))
	SCR_INT ExtraColour5;                      // 97 (SET/GET_VEHICLE_EXTRA_COLOUR_5)
	SCR_INT Livery2;                           // 98 (SET/GET_VEHICLE_LIVERY2)
	SCR_INT ExtraColour6;                      // 99 (SET/GET_VEHICLE_EXTRA_COLOUR_6)
	PLAYER_INDEX PlayerIndex;                  // 100
	SCR_INT ImportExportVehicle;               // 101
	SCR_INT TyreType;                          // 102
	SCR_BITSET<uint64_t> Flags3;               // 103 (flag 0 is set if the MLJ decor exists)
	SCR_BITSET<ePersonalVehicleFlags> PersonalVehicleFlags; // 104
	SCR_INT ImpoundTime;                       // 105 (MP_STAT_MPSV_IMPOUND_TIME)
	SCR_INT PremiumPaid;                       // 106 (MP_STAT_MPSV_PREMIUM_PAID)
	TEXT_LABEL_63 DestroyerName;               // 107
	TEXT_LABEL_63 PlayerRadioStationName;      // 123 (GET_PLAYER_RADIO_STATION_NAME)
	SCR_INT PrimaryColour;                     // 139
	SCR_INT SecondaryColour;                   // 140
	SCR_INT PurchasePrice;                     // 141
	SCR_INT ObtainedTime;                      // 142 (MP_STAT_MPSV_OBTAINED_TIME)
};
static_assert(sizeof(MPSV_Entry) == 143 * 8);

struct MPSV
{
	SCR_ARRAY<MPSV_Entry, 607> Entries;

	static MPSV* Get();
};
static_assert(sizeof(MPSV) == 86802 * 8);