#pragma once
#include "../MPScriptData.hpp"
#include "../types.hpp"

enum class eFreemodeState
{
	NONE = 0,
	UNK_2 = 2,
	RUNNING = 4,
	CLOSING = 5,
	UNK_10 = 10,
	UNK_11 = 11
};

enum class eMissionType
{
	NONE,
	MISSION,
	HEIST,
	UNK_3,
	ADVERSARY_MODE,
	LAST_TEAM_STANDING,
	CAPTURE,
	HEIST_SETUP,
	UNK_8,  // FMMC_RSTAR_MCP
	UNKNOWN // everything else
};

enum class eAnimationBitset
{
	kCashRainActive = 12,
	kChampagneSprayActive = 13
};

enum class eBlipFlags
{
	// 0 is unused
	kVisibleOnCutscene = 1,
	kFlashMinimapDisplay = 2,
	kFlashBlip = 3,
	kMicroLightOTRActive = 4,
	kSkipTutorialSessionChecks = 5,
	kHideOnMinimap = 6,                 // needs testing
	kHideOnMinimapWhenInterior = 7,     // needs testing
	kHideOnMinimapWhenBigMapActive = 9, // needs testing
	kDontUsePassiveBlip = 21,
	kUseRampageBlip = 24,
	kHideWhenFading = 25
};

enum class eBlipType
{
	ON_FOOT,
	TANK,
	PLAYER_JET,
	PLAYER_PLANE,
	PLAYER_HELI,
	PLAYER_GUNCAR,
	PLAYER_BOAT,
	ROCKET_VOLTIC,
	TECHNICAL,
	RUINER_2000,
	DUNE_BUGGY,
	PHANTOM_WEDGE,
	ARMORED_BOXVILLE, // boxville5
	WASTELANDER,
	QUAD,
	APC,
	OPPRESSOR_MK_1,
	HALF_TRACK,
	DUNE_FAV,
	WEAPONIZED_TAMPA,
	AA_TRAILER,
	ALPHA_Z1,
	BOMBUSHKA,
	HAVOK,
	HOWARD,
	HUNTER,
	MICROLIGHT,
	MOGUL,
	MOLOTOK,
	NOKOTA,
	PYRO,
	ROGUE,
	STARLING,
	SEABREEZE,
	TULA,
	STROMBERG,
	DELUXO,
	THRUSTER,
	KHANJALI,
	RIOT_VAN,
	VOLATOL,
	BARRAGE,
	AKULA,
	CHERNOBOG,
	AVENGER,
	TURRETED_LIMO,
	SEA_SPARROW,
	CARACARA,
	PARTY_BUS,
	TERRORBYTE,
	MENACER,
	SCRAMJET,
	POUNDER_CUSTOM,
	MULE_CUSTOM,
	SPEEDO_CUSTOM,
	OPPRESSOR_MK_2,
	STRIKEFORCE,
	ARENA_BRUISER,
	ARENA_BRUTUS,
	ARENA_CERBERUS,
	ARENA_DEATHBIKE,
	ARENA_DOMINATOR,
	ARENA_IMPALER,
	ARENA_IMPERATOR,
	ARENA_ISSI,
	ARENA_SASQUATCH,
	ARENA_SCARAB,
	ARENA_SLAMVAN,
	ARENA_ZR380,
	MINI_SUB,
	SPARROW,
	FOLDING_WING_JET,
	GANG_BIKE,
	MILITARY_QUAD,
	SQUADDIE, // SQUADEE
	CAYO_DINGHY,
	WINKY,
	PATROL_BOAT,
	ANNIHILATOR,
	KART_RETRO,
	KART_MODERN,
	MILITARY_TRUCK,
	SUBMARINE,
	CHAMPION,
	BUFFALO_STX,
	DEITY, // why does this have a blip?
	JUBILEE,
	GRANGER_3600LX,
	PATRIOT_MILSPEC,
	ARMS_DEALING_AIR, // requires some flag to be set
	BRICKADE_6X6,
	RAIJU,
	CONADA2,
	STEAMER2,
	TOW_TRUCK,
};

