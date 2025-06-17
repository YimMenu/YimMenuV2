#include "core/commands/LoopedCommand.hpp"
#include "core/commands/Commands.hpp"
#include "core/util/Joaat.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/network/CNetGamePlayer.hpp"
#include "types/network/netGameEvent.hpp"
#include "types/rage/datBitBuffer.hpp"
#include "types/script/globals/GlobalPlayerBD.hpp"

namespace YimMenu::Hooks
{
	static void SendEventAck(rage::netEventMgr* event_mgr, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint32_t event_index, uint32_t event_handled_bits)
	{
		if (source_player->m_PlayerIndex != 255 && !Pointers.EventAck(0x778LL * source_player->m_PlayerIndex + (intptr_t)event_mgr + 0x2C408, target_player, event_index, event_handled_bits))
		{
			Pointers.SendEventAck(event_mgr, source_player);
			Pointers.EventAck((intptr_t)event_mgr + 0x2C408 + 0x778LL * source_player->m_PlayerIndex, target_player, event_index, event_handled_bits);
		}

		*reinterpret_cast<std::uint32_t*>(0x118LL * event_index + (uint64_t)event_mgr + 4 * source_player->m_PlayerIndex + 0x458) = event_handled_bits;
	}

	// Returns true if bad event
	static bool ScanExplosionEvent(CExplosionEvent& event, Player player)
	{
		if (*(int16_t*)&event.m_InteriorIndex < -1)
		{
			LOG(INFO) << "blocked invalid interior crash from " << player.GetName();
			return true;
		}

		if (event.m_IsInvisible)
		{
			float dist = event.m_Position.GetDistance(Self::GetPed().GetPosition());
			if (event.m_CameraShake > 0.0f && dist <= 30.0f)
			{
				// Camera shake
				LOGF(WARNING, "Blocked EXPLOSION_EVENT from {} since m_CameraShake > 0.0f", player.GetName());
				return true;
			}

			if (event.m_DamageScale > 0.0f && dist <= 10.0f)
			{
				// Ragdoll
				LOGF(WARNING, "Blocked EXPLOSION_EVENT from {} since m_DamageScale > 0.0f", player.GetName());
				return true;
			}
		}

		// more?

		return false;
	}

