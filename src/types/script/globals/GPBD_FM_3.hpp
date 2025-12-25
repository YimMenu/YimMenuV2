#pragma once
#include "../HudColor.hpp"
#include "../MPScriptData.hpp"
#include "../Timer.hpp"
#include "../types.hpp"

enum class eActivityType
{
	HeistPrep = 233,
	Gunrunning = 180,
	Sightseer = 142,
	HeadHunter = 166,
	BuySpecialCargo = 167,
	SellSpecialCargo = 168,
	DefendSpecialCargo = 169,
	StealVehicle = 178,
	ExportVehicle = 188,
	Gunrunning2 = 225,
	GunrunningSell = 226,
	GunrunningDefend = 227,
	BikerSell = 190,
	BikerDefend = 191,
	BusinessResupply = 192,
	Survival = 3,
	Darts = 14,
	ArmWresling = 15,
	GangAttack = 6,
	PilotSchool = 122,
	Golf = 11,
	ShootingRange = 13,
	Tennis = 12,
	BaseJump = 8,
	Deathmatch = 1,
	ImpromptuDeathmatch = 5,
	Mission = 0,
	Race = 2,
	ExecutiveDeathmatch = 148,
	MarkedForDeath = 151,
	PiracyPrevention = 152,
	MostWanted = 153,
	AssetRecovery = 157,
	HostileTakeover = 159,
	Point2Point = 162,
	AmphibiousAssault = 216,
	Velocity = 219,
	GunsForHire = 185,
	ByThePound = 182,
	RippingItUp = 194,
	RaceToPoint = 189,
	HitAndRide = 193,
	CriminalMischief = 205,
	WeaponOfChoice = 186,
	FragileGoods = 207,
	Torched = 208,
	Outrider = 209,
	WheelieRider = 210,
	POW = 183,
	ExecutiveSearch = 199,
	StandYourGround = 201,
	AutoBuyout = 163,
	DueDiligence = 160,
	MarketManipulation = 154,
	CourierService = 155,
	Skydive = 267
};

enum class eBossGoonFlags
{
	kOneOnOneDM = 4,
	kJoinSuccess = 7,
	kJoinFail = 8,
	kSpectating = 24
};

enum class eGoonInviteType
{
	DEBUG,
	NEARBY,
	FRIENDS,
	CREW,
	INDIVIDUAL,
	LOOKING_FOR_WORK
};

enum class eBossVehicleState
{
	NONE,
	SPAWNED,
	DESTROYED = 3
};

enum class eMCRole
{
	PROSPECT = -1,
	VICE_PRESIDENT,
	ROAD_CAPTAIN,
	SERGEANT_IN_ARMS,
	ENFORCER
};

enum class eClubhouseActivity
{
	NONE = -1,
	DARTS,
	ARM_WRESTLING
};

struct MC_STYLE
{
	SCR_BOOL Enabled;
	SCR_INT BossOutfitType;
	SCR_INT GoonOutfitType;
	SCR_ARRAY<uint64_t, 7> GoonOutfitIndices; // one outfit for each goon
	SCR_ARRAY<uint64_t, 7> GoonOutfitIndicesOverride;
	SCR_INT PAD_0019;
	SCR_BOOL HeadgearEnabled;
	SCR_BOOL EmblemEnabled;
};
static_assert(sizeof(MC_STYLE) == 22 * 8);

struct VEHICLE_EXPORT
{
	SCR_ARRAY<uint64_t, 4> SellingVehicleIndices;
	SCR_INT PAD_0005; // this is set to zero in all export scripts and never read
};
static_assert(sizeof(VEHICLE_EXPORT) == 6 * 8);

struct HANGAR_CARGO
{
	SCR_INT PAD_0000; // unused?
	SCR_ARRAY<uint64_t, 20> DeliverableTypes;
	SCR_INT CargoType;
};
static_assert(sizeof(HANGAR_CARGO) == 23 * 8);

