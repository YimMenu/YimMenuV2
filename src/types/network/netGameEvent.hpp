#pragma once
#include <cstdint>
#include "types/rage/vector.hpp"
#include "types/script/CGameScriptId.hpp"

namespace rage
{
	class datBitBuffer;
	class netPlayer;

	class netGameEvent
	{
	public:
		enum class Type : uint16_t
		{
			OBJECT_ID_FREED_EVENT,
			OBJECT_ID_REQUEST_EVENT,
			ARRAY_DATA_VERIFY_EVENT,
			SCRIPT_ARRAY_DATA_VERIFY_EVENT,
			REQUEST_CONTROL_EVENT,
			GIVE_CONTROL_EVENT,
			WEAPON_DAMAGE_EVENT,
			REQUEST_PICKUP_EVENT,
			REQUEST_MAP_PICKUP_EVENT,
			GAME_CLOCK_EVENT,
			GAME_WEATHER_EVENT,
			RESPAWN_PLAYER_PED_EVENT,
			GIVE_WEAPON_EVENT,
			REMOVE_WEAPON_EVENT,
			REMOVE_ALL_WEAPONS_EVENT,
			VEHICLE_COMPONENT_CONTROL_EVENT,
			FIRE_EVENT,
			EXPLOSION_EVENT,
			START_PROJECTILE_EVENT,
			UPDATE_PROJECTILE_TARGET_EVENT,
			REMOVE_PROJECTILE_ENTITY_EVENT,
			BREAK_PROJECTILE_TARGET_LOCK_EVENT,
			ALTER_WANTED_LEVEL_EVENT,
			CHANGE_RADIO_STATION_EVENT,
			RAGDOLL_REQUEST_EVENT,
			PLAYER_TAUNT_EVENT,
			PLAYER_CARD_STAT_EVENT,
			DOOR_BREAK_EVENT,
			SCRIPTED_GAME_EVENT,
			REMOTE_SCRIPT_INFO_EVENT,
			REMOTE_SCRIPT_LEAVE_EVENT,
			MARK_AS_NO_LONGER_NEEDED_EVENT,
			CONVERT_TO_SCRIPT_ENTITY_EVENT,
			SCRIPT_WORLD_STATE_EVENT,
			CLEAR_AREA_EVENT,
			CLEAR_RECTANGLE_AREA_EVENT,
			NETWORK_REQUEST_SYNCED_SCENE_EVENT,
			NETWORK_START_SYNCED_SCENE_EVENT,
			NETWORK_STOP_SYNCED_SCENE_EVENT,
			NETWORK_UPDATE_SYNCED_SCENE_EVENT,
			INCIDENT_ENTITY_EVENT,
			GIVE_PED_SCRIPTED_TASK_EVENT,
			GIVE_PED_SEQUENCE_TASK_EVENT,
			NETWORK_CLEAR_PED_TASKS_EVENT,
			NETWORK_START_PED_ARREST_EVENT,
			NETWORK_START_PED_UNCUFF_EVENT,
			NETWORK_SOUND_CAR_HORN_EVENT,
			NETWORK_ENTITY_AREA_STATUS_EVENT,
			NETWORK_GARAGE_OCCUPIED_STATUS_EVENT,
			PED_CONVERSATION_LINE_EVENT,
			SCRIPT_ENTITY_STATE_CHANGE_EVENT,
			NETWORK_PLAY_SOUND_EVENT,
			NETWORK_STOP_SOUND_EVENT,
			NETWORK_PLAY_AIRDEFENSE_FIRE_EVENT,
			NETWORK_BANK_REQUEST_EVENT,
			NETWORK_AUDIO_BARK_EVENT,
			REQUEST_DOOR_EVENT,
			NETWORK_TRAIN_REPORT_EVENT,
			NETWORK_TRAIN_REQUEST_EVENT,
			NETWORK_INCREMENT_STAT_EVENT,
			MODIFY_VEHICLE_LOCK_WORD_STATE_DATA,
			MODIFY_PTFX_WORD_STATE_DATA_SCRIPTED_EVOLVE_EVENT,
			REQUEST_PHONE_EXPLOSION_EVENT,
			REQUEST_DETACHMENT_EVENT,
			KICK_VOTES_EVENT,
			GIVE_PICKUP_REWARDS_EVENT,
			BLOW_UP_VEHICLE_EVENT,
			NETWORK_SPECIAL_FIRE_EQUIPPED_WEAPON,
			NETWORK_RESPONDED_TO_THREAT_EVENT,
			NETWORK_SHOUT_TARGET_POSITION,
			VOICE_DRIVEN_MOUTH_MOVEMENT_FINISHED_EVENT,
			PICKUP_DESTROYED_EVENT,
			UPDATE_PLAYER_SCARS_EVENT,
			NETWORK_CHECK_EXE_SIZE_EVENT,
			NETWORK_PTFX_EVENT,
			NETWORK_PED_SEEN_DEAD_PED_EVENT,
			REMOVE_STICKY_BOMB_EVENT,
			NETWORK_CHECK_CODE_CRCS_EVENT,
			INFORM_SILENCED_GUNSHOT_EVENT,
			PED_PLAY_PAIN_EVENT,
			CACHE_PLAYER_HEAD_BLEND_DATA_EVENT,
			REMOVE_PED_FROM_PEDGROUP_EVENT,
			REPORT_MYSELF_EVENT,
			REPORT_CASH_SPAWN_EVENT,
			ACTIVATE_VEHICLE_SPECIAL_ABILITY_EVENT,
			BLOCK_WEAPON_SELECTION,
			NETWORK_CHECK_CATALOG_CRC
		};