	static bool ScanPlaySoundEvent(CPlaySoundEvent& event, Player player)
	{
		static constexpr std::array blocked_ref_hashes = {"Arena_Vehicle_Mod_Shop_Sounds"_J, "CELEBRATION_SOUNDSET"_J, "DLC_AW_Arena_Office_Planning_Wall_Sounds"_J, "DLC_AW_Arena_Spin_Wheel_Game_Frontend_Sounds"_J, "DLC_Biker_SYG_Sounds"_J, "DLC_BTL_SECURITY_VANS_RADAR_PING_SOUNDS"_J, "DLC_BTL_Target_Pursuit_Sounds"_J, "DLC_GR_Bunker_Door_Sounds"_J, "DLC_GR_CS2_Sounds"_J, "DLC_IO_Warehouse_Mod_Garage_Sounds"_J, "DLC_MPSUM2_HSW_Up_Sounds"_J, "DLC_sum20_Business_Battle_AC_Sounds"_J, "DLC_TG_Running_Back_Sounds"_J, "dlc_vw_table_games_frontend_sounds"_J, "dlc_xm_facility_entry_exit_sounds"_J, "Frontend"_J, "GTAO_Boss_Goons_FM_Soundset"_J, "GTAO_Exec_SecuroServ_Computer_Sounds"_J, "GTAO_Exec_SecuroServ_Warehouse_PC_Sounds"_J, "GTAO_Script_Doors_Faded_Screen_Sounds"_J, "GTAO_SMG_Hangar_Computer_Sounds"_J, "HUD_AMMO_SHOP_SOUNDSET"_J, "HUD_FRONTEND_CUSTOM_SOUNDSET"_J, "HUD_FRONTEND_DEFAULT_SOUNDSET"_J, "HUD_FRONTEND_MP_SOUNDSET"_J, "HUD_FRONTEND_MP_COLLECTABLE_SOUNDS"_J, "HUD_FRONTEND_TATTOO_SHOP_SOUNDSET"_J, "HUD_FRONTEND_CLOTHESSHOP_SOUNDSET"_J, "HUD_FRONTEND_STANDARD_PICKUPS_NPC_SOUNDSET"_J, "HUD_FRONTEND_VEHICLE_PICKUPS_NPC_SOUNDSET"_J, "HUD_FRONTEND_WEAPONS_PICKUPS_NPC_SOUNDSET"_J, "HUD_FREEMODE_SOUNDSET"_J, "HUD_MINI_GAME_SOUNDSET"_J, "HUD_AWARDS"_J, "JA16_Super_Mod_Garage_Sounds"_J, "Low2_Super_Mod_Garage_Sounds"_J, "MissionFailedSounds"_J, "MP_CCTV_SOUNDSET"_J, "MP_LOBBY_SOUNDS"_J, "MP_MISSION_COUNTDOWN_SOUNDSET"_J, "Phone_SoundSet_Default"_J, "Phone_SoundSet_Glasses_Cam"_J, "Phone_SoundSet_Prologue"_J, "Phone_SoundSet_Franklin"_J, "Phone_SoundSet_Michael"_J, "Phone_SoundSet_Trevor"_J, "PLAYER_SWITCH_CUSTOM_SOUNDSET"_J, "RESPAWN_ONLINE_SOUNDSET"_J, "TATTOOIST_SOUNDS"_J, "WastedSounds"_J, "WEB_NAVIGATION_SOUNDS_PHONE"_J};
		static constexpr std::array blocked_sound_hashes = {"Remote_Ring"_J, "COP_HELI_CAM_ZOOM"_J, "Object_Dropped_Remote"_J};
		static constexpr std::array blocked_script_hashes = {"main_persistent"_J, "shop_controller"_J};

		if (std::ranges::contains(blocked_ref_hashes, event.m_RefHash)
		    || std::ranges::contains(blocked_sound_hashes, event.m_SoundHash)
		    || std::ranges::contains(blocked_script_hashes, event.m_ScriptId.m_Hash))
			return true;

		switch (event.m_SoundHash)
		{
		case "DLC_XM_Explosions_Orbital_Cannon"_J:
		{
			if (event.m_IsEntity)
				return true;

			if (event.m_ScriptId.m_Hash != "am_mp_defunct_base"_J && event.m_ScriptId.m_Hash != "am_mp_orbital_cannon"_J
			    && event.m_ScriptId.m_Hash != "fm_mission_controller_2020"_J && event.m_ScriptId.m_Hash != "fm_mission_controller"_J)
				return true;

			if (!GlobalPlayerBD::Get()->Entries[player.GetId()].OrbitalBitset.IsSet(eOrbitalBitset::kOrbitalCannonActive))
				return true;

			break;
		}
		}

		switch (event.m_RefHash)
		{
		case "GTAO_Biker_Modes_Soundset"_J:
		case "DLC_Biker_Sell_Postman_Sounds"_J:
		{
			if (event.m_IsEntity)
				return true;

			if (event.m_ScriptId.m_Hash != "gb_biker_contraband_sell"_J)
				return true;

			break;
		}
		case "DLC_AW_General_Sounds"_J:
		{
			if (event.m_SoundHash != "Airhorn_Blast_Long"_J)
				return true;

			if (event.m_ScriptId.m_Hash != "gb_casino_heist"_J)
				return true;

			break;
		}
		case "GTAO_FM_Events_Soundset"_J:
		{
			if (!event.m_IsEntity)
				return true;

			if (event.m_SoundHash != "Explosion_Countdown"_J)
				return true;

			break;
		}
		}

		return false;
	}

