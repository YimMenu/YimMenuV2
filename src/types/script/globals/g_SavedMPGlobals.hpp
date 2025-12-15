#pragma once
#include "types/script/types.hpp"

// All the names can be found in the startup script

struct MP_PROPERTY_SAVED
{
	SCR_BOOL TVOn;                              // 0
	SCR_INT TVChannelId;                        // 1
	SCR_BOOL PenthouseTVOn;                     // 2
	SCR_INT PenthouseTVChannelId;               // 3
	SCR_BOOL MediaRoomTVOn;                     // 4
	SCR_INT MediaRoomTVChannelId;               // 5
	SCR_ARRAY<uint64_t, 2> RadioOnId;           // 6
	SCR_ARRAY<uint64_t, 2> RadioStationId;      // 7
	SCR_BOOL GarageTVOn;                        // 12
	SCR_INT GarageTVChannelId;                  // 13
	SCR_BOOL GarageRadioOn;                     // 14
	SCR_INT GarageRadioStationId;               // 15
	SCR_INT NumberTimesSmoked;                  // 16
	SCR_INT NumberTimesDrank;                   // 17
	SCR_INT NumberTimesStrippers;               // 18
	SCR_INT NumberTimesSmokedSecond;            // 19
	SCR_INT NumberTimesDrankSecond;             // 20
	SCR_INT NumberTimesStrippersSecond;         // 21
	SCR_INT NumberTimesSmoked3;                 // 22
	SCR_INT NumberTimesDrank3;                  // 23
	SCR_INT NumberTimesStrippers3;              // 24
	SCR_INT NumberTimesSmoked4;                 // 25
	SCR_INT NumberTimesDrank4;                  // 26
	SCR_INT NumberTimesStrippers4;              // 27
	SCR_INT NumberTimesSmoked5;                 // 28
	SCR_INT NumberTimesDrank5;                  // 29
	SCR_INT NumberTimesStrippers5;              // 30
	SCR_INT NumberTimesSmokedYatch;             // 31
	SCR_INT NumberTimesDrankYatch;              // 32
	SCR_INT NumberTimesStrippersYatch;          // 33
	SCR_INT DateLastCleanedApartment;           // 34
	SCR_INT ShowersTaken;                       // 35
	SCR_ARRAY<uint64_t, 22> PropDrinks;         // 36
	SCR_ARRAY<uint64_t, 22> PropSmokes;         // 59
	SCR_ARRAY<uint64_t, 22> PropStrippers;      // 82
	SCR_ARRAY<TEXT_LABEL_63, 30> PropNamedVehs; // 105
};
static_assert(sizeof(MP_PROPERTY_SAVED) == 586 * 8);

struct CAR_APP_ORDER
{
	// field 0 to 40 actually seems to be a struct (MISC::START_SAVE_STRUCT_WITH_SIZE(panParam0, 41, sParam1))
	SCR_INT Model;                        // 0
	SCR_INT ColourId1;                    // 1
	SCR_INT ColourId2;                    // 2
	SCR_INT Colour1Group;                 // 3
	SCR_INT Colour2Group;                 // 4
	SCR_INT WindowTint;                   // 5
	SCR_INT TyreSmokeR;                   // 6
	SCR_INT TyreSmokeG;                   // 7
	SCR_INT TyreSmokeB;                   // 8
	SCR_INT Engine;                       // 9
	SCR_INT Brakes;                       // 10
	SCR_INT Wheels;                       // 11
	SCR_INT WheelType;                    // 12
	SCR_INT Exhaust;                      // 13
	SCR_INT Suspension;                   // 14
	SCR_INT Armour;                       // 15
	SCR_INT Horn;                         // 16
	SCR_INT Lights;                       // 17
	SCR_BOOL BulletProofTyres;            // 18
	SCR_INT Turbo;                        // 19
	SCR_INT TyreSmoke;                    // 20
	TEXT_LABEL_15 PlateText;              // 21
	SCR_INT PlateBack;                    // 25
	SCR_INT UId;                          // 26
	SCR_INT Cost;                         // 27
	TEXT_LABEL_15 PlateTextPending;       // 28
	SCR_INT PlateBackPending;             // 32
	SCR_BOOL ProcessOrder;                // 33
	SCR_BOOL OrderForPlayerVehicle;       // 34
	SCR_BOOL OrderReceivedOnBoot;         // 35
	SCR_BOOL OrderPending;                // 36
	SCR_BOOL CheckPlateProfanity;         // 37
	SCR_BOOL SCProfanityFailed;           // 38
	SCR_BOOL SOrderFailedFunds;           // 39
	SCR_BOOL OrderPaidFor;                // 40
	SCR_ARRAY<uint64_t, 10> CarHidden;    // 41
	SCR_BOOL UpdateMods;                  // 52
	SCR_BOOL MultiplayerDataWiped;        // 53
	SCR_BOOL DeleteCarData;               // 54
	SCR_BOOL CarAppPlateSet;              // 55
	TEXT_LABEL_15 CarAppPlateText;        // 56
	SCR_INT CarAppPlateBack;              // 60
	SCR_INT OrderCount;                   // 61
	SCR_INT OrderVehicle;                 // 62
	SCR_ARRAY<uint64_t, 10> SavedVehSlot; // 63
	SCR_ARRAY<uint64_t, 10> SavedVehPrio; // 74
	SCR_INT LastUsed;                     // 85
	SCR_INT NewUsed;                      // 86
	SCR_BOOL SetupInit;                   // 87
};
static_assert(sizeof(CAR_APP_ORDER) == 88 * 8);