		virtual ~netGameEvent() {};

		virtual const char* GetName() { return nullptr; };
		virtual bool IsInScope(netPlayer* player) { return {}; };
		virtual bool TimeToResend(uint32_t time)  { return {}; };
		virtual bool CanChangeScope() { return {}; };
		virtual void PrepareData(datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player) {};
		virtual void HandleData(datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player) {};
		virtual bool Decide(netPlayer* source_player, netPlayer* target_player) { return false; };
		virtual void PrepareReply(datBitBuffer* buffer, netPlayer* reply_player) {};
		virtual void HandleReply(datBitBuffer* buffer, netPlayer* souce_player) {};
		virtual void PrepareExtraData(datBitBuffer* buffer, bool is_reply, netPlayer* player, netPlayer* player2) {};
		virtual void HandleExtraData(datBitBuffer* buffer, bool is_reply, netPlayer* player, netPlayer* player2) {};

	private:
		virtual void unk_0x60() {};
		virtual void unk_0x68() {};
		virtual void unk_0x70() {};
		virtual void unk_0x78() {};

	public:
		virtual bool operator==(netGameEvent const& other) { return {}; };
		virtual bool operator!=(netGameEvent const& other) { return {}; };

		virtual bool MustPersist() { return {}; };
		virtual bool MustPersistWhenOutOfScope() { return {}; };
		virtual bool HasTimedOut() { return {}; };

	public:
		Type m_Type;          // 0x08
		bool m_RequiresReply; // 0x0A
	private:
		char m_padding1[0x05]; // 0x0B
	public:
		netPlayer* m_SourcePlayer; // 0x10
		netPlayer* m_TargetPlayer; // 0x18
		uint32_t m_ResendTime;     // 0x20
	private:
		uint16_t m_0x24; // 0x24
		uint8_t m_0x26;  // 0x26
		uint8_t m_0x27;  // 0x27
		uint32_t m_0x28; // 0x28
	};
	static_assert(sizeof(rage::netGameEvent) == 0x30);
}

class CScriptedGameEvent : public rage::netGameEvent
{
public:
	bool Deserialize(rage::datBitBuffer& buffer);

	char m_padding[0x40]; // 0x30
	int64_t m_Args[54];   // 0x70
	uint32_t m_Bitset;    // 0x220
	uint32_t m_ArgsSize;  // 0x224
};

class CNetworkIncrementStatEvent : public rage::netGameEvent
{
public:
	void Deserialize(rage::datBitBuffer& buffer);

	uint32_t m_Stat;   // 0x30
	uint32_t m_Amount; // 0x34
};

class CDoorBreakEvent : public rage::netGameEvent
{
public:
	void Deserialize(rage::datBitBuffer& buffer);

	uint16_t m_VehicleId; // 0x30
	uint8_t m_DoorId;     // 0x32
};

class CPlaySoundEvent : public rage::netGameEvent
{
public:
	void Deserialize(rage::datBitBuffer& buffer);

	bool m_IsEntity;           // 0x30
	uint16_t m_EntityId;       // 0x32
	rage::fvector3 m_Position; // 0x40
	uint32_t m_RefHash;        // 0x50
	uint32_t m_SoundHash;      // 0x54
	uint8_t m_SoundId;         // 0x58
	CGameScriptId m_ScriptId;  // 0x60
	int m_0xA0;                // 0xA0
};

class CWeaponDamageEvent : public rage::netGameEvent
{
public:
	void Deserialize(rage::datBitBuffer& buffer);

	rage::fvector3 m_LocalPos;      // 0x30
	rage::fvector3 m_ImpactDir;     // 0x40
	uint32_t m_DamageFlags;         // 0x50
	uint32_t m_WeaponType;          // 0x54
	uint32_t m_WeaponDamage;        // 0x58
	uint8_t m_0x5C;                 // 0x5C
	uint32_t m_0x60;                // 0x60
	uint32_t m_DamageTime;          // 0x64
	uint32_t m_ActionResultName;    // 0x68
	uint32_t m_0x6C;                // 0x6C
	int m_HitComponent;             // 0x70
	uint16_t m_0x74;                // 0x74
	int16_t m_0x76;                 // 0x76
	uint16_t m_ActionResultId;      // 0x78
	uint16_t m_ParentGlobalId;      // 0x7A Source entity?
	uint16_t m_HitGlobalId;         // 0x7C Target entity?
	uint8_t m_TyreIndex;            // 0x7E
	uint8_t m_SuspensionIndex;      // 0x7F
	uint8_t m_DamageType;           // 0x80
	bool m_HasImpactDir;            // 0x81
	bool m_HitEntityWeapon;         // 0x82
	bool m_HitWeaponAmmoAttachment; // 0x83
	bool m_Silenced;                // 0x84
	bool m_WillKill;                // 0x85
	bool m_0x86;                    // 0x86
	bool m_0x87;                    // 0x87
	bool m_OverrideDefaultDamage;   // 0x88
	bool m_0x89;                    // 0x89
	bool m_0x8A;                    // 0x8A
	bool m_IsNetTargetPos;          // 0x8B
	bool m_0x8C;                    // 0x8C
	uint32_t m_Time;                // 0x90
	uint8_t m_0x94;                 // 0x94
};