	bool ShouldAllowNetEvent(Player player, uint16_t event_id, rage::datBitBuffer& buffer)
	{
		switch (static_cast<rage::netGameEvent::Type>(event_id))
		{
		case rage::netGameEvent::Type::REQUEST_CONTROL_EVENT:
		{
			// TODO
			break;
		}
		case rage::netGameEvent::Type::WEAPON_DAMAGE_EVENT:
		{
			CWeaponDamageEvent event;
			event.Deserialize(buffer);

			if (event.m_WeaponType == "WEAPON_TRANQUILIZER"_J)
			{
				LOGF(WARNING, "Blocked WEAPON_DAMAGE_EVENT from {} with m_WeaponType == WEAPON_TRANQUILIZER", player.GetName());
				return false;
			}

			break;
		}
		case rage::netGameEvent::Type::EXPLOSION_EVENT:
		{
			CExplosionEvent event;
			event.Deserialize(buffer);

			if (ScanExplosionEvent(event, player))
			{
				return false;
			}

			break;
		}
		case rage::netGameEvent::Type::CHANGE_RADIO_STATION_EVENT:
		{
			uint16_t veh_id = buffer.Read<uint16_t>(13);

			Vehicle self_veh = Self::GetVehicle();
			Vehicle sender_veh = player.GetPed().GetVehicle();

			if (self_veh && self_veh.GetNetworkObjectId() == veh_id && sender_veh && sender_veh.GetNetworkObjectId() != veh_id)
			{
				// Vehicle takeover
				LOGF(WARNING, "Blocked CHANGE_RADIO_STATION_EVENT on our local vehicle from {}", player.GetName());
				return false;
			}

			break;
		}
		case rage::netGameEvent::Type::DOOR_BREAK_EVENT:
		{
			// never used for legitimate reasons
			LOGF(WARNING, "Blocked DOOR_BREAK_EVENT from {}", player.GetName());
			return false;
		}
		case rage::netGameEvent::Type::SCRIPTED_GAME_EVENT:
		{
			CScriptedGameEvent event;

			if (!event.Deserialize(buffer))
				return false;

			if (!Network::HandleScriptedGameEvent(player, event))
				return false;

			break;
		}
		case rage::netGameEvent::Type::SCRIPT_WORLD_STATE_EVENT:
		{
			auto type = buffer.Read<CScriptWorldStateEvent::Type>(4);
			buffer.Read<bool>(1);
			CGameScriptId id;
			id.Deserialize(buffer);

			if (type == CScriptWorldStateEvent::Type::PopGroupOverride)
			{
				int pop_schedule = buffer.Read<int>(8);
				int pop_group = buffer.Read<int>(32);
				int percentage = buffer.Read<int>(7);

				if (pop_group == 0 && (percentage == 0 || percentage == 103))
				{
					// pop group override crash
					LOGF(WARNING, "Blocked SCRIPT_WORLD_STATE_EVENT of type PopGroupOverride with invalid params from {}", player.GetName());
					return false;
				}
			}
			else if (type == CScriptWorldStateEvent::Type::PopMultiplierArea && !NETWORK::NETWORK_IS_ACTIVITY_SESSION())
			{
				// Stop traffic
				LOGF(WARNING, "Blocked SCRIPT_WORLD_STATE_EVENT of type PopMultiplierArea from {}", player.GetName());
				return false;
			}

			break;
		}
		case rage::netGameEvent::Type::SCRIPT_ENTITY_STATE_CHANGE_EVENT:
		{
			uint16_t entity = buffer.Read<uint16_t>(13);
			auto type = buffer.Read<CScriptEntityStateChangeEvent::Type>(4);
			uint32_t unk = buffer.Read<uint32_t>(32);

			if (type == CScriptEntityStateChangeEvent::Type::SettingOfTaskVehicleTempAction)
			{
				uint16_t veh_id = buffer.Read<uint16_t>(13);
				uint32_t action = buffer.Read<uint32_t>(8);

				if (action >= 15 && action <= 18)
				{
					// vehicle temp action crash
					LOGF(WARNING, "Blocked SCRIPT_ENTITY_STATE_CHANGE_EVENT of type SettingOfTaskVehicleTempAction with invalid params from {}", player.GetName());
					return false;
				}

				if (Self::GetPed().GetNetworkObjectId() == entity)
				{
					// Ped takeover
					LOGF(WARNING, "Blocked SCRIPT_ENTITY_STATE_CHANGE_EVENT of type SettingOfTaskVehicleTempAction on our local ped from {}", player.GetName());
					return false;
				}

				Vehicle self_veh = Self::GetVehicle();
				if (self_veh && self_veh.GetNetworkObjectId() == veh_id)
				{
					// Vehicle takeover
					LOGF(WARNING, "Blocked SCRIPT_ENTITY_STATE_CHANGE_EVENT of type SettingOfTaskVehicleTempAction on our local vehicle from {}", player.GetName());
					return false;
				}
			}
			else if (type == CScriptEntityStateChangeEvent::Type::SetVehicleLockState)
			{
				Vehicle self_veh = Self::GetVehicle();
				if (self_veh && self_veh.GetNetworkObjectId() == entity)
				{
					LOGF(WARNING, "Blocked SCRIPT_ENTITY_STATE_CHANGE_EVENT of type SetVehicleLockState from {} on our local vehicle", player.GetName());
					return false;
				}
			}
			else if (type == CScriptEntityStateChangeEvent::Type::SetVehicleExclusiveDriver)
			{
				Vehicle self_veh = Self::GetVehicle();
				if (self_veh && self_veh.GetNetworkObjectId() == entity)
				{
					// Vehicle kick
					LOGF(WARNING, "Blocked SCRIPT_ENTITY_STATE_CHANGE_EVENT of type SetVehicleExclusiveDriver from {} on our local vehicle", player.GetName());
					return false;
				}
			}
			else if (type == CScriptEntityStateChangeEvent::Type::SetPedFacialIdleAnimOverride)
			{
				if (Self::GetPed().GetNetworkObjectId() == entity)
				{
					LOGF(WARNING, "Blocked SCRIPT_ENTITY_STATE_CHANGE_EVENT of type SetPedFacialIdleAnimOverride from {} on our local player", player.GetName());
					return false;
				}
			}
			else if (type > CScriptEntityStateChangeEvent::Type::SetVehicleExclusiveDriver)
			{
				// invalid script entity change type crash
				return false;
			}

			break;
		}
		case rage::netGameEvent::Type::NETWORK_PLAY_SOUND_EVENT:
		{
			CPlaySoundEvent event;
			event.Deserialize(buffer);

			if (ScanPlaySoundEvent(event, player))
			{
				LOGF(WARNING, "Blocked NETWORK_PLAY_SOUND_EVENT from {} with IsEntity: {}, RefHash: {:X}, SoundHash: {:X}, SoundId: {}, ScriptHash: {:X}", player.GetName(), event.m_IsEntity, event.m_RefHash, event.m_SoundHash, event.m_SoundId, event.m_ScriptId.m_Hash);
				return false;
			}

			break;
		}
		case rage::netGameEvent::Type::REPORT_MYSELF_EVENT:
		{
			CUpdateFxnEvent event;
			event.Deserialize(buffer);

			if (event.m_0x30 != 6) // false positives when telemetry endpoint is unreachable
			{
				// Triggered anti cheat
			}

			static auto cheaterPool = Commands::GetCommand<LoopedCommand>("cheaterpool"_J);

			if (cheaterPool->GetState())
			{
				LOGF(WARNING, "Blocked REPORT_MYSELF_EVENT from {} with type {} since we're in a cheater-only session", player.GetName(), event.m_0x30);
				return false;
			}

			break;
		}
		case rage::netGameEvent::Type::ACTIVATE_VEHICLE_SPECIAL_ABILITY_EVENT:
		{
			CActivateVehicleSpecialAbilityEvent event;
			event.Deserialize(buffer);

			if (Self::GetPed().GetVehicleObjectId() == event.m_VehicleId && !Self::GetVehicle().IsRemote())
			{
				// Vehicle takeover
				LOGF(WARNING, "Blocked ACTIVATE_VEHICLE_SPECIAL_ABILITY_EVENT on our local vehicle from {}", player.GetName());
				return false;
			}

			break;
		}
		case rage::netGameEvent::Type::RAGDOLL_REQUEST_EVENT:
		{
			CRagdollRequestEvent event;
			event.Deserialize(buffer);

			if (Self::GetPed().GetNetworkObjectId() == event.m_PedToRagdoll)
			{
				// is sometimes used legit, beware
				LOGF(WARNING, "Blocked RAGDOLL_REQUEST_EVENT on our local ped from {}", player.GetName());
				return false;
			}

			break;
		}
		default:
			break;
		}

		return true;
	}

	void Network::ReceiveNetGameEvent(Player player, uint16_t event_id, uint32_t event_index, uint32_t event_handled_bits, rage::datBitBuffer& buffer)
	{
		if (!ShouldAllowNetEvent(player, event_id, buffer))
			SendEventAck(*Pointers.NetEventMgr, player.GetHandle(), Self::GetPlayer().GetHandle(), event_index, event_handled_bits);
	}
}