enum class ePlayerStateFlags
{
	kScreenFadingOut = 0,
	kScreenFadedOut = 1,
	kCinematicNewsChannelActive = 2,
	kRepeatingPreviousCheckpoint = 3,
	kCarModIntro = 4,
	kPlayerSwitchStateAscent = 5,
	kPlayerSwitchStateInClouds = 6,
	kPlayerSwitchStatePan = 7,
	kPlayerSwitchStateDescent = 8,
	kModshopActive = 9,
	kModshopExitingVehicle = 10,
	kSpectating = 28,
	kBeastActive = 29,
	kPlayerNotInSCTV = 30,
	kPlayerInSCTV = 31
};

enum class ePlayerStateFlags2
{
	kHasGTAPlusMembership = 31
};

enum class eActivityFlags
{
	kWatchingMovie = 0,
	kInGangAttack = 1,
	kImpromptuRace = 2,
	kCrateDrop = 4, // tf is this? "~s~A plane is on its way to drop a Crate ~HUD_COLOUR_GREEN~~BLIP_CRATEDROP~ ~s~which contains useful equipment. Be the first to collect it."
	kDeliveringSimeonVehicle = 6,
	kInLapDance = 7,
	kHoldUpTutorial = 8,
	kJoyrider = 9, // uh what is this?
	kCarModTutorial = 10,
	kMissionLauncher = 11, // ???
	kLesterCutsceneActive = 12,
	kTrevorCutsceneActive = 13,
	kHeistIntro = 14,
	kPlaneTakedown = 15,  // not sure what this is
	kDistractCops = 16,   // "Great. Thank you for your help. Now some horrible criminals are in jail for a crime they did commit and it's all your fault!!" ???
	kDestroyVehicle = 17, // ???
	kPartakingInHotTarget = 18,
	kPartakingInKillList = 19,
	kTimeTrialStarted = 21,
	kPartakingInCheckpoints = 22,
	kPartakingInChallenge = 23,
	kPennedInActive = 24,
	kRCTimeTrialStarted = 25,
	kPartakingInHotProperty = 27,
	kPartakingInKingOfTheCastle = 29,
	kPartakingInCriminalDamage = 30,
	kLowriderIntro = 31
};

enum class eGamerTagFlags
{
	kShowPackageCount = 13,
	kFadeOutGamerTag = 17,
	kGangCEO = 19,
	kGangBiker = 20
}; // TODO!

enum class eOrbitalBitset
{
	kOrbitalCannonActive = 0,
	kWatchingMovie = 1, // not a typo, the orbital cannon script needs to know if you are inside a movie theater for some strange reason
	kCutsceneOrInterior = 2,
	kTransactionPending = 3
};

enum class eArcadeGameBitset
{
	kArcadeMachineActivated = 0,
	kLoveMeterActivated = 1,
	kLoveMeterAnimationGenderDecided = 2
};

enum class eOutOfSightFlags
{
	kOutOfSightEnabled = 0,
	kOutOfSightActive = 1, // this controls whether you appear on radar or not
	kHelpDisplayed = 2,
	kDamagedPlayerOutsideOrganization = 3
};