struct CASINO_HEIST_PREP
{
	SCR_INT PrepIndex;
	SCR_INT SupportCrewMemberIndex; // only set on preps 1 through 3
	SCR_INT LoadoutIndex;           // only set on prep 1 and 2
};
static_assert(sizeof(CASINO_HEIST_PREP) == 3 * 8);

struct LEAVE_IN_HELI
{
	SCR_INT Flags;
	PLAYER_INDEX Owner;
	SCR_INT SeatIndex;
};
static_assert(sizeof(LEAVE_IN_HELI) == 3 * 8);

struct BOSS_GOON
{
	PLAYER_INDEX Boss; // leader of CEO/MC
	SCR_INT TimeBecameBoss;
	SCR_INT TimeBecameGoon;
	SCR_INT LastPayTime;
	SCR_BITSET<eBossGoonFlags> Flags;
	SCR_INT Flags2; // TODO
	SCR_INT Flags3; // TODO
	SCR_INT Flags4; // added b3717
	SCR_INT TotalBossGoonTime;
	SCR_ARRAY<uint64_t, 2> BossGoonUUID;
	SCR_ARRAY<uint64_t, 8> Goons;
	SCR_INT GoonsRequestingJoin; // bitset
	SCR_INT PayGrade;
	SCR_INT InvitesByBosses; // bitset
	SCR_INT TransitionBossPersistanceStage;
	SCR_INT EndBeingGoonReason;
	SCR_INT PAD_0025; // TODO
	PLAYER_INDEX JoiningBoss;
	alignas(8) eGoonInviteType JoinedInviteType;
	SCR_INT NumBossDeathsSinceLastPay;
	SCR_VEC3 PAD_0029; // TODO
	alignas(8) eActivityType UnkActivity;
	alignas(8) eActivityType CurrentActivity;
	PLAYER_INDEX JoustTarget;
	PLAYER_INDEX ExecutiveDeathmatchTarget;
	MP_SCRIPT_DATA ActiveScript;
	PLAYER_INDEX PAD_0057;
	PLAYER_INDEX PAD_0058;
	alignas(8) eBossVehicleState BossVehicleState;
	SCR_INT BossVehicleSpawnState;
	PLAYER_INDEX PlayerInsideBossVehicle;
	SCR_HASH BossVehicleModel;
	TIMER LastBossVehicleSpawnTimer;
	TIMER BossVehicleInvincibleTimer;
	SCR_VEC3 BossVehicleSpawnedPosition;
	alignas(8) HudColor BossVehicleHudColor;
	TEXT_LABEL_15 BossVehicleTextLabel;
	SCR_INT BossVehicleNetId;
	MC_STYLE MCStyle;
	uint64_t PAD_0098[3]; // unused
	SCR_INT FriendlyFireDisabledPlayers;
	SCR_INT PiracyPreventionYachtIndex; // not used by the scripts
	SCR_INT BossGoonMissionLaunchState;
	SCR_INT ColorSlot;
	TEXT_LABEL_63 MCName;
	SCR_INT Language; // can be used to get the system language of player
	SCR_INT SpawnableBossVehicles;
	SCR_INT AutoBuyoutDeliveryLocationIndex;
	SCR_INT AutoBuyoutDeliveryLocationSubIndex;
	SCR_INT PAD_0125;                           // unused
	SCR_ARRAY<SCR_VEC3, 8> PAD_0126;            // TODO
	SCR_ARRAY<SCR_VEC3, 8> ContrabandPositions; // positions of cargo used to notify players to destroy them when they get near
	SCR_HASH ContrabandPickupModel;
	PLAYER_INDEX StealingContrabandVehiclePlayerIndex;
	SCR_INT PAD_0178; // TODO
	SCR_HASH ContrabandPickupModel2;
	SCR_BOOL DestroyedCargo;
	SCR_INT VIPGameplayDisabledTimer; // @181 as of 1.67
	SCR_INT SettingUpBusiness;
	uint64_t PAD_0183[4]; // TODO some unknown contraband struct
	VEHICLE_EXPORT VehicleExport;
	uint64_t PAD_0193[12];                       // TODO
	SCR_ARRAY<uint64_t, 9> ActiveFreemodeEvents; // force thunder, size 7 -> 8 b3258
	                                             //                     8 -> 9 b3407
	uint64_t PAD_0212[22];                       // I'm not even going to bother with this one
	HANGAR_CARGO HangarCargo;
	uint64_t PAD_0236[23]; // not going to bother with this one either
	SCR_ARRAY<uint64_t, 20> CasinoDeliverables;
	SCR_INT CasinoLimoDestination;
	SCR_BOOL CasinoLimoActive;
	SCR_BOOL CasinoLuxuryCarActive;
	SCR_HASH CasinoLuxuryCarModel;
	SCR_INT PAD_0309; // added b3717
	CASINO_HEIST_PREP CasinoHeistPrep;
	SCR_INT CayoPrepIndex;
	SCR_INT CompanySUVDestination;
	SCR_BOOL CompanySUVActive;
	SCR_ARRAY<uint64_t, 8> ContrabandIndices;     // type of selling cargo
	SCR_ARRAY<uint64_t, 10> VehicleExportIndices; // not sure what this is
	SCR_INT VehicleExportMissionType;             // valid range is 2000 to 2010, 2000 = 0, 2001 = 1 etc
	SCR_ARRAY<uint64_t, 4> VehicleExportSellingIndices;
	SCR_BOOL PAD_0337;           // TODO
	TEXT_LABEL_63 GangName;      // CEO Name
	TEXT_LABEL_63 ClubhouseName; // cut content?
	SCR_INT SourcingContrabandType;
	SCR_INT FragileGoodsMissionType;
	SCR_INT SalvageMissionType;
	SCR_INT DoomsdayPrepIndex;
	SCR_INT VehicleExportIndex; // another one...
	SCR_INT PAD_0375;           // unused
	SCR_INT BunkerSourceIndex;  // check gb_gunrunning func_1540
	SCR_ARRAY<uint64_t, 8> BunkerCargoIndices;
	uint64_t PAD_0386[5];
	uint64_t PAD_0391[2];     // unused
	uint64_t PAD_0393[15];    // smuggler data
	SCR_INT LastBossWorkTime; // seconds since epoch
	uint64_t PAD_0409[19];
	SCR_BOOL IsMC;
	alignas(8) eMCRole MCRole; // applies to goons only, boss is always the MC president
	SCR_BOOL FormationFlyingAssist;
	SCR_INT PAD_0431; // always set to zero and not read
	SCR_BOOL MCFormationActive;
	SCR_BOOL MCFormationHelpShown;
	TIMER MCFormationHealthBonusTimer;
	TIMER MCFormationLastHealthBonusTimer;
	TIMER MCFormationBreakTimer;
	SCR_INT PAD_0440; // unused
	SCR_BOOL MCFormationAssist;
	SCR_BOOL MCRidingStyleRelaxed;
	SCR_FLOAT PAD_0443;      // set from a tunable
	SCR_FLOAT PAD_0444;      // set from a tunable
	uint64_t PAD_0445[16];   // somewhat unused, a few fields are accessed in the business battle script
	SCR_INT ClothingValue;   // total value of equipped clothing used by criminal damage
	PLAYER_INDEX Adversary;  // for common adversary calculations?
	SCR_HASH ContrabandType; // unknown HASH_ENUM
	SCR_INT HitAndRideGangType;
	SCR_BOOL IsMC2;
	SCR_INT BossGoonVersion;
	SCR_INT MCTotalContributionPoints;
	SCR_INT MCContributionPoints;
	SCR_INT FavoriteBikeStyle; // not read by the scripts
	SCR_INT GreatestFormationTimeIndex;
	SCR_INT FormationTime;
	SCR_BOOL RidingFavoriteMotorcycle;
	SCR_INT ContrabandSellLocation;
	SCR_INT BusinessBattleType;
	SCR_INT PAD_0475;
	SCR_INT NightclubMissionIndex;
	SCR_INT NightclubDefendMissionIndex;
	uint64_t PAD_0478[18]; // TODO
	SCR_HASH PAD_0501;     // added b3717
	SCR_INT PAD_0502;      // added b3717
	SCR_BOOL DoubleActionCacheLocationRevealed;
};
static_assert(sizeof(BOSS_GOON) == 504 * 8);