class CActivateVehicleSpecialAbilityEvent : public rage::netGameEvent
{
public:
	void Deserialize(rage::datBitBuffer& buffer);

	uint16_t m_VehicleId;   // 0x30
	uint32_t m_AbilityType; // 0x34
	uint32_t m_Time;        // 0x38
};

enum class ExplosionType;
class CExplosionEvent : public rage::netGameEvent
{
public:
	void Deserialize(rage::datBitBuffer& buffer);

	struct
	{
		ExplosionType m_ExplosionType; // 0x30
		rage::fvector3 m_Position;     // 0x40
		uint64_t m_0x50;               // 0x50
		uint64_t m_0x58;               // 0x58
		uint64_t m_0x60;               // 0x60
		uint32_t m_0x68;               // 0x68
		float m_DamageScale;           // 0x6C
		uint32_t m_0x70;               // 0x70
		float m_CameraShake;           // 0x74
		float m_0x78;                  // 0x78
		bool m_IsAudible;              // 0x7C
		bool m_IsInvisible;            // 0x7D
		bool m_0x7E;                   // 0x7E
		rage::fvector3 m_0x80;         // 0x80
		uint64_t m_0x90;               // 0x90
		int m_0x98;                    // 0x98
		int m_0x9C;                    // 0x9C
		uint32_t m_0xA0;               // 0xA0
		uint32_t m_0xA4;               // 0xA4
		uint32_t m_InteriorIndex;      // 0xA8
		uint64_t m_0xB0;               // 0xB0
		uint8_t m_0xB8;                // 0xB8
		uint16_t m_0xBA;               // 0xBA
		bool m_0xBC;                   // 0xBC
		bool m_0xBD;                   // 0xBD
		bool m_0xBE;                   // 0xBE
		bool m_0xBF;                   // 0xBF
		bool m_0xC0;                   // 0xC0
		bool m_AddOwnedExplosion;      // 0xC1
		bool m_Expected;               // 0xC2 -- for telemetry
		uint32_t m_ScriptHash;         // 0xC4 -- for telemetry
		uint32_t m_ProgramCounter;     // 0xC8 -- for telemetry
	};
	uint16_t m_TargetEntity;      // 0xD0
	uint16_t m_TargetEnt2;        // 0xD2
	uint16_t m_OwnerNetId;        // 0xD4
	uint16_t m_UnkNetId;          // 0xD6
	uint8_t m_0xD8;               // 0xD8
	uint16_t m_0xDA;              // 0xDA
	rage::fvector3 m_PositionUnk; // 0xE0
	bool m_0xF0;                  // 0xF0
	bool m_0xF1;                  // 0xF1
	bool m_0xF2;                  // 0xF2
	bool m_HasTargetEnt2;         // 0xF3
	bool m_0xF4;                  // 0xF4
	uint32_t m_Time;              // 0xF8
};

class CScriptEntityStateChangeEvent
{
public:
	enum class Type : uint32_t
	{
		BlockingOfNonTemporaryEvents,
		SettingOfPedRelationshipGroupHash,
		SettingOfDriveTaskCruiseSpeed,
		SettingOfLookAtEntity,
		SettingOfPlaneMinHeightAboveTerrain,
		SetPedRagdollBlockFlag,
		SettingOfTaskVehicleTempAction,
		SetPedFacialIdleAnimOverride,
		SetVehicleLockState,
		SetVehicleExclusiveDriver
	};
};

class CScriptWorldStateEvent
{
public:
	enum class Type : uint32_t
	{
		CarGen,
		EntityArea,
		PopGroupOverride,
		PopMultiplierArea,
		PTFX,
		RoadNode,
		Rope,
		ScenarioBlockingArea,
		VehiclePlayerLocking
	};
};

class CUpdateFxnEvent : public rage::netGameEvent
{
public:
	void Deserialize(rage::datBitBuffer& buffer);

	uint32_t m_0x30; // 0x30
	uint32_t m_0x34; // 0x34
};

class CRagdollRequestEvent : public rage::netGameEvent
{
public:
	void Deserialize(rage::datBitBuffer& buffer);

	uint16_t m_PedToRagdoll; // 0x30
};