enum class eSimpleInteriorIndex
{
	SIMPLE_INTERIOR_INVALID = -1,
	SIMPLE_INTERIOR_WAREHOUSE_1,
	SIMPLE_INTERIOR_WAREHOUSE_2,
	SIMPLE_INTERIOR_WAREHOUSE_3,
	SIMPLE_INTERIOR_WAREHOUSE_4,
	SIMPLE_INTERIOR_WAREHOUSE_5,
	SIMPLE_INTERIOR_WAREHOUSE_6,
	SIMPLE_INTERIOR_WAREHOUSE_7,
	SIMPLE_INTERIOR_WAREHOUSE_8,
	SIMPLE_INTERIOR_WAREHOUSE_9,
	SIMPLE_INTERIOR_WAREHOUSE_10,
	SIMPLE_INTERIOR_WAREHOUSE_11,
	SIMPLE_INTERIOR_WAREHOUSE_12,
	SIMPLE_INTERIOR_WAREHOUSE_13,
	SIMPLE_INTERIOR_WAREHOUSE_14,
	SIMPLE_INTERIOR_WAREHOUSE_15,
	SIMPLE_INTERIOR_WAREHOUSE_16,
	SIMPLE_INTERIOR_WAREHOUSE_17,
	SIMPLE_INTERIOR_WAREHOUSE_18,
	SIMPLE_INTERIOR_WAREHOUSE_19,
	SIMPLE_INTERIOR_WAREHOUSE_20,
	SIMPLE_INTERIOR_WAREHOUSE_21,
	SIMPLE_INTERIOR_WAREHOUSE_22,
	SIMPLE_INTERIOR_FACTORY_METH_1,
	SIMPLE_INTERIOR_FACTORY_WEED_1,
	SIMPLE_INTERIOR_FACTORY_CRACK_1,
	SIMPLE_INTERIOR_FACTORY_MONEY_1,
	SIMPLE_INTERIOR_FACTORY_DOCUMENTS_1,
	SIMPLE_INTERIOR_FACTORY_METH_2,
	SIMPLE_INTERIOR_FACTORY_WEED_2,
	SIMPLE_INTERIOR_FACTORY_CRACK_2,
	SIMPLE_INTERIOR_FACTORY_MONEY_2,
	SIMPLE_INTERIOR_FACTORY_DOCUMENTS_2,
	SIMPLE_INTERIOR_FACTORY_METH_3,
	SIMPLE_INTERIOR_FACTORY_WEED_3,
	SIMPLE_INTERIOR_FACTORY_CRACK_3,
	SIMPLE_INTERIOR_FACTORY_MONEY_3,
	SIMPLE_INTERIOR_FACTORY_DOCUMENTS_3,
	SIMPLE_INTERIOR_FACTORY_METH_4,
	SIMPLE_INTERIOR_FACTORY_WEED_4,
	SIMPLE_INTERIOR_FACTORY_CRACK_4,
	SIMPLE_INTERIOR_FACTORY_MONEY_4,
	SIMPLE_INTERIOR_FACTORY_DOCUMENTS_4,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_POLICE_STATION,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_MC_CLUBHOUSE,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_BANK_ROCKFORD,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_BANK_PILLBOX,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_BANK_ALTA,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_BANK_BURTON,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_BANK_PALETO,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_BANK_GRAND_SENORA,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_BANK_CHUMASH,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_ROCKCLUB,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_CHICKEN_FACTORY,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_CHICKEN_FACTORY_PART_2,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_CHICKEN_FACTORY_PART_3,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_CHICKEN_FACTORY_PART_4,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_FARMHOUSE,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_HEIST_YACHT,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_RECYCLING_PLANT,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_BIOLAB,
	SIMPLE_INTERIOR_IE_WAREHOUSE_1,
	SIMPLE_INTERIOR_IE_WAREHOUSE_2,
	SIMPLE_INTERIOR_IE_WAREHOUSE_3,
	SIMPLE_INTERIOR_IE_WAREHOUSE_4,
	SIMPLE_INTERIOR_IE_WAREHOUSE_5,
	SIMPLE_INTERIOR_IE_WAREHOUSE_6,
	SIMPLE_INTERIOR_IE_WAREHOUSE_7,
	SIMPLE_INTERIOR_IE_WAREHOUSE_8,
	SIMPLE_INTERIOR_IE_WAREHOUSE_9,
	SIMPLE_INTERIOR_IE_WAREHOUSE_10,
	SIMPLE_INTERIOR_BUNKER_1,
	SIMPLE_INTERIOR_BUNKER_2,
	SIMPLE_INTERIOR_BUNKER_3,
	SIMPLE_INTERIOR_BUNKER_4,
	SIMPLE_INTERIOR_BUNKER_5,
	SIMPLE_INTERIOR_BUNKER_6,
	SIMPLE_INTERIOR_BUNKER_7,
	SIMPLE_INTERIOR_BUNKER_9,
	SIMPLE_INTERIOR_BUNKER_10,
	SIMPLE_INTERIOR_BUNKER_11,
	SIMPLE_INTERIOR_BUNKER_12,
	SIMPLE_INTERIOR_ARMORY_TRUCK_1,
	SIMPLE_INTERIOR_CREATOR_TRAILER_1,
	SIMPLE_INTERIOR_HANGAR_1,
	SIMPLE_INTERIOR_HANGAR_2,
	SIMPLE_INTERIOR_HANGAR_3,
	SIMPLE_INTERIOR_HANGAR_4,
	SIMPLE_INTERIOR_HANGAR_5,
	SIMPLE_INTERIOR_ARMORY_AIRCRAFT_1,
	SIMPLE_INTERIOR_DEFUNCT_BASE_1,
	SIMPLE_INTERIOR_DEFUNCT_BASE_2,
	SIMPLE_INTERIOR_DEFUNCT_BASE_3,
	SIMPLE_INTERIOR_DEFUNCT_BASE_4,
	SIMPLE_INTERIOR_DEFUNCT_BASE_6,
	SIMPLE_INTERIOR_DEFUNCT_BASE_7,
	SIMPLE_INTERIOR_DEFUNCT_BASE_8,
	SIMPLE_INTERIOR_DEFUNCT_BASE_9,
	SIMPLE_INTERIOR_DEFUNCT_BASE_10,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_MEDIUM_GARAGE,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_LOWEND_STUDIO,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_MIDEND_APARTMENT,
	SIMPLE_INTERIOR_CREATOR_AIRCRAFT_1,
	SIMPLE_INTERIOR_HUB_LA_MESA,
	SIMPLE_INTERIOR_HUB_MISSION_ROW,
	SIMPLE_INTERIOR_HUB_STRAWBERRY_WAREHOUSE,
	SIMPLE_INTERIOR_HUB_WEST_VINEWOOD,
	SIMPLE_INTERIOR_HUB_CYPRESS_FLATS,
	SIMPLE_INTERIOR_HUB_LSIA_WAREHOUSE,
	SIMPLE_INTERIOR_HUB_ELYSIAN_ISLAND,
	SIMPLE_INTERIOR_HUB_DOWNTOWN_VINEWOOD,
	SIMPLE_INTERIOR_HUB_DEL_PERRO_BUILDING,
	SIMPLE_INTERIOR_HUB_VESPUCCI_CANALS,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_SHERIFF,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_SHERIFF2,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_UNION_DEPOSITORY_CARPARK,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_SIMEON_SHOWROOM,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_ABATTOIR,
	SIMPLE_INTERIOR_HACKER_TRUCK,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_JEWEL_STORE,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_LIFE_INVADER,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_DJ_YACHT,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_MELANOMA_GARAGE,
	SIMPLE_INTERIOR_ARENA_GARAGE_1,
	SIMPLE_INTERIOR_CASINO,
	SIMPLE_INTERIOR_CASINO_APT,
	SIMPLE_INTERIOR_CASINO_VAL_GARAGE,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_HAYES_AUTOS,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_METH_LAB,
	SIMPLE_INTERIOR_ARCADE_PALETO_BAY,
	SIMPLE_INTERIOR_ARCADE_GRAPESEED,
	SIMPLE_INTERIOR_ARCADE_DAVIS,
	SIMPLE_INTERIOR_ARCADE_WEST_VINEWOOD,
	SIMPLE_INTERIOR_ARCADE_ROCKFORD_HILLS,
	SIMPLE_INTERIOR_ARCADE_LA_MESA,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_FIB_BUILDING,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_BIOLAB_AND_TUNNEL,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_FOUNDRY,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_MAX_RENDA,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_AIRCRAFT_CARRIER,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_AIRCRAFT_CARRIER_PART_2,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_AIRCRAFT_CARRIER_PART_3,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_AIRCRAFT_CARRIER_PART_4,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_AIRCRAFT_CARRIER_PART_5,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_AIRCRAFT_CARRIER_PART_6,
	SIMPLE_INTERIOR_RESTRICTED_INTERIOR_OMEGA,
	SIMPLE_INTERIOR_SOLOMONS_OFFICE,
	SIMPLE_INTERIOR_CASINO_NIGHTCLUB,
	SIMPLE_INTERIOR_SUBMARINE,
	SIMPLE_INTERIOR_MUSIC_STUDIO,
	SIMPLE_INTERIOR_AUTO_SHOP_LA_MESA,
	SIMPLE_INTERIOR_AUTO_SHOP_STRAWBERRY,
	SIMPLE_INTERIOR_AUTO_SHOP_BURTON,
	SIMPLE_INTERIOR_AUTO_SHOP_RANCHO,
	SIMPLE_INTERIOR_AUTO_SHOP_MISSION_ROW,
	SIMPLE_INTERIOR_CAR_MEET,
	SIMPLE_INTERIOR_FIXER_HQ_HAWICK,
	SIMPLE_INTERIOR_FIXER_HQ_ROCKFORD,
	SIMPLE_INTERIOR_FIXER_HQ_SEOUL,
	SIMPLE_INTERIOR_FIXER_HQ_VESPUCCI,
	SIMPLE_INTERIOR_ACID_LAB,
	SIMPLE_INTERIOR_JUGGALO_HIDEOUT,
	SIMPLE_INTERIOR_MULTISTOREY_GARAGE,
	SIMPLE_INTERIOR_SALVAGE_YARD_LA_PUERTA,
	SIMPLE_INTERIOR_SALVAGE_YARD_MURIETTA_HEIGHTS,
	SIMPLE_INTERIOR_SALVAGE_YARD_PALETO_BAY,
	SIMPLE_INTERIOR_SALVAGE_YARD_SANDY_SHORES,
	SIMPLE_INTERIOR_SALVAGE_YARD_STRAWBERRY,
	SIMPLE_INTERIOR_BAIL_OFFICE_DAVIS,
	SIMPLE_INTERIOR_BAIL_OFFICE_DEL_PERRO,
	SIMPLE_INTERIOR_BAIL_OFFICE_MISSION_ROW,
	SIMPLE_INTERIOR_BAIL_OFFICE_PALETO_BAY,
	SIMPLE_INTERIOR_BAIL_OFFICE_WEST_VINEWOOD,
	SIMPLE_INTERIOR_HACKER_DEN,
	SIMPLE_INTERIOR_FIELD_HANGAR,
	SIMPLE_INTERIOR_SMALL_BUSINESS_CAR_WASH,
	SIMPLE_INTERIOR_SMALL_BUSINESS_WEED_SHOP,
	SIMPLE_INTERIOR_SMALL_BUSINESS_HELI_TOURS,
	SIMPLE_INTERIOR_MAX
};

