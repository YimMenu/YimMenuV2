#pragma once
#include "types.hpp"

#define REGISTER_SCRIPT_EVENT(classType, indexType)                  \
	constexpr static auto EVENT_INDEX = ScriptEventIndex::indexType; \
	classType()                                                      \
	{                                                                \
		memset(this, 0, sizeof(classType));                          \
		EventIndex = static_cast<int>(EVENT_INDEX);                  \
	}                                                                \
	classType(const classType& other)                                \
	{                                                                \
		memcpy(this, &other, sizeof(classType));                     \
		EventIndex = static_cast<int>(EVENT_INDEX);                  \
	}                                                                \
	static constexpr size_t GetSize()                                \
	{                                                                \
		return sizeof(classType);                                    \
	}                                                                \
	inline void Send()                                               \
	{                                                                \
		SendImpl(GetSize());                                         \
	}                                                                \
	inline void Send(int player)                                     \
	{                                                                \
		SetPlayer(player);                                           \
		SendImpl(GetSize());                                         \
	}

// I doubt rockstar would cycle this again, but best to keep this, just in case
enum class ScriptEventIndex
{
	Bounty   = 1517551547, // (137, "FM_TXT_BNTY0", iVar1, PLAYER::GET_PLAYER_NAME(Var2.f_1), "", 5000, Var2.f_6);
	CeoBan   = 1531565154, // mpply_vipgameplaydisabledtimer
	CeoKick  = -11681548,
	CeoMoney = -337848027, // Goon_Paid_Large
	ClearWantedLevel = -1704545346,
	ForceMission     = 259469385,  // ), Var0.f_2, 1))
	GiveCollectible  = 968269233,  // DLC_SUM20_HIDDEN_COLLECTIBLES xref
	GtaBanner        = -330501227, // NETWORK::NETWORK_IS_SCRIPT_ACTIVE("BUSINESS_BATTLES", -1, true, 0) second one
	NetworkBail      = -901348601, // NETWORK::NETWORK_BAIL(16, 0, 0); xref func
	PersonalVehicleDestroyed = 1655503526,  // PLYVEH_INS_DES1
	RemoteOffradar           = 57493695,    // NETWORK::GET_TIME_DIFFERENCE(NETWORK::GET_NETWORK_TIME(), Var0.f_2)
	SendToCutscene           = -1951335381, // (bVar3, bVar4, 125f, 1)
	SendToCayoPerico         = 373376135,   // CELL_HI_INV
	SendToLocation           = 1669592503,  // &Var222, 11);
	SoundSpam                = 996099702,   // CELL_APTINVYACHT
	Spectate                 = 1840946429,  // SPEC_TCK1
	Teleport                 = -1321657966, // Mission_Pass_Notify
	TeleportToWarehouse      = -1253241415, // .f_4 == 50
	// TransactionError         = -830063381,  // NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH
	VehicleKick              = -503325966,  // PIM_RFMOC
	MCTeleport    = 1103127469, // NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(PLAYER::PLAYER_ID()) == (first one)
	StartActivity = 1450115979, // (Var0.f_2, -1); first match
	MarkPlayerAsBeast = 1649541577, // GB_BOSSBST xref == PLAYER... global (sadly doesn't actually turn people into the beast)
	KickFromInterior = -1496371358, // ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), PED::GET_PED_MAX_HEALTH(PLAYER::PLAYER_PED_ID()), false)
	InteriorControl  = -1638522928, // eventData.f_3 != _INVALID_PLAYER_INDEX_0()
	SendTextLabelSMS = -1773335296,

	Crash  = -1604421397, // SET_NO_LOADING_SCREEN, xref it
	Crash2 = -375628860,
	Crash3 = 323285304,

	TSECommand          = 800157557, // CnCTG_IN_BF
	TSECommandRotateCam = 225624744, // != 29) && f
	TSECommandSound     = 385726943,
	TSECommandLaunchHeist = 1733306780, // HEIST_NOTE_3 in fmmc_launcher

	Notification             = -642704387,
	NotificationMoneyBanked  = 94410750,   // TICK_TC_BANK
	NotificationMoneyRemoved = -242911964, // TICK_TC_REMO
	NotificationMoneyStolen  = -295926414, // TICK_TC_STOL
	NotificationCrash1       = -994541138, // AMCH_ATTEMPT2
	NotificationCrash2       = 782258655,  // GBSAL_COLL

