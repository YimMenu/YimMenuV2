#include "core/commands/Command.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "game/backend/Tunables.hpp"
#include "core/backend/FiberPool.hpp"

namespace YimMenu::Features
{
	namespace CayoPericoHeist
	{
		static IntCommand _CayoPericoHeistCut1{"cayopericoheistcut1", "Player 1", "Player 1 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _CayoPericoHeistCut2{"cayopericoheistcut2", "Player 2", "Player 2 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _CayoPericoHeistCut3{"cayopericoheistcut3", "Player 3", "Player 3 cut", std::nullopt, std::nullopt, 0};
		static IntCommand _CayoPericoHeistCut4{"cayopericoheistcut4", "Player 4", "Player 4 cut", std::nullopt, std::nullopt, 0};

		class SetCuts : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				auto base = ScriptGlobal(1980034).At(831).At(56);

				*base.At(0, 1).As<int*>() = _CayoPericoHeistCut1.GetState();
				*base.At(1, 1).As<int*>() = _CayoPericoHeistCut2.GetState();
				*base.At(2, 1).As<int*>() = _CayoPericoHeistCut3.GetState();
				*base.At(3, 1).As<int*>() = _CayoPericoHeistCut4.GetState();
			}
		};

		class ForceReady : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				auto base = ScriptGlobal(1981146);