struct JOB_STATS
{
	SCR_INT Wins;
	SCR_INT Losses;
	SCR_INT Kills;
	SCR_INT Deaths;
	SCR_INT PAD_0004; // unused
};

struct JOB_BET
{
	SCR_INT PAD_0000; // TODO
	SCR_INT Amount;
};

struct MISSION_BETS
{
	SCR_INT Identifier; // a random integer between 100 and 10000000
	JOB_STATS Stats;
	SCR_ARRAY<JOB_BET, 32> PlacedBets;
	SCR_BOOL CancelBetting;
};
static_assert(sizeof(MISSION_BETS) == 72 * 8);

struct PLAYER_BLIP
{
	SCR_INT PAD_0000;
	SCR_INT NumPassengersInVehicle;
	SCR_BITSET<eBlipFlags> BlipFlags;
	alignas(8) eBlipType PlayerVehicleBlipType; // can be used to spoof your blip as a tank, oppressor etc
	SCR_INT IdleDurationUntilBlipIsVisible;
	SCR_INT BlipVisibleDuration;
	SCR_INT MissionInteriorIndex; // can be used to spoof blip position
	SCR_VEC3 MissionInteriorBlipLocation;
	SCR_FLOAT MissionInteriorBlipRotation;
	SCR_BOOL UnknownOverride; // can also be used to spoof position
	SCR_VEC3 UnknownOverridePosition;
};
static_assert(sizeof(PLAYER_BLIP) == 15 * 8);

