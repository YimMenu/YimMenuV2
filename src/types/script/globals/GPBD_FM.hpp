#pragma once
#include "../MPScriptData.hpp"
#include "../Timer.hpp"
#include "../types.hpp"

enum class eMissionDataFlags
{
	kMissionLaunched = 0,
	kJobDownloaded = 2,
	kStartingJob = 3,
	kRequestingScript = 4,
	kLaunchedScript = 6,       // should be set if kMissionLaunched is set
	kAutoStartOnProximity = 7, // used by gang attack
	kNJVSQuickMatch = 8,
	kVoteLiked = 10,
	kVoteDisliked = 11,
	kNoVote = 25
}; // TODO

enum class eTutorialBitset
{
	kInTutorialRace = 0,
	kTutorialRaceActive = 2,
	kShowCredits = 4,
	kNeedFreeVehicle = 6
};

enum class eGangCallServices
{
	kMugger = 0,
	kMercenary = 1
};

enum class eVehicleSelectionState
{
	NONE,
	SELECTING,
	SELECTED
};

enum class eStatState
{
	NONE,
	LETHARGIC,
	OUT_OF_SHAPE,
	HEALTHY,
	ATHLETE,
	TRI_ATHLETE,
	UNTRAINED,
	SPRAY_AND_PRAY,
	POLICE_TRAINING,
	MILITARY_TRAINING,
	DEAD_EYE,
	FRAGILE,
	WEAK,
	AVERAGE,
	TOUGH,
	BODYBUILDER,
	CLUMSY,
	LOUD,
	SNEAKY,
	HUNTER,
	NINJA,
	DANGEROUS,
	RC_PILOT,
	COMMERCIAL_PILOT,
	FIGHTER_PILOT,
	ACE,
	UNLICENSED,
	SUNDAY_DRIVER,
	COMMUTER,
	STREET_RACER,
	PRO_RACER,
	NORMAL,
	UNSTABLE,
	DERANGED,
	MANIAC,
	PSYCHOPATH,
	DRUNK
};

enum class ePropertyInteriorFlags
{
	kOwnerOfInterior = 0,
	kVisitorOfInterior = 1, // mutually exclusive with above flag
	kConcealWhenDead = 12,
	kRenovatingProperty = 19,
	kPreviewingDecor = 20,
	kRenovatingClubhouse = 21,
	kUsingYachtRmBath1 = 22,
	kUsingYachtRmBath3 = 23,
	kUsingYachtRmWeeBathroom = 25,
	kGunLockerOpen = 27,
	kOfficeSafeOpen = 28,
	kOfficeAssistantMale = 29
};

enum class eInteriorStyleFlags
{
	kGunLockerShowPumpShotgun = 0,
	kGunLockerShowMicroSMG = 1,
	kGunLockerShowC4 = 2, // proximity or sticky
	kGunLockerShowGrenade = 3,
	kGunLockerShowCombatMG = 4,
	kGunLockerShowMarksmanRifle = 5,
	kPurchasedSnacks = 6,
	kPurchasedInteriorRenovations = 7,
	kForceOfficeAssistantSpawn = 8,
	kAssistantAnimationOver = 9,
	kChangeInteriorDecorOfficeHelpShown = 11,
	kChangeInteriorDecorApartmentHelpShown = 12,
	kOwnsOfficeBedroom = 13,
	kOwnsClubhouseBikeShop = 16,
	kOwnsOfficeGunLocker = 17,
	KOwnsClubhouseWalls = 18, // ???
	kOwnsClubhouseFurnishings = 19,
	kOwnsClubhouseDecors = 20
};

enum class eBusinessHubProductIndex
{
	CARGO,
	WEAPONS,
	COCAINE,
	METH,
	WEED,
	FORGED_DOCUMENTS,
	COUNTERFEIT_CASH
};

struct PLAYLIST_DATA
{
	PLAYER_INDEX Host;
	SCR_INT Flags;
	SCR_BOOL PAD_0002;
	SCR_INT CurrentMission;
	SCR_INT TotalMissions;
	PLAYER_INDEX PAD_0006;
};
static_assert(sizeof(PLAYLIST_DATA) == 6 * 8);

