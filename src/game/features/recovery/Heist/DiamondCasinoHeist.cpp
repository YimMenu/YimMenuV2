#include "core/commands/Command.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/gta/Stats.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/backend/Tunables.hpp"

namespace YimMenu::Features
{
	namespace DiamondCasinoHeist
	{
		static IntCommand _DiamondCasinoHeistCut1{"diamondcasinoheistcut1", "Player 1", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _DiamondCasinoHeistCut2{"diamondcasinoheistcut2", "Player 2", "Player 2 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _DiamondCasinoHeistCut3{"diamondcasinoheistcut3", "Player 3", "Player 3 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _DiamondCasinoHeistCut4{"diamondcasinoheistcut4", "Player 4", "Player 4 cut", std::nullopt, std::nullopt, 0};

		class SetCuts : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				auto base = ScriptGlobal(1966898).At(1497).At(736).At(92);

				*base.At(1).As<int*>() = _DiamondCasinoHeistCut1.GetState();
				*base.At(2).As<int*>() = _DiamondCasinoHeistCut2.GetState();
				*base.At(3).As<int*>() = _DiamondCasinoHeistCut3.GetState();
				*base.At(4).As<int*>() = _DiamondCasinoHeistCut4.GetState();
			}
		};

		class ForceReady : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				auto base = ScriptGlobal(1971261);