struct YACHT_APPEARANCE
{
	SCR_INT PAD_0000; // TODO
	SCR_INT PAD_0001;
	SCR_INT PAD_0002;
	SCR_INT PAD_0003;
	SCR_INT PAD_0004;
	TEXT_LABEL_63 Name;
	SCR_HASH NameHash;
};
static_assert(sizeof(YACHT_APPEARANCE) == 22 * 8);

struct YACHT_DATA
{
	SCR_BOOL HasYacht;
	SCR_VEC3 Position;
	SCR_INT TravelStage;
	SCR_BOOL TravelInProgress;
	SCR_ARRAY<uint64_t, 7> VehicleNetIds; // the heli and the boats that spawn near the yacht
	SCR_INT YachtIndexPlayerIsIn;         // owned or unowned
	SCR_INT UnkYachtIndex;                // TODO
	SCR_INT YachtIndexPlayerIsInCouldBeDriving;
	SCR_ARRAY<uint64_t, 2> NearbyYachts;
	SCR_INT ClosestYachtIndex;
	SCR_INT TurbulenceState; // controls random camera shakes when on a yacht
	SCR_INT DefenseSetting;
	YACHT_APPEARANCE Appearance;
	SCR_BOOL RemoveClothingWhileInHotTub;
	SCR_HASH MissionYachtOwnerHandleHash; // always -1 or NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(PLAYER::PLAYER_ID())
	SCR_BOOL SpawnAccess;                 // "spawn access"?
	SCR_INT MissionYachtIndex;
};
static_assert(sizeof(YACHT_DATA) == 49 * 8);