// local copy can be found at Global_2680247
struct JOB_SETTINGS
{
	SCR_ARRAY<uint64_t, 31> Settings; // indices vary based on job type. take a look at func_8988 in fmmc_launcher if you wish to change them
	SCR_INT NumPlayers;               // verify
	SCR_INT PAD_0033;
	SCR_INT SpawnSimpleInteriorIndex;
	SCR_INT PAD_0035; // unused
	SCR_BOOL MatchmakingOpen;
	SCR_INT ContentHash;
};
static_assert(sizeof(JOB_SETTINGS) == 38 * 8);

struct VEHICLE_SELECTION
{
	SCR_BOOL Active;
	SCR_BOOL Active2;
	PLAYER_INDEX PAD_0002; // set to host by fmmc but not read at all
	SCR_HASH VehicleModel;
	SCR_INT CreatorIndex;
	alignas(8) eVehicleSelectionState State;
	SCR_INT PrimaryColor;
	Color3 CustomPrimaryColor;
	Color3 CustomSecondaryColor;
	PLAYER_INDEX Partner; // for rally races?
	GAMER_HANDLE PartnerHandle;
	SCR_INT PreferredRole; // target assault races
	SCR_INT PAD_0028;      // TODO
	SCR_INT ControlType;   // 1 = kb&m 2 = controller
	SCR_INT BettingFlags;
	SCR_INT Team;
	SCR_INT Flags;
	SCR_INT JoinedMembers; // bitset of joined transition members set by the host
	SCR_INT AdversaryOutfitIndex;
	alignas(8) eStatState StatState; // see func_9142 in fmmc_launcher, shown to other players
	SCR_INT CashWager;               // shown to other players...
	uint64_t PAD_0037[2];            // TODO
	SCR_INT PAD_0039;                // TODO random integer between 1 and 11
};
static_assert(sizeof(VEHICLE_SELECTION) == 40 * 8);

struct STRIKE_TEAM
{
	PLAYER_INDEX Target;
	TIMER Cooldown;
	SCR_BOOL CancelStrikeTeam; // read but not written to
	SCR_INT Level;
};
static_assert(sizeof(STRIKE_TEAM) == 5 * 8);

struct PLAYER_STATS
{
	SCR_INT Team;
	SCR_INT RP;
	SCR_INT CrewRP;
	SCR_INT WalletBalance;
	SCR_INT HeistBonus;
	SCR_INT GlobalRP;
	SCR_INT Rank;
	TEXT_LABEL_31 CrewTitle;
	SCR_INT TotalRacesWon;
	SCR_INT TotalRacesLost;
	SCR_INT TimesFinishRaceAsTop3;
	SCR_INT TimesFinishRaceLast;
	SCR_INT TimesRaceBestLap;
	SCR_INT TotalDeathmatchesWon;
	SCR_INT TotalDeathmatchesLost;
	SCR_INT TotalTeamDeathmatchesWon;
	SCR_INT TotalTeamDeathmatchesLost;
	SCR_INT Shots;
	SCR_INT Hits;
	SCR_FLOAT KdRatio;
	SCR_FLOAT DropoutRate;
	SCR_INT KillsOnPlayers;
	SCR_INT DeathsByPlayers;
	SCR_INT TotalFinishDeathmatchAsTop3;
	SCR_INT TotalFinishDeathmatchLast;
	SCR_INT DartsTotalWins;
	SCR_INT DartsTotalMatches;
	SCR_INT ArmwrestlingTotalWins;
	SCR_INT ArmwrestlingTotalMatches;
	SCR_INT TennisMatchesWon;
	SCR_INT TennisMatchesLost;
	SCR_INT BaseJumpWins;
	SCR_INT BaseJumpLosses;
	SCR_INT GolfWins;
	SCR_INT GolfLosses;
	SCR_INT ShootingRangeWins;
	SCR_INT ShootingRangeLosses;
	SCR_INT ShootingAbility;
	SCR_INT MissionWins;
	SCR_INT TotalMissionsPlayed;
	SCR_INT SurvivalWins;
	SCR_INT TotalSurvivalsPlayed;
	SCR_INT PAD_0049; // TODO
	SCR_INT MissionsCreated;
	SCR_INT CommunicationRestrictions;
	SCR_BOOL CanSpectate;
	SCR_INT MostFavoriteStation;
	SCR_INT ProstitutesFrequented;
	SCR_INT LapDancesBought;
	SCR_INT Money;
	SCR_FLOAT WeaponAccuracy;
	SCR_HASH FavoriteVehicle;
	SCR_HASH FavoriteWeapon;
};
static_assert(sizeof(PLAYER_STATS) == 60 * 8);

