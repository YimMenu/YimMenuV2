#pragma once
#include "types/script/types.hpp"
#include "types/script/Timer.hpp"
#include "types/script/globals/GSBD_BlockB.hpp"

enum class eDealerPremiumProducts
{
	COKE = 2,
	METH = 3,
	WEED = 4,
	ACID = 7
};

struct STREET_DEALER_DATA
{
	SCR_INT Location;                                 // 0
	alignas(8) eDealerPremiumProducts PremiumProduct; // 1 (https://github.com/ShinyWasabi/GTAO-Bot/blob/8394e090afa584938c8e9a63a55b22e2803a51e0/src/modules/street_dealers.js#L76)
	SCR_INT CokePrice;                                // 2
	SCR_INT MethPrice;                                // 3
	SCR_INT WeedPrice;                                // 4
	SCR_INT AcidPrice;                                // 5
	SCR_INT UNK_0006;                                 // 6
};
static_assert(sizeof(STREET_DEALER_DATA) == 7 * 8);

struct STREET_DEALERS
{
	SCR_ARRAY<STREET_DEALER_DATA, 3> Dealers; // 0
	SCR_INT ClosestDealerLocation;            // 22
	SCR_INT ClosetsDealerIndex;               // 23
};
static_assert(sizeof(STREET_DEALERS) == 24 * 8);

struct DAILY_RESET_DATA
{
	TIMER Timer;             // 0
	SCR_INT ResetDurationMs; // 1 (86400000ms = 24 hours)
	SCR_INT Seed;            // 2
};
static_assert(sizeof(DAILY_RESET_DATA) == 4 * 8);

struct FREEMODE_DELIVERY_DATA
{
	SCR_INT Flags;             // 0
	SCR_INT TransactionStatus; // 1
	BLIP_INDEX Blip;           // 2
	SCR_INT Type;              // 3 (this seems to be the same as DeliverableHash, at least for exotic exports)
	SCR_INT FMMCType;          // 4
	DELIVERABLE_ID Id;         // 5
	GAMER_HANDLE GamerHandle;  // 7
	TIMER Timer;               // 20
	SCR_HASH DeliverableHash;  // 22
	SCR_BOOL Refresh;          // 23 (needs more testing)
};
static_assert(sizeof(FREEMODE_DELIVERY_DATA) == 24 * 8);

struct FreemodeGeneral
{
	uint64_t PAD_0000[301];
	VEHICLE_INDEX PersonalVehicleIndex; // 301
	uint64_t PAD_0302[273];
	SCR_BOOL PersonalVehicleRequested; // 575
	uint64_t PAD_0576[14];
	SCR_BOOL NodeDistanceCheck; // 590
	uint64_t PAD_0591[48];
	SCR_INT RequestedPersonalVehicleId; // 639
	uint64_t PAD_0640[2];
	SCR_BOOL Exec1Impound; // 642
	uint64_t PAD_0643[4992];
	STREET_DEALERS StreetDealers; // 5635
	uint64_t PAD_5659[107];
	DAILY_RESET_DATA DailyReset; // 5766
	FREEMODE_DELIVERY_DATA DeliveryData; // 5770

	static FreemodeGeneral* Get();
};
//static_assert(sizeof(FreemodeGeneral) == 6073 * 8);