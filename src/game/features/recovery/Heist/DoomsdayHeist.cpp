#include "core/commands/Command.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "core/backend/ScriptMgr.hpp"

namespace YimMenu::Features
{
	namespace DoomsdayHeist
	{
		static IntCommand _DoomsdayHeistCut1{"doomsdayheistcut1", "Player 1", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _DoomsdayHeistCut2{"doomsdayheistcut2", "Player 2", "Player 2 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _DoomsdayHeistCut3{"doomsdayheistcut3", "Player 3", "Player 3 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _DoomsdayHeistCut4{"doomsdayheistcut4", "Player 4", "Player 4 cut", std::nullopt, std::nullopt, 0};

		class SetCuts : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				auto base = ScriptGlobal(1964170).At(812).At(50);

				*base.At(1).As<int*>() = _DoomsdayHeistCut1.GetState();
				*base.At(2).As<int*>() = _DoomsdayHeistCut2.GetState();
				*base.At(3).As<int*>() = _DoomsdayHeistCut3.GetState();
				*base.At(4).As<int*>() = _DoomsdayHeistCut4.GetState();
			}
		};

		class ForceReady : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				auto base = ScriptGlobal(1882449);

				*base.At(0, 201).At(43).At(0).At(4).At(8).As<int*>() = 1;
				*base.At(1, 201).At(43).At(1).At(4).At(8).As<int*>() = 1;
				*base.At(2, 201).At(43).At(2).At(4).At(8).As<int*>() = 1;
				*base.At(3, 201).At(43).At(3).At(4).At(8).As<int*>() = 1;
			}
		};

		static std::vector<std::pair<int, const char*>> doomsdayHeistCategory = {{0, "The Data Breaches"}, {1, "The Bogdan Problem"}, {2, "The Doomsday Senario"}};
		static ListCommand _DoomsdayHeistCategory{"doomsdayheistcategory", "Select Heist", "Heist categories", doomsdayHeistCategory, 0};

		class Setup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				switch (_DoomsdayHeistCategory.GetState())
				{
				case 0:
					Stats::SetInt("MPX_GANGOPS_FLOW_MISSION_PROG", 503);
					Stats::SetInt("MPX_GANGOPS_HEIST_STATUS", -229383);
					Stats::SetInt("MPX_GANGOPS_FLOW_NOTIFICATIONS", 1557);
					break;
				case 1:
					Stats::SetInt("MPX_GANGOPS_FLOW_MISSION_PROG", 240);
					Stats::SetInt("MPX_GANGOPS_HEIST_STATUS", -229378);
					Stats::SetInt("MPX_GANGOPS_FLOW_NOTIFICATIONS", 1557);
					break;
				case 2:
					Stats::SetInt("MPX_GANGOPS_FLOW_MISSION_PROG", 16368);
					Stats::SetInt("MPX_GANGOPS_HEIST_STATUS", -229380);
					Stats::SetInt("MPX_GANGOPS_FLOW_NOTIFICATIONS", 1557);
					break;
				default: break;
				}

				ScriptMgr::Yield(500ms);

				*ScriptLocal("gb_gang_ops_planning"_J, 207).As<int*>() = 6; // Reload planning screen
			}
		};

		class SkipHacking : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				*ScriptLocal("fm_mission_controller"_J, 1540).As<int*>() = 3;
				*ScriptLocal("fm_mission_controller"_J, 1571).As<int*>() = 2;
				*ScriptLocal("fm_mission_controller"_J, 1296).At(135).As<int*>() = 3;
			}
		};

		class InstantFinish : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Scripts::ForceScriptHost(Scripts::FindScriptThread("fm_mission_controller"_J));
				ScriptMgr::Yield(500ms);

				*ScriptLocal("fm_mission_controller"_J, 20391).At(1725).At(1).As<int*>() = 80;
				*ScriptLocal("fm_mission_controller"_J, 20391).As<int*>() = 12;
				*ScriptLocal("fm_mission_controller"_J, 29011).At(1).As<int*>() = 99999;
				*ScriptLocal("fm_mission_controller"_J, 32467).At(1).At(68).As<int*>() = 99999;

				// TODO: find a way of getting current heist info so that InstantFinishAct3 can be implemented here conditionally.
			}
		};

		class InstantFinishAct3 : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Scripts::ForceScriptHost(Scripts::FindScriptThread("fm_mission_controller"_J));
				ScriptMgr::Yield(500ms);

				*ScriptLocal("fm_mission_controller"_J, 20391).As<int*>() = 12;
				*ScriptLocal("fm_mission_controller"_J, 20391).At(1740).At(1).As<int*>() = 150;
				*ScriptLocal("fm_mission_controller"_J, 20391).At(1062).As<int*>() = 5;
				*ScriptLocal("fm_mission_controller"_J, 29011).At(1).As<int*>() = 99999;
				*ScriptLocal("fm_mission_controller"_J, 32467).At(1).At(68).As<int*>() = 99999;
			}
		};

		static SetCuts _DoomsdayHeistSetCuts{"doomsdayheistsetcuts", "Set Cuts", "Sets heist cut"};
		static ForceReady _DoomsdayHeistForceReady{"doomsdayheistforceready", "Force Ready", "Forces all players to be ready"};
		static Setup _DoomsdayHeistSetup{"doomsdayheistsetup", "Setup", "Sets up doomsday heist"};
		static SkipHacking _DoomsdayHeistSkipHacking{"doomsdayheistskiphacking", "Skip Hacking", "Skips hacking process"};
		static InstantFinish _DoomsdayHeistInstantFinish{"doomsdayheistinstantfinish", "Instant Finish", "Instantly passes the heist"};
		static InstantFinishAct3 _DoomsdayHeistInstantFinishAct3{"doomsdayheistinstantfinishact3", "Instant Finish (Act: III)", "Instantly passes Doomsday Scenario Act: III"};
	}
}