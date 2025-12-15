#pragma once
#include "../types.hpp"

struct PLAYER_BOUNTY
{
	SCR_BOOL HasBounty;
	SCR_INT BountyAmount;
	SCR_INT PAD_0002; // unused
};
static_assert(sizeof(PLAYER_BOUNTY) == 3 * 8);

struct ACTIVE_CONTACT_SERVICE
{
	SCR_INT Id;
	PLAYER_INDEX Target;
	SCR_BOOL Bounty; // unknown usage
	SCR_INT Flags;
};
static_assert(sizeof(ACTIVE_CONTACT_SERVICE) == 4 * 8);

struct WEAPON_PICKUPS
{
	SCR_INT LastUnkWeaponPickupTime;
	SCR_INT LastMeleeWeaponPickupTime;
	SCR_INT LastProjectilePickupTime;
	SCR_INT LastGunPickupTime;
	SCR_ARRAY<uint64_t, 95> Indices; // size increased in b3095 (62 -> 95) // and in b3407 (95 -> 96) // one of PICKUP_WEAPON_VINTAGEPISTOL removed in b1013.17g9
	SCR_ARRAY<uint64_t, 95> Owners;
	SCR_INT SpawnCounter;
	SCR_INT AmmoCount;
};
static_assert(sizeof(WEAPON_PICKUPS) == 198 * 8);

struct BIKER_CONTRACTS_SERVER
{
	SCR_ARRAY<uint64_t, 3> ActiveContracts;
	SCR_ARRAY<uint64_t, 3> ContractCompleteCount;
	SCR_INT CompletedContractBitset;
	SCR_INT LastContractRefreshTime;
};
static_assert(sizeof(BIKER_CONTRACTS_SERVER) == 10 * 8);

struct GSBD_FM
{
	SCR_ARRAY<uint64_t, 2> ModelSwapBits; // 0
	SCR_INT PAD_0003; // unused
	SCR_ARRAY<PLAYER_BOUNTY, 32> PlayerBounties; // 4
	uint64_t PAD_0101[5];                  // unused
	SCR_ARRAY<uint64_t, 2> MuggingPlayers; // 0 = mugger, 1 = merryweather mercs
	SCR_ARRAY<uint64_t, 2> MuggedPlayers;
	uint64_t PAD_0112[4];             // unused
	SCR_ARRAY<uint64_t, 65> PAD_0116; // TODO b3407 (61 -> 62), 62 -> 65
	SCR_INT ShopProcessingBitset;
	SCR_ARRAY<uint64_t, NUM_CONTACTS> ActiveContactServiceBitsets;
	SCR_ARRAY<ACTIVE_CONTACT_SERVICE, 32> ActiveContactServices;
	PLAYER_INDEX SpectatorTVWantedPlayer;
	SCR_BOOL SpectatorTVWantedClosing;
	SCR_BOOL SpectatorTVWantedActive;
	uint64_t PAD_0390[2]; // not read by the scripts
	SCR_INT PAD_0392;     // TODO
	uint64_t PAD_0393[6]; // TODO
	WEAPON_PICKUPS WeaponPickups;
	BIKER_CONTRACTS_SERVER BikerContracts;
	SCR_ARRAY<uint64_t, 32> DoubleActionCacheLocationRevealed;
	SCR_INT LastBroadcastTime; // added b889g9, unused

	static GSBD_FM* Get();
};
static_assert(sizeof(GSBD_FM) == 653 * 8);