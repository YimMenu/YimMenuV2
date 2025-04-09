#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/Natives.hpp"
#include "game/backend/Self.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/gta/data/Weapons.hpp"
#include "core/util/Joaat.hpp"
#include "types/ped/PedConfigFlag.hpp"

namespace YimMenu::Features
{
	class UnlockAll : public Command
	{
		using Command::Command;

        void loopBool(int from, int to)  
        {
            for (int i = from; i < to; i++)
            {
                Stats::SetPackedBool(i, true);
            }
        }

		void unlockWeapons()
		{
			for (auto weapon : Data::Weapons)
			{
				Self::GetPed().GiveWeapon(weapon);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(Self::GetPed().GetHandle(), weapon, 7);
			}

			Stats::SetInt("MPX_CHAR_WEAPON_FM_PURCHASE", -1);
			Stats::SetInt("MPX_CHAR_WEAPON_FM_PURCHASE_2", -1);
			Stats::SetInt("MPX_CHAR_WEAPON_FM_PURCHASE_3", -1);
			Stats::SetInt("MPX_CHAR_WEAPON_FM_PURCHASE_4", -1);
			Stats::SetInt("MPX_CHAR_FM_WEAP_ADDON_1_UNLCK", -1);
			Stats::SetInt("MPX_CHAR_FM_WEAP_ADDON_2_UNLCK", -1);
			Stats::SetInt("MPX_CHAR_FM_WEAP_ADDON_3_UNLCK", -1);
			Stats::SetInt("MPX_CHAR_FM_WEAP_ADDON_4_UNLCK", -1);
			Stats::SetInt("MPX_CHAR_FM_WEAP_ADDON_5_UNLCK", -1);
			Stats::SetInt("MPX_CHAR_FM_WEAP_UNLOCKED", -1);
			Stats::SetInt("MPX_CHAR_FM_WEAP_UNLOCKED2", -1);
			Stats::SetInt("MPX_CHAR_WEAP_FM_PURCHASE", -1);
			Stats::SetInt("MPX_CHAR_WEAP_FM_PURCHASE2", -1);
			Stats::SetInt("MPX_CHAR_FM_WEAP_ADDON_PURCH", -1);
			Stats::SetInt("MPX_CHAR_FM_WEAP_ADDON_PURCH2", -1);
			Stats::SetInt("MPX_CHAR_FM_WEAP_ADDON_PURCH3", -1);
			Stats::SetInt("MPX_CHAR_FM_WEAP_ADDON_PURCH4", -1);
			Stats::SetInt("MPX_CHAR_FM_WEAP_ADDON_PURCH5", -1);

			Stats::SetInt("MPX_REV_NV_KILLS", 50);
			
			loopBool(15425, 15439);
			loopBool(51189, 51189);
			loopBool(51196, 51197);
		}

		void unlockVehicles()
		{
			Stats::SetInt("MPX_CHAR_FM_CARMOD_1_UNLCK", -1);
			Stats::SetInt("MPX_CHAR_FM_CARMOD_2_UNLCK", -1);
			Stats::SetInt("MPX_CHAR_FM_CARMOD_3_UNLCK", -1);
			Stats::SetInt("MPX_CHAR_FM_CARMOD_4_UNLCK", -1);
			Stats::SetInt("MPX_CHAR_FM_CARMOD_5_UNLCK", -1);
			Stats::SetInt("MPX_CHAR_FM_CARMOD_6_UNLCK", -1);
			Stats::SetInt("MPX_CHAR_FM_CARMOD_7_UNLCK", -1);
			Stats::SetInt("MPX_CHAR_FM_VEHICLE_1_UNLCK", -1);
			Stats::SetInt("MPX_CHAR_FM_VEHICLE_2_UNLCK", -1);
			
			Stats::SetInt("MPX_AWD_FMRALLYWONDRIVE", 1);
			Stats::SetInt("MPX_AWD_FMRALLYWONNAV", 1);
			Stats::SetInt("MPX_AWD_FMWINSEARACE", 1);
			Stats::SetInt("MPX_AWD_FMWINAIRRACE", 1);
			Stats::SetInt("MPX_NUMBER_TURBO_STARTS_IN_RACE", 50);
			Stats::SetInt("MPX_NUMBER_SLIPSTREAMS_IN_RACE", 100);
			Stats::SetInt("MPX_AWD_FM_RACES_FASTEST_LAP", 50);
			Stats::SetInt("MPX_USJS_COMPLETED", 50);
			Stats::SetInt("MPX_USJS_FOUND", 50);
			Stats::SetInt("MPX_USJS_TOTAL_COMPLETED", 50);
			Stats::SetInt("MPX_AWD_FMHORDWAVESSURVIVE", 10);
			Stats::SetInt("MPX_AWD_CAR_BOMBS_ENEMY_KILLS", 25);
			Stats::SetInt("MPX_AWD_FMBBETWIN", 50000);
			Stats::SetInt("MPX_AWD_FMWINEVERYGAMEMODE", 1);
			Stats::SetInt("MPX_AWD_FMRACEWORLDRECHOLDER", 1);
			Stats::SetInt("MPX_AWD_FMMOSTKILLSSURVIVE", 1);
			Stats::SetInt("MPX_AWD_FMKILL3ANDWINGTARACE", 1);
			Stats::SetInt("MPX_AWD_FMDRIVEWITHOUTCRASHING", 30);
			Stats::SetInt("MPX_CAR_EXPORT", 50);

			loopBool(25407, 25511);
			loopBool(25516, 25516);
			loopBool(25520, 25521);
			
			Stats::SetInt("MPX_XM22_FLOW", -1); 
			Stats::SetInt("MPX_XM22_MISSIONS", -1);
			Stats::SetInt("MPX_AWD_CALLME", 50);
		}