struct EXEC_WAREHOUSE_INFO
{
	SCR_INT Index;
	SCR_INT Stock;
	SCR_INT PAD_0002; // unused
};
static_assert(sizeof(EXEC_WAREHOUSE_INFO) == 3 * 8);

struct IE_WAREHOUSE_DATA
{
	SCR_INT Index;
	SCR_INT NumVehicles;
	SCR_ARRAY<uint64_t, 40> Vehicles;
	SCR_INT PAD_0043; // set to zero and not read
	SCR_INT OwnedWarehouseVariation;
};
static_assert(sizeof(IE_WAREHOUSE_DATA) == 45 * 8);

struct FACTORY_INFO
{
	SCR_INT Index;
	SCR_INT TotalProduct;
	SCR_INT TotalSupplies;
	SCR_INT TotalSupplies2; // TODO: what's the difference?
	uint64_t PAD_0004;
	SCR_INT EquipmentUpgrades;
	SCR_BOOL Running;
	SCR_BOOL SetupDone;
	SCR_BOOL PAD_0008;
	SCR_INT Research; // valid only for factory index 5 (bunker)
	SCR_INT StaffState;
	SCR_INT ProductValue;        // untested
	SCR_INT StaffAssignmentType; // valid only for factory index 5 (bunker) 0 = manufacturing, 1 = research, 2 = both
};
static_assert(sizeof(FACTORY_INFO) == 13 * 8);

struct HANGAR_DATA
{
	SCR_INT Index;
	SCR_INT AppearanceBitset;
	SCR_INT PAD_0002; // unused
	SCR_INT TotalContraband;
	SCR_INT PAD_0004; // unused, a function tries to set it to something but is never called with the right parameters. it isn't read either
	SCR_BOOL SetupDone;
};
static_assert(sizeof(HANGAR_DATA) == 6 * 8);

// facility
struct DEFUNCT_BASE_DATA
{
	SCR_INT Index;
	SCR_INT AppearanceBitset;
	SCR_INT AppearanceBitset2;
	SCR_INT ObtainedAwards;
	SCR_INT PAD_0004; // unused, a function tries to set it to something but is never called with the right parameters. it isn't read either
	SCR_INT PAD_0005;
	SCR_INT TotalContraband; // wat
};
static_assert(sizeof(DEFUNCT_BASE_DATA) == 7 * 8);

// nightclub
struct BUSINESS_HUB_DATA
{
	SCR_INT Index;
	SCR_INT TotalContraband;     // not read by the scripts
	SCR_INT ProducingBusinesses; // bitset
	SCR_INT ProducingFactories;  // bitset
	SCR_INT Upgrades;
	SCR_INT PAD_0005;
	SCR_INT PAD_0006;                     // not read by the scripts
	SCR_INT SetupBitset;                  // includes owned DJs
	SCR_ARRAY<uint64_t, 8> ProductStocks; // see eBusinessHubProductIndex
	SCR_ARRAY<uint64_t, 16> PAD_0017;     // have no clue what this is
	SCR_ARRAY<uint64_t, 8> TotalSoldProduct;
};
static_assert(sizeof(BUSINESS_HUB_DATA) == 43 * 8);

// also the nightclub? strange
struct NIGHTCLUB_DATA
{
	SCR_INT Index; // same as BusinessHubData::Index
	SCR_INT AppearanceBitset;
	SCR_INT AppearanceBitset2;
	SCR_INT AccessSettings; // TODO: figure out how this works
	SCR_FLOAT Popularity;   // 0.0 to 1.0
	SCR_INT SafeCashValue;
	SCR_INT EntryCost; // can be set to any arbitrary value
	SCR_INT CroudVariation;
	SCR_INT DanceAwardProgress;  // "Gold Dancer trophy unlocked."
	SCR_INT DanceAward2Progress; // "Gold Battler trophy unlocked."
	TIMER DJMusicChangeTimer;
};
static_assert(sizeof(NIGHTCLUB_DATA) == 12 * 8);

