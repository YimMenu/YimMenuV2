#pragma once
#include "../types.hpp"
#include "GlobalPlayerBD.hpp"

struct IMPOUND_VEHICLE_INFO
{
	SCR_INT ImpoundId;
	SCR_BOOL OccupiedCheckDone;
	SCR_INT EntityAreaHandle;
	SCR_INT TimeCreated;
};
static_assert(sizeof(IMPOUND_VEHICLE_INFO) == 4 * 8);

struct CEO_COLOR
{
	PLAYER_INDEX Owner;
	SCR_INT Color;
};
static_assert(sizeof(CEO_COLOR) == 2 * 8);

// I don't think this class has anything to do with ceo colors at all
struct CEO_COLORS
{
	SCR_ARRAY<uint64_t, 10> CeoColorIndices;
	SCR_ARRAY<uint64_t, 32> CeoColorIndices2;
	SCR_ARRAY<CEO_COLOR, 10> CeoColors;
	SCR_INT PAD_0065;
	uint64_t PAD_0066[19];
	SCR_INT PAD_0085; // added b3095 ("Press ~INPUT_CONTEXT~ to contact Jamal and begin stealing bolt cutters for The Cargo Ship Robbery" mission variation)
};
static_assert(sizeof(CEO_COLORS) == 86 * 8);

struct SMPL_INTERIOR_DATA_SERVER
{
	SCR_INT PAD_0000; // unused
	SCR_ARRAY<uint64_t, 32> PlayerInteriorInstances;
	SCR_ARRAY<uint64_t, 32> PlayerInteriorIds; // used solely for telemetry
	SCR_INT PlayerInteriorCreationRequestBitset;
	SCR_ARRAY<uint64_t, 32> PlayerOwnerBitset;
	SCR_INT PlayerInteriorRemovalRequestBitset;
	SCR_ARRAY<uint64_t, 32> PlayerInteriorCreationTimes;
	SCR_ARRAY<uint64_t, 32> PlayerInteriorSimpleInteriorTypes;
	SCR_ARRAY<uint64_t, 32> PlayerInteriorIsOwnerless;
	SCR_ARRAY<uint64_t, 32> PlayerInteriorOwners;
	SCR_INT LastBroadcastTime; // added b889g9, unused
};
static_assert(sizeof(SMPL_INTERIOR_DATA_SERVER) == 235 * 8);

struct LEAVE_CLUBHOUSE_SERVER
{
	SCR_ARRAY<uint64_t, 32> Identifiers;
	SCR_ARRAY<uint64_t, 32> ExitLocations;
	SCR_ARRAY<uint64_t, 32> ExitLocationSlots;
};
static_assert(sizeof(LEAVE_CLUBHOUSE_SERVER) == 99 * 8);

struct IE_DELIVERY_INFO
{
	PLAYER_INDEX Player_;
	SCR_HASH VehicleModel;
	PLAYER_INDEX ContrabandOwner;
	SCR_INT TimeCreated;
	SCR_BOOL PAD_0004;
};
static_assert(sizeof(IE_DELIVERY_INFO) == 5 * 8);

struct GSBD
{
	alignas(8) eFreemodeState FreemodeState;
	SCR_INT SessionToken; // time when freemode had started for the script host
	SCR_ARRAY<IMPOUND_VEHICLE_INFO, 32> ImpoundVehicleInfos;
	SCR_ARRAY<SCR_VEC3, 32> SpawnPositions;
	SCR_ARRAY<uint64_t, 32> SpawnPositionCreationTimes;
	SCR_ARRAY<uint64_t, 32> SpawnPositionsValid;
	SCR_ARRAY<uint64_t, 32> PAD_0294;
	SCR_ARRAY<uint64_t, 32> SpawnPositionTokens;
	SCR_INT SpawnPositionCounter;
	SCR_ARRAY<uint64_t, 32> RespawnVehicles;
	SCR_ARRAY<uint64_t, 32> RespawnVehicleSeats;
	SCR_ARRAY<uint64_t, 32> MorsMutualSpawnSlots;
	SCR_INT MorsMutualSpawnPlayersBitset;
	uint64_t PAD_0461[353]; // TODO
	SCR_BOOL CopTimerOn;    // cut CnC content
	SCR_BOOL CrookTimerOn;
	SCR_BOOL PAD_0816; // always set to FALSE
	SCR_INT PAD_0817;  // unused
	CEO_COLORS CeoColors;
	//SMPL_INTERIOR_DATA_SERVER SimpleInteriorData;
	LEAVE_CLUBHOUSE_SERVER LeaveClubhouse;
	SCR_ARRAY<IE_DELIVERY_INFO, 32> IEDeliveryInfos;
	SCR_INT PAD_1397;
	NETWORK_INDEX IAATurretCameraVehicleId; // used by DDH act 1
	uint64_t PAD_1399[97];
	SCR_INT CayoPericoStrandedAnimalChoice;

	static GSBD* Get();
};
static_assert(sizeof(GSBD) == 1264 * 8);