		void unlockAchievements()
		{
			Stats::SetInt("MPX_AWD_FMPICKUPDLCCRATE1ST", 1);
			Stats::SetInt("MPX_AWD_FMSHOOTDOWNCOPHELI", 1);
			Stats::SetInt("MPX_AWD_FMKILLSTREAKSDM", 1);
			Stats::SetInt("MPX_AWD_FMMOSTRECOVERIES", 1);
			Stats::SetInt("MPX_AWD_FMFURTHESTWHEELIE", 500);
			Stats::SetInt("MPX_AWD_FMFULLYMODDEDCAR", 1);
			Stats::SetInt("MPX_AWD_ENEMYDRIVEBYKILLS", 10);
			Stats::SetInt("MPX_PLAYER_HEADSHOTS", 500);
			Stats::SetInt("MPX_DB_PLAYER_KILLS", 1000);
			Stats::SetInt("MPX_AWD_FMRACESWON", 50);
			Stats::SetInt("MPX_AWD_FMRACEWONBY1SEC", 25);
			Stats::SetInt("MPX_AWD_FMWONALLCTF", 25);
			Stats::SetInt("MPX_AWD_FMWINALLGAMEMODES", 1);
			Stats::SetInt("MPX_AWD_FMTATTOOALLBODYPARTS", 1);
			
			Stats::SetInt("MPX_AWD_HOLD_UP_SHOPS", 20);
			Stats::SetInt("MPX_AWD_LAPDANCES", 25);
			Stats::SetInt("MPX_AWD_SECURITY_CARS_ROBBED", 25);
			Stats::SetInt("MPX_AWD_CAR_EXPORT", 50);
			Stats::SetInt("MPX_AWD_KILLS_PLAYERS", 1000);
			Stats::SetInt("MPX_AWD_CARS_EXPORTED", 50);
			
			loopBool(26811, 26964);
			loopBool(30230, 30251);
		}

		void unlockHeists()
		{
			Stats::SetInt("MPX_HEIST_SAVED_STRAND_0_L", 5);
			Stats::SetInt("MPX_HEIST_SAVED_STRAND_1_L", 5);
			Stats::SetInt("MPX_HEIST_SAVED_STRAND_2_L", 5);
			Stats::SetInt("MPX_HEIST_SAVED_STRAND_3_L", 5);
			Stats::SetInt("MPX_HEIST_SAVED_STRAND_4_L", 5);
			Stats::SetBool("MPX_UNLOCKED_MESSAGE_FLEECA", true);
			
			Stats::SetInt("MPX_GANGOPS_FLOW_PASSED_BITSET", -1);
			Stats::SetInt("MPX_VCM_FLOW_PROGRESS", -1);
			Stats::SetInt("MPX_TUNER_FLOW_BS", -1);
			Stats::SetInt("MPX_TUNER_MIS_BS", -1);
			Stats::SetInt("MPX_TUNER_COMP_BS", -1);
			Stats::SetInt("MPX_GANGOPS_FM_MISSION_PROG", -1);
			Stats::SetInt("MPX_GANGOPS_FM_BITSET_MISS0", -1);
			
			Stats::SetInt("MPX_AWD_FINISH_HEIST_NO_DAMAGE", 1);
			Stats::SetInt("MPX_AWD_SPLIT_HEIST_TAKE_EVENLY", 1);
			Stats::SetInt("MPX_AWD_COMPLETE_HEIST_NOT_DIE", 1);
			Stats::SetInt("MPX_HEIST_ULT_CHALLENGE", 1);
			
			Stats::SetInt("MPX_H4_PROGRESS", 131055);
			Stats::SetInt("MPX_H4_MISSIONS", 65535);
			Stats::SetInt("MPX_H4CNF_BS_GEN", 131071);
			Stats::SetInt("MPX_H4CNF_BS_ENTR", 63);
			Stats::SetInt("MPX_H4CNF_WEAPONS", 5);
			Stats::SetInt("MPX_H4CNF_TARGET", 5);
			Stats::SetInt("MPX_H4LOOT_GOLD_C", -1);
			Stats::SetInt("MPX_H4LOOT_GOLD_C_SCOPED", -1);
			
			Stats::SetInt("MPX_CAS_HEIST_FLOW", -1);
			Stats::SetInt("MPX_H3_BOARD_DIALOGUE0", -1);
			Stats::SetInt("MPX_H3_BOARDROOM_ACCESS", -1);
			Stats::SetInt("MPX_H3OPT_ACCESSPOINTS", -1);
			Stats::SetInt("MPX_H3OPT_POI", -1);
			Stats::SetInt("MPX_H3_VEHICLESUSED", -1);
			
			Stats::SetInt("MPX_GANGOPS_FLOW", -1);
			Stats::SetInt("MPX_GANGOPS_HEIST_STATUS", -229384);
			Stats::SetInt("MPX_GANGOPS_FLOW_MISSION_PROG", -1);
		}