struct SMPL_INTERIOR_DATA
{
	SCR_INT Flags; // TODO!!!
	SCR_INT Flags2;
	SCR_INT Flags3;
	SCR_INT Flags4;
	SCR_INT Flags5;
	SCR_INT Flags6;
	SCR_INT Flags7;
	SCR_INT Flags8; // added b3258
	alignas(8) eSimpleInteriorIndex Index;
	SCR_INT InstanceId;
	SCR_INT AllowedGoons;
	PLAYER_INDEX Owner;
	PLAYER_INDEX VehicleOwner;
	SCR_VEC3 SpecialVehicleSpawnPosition;
	SCR_FLOAT SpecialVehicleSpawnHeading;
	SCR_INT EnteringSimpleInteriorIndex;
	SCR_INT SpecialVehicleSimpleInteriorIndex; // MOC, Terrorbyte etc
	alignas(8) eSimpleInteriorIndex UnkSimpleInteriorIndex;
	alignas(8) eSimpleInteriorIndex UnkSimpleInteriorIndex2;
	SCR_VEC3 AvengerPosition;
	SCR_VEC3 AvengerPosition2; // not sure how this is different from the field above
	SCR_FLOAT AvengerHeading;
	SCR_INT MissionSpawnSimpleInteriorIndex;
	SCR_INT InteriorSubtype; // nightclub vs nightclub garage etc
};
static_assert(sizeof(SMPL_INTERIOR_DATA) == 30 * 8);

// yes there's a struct for leaving your clubhouse
struct LEAVE_CLUBHOUSE
{
	SCR_BOOL Active;
	SCR_BOOL Active2;
	SCR_INT Identifier;
	SCR_INT ExitLocation;
	SCR_ARRAY<uint64_t, 32> ParticipantHashes;
};
static_assert(sizeof(LEAVE_CLUBHOUSE) == 37 * 8);

struct ARCADE_GAME
{
	SCR_BITSET<eArcadeGameBitset> Bits;
	SCR_INT CabinetIndex;
	SCR_INT PAD_0002;    // The only valid value is 0 so idk
	SCR_INT CabinetGame; // TODO
	SCR_INT GameStage;
};
static_assert(sizeof(ARCADE_GAME) == 5 * 8);