struct MC_STATS
{
	SCR_INT FormationTime0;
	SCR_INT FormationTime1;
	SCR_INT FormationTime2;
	SCR_INT FormationTime3;
	SCR_INT MembersMarkedForDeath;
	SCR_INT MCKills;
	SCR_INT MCDeaths;
	SCR_INT RivalPresidentKills;
	SCR_INT RivalCEOAndVIPKills;
	SCR_INT MeleeKills;
	SCR_INT ClubhouseContractsComplete;
	SCR_INT ClubhouseContractEarnings;
	SCR_INT ClubworkCompleted;
	SCR_INT ClubChallengesCompleted;
	SCR_INT MemberChallengesCompleted;
};
static_assert(sizeof(MC_STATS) == 15 * 8);

struct GBPD_FM_3_Entry
{
	alignas(8) eActivityType CurrentActivity;         // enum is outdated
	SCR_INT Flags;                                    // TODO
	alignas(8) eActivityType CurrentFreemodeActivity; // subset of CurrentActivity
	SCR_INT SeatingFlags;
	SCR_VEC3 CurrentFreemodeActivityObjectivePosition;
	SCR_INT VehiclesNearbyActivityObjective; // only used by challenges and checkpoints
	SCR_BOOL PassiveMode;
	SCR_BOOL TimeTrialActive; // verify
	BOSS_GOON BossGoon;
	uint64_t PAD_507[3]; // unused
	SCR_INT ScriptEventReplayProtectionCounter; // "uniqueId"
	TIMER CoronaForcedLaunchTimer;
	LEAVE_IN_HELI LeaveInHeli;
	SCR_INT OfficeDesktopFlags; // bit 0 -> login, bit 1 -> map
	uint64_t PAD_514[8];        // some IE stuff, most of it is unused
	SCR_INT IlluminatedClothingState;
	SCR_INT MatchHistoryId1; // used for telemetry
	SCR_INT MatchHistoryId2;
	alignas(8) eClubhouseActivity ClubhouseActivity;
	SCR_INT ClubhouseFont;
	SCR_INT ClubhouseColor;
	SCR_INT ClubhouseEmblem;
	SCR_BOOL ClubhouseHideSignage;
	uint64_t PAD_0533[2]; // facility exit
	uint64_t PAD_0535[6]; // no clue what this is
	MC_STATS MCStats;
	uint64_t PAD_0556[29];
	SCR_HASH ForcedWeapon;
	SCR_INT HangarCargoMissionLocationIndex;
	SCR_VEC3 AvengerPosition;
	SCR_VEC3 TerrorbytePosition;
	SCR_VEC3 AcidLabPosition;
	PLAYER_INDEX DeliveringExportVehicleOwner;
	uint64_t PAD_0597[2]; // TODO
	SCR_INT BountyAmount; // values above 10000 will prevent payout
	PLAYER_INDEX BountyPlacedBy;
	SCR_INT PAD_0601;                       // unused, set to -1 by business_battles_sell and never read
	SCR_INT CurrentlyUsingArenaTurretIndex; // works similar to the vars found in GlobalPlayerBD
	SCR_INT CurrentlyUsingArenaTurretActivatedTime;
	SCR_INT CasinoStoryProgress;
	SCR_INT CasinoFlowProgress;
	SCR_ARRAY<uint64_t, 1> DailyObjectiveFlags; // @607 as of 1.67
};
static_assert(sizeof(GBPD_FM_3_Entry) == 615 * 8);

struct GPBD_FM_3
{
	SCR_ARRAY<GBPD_FM_3_Entry, 32> Entries;

	static GPBD_FM_3* Get();
};
static_assert(sizeof(GPBD_FM_3) == 19681 * 8);