struct DAILY_OBJECTIVES
{
	SCR_INT Objective;  // 0
	SCR_BOOL Completed; // 1
	SCR_INT Initial;    // 2
};
static_assert(sizeof(DAILY_OBJECTIVES) == 3 * 8);

struct MP_GENERAL_SAVED
{
	SCR_INT CashGivenTotal;                         // 0
	SCR_INT CashGivenTime;                          // 1
	SCR_INT LastSavedCar;                           // 2
	SCR_INT CurrentPropValue;                       // 3
	SCR_INT WheelieTimer;                           // 4
	SCR_INT WheelieUpdates;                         // 5
	SCR_INT WheelieTime;                            // 6
	SCR_BOOL GrabTime;                              // 7
	SCR_INT LastSoldVehicleTime;                    // 8
	SCR_INT LastTimePlayed;                         // 9
	SCR_INT SaveCoupons;                            // 10
	SCR_INT NewVehPurchased;                        // 11
	SCR_INT LastBruciePillReminder;                 // 12
	SCR_INT LastSecVanReminder;                     // 13
	SCR_INT LastBountyReminder;                     // 14
	SCR_INT LastParaReminder;                       // 15
	SCR_INT LastCrateDropReminder;                  // 16
	SCR_INT LastGangAttackReminder;                 // 17
	SCR_INT LastImpExpReminder;                     // 18
	SCR_INT LastInsuranceReminder;                  // 19
	SCR_INT LastSurvivalReminder;                   // 20
	SCR_INT LastBikerBackupReminder;                // 21
	SCR_INT LastVagosBackupReminder;                // 22
	SCR_INT LastLesterVehReminder;                  // 23
	SCR_INT LastPersonalVehDeliveryReminder;        // 24
	SCR_INT LastPegasusVehicleReminder;             // 25
	SCR_INT LastMerryweatherReminder;               // 26
	SCR_INT LastLesterHelpReminder;                 // 27
	SCR_INT LastLesterReqJobReminder;               // 28
	SCR_INT LastGeraldReqJobReminder;               // 29
	SCR_INT LastSimeonReqJobReminder;               // 30
	SCR_INT LastMartinReqJobReminder;               // 31
	SCR_INT LastRonReqJobReminder;                  // 32
	SCR_INT RecentlyPassedMissionBitset;            // 33
	SCR_INT RecentlyPassedMissionTime;              // 34
	SCR_INT LastImportExportDelTime;                // 35
	SCR_INT LastImportExportListTime;               // 36
	SCR_INT MyLastImportExportListDay;              // 37
	SCR_INT VehicleWebsiteReminderTime;             // 38
	SCR_BOOL DefaultClothesSet;                     // 39
	SCR_ARRAY<uint64_t, 6> Clothes;                 // 40
	SCR_ARRAY<uint64_t, 1224> Carmods;              // 47
	SCR_INT LastCrewCharWasIn;                      // 1272
	SCR_INT StripperUnlockedBS;                     // 1273
	SCR_INT GeneralBS;                              // 1274
	SCR_INT CarsModifiedTimeStamp;                  // 1275
	SCR_ARRAY<uint64_t, 9> GolfLongestDriveHole;    // 1276
	SCR_ARRAY<uint64_t, 9> GolfLongestPuttHole;     // 1286
	SCR_INT GolfBestRound;                          // 1296
	SCR_FLOAT GolfLongestDrive;                     // 1297
	SCR_FLOAT GolfLongestPutt;                      // 1298
	SCR_INT ShareLJCashTotal;                       // 1299
	SCR_INT ShareLJCashTime;                        // 1300
	SCR_INT ReceiveLJCashTotal;                     // 1301
	SCR_INT ReceiveLJCashTime;                      // 1302
	SCR_INT LastAccProp;                            // 1303
	SCR_INT Multi1PropVal;                          // 1304
	SCR_ARRAY<uint64_t, 34> PropAryVal;             // 1305
	SCR_INT LastAccSmplInt;                         // 1337
	SCR_INT KrPatchUpdate;                          // 1338
	SCR_ARRAY<uint64_t, 273> OutfitCompDraw;        // 1339
	SCR_ARRAY<uint64_t, 273> OutfitCompTex;         // 1613
	SCR_ARRAY<uint64_t, 210> OutfitPropID;          // 1887
	SCR_ARRAY<uint64_t, 210> OutfitPropTex;         // 2098
	SCR_ARRAY<uint64_t, 21> OutfitStored;           // 2309
	SCR_ARRAY<uint64_t, 21> OutfitTatCrewA;         // 2331
	SCR_ARRAY<uint64_t, 21> OutfitTatCrewB;         // 2353
	SCR_ARRAY<uint64_t, 21> OutfitTatCrewC;         // 2375
	SCR_ARRAY<uint64_t, 21> OutfitTatCrewD;         // 2397
	SCR_ARRAY<uint64_t, 21> OutfitTatCrewE;         // 2419
	SCR_ARRAY<uint64_t, 21> OutfitTatCrewF;         // 2441
	SCR_ARRAY<TEXT_LABEL_31, 21> OutfitName;        // 2463
	SCR_ARRAY<uint64_t, 21> OutfitShirt;            // 2632
	SCR_ARRAY<GAMER_HANDLE, 3> LastJobGamer;        // 2654
	SCR_ARRAY<uint64_t, 918> DLCMods;               // 2694
	SCR_ARRAY<uint64_t, 626> DLCSuperMods;          // 3613
	SCR_BOOL DOCompletedObjectives;                 // 4240
	SCR_BOOL DOLoggedInToday;                       // 4241
	SCR_INT DOXValue;                               // 4242
	SCR_INT DOLastHistoryLength;                    // 4243
	SCR_INT DOLastResetTime;                        // 4244
	SCR_ARRAY<DAILY_OBJECTIVES, 3> DOObjectives;    // 4245
	SCR_ARRAY<uint64_t, 24> DOHistory;              // 4255
	SCR_ARRAY<TEXT_LABEL_63, 3> LastJobGamerName;   // 4280
	SCR_ARRAY<uint64_t, 10> BGSaveInt;              // 4329
	SCR_ARRAY<uint64_t, 2> PropLib;                 // 4340
	SCR_ARRAY<GAMER_HANDLE, 3> LastGOGGamer;        // 4343
	SCR_ARRAY<GAMER_HANDLE, 3> LastGOJobGamer;      // 4383
	SCR_ARRAY<TEXT_LABEL_63, 3> LastGOJobGamerName; // 4423
};
static_assert(sizeof(MP_GENERAL_SAVED) == 4475 * 8);