				for (int i = 0; i <= 3; i++)
				{
					*base.At(i, 27).At(7).At(i, 1).As<int*>() = 1;
				}
			}
		};

		static std::vector<std::pair<int, const char*>> cayoPericoHeistDifficulty = {
			{126823, "Normal"},
			{131055, "Hard"}
		};
		static ListCommand _CayoPericoHeistDifficulty{"cayopericoheistdifficulty", "Difficulty", "Heist difficulty", cayoPericoHeistDifficulty, 126823};

		static std::vector<std::pair<int, const char*>> cayoPericoHeistPrimaryTarget = {
			{5, "Panther Statue"},
			{3, "Pink Diamond"},
			{4, "Madrazo Files"},
			{2, "Bearer Bonds"},
			{1, "Ruby Necklace"},
			{0, "Sinsimito Tequila"}
		};
		static ListCommand _CayoPericoHeistPrimaryTarget{"cayopericoheistprimarytarget", "Primary Target", "Primary target", cayoPericoHeistPrimaryTarget, 5};

		static std::vector<std::pair<int, const char*>> cayoPericoHeistWeapon = {
			{1, "Aggressor"},
			{2, "Conspirator"},
			{3, "Crack Shot"},
			{4, "Saboteur"},
			{5, "Marksman"}
		};
		static ListCommand _CayoPericoHeistWeapon{"cayopericoheistweapon", "Weapon", "Weapon category", cayoPericoHeistWeapon, 1};

		class Setup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_H4CNF_TARGET", _CayoPericoHeistPrimaryTarget.GetState()); // Primary target
				Stats::SetInt("MPX_H4LOOT_CASH_I", 16711680);
				Stats::SetInt("MPX_H4LOOT_CASH_I_SCOPED", 16711680);
				Stats::SetInt("MPX_H4LOOT_CASH_C", 0);
				Stats::SetInt("MPX_H4LOOT_CASH_C_SCOPED", 0);
				Stats::SetInt("MPX_H4LOOT_COKE_I", 255);
				Stats::SetInt("MPX_H4LOOT_COKE_I_SCOPED", 255);
				Stats::SetInt("MPX_H4LOOT_COKE_C", 0);
				Stats::SetInt("MPX_H4LOOT_COKE_C_SCOPED", 0);
				Stats::SetInt("MPX_H4LOOT_GOLD_I", 0);
				Stats::SetInt("MPX_H4LOOT_GOLD_I_SCOPED", 0);
				Stats::SetInt("MPX_H4LOOT_GOLD_C", 255);
				Stats::SetInt("MPX_H4LOOT_GOLD_C_SCOPED", 255);
				Stats::SetInt("MPX_H4LOOT_WEED_I", 65280);
				Stats::SetInt("MPX_H4LOOT_WEED_I_SCOPED", 65280);
				Stats::SetInt("MPX_H4LOOT_WEED_C", 0);
				Stats::SetInt("MPX_H4LOOT_WEED_C_SCOPED", 0);
				Stats::SetInt("MPX_H4LOOT_PAINT", 127);
				Stats::SetInt("MPX_H4LOOT_PAINT_SCOPED", 127);
				Stats::SetInt("MPX_H4LOOT_CASH_V", 83250);
				Stats::SetInt("MPX_H4LOOT_COKE_V", 202500);
				Stats::SetInt("MPX_H4LOOT_GOLD_V", 333333);
				Stats::SetInt("MPX_H4LOOT_WEED_V", 135000);
				Stats::SetInt("MPX_H4LOOT_PAINT_V", 180000);
				Stats::SetInt("MPX_H4_PROGRESS", _CayoPericoHeistDifficulty.GetState()); // Difficulty
				Stats::SetInt("MPX_H4CNF_BS_GEN", 262143);
				Stats::SetInt("MPX_H4CNF_BS_ENTR", 63);
				Stats::SetInt("MPX_H4CNF_BS_ABIL", 63);
				Stats::SetInt("MPX_H4CNF_WEP_DISRP", 3);
				Stats::SetInt("MPX_H4CNF_ARM_DISRP", 3);
				Stats::SetInt("MPX_H4CNF_HEL_DISRP", 3);
				Stats::SetInt("MPX_H4CNF_APPROACH", -1);
				Stats::SetInt("MPX_H4CNF_BOLTCUT", 4424);
				Stats::SetInt("MPX_H4CNF_UNIFORM", 5256);
				Stats::SetInt("MPX_H4CNF_GRAPPEL", 5156);
				Stats::SetInt("MPX_H4_MISSIONS", -1);
				Stats::SetInt("MPX_H4CNF_WEAPONS", _CayoPericoHeistWeapon.GetState()); // Weapon
				Stats::SetInt("MPX_H4CNF_TROJAN", 5);
				Stats::SetInt("MPX_H4_PLAYTHROUGH_STATUS", 100);

				ScriptMgr::Yield(500ms);

				if (auto thread = Scripts::FindScriptThread("heist_island_planning"_J))
					*ScriptLocal(thread, 1570).As<int*>() = 2;
			}
		};

		static IntCommand _CayoPericoHeistPrimaryTargetValue{"cayopericoheistprimarytargetvalue", "Primary Target Value", "Updates primary target value", std::nullopt, std::nullopt, 0};

		class SetPrimaryTargetValue : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				auto primary_target = Stats::GetInt("MPX_H4CNF_TARGET");

				switch (primary_target)
				{
				case 0:
				{
					static Tunable tunable{"IH_PRIMARY_TARGET_VALUE_TEQUILA"_J};
					if (tunable.IsReady())
						tunable.Set(_CayoPericoHeistPrimaryTargetValue.GetState());
					break;
				}
				case 1:
				{
					static Tunable tunable{"IH_PRIMARY_TARGET_VALUE_PEARL_NECKLACE"_J};
					if (tunable.IsReady())
						tunable.Set(_CayoPericoHeistPrimaryTargetValue.GetState());
					break;
				}
				case 2:
				{
					static Tunable tunable{"IH_PRIMARY_TARGET_VALUE_BEARER_BONDS"_J};
					if (tunable.IsReady())
						tunable.Set(_CayoPericoHeistPrimaryTargetValue.GetState());
					break;
				}
				case 3:
				{
					static Tunable tunable{"IH_PRIMARY_TARGET_VALUE_PINK_DIAMOND"_J};
					if (tunable.IsReady())
						tunable.Set(_CayoPericoHeistPrimaryTargetValue.GetState());
					break;
				}
				case 4:
				{
					static Tunable tunable{"IH_PRIMARY_TARGET_VALUE_MADRAZO_FILES"_J};
					if (tunable.IsReady())
						tunable.Set(_CayoPericoHeistPrimaryTargetValue.GetState());
					break;
				}
				case 5:
				{
					static Tunable tunable{"IH_PRIMARY_TARGET_VALUE_SAPPHIRE_PANTHER_STATUE"_J};
					if (tunable.IsReady())
						tunable.Set(_CayoPericoHeistPrimaryTargetValue.GetState());
					break;
				}
				default: break;
				}
			}
		};

		static IntCommand _CayoPericoHeistSecondaryTakeValue{"cayopericoheistsecondarytakevalue", "Secondary Take Value", "Updates secondary take value", std::nullopt, std::nullopt, 0};

		class SetSecondaryTakeValue : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_2020"_J))
					*ScriptLocal(thread, 59705).At(1376).At(53).As<int*>() = _CayoPericoHeistSecondaryTakeValue.GetState();
			}
		};

		class SkipHacking : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_2020"_J))
					*ScriptLocal(thread, 26486).As<int*>() = 5;
			}
		};

		class CutSewer : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_2020"_J))
					*ScriptLocal(thread, 31349).As<int*>() = 6;
			}
		};

		class CutGlass : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_2020"_J))
					*ScriptLocal(thread, 32589).At(3).As<float*>() = 100.0f;
			}
		};

		class TakePrimaryTarget : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_2020"_J))
				{
					auto ped = Self::GetPed();

					if (!ped)
						return;

					auto pos = ped.GetPosition();
					auto heading = ped.GetHeading();
					auto primary_target = Stats::GetInt("MPX_H4CNF_TARGET");

					FiberPool::Push([&] {
						TASK::TASK_GO_STRAIGHT_TO_COORD(ped.GetHandle(), 5006.917, -5755.931, 15.484, 1.0, 3, 15, 5);

						switch (primary_target)
						{
						case 0:
						case 1:
						case 3:
						case 5:
							*ScriptLocal(thread, 32588).As<int*>() = 5;
							*ScriptLocal(thread, 32589).As<int*>() = 3;
							break;
						case 2:
						case 4:
							*ScriptLocal(thread, 32563).As<int*>() = 7;
							break;
						default: break;
						}

						ScriptMgr::Yield(4000ms);

						TASK::TASK_GO_STRAIGHT_TO_COORD(ped.GetHandle(), pos.x, pos.y, pos.z, 1.0, 3, heading, 5);
					});
				}
			}
		};

		class InstantFinish : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_2020"_J))
				{
					Scripts::ForceScriptHost(thread);
					ScriptMgr::Yield(500ms);

					*ScriptLocal(thread, 56223).As<int*>() = 9;
					*ScriptLocal(thread, 56223).At(1776).At(0, 1).As<int*>() = 50;
				}
			}
		};

		static SetCuts _CayoPericoHeistSetCuts{"cayopericoheistsetcuts", "Set Cuts", "Sets heist cut"};
		static ForceReady _CayoPericoHeistForceReady{"cayopericoheistforceready", "Force Ready", "Forces all players to be ready"};
		static Setup _CayoPericoHeistSetup{"cayopericoheistsetup", "Setup", "Sets up cayo perico heist"};
		static SetPrimaryTargetValue _CayoPericoHeistSetPrimaryTargetValue{"cayopericoheistsetprimarytargetvalue", "Set Primary Target Value", "Updates primary target value"};
		static SetSecondaryTakeValue _CayoPericoHeistSetSecondaryTakeValue{"cayopericoheistsetsecondarytakevalue", "Set Secondary Take Value", "Updates secondary take value"};
		static SkipHacking _CayoPericoHeistSkipHacking{"cayopericoheistskiphacking", "Skip Hacking", "Skips hacking process"};
		static CutSewer _CayoPericoHeistCutSewer{"cayopericoheistcutsewer", "Cut Sewer", "Cuts the sewer"};
		static CutGlass _CayoPericoHeistCutGlass{"cayopericoheistcutglass", "Cut Glass", "Cuts the glass"};
		static TakePrimaryTarget _CayoPericoHeistTakePrimaryTarget{"cayopericoheisttakeprimarytarget", "Take Primary Target", "Takes primary target"};
		static InstantFinish _CayoPericoHeistInstantFinish{"cayopericoheistinstantfinish", "Instant Finish", "Instantly passes the heist"};
	}
}