				*base.At(0, 68).At(8).At(0).As<int*>() = 1;
				*base.At(1, 68).At(8).At(1).As<int*>() = 1;
                *base.At(2, 68).At(8).At(2).As<int*>() = 1; 
                *base.At(3, 68).At(8).At(3).As<int*>() = 1;
			}
		};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistDifficulty = {
			{0, "Normal"},
			{1, "Hard"}
		};
		static ListCommand _DiamondCasinoHeistDifficulty{"diamondcasinoheistdifficulty", "Difficulty", "Heist difficulty", diamondCasinoHeistDifficulty, 0};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistPrimaryTarget = {
			{3, "Diamonds"},
			{1, "Gold"},
			{2, "Artwork"},
			{0, "Cash"}
		};
		static ListCommand _DiamondCasinoHeistPrimaryTarget{"diamondcasinoheistprimarytarget", "Primary Target", "Primary target", diamondCasinoHeistPrimaryTarget, 3};

		static ListCommand* _DiamondCasinoHeistGunmanPtr   = nullptr;
		static ListCommand* _DiamondCasinoHeistApproachPtr = nullptr;

		static std::vector<std::vector<std::vector<std::pair<int, const char*>>>> diamondCasinoHeistWeapon = {
			{
		        {{0, "MK II Shotgun Loadout"}, {1, "MK II Rifle Loadout"}},
		        {{0, "MK II SMG Loadout"}, {1, "MK II Rifle Loadout"}},
		        {{0, "MK II Shotgun Loadout"}, {1, "MK II Rifle Loadout"}}
			},
			{
				{{0, "Rifle Loadout"}, {1, "Shotgun Loadout"}},
				{{0, "Rifle Loadout"}, {1, "Shotgun Loadout"}},
				{{0, "Rifle Loadout"}, {1, "Shotgun Loadout"}}
			},
			{
				{{0, "Combat PDW Loadout"}, {1, "Rifle Loadout"}},
				{{0, "Shotgun Loadout"}, {1, "Rifle Loadout"}},
				{{0, "Shotgun Loadout"}, {1, "Combat MG Loadout"}}
			},
			{
		        {{0, "SMG Loadout"}, {1, "Shotgun Loadout"}},
		        {{0, "Machine Pistol Loadout"}, {1, "Shotgun Loadout"}},
		        {{0, "SMG Loadout"}, {1, "Shotgun Loadout"}}
			},
			{
		        {{0, "Micro SMG Loadout"}, {1, "Machine Pistol Loadout"}},
		        {{0, "Micro SMG Loadout"}, {1, "Shotgun Loadout"}},
				{{0, "Shotgun Loadout"}, {1, "Revolver Loadout"}}
			},
			{
		        {{0, "                                        "}, {1, ""}},
				{{0, ""}, {1, ""}},
				{{0, ""}, {1, ""}}
			}
		};
		static ListCommand _DiamondCasinoHeistWeapon{"diamondcasinoheistweapon", "Weapon", "Weapon", diamondCasinoHeistWeapon[5][0], 0};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistGunman = {
			{0, "Chester McCoy"},
			{1, "Gustavo Mota"},
			{2, "Patrick McReary"},
			{3, "Charlie Reed"},
			{4, "Karl Abolaji"},
			{5, "Remove Gunman"}
		};

		class Gunman : public ListCommand
		{
			using ListCommand::ListCommand;

			virtual void OnChange() override
			{
				_DiamondCasinoHeistWeapon.SetList(diamondCasinoHeistWeapon[this->GetState()][_DiamondCasinoHeistApproachPtr->GetState()]);
				_DiamondCasinoHeistWeapon.SetState(0);
			}
		};
		static Gunman _DiamondCasinoHeistGunman{"diamondcasinoheistgunman", "Gunman", "Gunman", diamondCasinoHeistGunman, 5};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistApproach = {
			{0, "Silent & Sneaky"},
			{1, "The Big Con"},
			{2, "Aggressive"}
		};

		class Approach : public ListCommand
		{
			using ListCommand::ListCommand;

			virtual void OnChange() override
			{
				_DiamondCasinoHeistWeapon.SetList(diamondCasinoHeistWeapon[_DiamondCasinoHeistGunmanPtr->GetState()][this->GetState()]);
				_DiamondCasinoHeistWeapon.SetState(0);
			}
		};
		static Approach _DiamondCasinoHeistApproach{"diamondcasinoheistapproach", "Approach", "Heist approach", diamondCasinoHeistApproach, 0};

		static struct InitPtrs
		{
			InitPtrs()
			{
				_DiamondCasinoHeistGunmanPtr   = &_DiamondCasinoHeistGunman;
				_DiamondCasinoHeistApproachPtr = &_DiamondCasinoHeistApproach;
			}
		} _initPtrs;

		static std::vector<std::vector<std::pair<int, const char*>>> diamondCasinoHeistVehicle = {
			{{0, "Zhaba"}, {1, "Vagrant"}, {2, "Outlaw"}, {3, "Everon"}},
			{{0, "Sultan Classic"}, {1, "Gauntlet Classic"}, {2, "Ellie"}, {3, "Komoda"}},
			{{0, "Retinue MK II"}, {1, "Drifty Yosemite"}, {2, "Sugoi"}, {3, "Jugular"}},
			{{0, "Manchez"}, {1, "Stryder"}, {2, "Defiler"}, {3, "Lectro"}},
			{{0, "Issi Classic"}, {1, "Asbo"}, {2, "Kanjo"}, {3, "Sentinel Classic"}},
		    {{0, "                           "}, {1, ""}, {2, ""}, {3, ""}}
		};
		static ListCommand _DiamondCasinoHeistVehicle{"diamondcasinoheistvehicle", "Vehicle", "Vehicle", diamondCasinoHeistVehicle[5], 0};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistDriver = {
			{0, "Chester McCoy"},
			{1, "Eddie Toh"},
			{2, "Taliana Martinez"},
			{3, "Zach Nelson"},
			{4, "Karim Denz"},
			{5, "Remove Driver"}
		};

		class Driver : public ListCommand
		{
			using ListCommand::ListCommand;

			virtual void OnChange() override
			{
				_DiamondCasinoHeistVehicle.SetList(diamondCasinoHeistVehicle[this->GetState()]);
				_DiamondCasinoHeistVehicle.SetState(0);
			}
		};
		static Driver _DiamondCasinoHeistDriver{"diamondcasinoheistdriver", "Driver", "Driver", diamondCasinoHeistDriver, 5};

		static std::vector<std::pair<int, const char*>> diamondCasinoHeistHacker = {
			{4, "Avi Schwartzman"},
		    {5, "Paige Harris"},
		    {2, "Christian Feltz"},
		    {3, "Yohan Blair"},
		    {1, "Rickie Lukens"},
		    {6, "Remove Hacker"}
		};
		static ListCommand _DiamondCasinoHeistHacker{"diamondcasinoheisthacker", "Hacker", "Hacker", diamondCasinoHeistHacker, 6};

		class Setup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_H3_COMPLETEDPOSIX", -1);
				Stats::SetInt("MPX_H3OPT_MASKS", 4);
				Stats::SetInt("MPX_H3OPT_WEAPS", _DiamondCasinoHeistWeapon.GetState());
				Stats::SetInt("MPX_H3OPT_VEHS", _DiamondCasinoHeistVehicle.GetState());
				Stats::SetInt("MPX_CAS_HEIST_FLOW", -1);
				Stats::SetInt("MPX_H3_LAST_APPROACH", 0);
				Stats::SetInt("MPX_H3OPT_APPROACH", _DiamondCasinoHeistApproach.GetState() + 1); // 1 = Silent & Sneaky, 2 = The Big Con, 3 = Aggressive

				switch (_DiamondCasinoHeistDifficulty.GetState())
				{
				case 0: Stats::SetInt("MPX_H3_HARD_APPROACH", 0); break;
				case 1: Stats::SetInt("MPX_H3_HARD_APPROACH", _DiamondCasinoHeistApproach.GetState() + 1); break;
				default: break;
				}
				
				Stats::SetInt("MPX_H3OPT_TARGET", _DiamondCasinoHeistPrimaryTarget.GetState());
				Stats::SetInt("MPX_H3OPT_POI", 1023);
				Stats::SetInt("MPX_H3OPT_ACCESSPOINTS", 2047);

				switch (_DiamondCasinoHeistGunman.GetState())
				{
				case 0: Stats::SetInt("MPX_H3OPT_CREWWEAP", 4); break;
				case 1: Stats::SetInt("MPX_H3OPT_CREWWEAP", 2); break;
				case 2: Stats::SetInt("MPX_H3OPT_CREWWEAP", 5); break;
				case 3: Stats::SetInt("MPX_H3OPT_CREWWEAP", 3); break;
				case 4: Stats::SetInt("MPX_H3OPT_CREWWEAP", 1); break;
				case 5: Stats::SetInt("MPX_H3OPT_CREWWEAP", 6); break;
				default: break;
				}

				switch (_DiamondCasinoHeistDriver.GetState())
				{
				case 0: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 5); break;
				case 1: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 3); break;
				case 2: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 2); break;
				case 3: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 4); break;
				case 4: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 1); break;
				case 5: Stats::SetInt("MPX_H3OPT_CREWDRIVER", 6); break;
				default: break;
				}

				Stats::SetInt("MPX_H3OPT_CREWHACKER", _DiamondCasinoHeistHacker.GetState());
				Stats::SetInt("MPX_H3OPT_DISRUPTSHIP", 3); // Security Strength: 1 = Strong, 2 = Medium, 3 = Weak
				Stats::SetInt("MPX_H3OPT_BODYARMORLVL", -1);
				Stats::SetInt("MPX_H3OPT_KEYLEVELS", 2);   // 1 = Level1 Security Pass, 2 = Level2 Security Pass

				Stats::SetInt("MPX_H3OPT_BITSET0", rand() % (INT_MAX)); // Refresh board
				Stats::SetInt("MPX_H3OPT_BITSET1", rand() % (INT_MAX)); // Refresh board

                ScriptMgr::Yield(500ms);

				Stats::SetInt("MPX_H3OPT_BITSET0", -1); // Refresh board
				Stats::SetInt("MPX_H3OPT_BITSET1", -1); // Refresh board
			}
		};

		static IntCommand _DiamondCasinoHeistPotentialTake{"diamondcasinoheistpotentialtake", "Potential Take", "Updates potential take", std::nullopt, std::nullopt, 0};
		
		class SetPotentialTake : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int primary_target = Stats::GetInt("MPX_H3OPT_TARGET");

				switch (primary_target)
				{
				case 0: *Tunables::GetTunable(static_cast<joaat_t>(-1638885821)).As<int*>() = _DiamondCasinoHeistPotentialTake.GetState(); break; // "Cash"
				case 1: *Tunables::GetTunable(static_cast<joaat_t>(-582734553)).As<int*>() = _DiamondCasinoHeistPotentialTake.GetState(); break; // "Gold"
				case 2: *Tunables::GetTunable(static_cast<joaat_t>(1934398910)).As<int*>() = _DiamondCasinoHeistPotentialTake.GetState(); break; // "Artwork"
				case 3: *Tunables::GetTunable(static_cast<joaat_t>(1277889925)).As<int*>() = _DiamondCasinoHeistPotentialTake.GetState(); break; // "Diamond"
				default: break;
				}
			}
		};
		
		static IntCommand _DiamondCasinoHeistActualTake{"diamondcasinoheistactualtake", "Actual Take", "Updates actual take", std::nullopt, std::nullopt, 0};

		class SetActualTake : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				*ScriptLocal("fm_mission_controller"_J, 20387).At(2686).As<int*>() = _DiamondCasinoHeistActualTake.GetState();
			}
		};

		class SkipHacking : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				*ScriptLocal("fm_mission_controller"_J, 53999).As<int*>() = 5;
				*ScriptLocal("fm_mission_controller"_J, 55065).As<int*>() = 5;
			}
		};

		class SkipDrilling : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				*ScriptLocal("fm_mission_controller"_J, 10547).At(7).As<int*>() = *ScriptLocal("fm_mission_controller"_J, 10547).At(37).As<int*>();
			}
		};

		class InstantFinish : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Scripts::ForceScriptHost(Scripts::FindScriptThread("fm_mission_controller"_J));
				ScriptMgr::Yield(500ms);

				*ScriptLocal("fm_mission_controller"_J, 20387).At(1740).At(1).As<int*>() = 80;
				*ScriptLocal("fm_mission_controller"_J, 20387).At(2686).As<int*>() = 4443220;
				*ScriptLocal("fm_mission_controller"_J, 20387).At(1062).As<int*>() = 5;
				*ScriptLocal("fm_mission_controller"_J, 20387).As<int*>() = 12;
				*ScriptLocal("fm_mission_controller"_J, 29006).At(1).As<int*>() = 99999;
				*ScriptLocal("fm_mission_controller"_J, 32462).At(1).At(68).As<int*>() = 99999;
			}
		};

		static SetCuts _DiamondCasinoHeistSetCuts{"diamondcasinoheistsetcuts", "Set Cuts", "Sets heist cut"};
		static ForceReady _DiamondCasinoHeistForceReady{"diamondcasinoheistforceready", "Force Ready", "Forces all players to be ready"};
		static Setup _DiamondCasinoHeistSetup{"diamondcasinoheistsetup", "Setup", "Sets up diamond casino heist"};
		static SetPotentialTake _DiamondCasinoHeistSetPotentialTake{"diamondcasinoheistsetpotentialtake", "Set Potential Take", "Updates potential take"};
		static SetActualTake _DiamondCasinoHeistSetActualTake{"diamondcasinoheistsetactualtake", "Set Actual Take", "Updates actual take"};
		static SkipHacking _DiamondCasinoHeistSkipHacking{"diamondcasinoheistskiphacking", "Skip Hacking", "Skips hacking process"};
		static SkipDrilling _DiamondCasinoHeistSkipDrilling{"diamondcasinoheistskipdrilling", "Skip Drilling", "Skips drilling process"};
		static InstantFinish _DiamondCasinoHeistInstantFinish{"diamondcasinoheistinstantfinish", "Instant Finish", "Instantly passes the heist"};
	}
}