struct MP_BOUNTY_SAVED
{
	GAMER_HANDLE BountyGamer;                       // 0
	SCR_INT BountyTime;                             // 13
	SCR_INT BountyValue;                            // 14
	SCR_ARRAY<GAMER_HANDLE, 16> BountyGamerHandles; // 15
	SCR_ARRAY<uint64_t, 16> BountyTim;              // 224
};
static_assert(sizeof(MP_BOUNTY_SAVED) == 241 * 8);

struct MP_ATM_SAVED
{
	SCR_INT MPATMCaret;                        // 0
	SCR_ARRAY<uint64_t, 16> MPATMLogVal;       // 1
	SCR_ARRAY<TEXT_LABEL_23, 16> MPATMLogScrs; // 18
	SCR_ARRAY<uint64_t, 16> MPATMLogAct;       // 115
	SCR_ARRAY<uint64_t, 16> MPATMLogDat;       // 132
	SCR_BOOL MPAnyVehBought;                   // 149
};
static_assert(sizeof(MP_ATM_SAVED) == 150 * 8);

struct MP_SCRIPT_SAVES_DATA
{
	SCR_ARRAY<uint64_t, 1> SaveDataIntScriptSaves;         // 0
	SCR_ARRAY<uint64_t, 1> SaveDataFloatScriptSaves;       // 2
	SCR_ARRAY<uint64_t, 1> SaveDataBoolScriptSaves;        // 4
	SCR_ARRAY<TEXT_LABEL_31, 1> SaveDataStringScriptSaves; // 6
	SCR_ARRAY<SCR_VEC3, 1> SaveDataVectorScriptSaves;      // 15
	SCR_ARRAY<Date, 1> SaveDataDateScriptSaves;            // 19
};
static_assert(sizeof(MP_SCRIPT_SAVES_DATA) == 27 * 8);

struct g_SavedMPGlobalsEntry
{
	// Are these two a struct? TEXT_LABEL_ASSIGN_STRING(&unk, "MP_BIG_ASS_VEHICLES", 24) -> MISC::START_SAVE_STRUCT_WITH_SIZE(panParam0, 7, sParam1)
	SCR_INT BAVTimestamp;                 // 0
	SCR_ARRAY<uint64_t, 5> BAVFlags;      // 1
	MP_PROPERTY_SAVED PropertySaved;      // 7
	CAR_APP_ORDER CarAppOrder;            // 593
	MP_GENERAL_SAVED GeneralSaved;        // 681
	MP_BOUNTY_SAVED BountySaved;          // 5156
	MP_ATM_SAVED ATMSaved;                // 5397
	MP_SCRIPT_SAVES_DATA ScriptSavesData; // 5547
};
static_assert(sizeof(g_SavedMPGlobalsEntry) == 5574 * 8);

struct g_SavedMPGlobals
{
	SCR_ARRAY<g_SavedMPGlobalsEntry, 1> Entries;

	static g_SavedMPGlobals* Get();
};
static_assert(sizeof(g_SavedMPGlobals) == 5575 * 8);