struct GlobalPlayerBDEntry
{
	alignas(8) eFreemodeState FreemodeState;
	MP_SCRIPT_DATA CurrentScript;
	uint64_t PAD_0022[11]; // unused
	SCR_INT PlayersVisible;
	SCR_INT PlayersTracked;
	SCR_BITSET<eAnimationBitset> AnimationBitset;
	SCR_INT NumSuccessfulHoldups; // resets every 12 minutes
	SCR_INT PAD_0037;
	NETWORK_INDEX PersonalVehicleNetId;
	NETWORK_INDEX UnkVehicleNetId;
	NETWORK_INDEX UnkVehicleNetId2;
	SCR_ARRAY<uint64_t, 2> UnkVehicleNetIds;
	NETWORK_INDEX DeliveryMechanicNetId;
	NETWORK_INDEX DeliveryMechanicNetId2;
	SCR_INT SpawningVehicleLiveryIndex;
	SCR_INT SpawningVehiclePrimaryColor;
	SCR_INT SpawningVehicleSecondaryColor;
	NETWORK_INDEX AvengerNetId;
	NETWORK_INDEX DeliveryMechanicNetId3; // wtf is this?
	NETWORK_INDEX TerrorbyteNetId;        // or is it the MOC?
	NETWORK_INDEX SubmarineNetId;
	NETWORK_INDEX DinghyNetId;
	NETWORK_INDEX DeliveryMechanicNetId4; // another one...
	NETWORK_INDEX AcidLabNetId;
	NETWORK_INDEX DeliveryBikeNetId;
	NETWORK_INDEX BountyTransporterNetId; // added b3258
	NETWORK_INDEX FieldDusterNetId;       // added b3407
	NETWORK_INDEX MansionHeliNetId;       // added b3407
	SCR_BOOL PAD_0057;                    // (@59 as of b3407)
	uint64_t PAD_0058[15];                // confirmed these are not used by PC scripts
	PLAYER_BLIP PlayerBlip;
	SCR_BOOL NeedToPopulateSessionStartTime; // the session start time is unused
	uint64_t PAD_0089[33];                   // TODO (@91 as of b3407)
	                                         // 32 -> 33 (new field) b3407
	alignas(8) eMissionType MissionType;
	SCR_BOOL SpawningVehicle;
	uint64_t PAD_0123[3]; // confirmed these are not used by PC scripts
	MISSION_BETS MissionBets;
	SCR_BOOL RadarBlipVisibliltyMechanicEnabled;
	SCR_BITSET<ePlayerStateFlags> PlayerStateFlags;
	SCR_BITSET<ePlayerStateFlags2> PlayerStateFlags2; // TODO
	SCR_INT PlayerStateFlags3;                        // TODO
	SCR_INT CarMeetModShopSlotPreTakeover;
	PLAYER_INDEX CurrentCarMeetSlotOwnerIndex; // can be player or player's CEO/MC leader
	SCR_INT CarMeetModShopSlotPostTakeover;
	SCR_HASH CarMeetModdingVehicleModel;
	PLAYER_INDEX CarMeetCurrentlySeatedVehicleOwner;
	SCR_VEC3 PlayerPosition; // updates every two seconds, used by spectate
	SCR_BOOL OffRadarActive;
	SCR_BOOL PassengerOfVehicleWithOffRadarDriver;
	SCR_BOOL GoonOfBossWithOffRadar;
	SCR_BOOL RevealPlayersActive;
	PLAYER_INDEX RemoteWantedLevelPlayer; // cut content but still works
	SCR_INT RemoteWantedLevelAmount;
	PLAYER_INDEX RemoteWantedLevelRemovePlayer; // doesn't work at all
	SCR_INT UnkTeleportStage;
	SCR_BITSET<eActivityFlags> ActivityFlags;
	SCR_INT NumReservedMissionPeds;
	SCR_INT NumReservedMissionVehicles;
	SCR_INT NumReservedMissionObjects;
	SCR_INT TransitionSessionState;       // TODO reverse enum
	SCR_VEC3 TransitionReturningPosition; // TODO
	TEXT_LABEL_23 TransitionContentIDToLaunch;
	SCR_INT RespawnState;
	SCR_INT LastRespawnTime;
	SCR_BOOL CollisionLoaded;
	SCR_BOOL CommitingSuicide;
	SCR_BOOL RespawningInVehicleAsDriver;
	SCR_BOOL RespawningInVehicle;
	SCR_BOOL PAD_0238; // this value is set but not read at all by any PC scripts
	SCR_BITSET<eGamerTagFlags> GamerTagFlags;
	SCR_BOOL IsMale;
	SCR_INT ArmwrestlingLocationFlags;
	SCR_INT PAD_0242; // TODO
	SCR_BOOL GamerTagShowArrow;
	SCR_BOOL CarWashInProgress;
	INTERIOR_INDEX CurrentInteriorIndex;
	SCR_INT CurrentShopIndex;  // things like clothing and tattoo stores
	SCR_INT CurrentStoreIndex; // the stores in the map which can be held up
	SCR_BOOL ShopActive;       // any shop
	SCR_BOOL InTaxi;
	SCR_INT Haircut; // @250 as of 1.67
	SCR_INT PrimaryHairColor;
	SCR_INT SecondaryHairColor;
	SCR_INT FriendlyPlayers; // bitset of player team relgroups that obtain a Respect relationship with player
	SCR_BOOL IsInvisible;
	SCR_BOOL InImpromptuDeathmatch;
	SCR_VEC3 ImpromptuDeatmatchStartPosition;
	SCR_INT PAD_0569; // not read by scripts, impromptu DM related
	SCR_INT MissionLoseAnimType;
	SCR_INT MissionWinAnimType; // verify
	SCR_INT MissionCrewAnimType;
	SCR_INT RallyRaceAnim;
	SCR_BOOL IsRallyRace;
	SCR_BOOL JustGetsPulledOutWhenElectrocuted;
	SCR_INT HeistCutSelectionStage; // the only valid values seem to be 6 and 7
	SCR_BOOL IsBadsport;
	SCR_FLOAT MentalState;
	SCR_BOOL IsRockstarDev; // dev dlc check and not the CNetGamePlayer flag so can be used to detect YimMenu
	SCR_BOOL ScreenFadedOut;
	SCR_BOOL TimeTrialActive;
	YACHT_DATA YachtData;
	SMPL_INTERIOR_DATA SimpleInteriorData;
	SCR_BOOL PAD_0350; // TODO
	SCR_INT PAD_0351;  // unused vehicle/interior stuff
	SCR_INT BlipShownBitset;
	LEAVE_CLUBHOUSE LeaveClubhouse;   // @353 as of 1.67
	SCR_INT Friends;                  // bitset of players that are friends
	SCR_VEC3 InteriorVehiclePosition; // for terrorbyte and MOC, used to fake player blip position on map
	SCR_FLOAT InteriorVehicleHeading;
	SCR_VEC3 AcidLabPosition; // not read by the scripts
	SCR_FLOAT AcidLabHeading;
	SCR_INT VehicleTurretsActive;                        // bitset
	SCR_ARRAY<SCR_VEC3, 4> VehicleTurretsCameraPosition; // 3->4 in 1.67
	SCR_INT PAD_0416;                                    // TODO
	SCR_BOOL DozerDetected;                              // very shady stuff, anticheat?	       @414 as of 1.67
	SCR_ARRAY<uint64_t, 6> MissionTurretParticipants;
	SCR_INT PAD_0425; // some seat index
	SCR_INT MissionTurretSlot;
	SCR_BITSET<eOrbitalBitset> OrbitalBitset;
	SCR_BOOL FacilityIntroCutsceneInProgress;
	SCR_BOOL FacilityIntroCutsceneStarted; // like above but is enabled 2 stages earlier
	SCR_BOOL PAD_0430;                     // todo
	SCR_BOOL BeingSolicitedByProstitute;   // why tf is this used by the orbital cannon?
	SCR_VEC3 DronePosition;                // updates every second
	SCR_FLOAT DroneHeading;                // @432 as of 1.67
	SCR_INT OrbitalBitset2;                // ugh
	SCR_INT CurrentlyUsingArenaTrapIndex;
	SCR_INT CurrentlyUsingArenaTrapActivatedTime;
	ARCADE_GAME ArcadeGame;
	SCR_INT DancePartner;
	SCR_INT CayoPericoFlags;
	SCR_INT BeachPartyFlags;
	uint64_t PAD_0477[10]; // I don't think we'll ever be able to figure out what this does
	SCR_INT ThreeCardPokerStyle;
	SCR_INT BlackjackStyle;
	SCR_BITSET<eOutOfSightFlags> OutOfSightFlags;
	SCR_VEC3 OutOfSightArea;
	SCR_INT AmmunationWeaponPartFlags;
	PLAYER_INDEX LastKilledBy; // @461 as of 1.67
	SCR_BOOL CanSpawnGunVan;
};

static_assert(sizeof(GlobalPlayerBDEntry) == 468 * 8);

struct GlobalPlayerBD
{
	SCR_ARRAY<GlobalPlayerBDEntry, 32> Entries;

	static GlobalPlayerBD* Get();
};
static_assert(sizeof(GlobalPlayerBD) == 14977 * 8);