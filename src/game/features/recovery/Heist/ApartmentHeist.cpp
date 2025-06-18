#include "core/commands/IntCommand.hpp"
#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"
#include "game/backend/Players.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "types/script/globals/GlobalPlayerBD.hpp"

namespace YimMenu::Features
{
	namespace ApartmentHeist
	{
		static IntCommand _ApartmentHeistCut1{"apartmentheistcut1", "Player 1", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _ApartmentHeistCut2{"apartmentheistcut2", "Player 2", "Player 2 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _ApartmentHeistCut3{"apartmentheistcut3", "Player 3", "Player 3 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _ApartmentHeistCut4{"apartmentheistcut4", "Player 4", "Player 4 cut", std::nullopt, std::nullopt, 0};

		class SetCuts : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				auto base1 = ScriptGlobal(1931800).At(1);
				auto base2 = ScriptGlobal(1933768).At(3008);

				*base1.At(1).As<int*>() = 100
				    - (_ApartmentHeistCut1.GetState() + _ApartmentHeistCut2.GetState() + _ApartmentHeistCut3.GetState()
				        + _ApartmentHeistCut4.GetState());
				*base1.At(2).As<int*>() = _ApartmentHeistCut2.GetState();
				*base1.At(3).As<int*>() = _ApartmentHeistCut3.GetState();
				*base1.At(4).As<int*>() = _ApartmentHeistCut4.GetState();

				ScriptMgr::Yield(500ms);

				*base2.At(1).As<int*>() =
				    -1 * (*base1.At(1).As<int*>() + *base1.At(2).As<int*>() + *base1.At(3).As<int*>() + *base1.At(4).As<int*>() - 100);
				*base2.At(2).As<int*>() = *base1.At(2).As<int*>();
				*base2.At(3).As<int*>() = *base1.At(3).As<int*>();
				*base2.At(4).As<int*>() = *base1.At(4).As<int*>();
			}
		};

		class ForceReady : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto gpbd = GlobalPlayerBD::Get(); gpbd && Scripts::SafeToModifyFreemodeBroadcastGlobals())
				{
					for (auto& player : Players::GetPlayers())
					{
						gpbd->Entries[player.second.GetId()].HeistCutSelectionStage = 6;
					}
				}
			}
		};

		class Setup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_HEIST_PLANNING_STAGE", -1);
			}
		};

		class SkipHacking : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				*ScriptLocal("fm_mission_controller"_J, 12220).At(24).As<int*>() = 7;
				*ScriptLocal("fm_mission_controller"_J, 10215).As<int*>() =
				    *ScriptLocal("fm_mission_controller"_J, 10215).As<int*>() | (1 << 9);
			}
		};

		class SkipDrilling : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				*ScriptLocal("fm_mission_controller"_J, 10509).At(11).As<float*>() = 100.0f;
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

				// TODO: find a way of getting current heist info so that InstantFinishPacific can be implemented here conditionally.
			}
		};

		class InstantFinishPacific : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Scripts::ForceScriptHost(Scripts::FindScriptThread("fm_mission_controller"_J));
				ScriptMgr::Yield(500ms);

				*ScriptLocal("fm_mission_controller"_J, 20391).At(2686).As<int*>() = 1875000;
				*ScriptLocal("fm_mission_controller"_J, 20391).At(1062).As<int*>() = 5;
				*ScriptLocal("fm_mission_controller"_J, 20391).As<int*>() = 12;
				*ScriptLocal("fm_mission_controller"_J, 29011).At(1).As<int*>() = 99999;
				*ScriptLocal("fm_mission_controller"_J, 32467).At(1).At(68).As<int*>() = 99999;
			}
		};

		static SetCuts _ApartmentHeistSetCuts{"apartmentheistsetcuts", "Set Cuts", "Sets heist cut"};
		static ForceReady _ApartmentHeistForceReady{"apartmentheistforceready", "Force Ready", "Forces all players to be ready"};
		static Setup _ApartmentHeistSetup{"apartmentheistsetup", "Setup", "Sets up current apartment heist"};
		static SkipHacking _ApartmentHeistSkipHacking{"apartmentheistskiphacking", "Skip Hacking", "Skips hacking process"};
		static SkipDrilling _ApartmentHeistSkipDrilling{"apartmentheistskipdrilling", "Skip Drilling", "Skips drilling process"};
		static InstantFinish _ApartmentHeistInstantFinish{"apartmentheistinstantfinish", "Instant Finish", "Instantly passes the heist"};
		static InstantFinishPacific _ApartmentHeistInstantFinishPacific{"apartmentheistinstantfinishpacific", "Instant Finish (Pacific)", "Instantly passes Pacific Standard Job"};
	}
}