	DestroyPersonalVehicle = 109434679, // CnC_PV_THEFT
	TriggerCEORaid         = -1906536929,

	StartScriptBegin   = -366707054,
	StartScriptProceed = 1757622014,

	RequestRandomEvent = -126218586
};

struct SCRIPT_EVENT
{
protected:
	SCR_HASH EventIndex;          // 0x00
	PLAYER_INDEX SenderIndex;     // 0x08
	SCR_INT PlayerBits;           // 0x10

public:
	int GetSender() const
	{
		return SenderIndex;
	}

	Hash GetEventIndex() const
	{
		return EventIndex;
	}

	bool ShouldReceiveEvent(int player) const
	{
		return PlayerBits & (1 << player);
	}

	void SetAllPlayers()
	{
		PlayerBits = -1;
	}

	void SetAllPlayersExcept(int player_to_exclude)
	{
		PlayerBits = -1 & ~(1 << player_to_exclude);
	}

	void SetPlayer(int player)
	{
		PlayerBits |= (1 << player);
	}

protected:
	void SendImpl(int size);
};
static_assert(sizeof(SCRIPT_EVENT) == 3 * 8);

struct SCRIPT_EVENT_BOUNTY : public SCRIPT_EVENT
{
	REGISTER_SCRIPT_EVENT(SCRIPT_EVENT_BOUNTY, Bounty);

	PLAYER_INDEX Target;
	SCR_INT BountyFlags;
	SCR_INT Amount;
	SCR_INT PAD_0006;
	SCR_BOOL FromPed;
	uint64_t PAD_0008[13];
	SCR_INT AntiReplayValue1;
	SCR_INT AntiReplayValue2;
};
static_assert(sizeof(SCRIPT_EVENT_BOUNTY) == 23 * 8);

struct SCRIPT_EVENT_SEND_TEXT_LABEL_MESSAGE : public SCRIPT_EVENT
{
	REGISTER_SCRIPT_EVENT(SCRIPT_EVENT_SEND_TEXT_LABEL_MESSAGE, SendTextLabelSMS);

	TEXT_LABEL_23 Label;
};
static_assert(sizeof(SCRIPT_EVENT_SEND_TEXT_LABEL_MESSAGE) == 9 * 8);

struct SCRIPT_EVENT_KICK_FROM_CEO : public SCRIPT_EVENT
{
	REGISTER_SCRIPT_EVENT(SCRIPT_EVENT_KICK_FROM_CEO, CeoKick);
};
static_assert(sizeof(SCRIPT_EVENT_KICK_FROM_CEO) == 3 * 8);

struct SCRIPT_EVENT_SEND_TO_INTERIOR : public SCRIPT_EVENT
{
	REGISTER_SCRIPT_EVENT(SCRIPT_EVENT_SEND_TO_INTERIOR, InteriorControl);

	SCR_INT Interior;
	PLAYER_INDEX Owner;
	SCR_BOOL GoonsOnly;
	SCR_BOOL EnterOwnerInterior;
	SCR_VEC3 Position;
	SCR_BOOL PAD_0010;
	SCR_INT InstanceId;
	SCR_INT PAD_0012;
	SCR_INT Distance;
	SCR_BOOL PAD_0014;
	SCR_INT SubInstanceId;
};
static_assert(sizeof(SCRIPT_EVENT_SEND_TO_INTERIOR) == 16 * 8);

struct SCRIPT_EVENT_REQUEST_RANDOM_EVENT : public SCRIPT_EVENT
{
	REGISTER_SCRIPT_EVENT(SCRIPT_EVENT_REQUEST_RANDOM_EVENT, RequestRandomEvent);

	SCR_INT FMMCType;
	SCR_INT Variation;
	SCR_INT Subvariation;
	SCR_INT PlayersToSend;
};
static_assert(sizeof(SCRIPT_EVENT_REQUEST_RANDOM_EVENT) == 7 * 8);

struct SCRIPT_EVENT_COMMAND : public SCRIPT_EVENT
{
	enum class eCommand
	{
		LaunchHeist = 1733306780
	};

	REGISTER_SCRIPT_EVENT(SCRIPT_EVENT_COMMAND, TSECommand);

	eCommand Command;
	SCR_INT RandomNumber; // it's fine if we don't set this
};

#undef REGISTER_SCRIPT_EVENT