		void unlockCharacterStats()
		{
            Stats::SetInt("MPX_SCRIPT_INCREASE_STAM", 100);
            Stats::SetInt("MPX_SCRIPT_INCREASE_STRN", 100);
            Stats::SetInt("MPX_SCRIPT_INCREASE_LUNG", 100);
            Stats::SetInt("MPX_SCRIPT_INCREASE_DRIV", 100);
            Stats::SetInt("MPX_SCRIPT_INCREASE_FLY", 100);
            Stats::SetInt("MPX_SCRIPT_INCREASE_SHO", 100);
            Stats::SetInt("MPX_SCRIPT_INCREASE_STL", 100);
            Stats::SetInt("MPX_SCRIPT_INCREASE_MECH", 100);
            
            Stats::SetInt("MPX_STEALTH_KILLS", 100);
            Stats::SetInt("MPX_KILLS_PLAYERS", 1000);
            Stats::SetInt("MPX_KILLS_STEALTH", 100);
            Stats::SetInt("MPX_SHOTS", 1000);
            Stats::SetInt("MPX_HITS", 1000);
            Stats::SetInt("MPX_HEADSHOTS", 500);
            Stats::SetInt("MPX_KILLS", 1000);
            Stats::SetInt("MPX_CHARS_EXPLODED_DEATHS", 1000);
            Stats::SetInt("MPX_DEATH_RUNOVER", 1000);
            Stats::SetInt("MPX_DEATHS", 1000);
            Stats::SetInt("MPX_HITS_PEDS_VEHICLES", 1000);
            Stats::SetInt("MPX_SHOTS_PEDS_VEHICLES", 1000);
            Stats::SetInt("MPX_STARS_ATTAINED", 1000);
            Stats::SetInt("MPX_STARS_EVADED", 1000);
		}

		void fillInventory()
		{
			Stats::SetInt("MPX_NO_BOUGHT_YUM_SNACKS", 30);
			Stats::SetInt("MPX_NO_BOUGHT_HEALTH_SNACKS", 15);
			Stats::SetInt("MPX_NO_BOUGHT_EPIC_SNACKS", 5);
			Stats::SetInt("MPX_NUMBER_OF_CHAMP_BOUGHT", 5);
			Stats::SetInt("MPX_NUMBER_OF_ORANGE_BOUGHT", 10);
			Stats::SetInt("MPX_NUMBER_OF_BOURGE_BOUGHT", 10);
			Stats::SetInt("MPX_NUMBER_OF_SPRUNK_BOUGHT", 10);
			Stats::SetInt("MPX_MP_CHAR_ARMOUR_1_COUNT", 10);
			Stats::SetInt("MPX_MP_CHAR_ARMOUR_2_COUNT", 10);
			Stats::SetInt("MPX_MP_CHAR_ARMOUR_3_COUNT", 10);
			Stats::SetInt("MPX_MP_CHAR_ARMOUR_4_COUNT", 10);
			Stats::SetInt("MPX_MP_CHAR_ARMOUR_5_COUNT", 10);
			Stats::SetInt("MPX_CIGARETTES_BOUGHT", 20);
			Stats::SetInt("MPX_BREATHING_APPAR_BOUGHT", 20);
		}