struct ARENA_GARAGE_DATA
{
	SCR_INT Index; // always one for obvious reasons
	SCR_INT OwnedGarageFloorLevel;
	SCR_INT AppearanceBitset;
	SCR_INT AppearanceBitset2;
	SCR_INT InteriorTypeA;
	SCR_INT InteriorTypeB;
	SCR_INT SpectatingIndex;
	SCR_INT SpectatingType;
	SCR_INT PAD_0008; // unused
};
static_assert(sizeof(ARENA_GARAGE_DATA) == 9 * 8);

struct INSIDE_TRACK
{
	TEXT_LABEL_63 PlayerName;
	SCR_INT BetHorseID;
	SCR_INT BetChips;
};
static_assert(sizeof(INSIDE_TRACK) == 18 * 8);

// casino penthouse
struct CASINO_APARTMENT_DATA
{
	SCR_INT Index;    // always one for obvious reasons
	SCR_INT PAD_0001; // unused
	SCR_INT AppearanceBitset;
	SCR_INT AppearanceBitset2;
	uint64_t PAD_0005[2];
	INSIDE_TRACK InsideTrack;
};
static_assert(sizeof(CASINO_APARTMENT_DATA) == 24 * 8);

struct ARCADE_DATA
{
	SCR_INT Index;
	SCR_INT AppearanceBitset;
	SCR_INT AppearanceBitset2;
	SCR_INT AppearanceBitset3;
	SCR_INT UNK_0004;
	SCR_INT SafeCashValue;
};
static_assert(sizeof(ARCADE_DATA) == 6 * 8);

struct ARCADE_MACHINES
{
	SCR_INT OrderedMachinesBitset;
	SCR_INT ArrivedMachinesBitset;
};
static_assert(sizeof(ARCADE_MACHINES) == 2 * 8);

struct SUBMARINE_DATA
{
	SCR_INT AppearanceBitset;
	SCR_HASH Model; // not read by the scripts, always set to HASH("kosatka")
	SCR_INT Color;  // "PACKED_MP_INT_KOSATKA_COLOUR"
	SCR_INT Flag;   // "PACKED_MP_INT_KOSATKA_FLAG"
	SCR_INT LastGuidedMissileUseTime;
	SCR_INT PAD_0005; // unused
};
static_assert(sizeof(SUBMARINE_DATA) == 6 * 8);

struct AUTOSHOP_DATA
{
	SCR_INT Index;
	SCR_INT AccessSetting;
	SCR_INT AppearanceBitset;
	SCR_INT AppearanceBitset2;
	SCR_INT PAD_0004;
	SCR_ARRAY<uint64_t, 2> ModdingVehicles; // VEHICLE_INDEX, not NETWORK_INDEX
};
static_assert(sizeof(AUTOSHOP_DATA) == 8 * 8);

// LS car meet
struct CAR_CLUB_DATA
{
	SCR_INT Flags;
	SCR_INT Reputation;
	SCR_INT ReputationLevel;
	SCR_INT TestTrackAccess; // unused?
};
static_assert(sizeof(CAR_CLUB_DATA) == 4 * 8);

// agency
struct FIXER_HQ_DATA
{
	SCR_INT Index;
	SCR_INT AppearanceBitset;
	SCR_INT SafeCashValue;
};
static_assert(sizeof(FIXER_HQ_DATA) == 3 * 8);

// eclipse blvd garage
struct MULTI_STOREY_GARAGE_DATA
{
	SCR_INT Index; // always one for obvious reasons
	SCR_INT AppearanceBitset;
	SCR_INT AppearanceBitset2;
	SCR_ARRAY<uint64_t, 2> GarageTints;
};
static_assert(sizeof(MULTI_STOREY_GARAGE_DATA) == 6 * 8);

struct SALVAGE_YARD_DATA
{
	SCR_INT Index;
	SCR_INT PAD_0001;
	SCR_INT AppearanceBitset;
	SCR_INT TowTruckColor;
	SCR_INT TowTruckType; // TODO
	SCR_INT VehicleRobVehicleIndex;
	SCR_INT TotalEarnings;
};
static_assert(sizeof(SALVAGE_YARD_DATA) == 7 * 8);

struct BAIL_SHOP_DATA
{
	SCR_INT Index;
	SCR_INT StyleFlags;
	SCR_INT SafeCashValue;
	uint64_t PAD_0001[9]; // a field was removed in b3407
};
static_assert(sizeof(BAIL_SHOP_DATA) == 12 * 8);

