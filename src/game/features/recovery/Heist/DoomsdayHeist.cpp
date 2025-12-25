#include "core/commands/Command.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "types/script/globals/GPBD_FM_2.hpp"

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
				auto base = ScriptGlobal(1968543).At(812).At(50);

				*base.At(0, 1).As<int*>() = _DoomsdayHeistCut1.GetState();
				*base.At(1, 1).As<int*>() = _DoomsdayHeistCut2.GetState();
				*base.At(2, 1).As<int*>() = _DoomsdayHeistCut3.GetState();
				*base.At(3, 1).As<int*>() = _DoomsdayHeistCut4.GetState();
			}
		};

		class ForceReady : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto gpbd_fm_2 = GPBD_FM_2::Get())
				{
					gpbd_fm_2->Entries[0].GangopsData.ArePlayersReady[0] = TRUE;
					gpbd_fm_2->Entries[1].GangopsData.ArePlayersReady[1] = TRUE;
					gpbd_fm_2->Entries[2].GangopsData.ArePlayersReady[2] = TRUE;
					gpbd_fm_2->Entries[3].GangopsData.ArePlayersReady[3] = TRUE;
				}
			}
		};

		static std::vector<std::pair<int, const char*>> doomsdayHeistCategory = {
			{0, "The Data Breaches"},
			{1, "The Bogdan Problem"},
			{2, "The Doomsday Senario"}
		};
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

				if (auto thread = Scripts::FindScriptThread("gb_gang_ops_planning"_J))
					*ScriptLocal(thread, 211).As<int*>() = 6;
			}
		};

		class SkipHacking : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller"_J))
				{
					*ScriptLocal(thread, 1572).As<int*>() = 2;
					*ScriptLocal(thread, 1541).As<int*>() = 3;
					*ScriptLocal(thread, 1298).At(135).As<int*>() = 3;
				}
			}
		};

		class InstantFinish : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller"_J))
				{
					Scripts::ForceScriptHost(thread);
					ScriptMgr::Yield(500ms);

					*ScriptLocal(thread, 20395).At(1725).At(0, 1).As<int*>() = 80;
					*ScriptLocal(thread, 20395).As<int*>() = 12;
					*ScriptLocal(thread, 29016).At(0, 1).As<int*>() = 99999;
					*ScriptLocal(thread, 32472).At(0, 294).At(68).As<int*>() = 99999;
				}
				// TODO: find a way of getting current heist info so that InstantFinishAct3 can be implemented here conditionally.
			}
		};

		class InstantFinishAct3 : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller"_J))
				{
					Scripts::ForceScriptHost(thread);
					ScriptMgr::Yield(500ms);

					*ScriptLocal(thread, 20395).As<int*>() = 12;
					*ScriptLocal(thread, 20395).At(1740).At(0, 1).As<int*>() = 150;
					*ScriptLocal(thread, 20395).At(1062).As<int*>() = 5;
					*ScriptLocal(thread, 29016).At(0, 1).As<int*>() = 99999;
					*ScriptLocal(thread, 32472).At(0, 294).At(68).As<int*>() = 99999;
				}
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