		void unlockClothesHairstyles()
		{
			Stats::SetInt("MPX_CLTHS_AVAILABLE_FEET", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_HAIR", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_JBIB", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_LEGS", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_TEETH", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_TORSO", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_SPECIAL", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_SPECIAL2", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_SPECIAL3", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_SPECIAL4", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_WATCHES", -1);
			
			Stats::SetInt("MPX_CLTHS_AVAILABLE_HAIR_1", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_HAIR_2", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_HAIR_3", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_HAIR_4", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_HAIR_5", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_HAIR_6", -1);
			Stats::SetInt("MPX_CLTHS_AVAILABLE_HAIR_7", -1);
			
			loopBool(4247, 4269);
			loopBool(31760, 31764);
			loopBool(31766, 31777);
			loopBool(28254, 28255);
			loopBool(42286, 42287);
			
			Stats::SetBool("MPX_BS_IMANI_D_APP_HOOD", true);
			Stats::SetBool("MPX_BS_IMANI_D_APP_HOOD_2", true);
			Stats::SetBool("MPX_BS_IMANI_D_APP_HOOD_F", true);
			loopBool(32312, 32312);
			
			Stats::SetBool("MPX_CARMEET_PV_CHLLGE_CMPLT", true);
		}

		void unlockTattoos()
		{
			Stats::SetInt("MPX_TATTOO_FM_CURRENT_32", -1);
			Stats::SetInt("MPX_TATTOO_FM_CURRENT_33", -1);
			Stats::SetInt("MPX_TATTOO_FM_CURRENT_34", -1);
			Stats::SetInt("MPX_TATTOO_FM_CURRENT_35", -1);
			Stats::SetInt("MPX_TATTOO_FM_CURRENT_36", -1);
			Stats::SetInt("MPX_TATTOO_FM_CURRENT_37", -1);
			Stats::SetInt("MPX_TATTOO_FM_CURRENT_38", -1);
			Stats::SetInt("MPX_TATTOO_FM_CURRENT_39", -1);
			Stats::SetInt("MPX_TATTOO_FM_CURRENT_40", -1);
			Stats::SetInt("MPX_TATTOO_FM_CURRENT_41", -1);
			Stats::SetInt("MPX_TATTOO_FM_CURRENT_42", -1);
			Stats::SetInt("MPX_TATTOO_FM_CURRENT_43", -1);
			Stats::SetInt("MPX_TATTOO_FM_CURRENT_44", -1);
			Stats::SetInt("MPX_TATTOO_FM_CURRENT_45", -1);
			
			Stats::SetInt("MPX_TATTOO_FM_UNLOCKS_0", -1);
			Stats::SetInt("MPX_TATTOO_FM_UNLOCKS_1", -1);
			Stats::SetInt("MPX_TATTOO_FM_UNLOCKS_2", -1);
			Stats::SetInt("MPX_TATTOO_FM_UNLOCKS_3", -1);
			Stats::SetInt("MPX_TATTOO_FM_UNLOCKS_4", -1);
			Stats::SetInt("MPX_TATTOO_FM_UNLOCKS_5", -1);
			Stats::SetInt("MPX_TATTOO_FM_UNLOCKS_6", -1);
		}

		void unlockPedConfigFlags()
		{
			if (auto ped = Self::GetPed())
			{
				ped.SetConfigFlag(PedConfigFlag::DontActivateRagdollFromBulletImpact, true);
				ped.SetConfigFlag(PedConfigFlag::DontActivateRagdollFromExplosions, true);
				ped.SetConfigFlag(PedConfigFlag::DontActivateRagdollFromFire, true);
				ped.SetConfigFlag(PedConfigFlag::DisableEvasiveDives, true);
				ped.SetConfigFlag(PedConfigFlag::BlockWeaponSwitching, false);
				ped.SetConfigFlag(PedConfigFlag::AllowLockonToFriendlyPlayers, false);
			}
		}

		void unlockPackedBools()
		{
			loopBool(0, 500);
			loopBool(15425, 15439);
			loopBool(25407, 25511);
			loopBool(25516, 25521);
			loopBool(26811, 26964);
			loopBool(28254, 28255);
			loopBool(30230, 30251);
			loopBool(31760, 31777);
			loopBool(32312, 32312);
			loopBool(42286, 42287);
			loopBool(51189, 51189);
			loopBool(51196, 51197);
		}
		
		void unlockLifetimeBuys()
		{
			Stats::SetInt("MPX_LIFETIME_BUY_COMPLETE", 1025);
		}

		virtual void OnCall() override
		{
			unlockCharacterStats();
			unlockWeapons();
			unlockVehicles();
			unlockAchievements();
			unlockHeists();
			fillInventory();
			unlockClothesHairstyles();
			unlockTattoos();
			unlockPedConfigFlags();
			unlockPackedBools();
			unlockLifetimeBuys();

			Notifications::Show("Unlock All", "Successfully unlocked all items, stats and achievements", NotificationType::Success);
		}
	};

	static UnlockAll _UnlockAll{"unlockall", "Unlock All", "Unlocks weapons, stats, achievements, vehicles, clothes and more"};
}