struct HACKER_DEN_DATA
{
	SCR_INT Index; // always one for obvious reasons
	SCR_INT Flags;
	SCR_INT SafeCashValue;
};
static_assert(sizeof(HACKER_DEN_DATA) == 3 * 8);

struct FIELD_HANGAR_DATA
{
	SCR_INT Index;
	SCR_INT Flags;
};
static_assert(sizeof(FIELD_HANGAR_DATA) == 2 * 8);

#define NUM_PROPERTY_INTERIORS 36 // (30 -> 31) b3095 \
	                              // (31 -> 32) b3258 \
	                              // (32 -> 33) b3407 \
	                              // (33 -> 36) b3717

struct PROPERTY_DATA
{
	SCR_ARRAY<uint64_t, NUM_PROPERTY_INTERIORS> PropertyIds;
	SCR_BITSET<ePropertyInteriorFlags> Flags; // I really don't want to indent everything again
	SCR_INT RingingPlayers;                   // bitset of players requesting entry into property
	SCR_INT Index;                            // the value you pass to the send to apartment TSE
	SCR_INT Instance;
	SCR_INT ExteriorIndex;
	PLAYER_INDEX ExteriorOwner;
	SCR_ARRAY<uint64_t, 32> RingingPlayersState; // 0 = ringing, 1 = accepted, 2 = denied
	GAMER_HANDLE OwnerHandle;                    // can be used to bypass RID spoofing when player is inside interior
	SCR_ARRAY<uint64_t, NUM_PROPERTY_INTERIORS> EclipseTheme;
	SCR_INT ApartmentType; // normal vs stilt vs eclipse
	SCR_INT OwnerInstance; // same as Instance in most cases
	SCR_ARRAY<EXEC_WAREHOUSE_INFO, 5> ExecutiveWarehouseInfos;
	SCR_INT OfficeSafeMoneyMultiplier;
	SCR_BITSET<eInteriorStyleFlags> StyleFlags;
	SCR_INT PAD_0134; // unused
	SCR_INT AssistantGreetingChoice;
	SCR_INT AssistantDialogBitset;
	SCR_INT AssistantDialogBitset2;
	SCR_INT LifetimeCargoMissionsComplete; // used for trophy type
	SCR_INT CasinoChipsMultiplier;
	SCR_INT AssistantDialogBitset3;
	SCR_INT AssistantDialogBitset4;
	SCR_INT AssistantDialogBitset5;
	SCR_INT AssistantDialogBitset6; // do we REALLY need 6 bitsets for assistant dialog?
	IE_WAREHOUSE_DATA IEWarehouseData;
	SCR_INT Garage1DataBitset;
	SCR_INT Garage2DataBitset;
	SCR_INT Garage3DataBitset;
	SCR_INT ModshopDataBitset;
	SCR_ARRAY<FACTORY_INFO, 7> FactoryInfos;
	SCR_INT TotalBunkerResearch; // (@291 b889g9)
	SCR_INT CurrentBunkerResearchProgress;
	// SCR_INT BunkerDecorVariation; REMOVED b889g9
	SCR_INT MOCBitset;
	SCR_INT MOCColor;     // bitset for some reason
	uint64_t PAD_0290[2]; // unused
	SCR_INT GunShopFlags;
	HANGAR_DATA HangarData;
	SCR_INT PAD_0299;
	DEFUNCT_BASE_DATA DefunctBaseData;
	SCR_INT AvengerInteriorDecorFlags; // "PACKED_MP_INT_ARMORY_AIRCRAFT_INTERIOR_v0"
	uint64_t PAD_0308[2]; // one field removed here b889g9
	BUSINESS_HUB_DATA BusinessHubData;
	NIGHTCLUB_DATA NightclubData;
	SCR_INT PAD_0365;
	SCR_INT TerrorbyteDesign;
	SCR_INT PAD_0367;
	SCR_INT AcidLabRadio;
	SCR_INT TerrorbyteRadio;
	SCR_INT NanoDroneCooldown;
	PLAYER_INDEX HostOfInteriorScript;
	ARENA_GARAGE_DATA ArenaGarageData;
	SCR_INT ArcadeJukeboxStation; // for simple interior type 17
	SCR_INT JukeboxFavoritePlaylist;
	SCR_INT ClubhouseBarCashAmount;
	SCR_INT DefaultJukeboxStation;
	SCR_INT FreakshopJukeboxStation;
	SCR_INT PAD_0386;  // TODO
	SCR_HASH MOCModel; // used by the bunker script to detect exits with MOC
	SCR_INT PAD_0388;  // unused
	SCR_HASH TerrorbyteModel;
	SCR_ARRAY<uint64_t, 7> PAD_0390; // some property interior stuff
	uint64_t PAD_0398[4];
	SCR_INT OfficeGarageModdingVehicleSlot;
	SCR_INT CurrentOfficeGarageFloor;
	CASINO_APARTMENT_DATA CasinoApartmentData; // @405 as of 1.67
	ARCADE_DATA ArcadeData;
	ARCADE_MACHINES ArcadeMachines;
	SCR_ARRAY<uint64_t, 41> ArcadeMachineSlots;
	SCR_INT PAD_0478; // TODO
	SUBMARINE_DATA SubmarineData;
	AUTOSHOP_DATA AutoShopData;
	SALVAGE_YARD_DATA SalvageYardData;
	SCR_ARRAY<uint64_t, 2> AutoShopArcadeMachineSlots;
	CAR_CLUB_DATA CarClubData;
	FIXER_HQ_DATA FixerHQData;
	SCR_INT PAD_0503; // not read by the scripts
	SCR_INT PAD_0504;
	VEHICLE_INDEX CurrentlyModdingVehicleFixerHQ;
	MULTI_STOREY_GARAGE_DATA MultiStoreyGarageData; // @507 as of 1.67
	SCR_INT FreakshopBits;                          // 0: has weapon workshop, 1: radio enabled
	SCR_INT VinewoodGarageBits;                     // added b812g9, 0 seems to indicate a cutscene
	BAIL_SHOP_DATA BailShopData;
	HACKER_DEN_DATA HackerDenData;
	FIELD_HANGAR_DATA FieldHangarData;
};
static_assert(sizeof(PROPERTY_DATA) == 549 * 8);

struct BIKER_CONTRACTS
{
	SCR_ARRAY<uint64_t, 4> ActiveContractMissions;
	SCR_INT SelectedContractMission;
	SCR_BOOL Enabled;
};
static_assert(sizeof(BIKER_CONTRACTS) == 7 * 8);

// rewritten b811g9 to integrate GTA+ stuff
struct NIGHTCLUB_SALE
{
	SCR_INT BuyerIndex;                            // 0
	SCR_INT NumSoldItems;                          // 1
	SCR_INT SaleAmount;                            // 2
	SCR_INT SaleAmountWithMembershipModifiers;     // 3
	SCR_INT TotalSaleAmountWithMembershipModifers; // 4
	SCR_INT TotalSaleAmount;                       // 5
	SCR_INT UnkSaleAmount;                         // 6 some kind of partial sum over certain goods, never read
	SCR_INT BuyerIndex2;                           // 7 min(BuyerIndex, 3)
};
static_assert(sizeof(NIGHTCLUB_SALE) == 8 * 8);

struct ARENA_WAR_DATA
{
	SCR_INT PointsTier;
	SCR_INT SkillLevel;
	SCR_INT TrinketBitset; // MP_STAT_ARN_BS_TRINKET_SAVED
};
static_assert(sizeof(ARENA_WAR_DATA) == 3 * 8);

struct GPBD_FM_Entry
{
	SCR_INT CurrentActivity;
	SCR_INT MissionScriptInstance;
	SCR_INT PAD_0002; // TODO
	SCR_INT NumFreeSpectatorSlots;
	SCR_INT NumPlayersInTransition; // not really
	SCR_INT NJVSVoteState;          // voting screen shown after a mission ends
	SCR_INT NJVSVoteContentBitset;
	SCR_BOOL NJVSChoiceMade;
	SCR_INT NJVSLeaveState; // network error or quit
	SCR_INT JobPoints;      // can be spoofed to change the "JP" value in the player list
	PLAYER_INDEX NextHost;  // transfer transition host when joining next job
	PLAYLIST_DATA PlaylistData;
	TEXT_LABEL_63 JobName;
	SCR_ARRAY<uint64_t, 2> ActiveGunRange; // this should have really been an enum lol
	MP_SCRIPT_DATA MissionScriptData;
	SCR_BOOL PAD_0057; // added b3258, some mission thing
	JOB_SETTINGS JobSettings;
	SCR_INT FMMCLauncherState;
	VEHICLE_SELECTION VehicleSelection;
	SCR_INT JobStartCloudTime; // this is a struct but too lazy to create one
	SCR_INT ContentHash;
	SCR_BOOL PAD_0138; // unused
	SCR_BITSET<eTutorialBitset> TutorialBitset;
	SCR_BITSET<eGangCallServices> GangCallRequestedServices;
	PLAYER_INDEX GangCallTarget; // can be used to send muggers/hit squad
	SCR_BITSET<eGangCallServices> GangCallSentServices;
	SCR_INT TutorialBitset2; // @144 as of b889g9
	TEXT_LABEL_23 PlayingContentUsedId;
	TEXT_LABEL_23 MatchId;
	// uint64_t PAD_0156[8];         // unused (REMOVED b889g9)
	TEXT_LABEL_63 DisplayJobName; // as shown in the playerlist? (@157 b889g9)
	STRIKE_TEAM StrikeTeam;
	uint64_t PAD_0185[7]; // pad
	SCR_INT FMMCState;
	SCR_INT PAD_0193; // TODO
	SCR_INT KillStreak;
	SCR_INT NumSuicides;      // deducts RP reward in missions
	SCR_INT DeathmatchBounty; // "You have been deducted $~1~ for being idle for too long, and you now have a bounty placed on you."
	SCR_BOOL CollectedBounty;
	SCR_INT AliveDeathmatchPlayers;
	SCR_INT WantedLevelFlags;
	SCR_ARRAY<uint64_t, 2> PAD_0201;
	SCR_INT HairdoShopIndex;
	SCR_INT PAD_0204;
	PLAYER_STATS PlayerStats;
	SCR_INT PAD_265;
	SCR_INT Mood;
	PROPERTY_DATA PropertyData; // @260 as of b889g9
	uint64_t PAD_0779[4];       // TODO
	uint64_t PAD_0783[12];      // no clue what it does but it looks rather interesting
	SCR_INT AssistedKillFlags;
	NETWORK_INDEX UnkNetworkId;
	SCR_BOOL SpawningUnkVehicle;
	SCR_BOOL MeltdownComplete; // yes, the singleplayer mission "Meltdown" (michael4)
	SCR_INT UNK_0799;
	SCR_INT GangAttackTarget; // triggers unique dialog from some phone NPCs
	SCR_INT ActivePVSlot;
	PLAYER_INDEX SpectatingPlayer;
	SCR_INT PAD_0803;
	SCR_ARRAY<uint64_t, 3> ActiveAmbientWeaponPickups; // size 2 -> 3 b3095
	SCR_ARRAY<uint64_t, 6> OfficeMapMarkers;
	SCR_INT OfficeLargestMoneyThresholdIndex;
	SCR_ARRAY<uint64_t, 2> EnabledOfficeCashPiles;
	SCR_ARRAY<uint64_t, 2> EnabledClubhouseCashPiles;
	BIKER_CONTRACTS BikerContracts;
	SCR_INT CasinoWonBitset; // can be used to tamper with the casino PA system
	uint64_t PAD_0829[2];
	SCR_BOOL CameraPositionOverriden;
	SCR_VEC3 OverrideCameraPosition;
	SCR_INT PAD_0835;
	SCR_INT HeliRappelFlags;
	SCR_INT PAD_0837; // some more aircraft flags
	SCR_BOOL RespawningToPreviousCheckpoint;
	NIGHTCLUB_SALE NightclubSale; // @874 as of b812g9
	SCR_INT SeatingIndex;
	ARENA_WAR_DATA ArenaWarData; // @883 as of b812g9
	// int64_t PAD_0861[2]; removed b889g9
	SCR_INT ApartmentEnterFlags;
	// SCR_VEC3 AvengerMissionStartPosition; removed b889g9
};
static_assert(sizeof(GPBD_FM_Entry) == 883 * 8);

struct GPBD_FM
{
	SCR_ARRAY<GPBD_FM_Entry, 32> Entries;

	static GPBD_FM* Get();
};
static_assert(sizeof(GPBD_FM) == 28257 * 8);