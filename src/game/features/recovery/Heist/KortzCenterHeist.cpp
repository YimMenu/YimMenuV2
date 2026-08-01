#include "core/commands/Command.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/gta/Stats.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/gta/Scripts.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	namespace KortzCenterHeist
	{
		// --- Primary Target ---
		static std::vector<std::pair<int, const char*>> kortzCenterTargets = {
		    {0, "La Dernière Débauche"},
		    {1, "Hare Oneself Think"},
		    {2, "The Downfall of Rome"},
		    {3, "Brother Brother"},
		    {4, "A Cast of Characters"},
		    {5, "Gone To Seed"},
		    {6, "True Love"},
		    {7, "Breathless"},
		    {8, "Consumato"},
		    {9, "I Hear Voices"},
		    {10, "Winter, Nowhere in Particular"},
		    {11, "The Girl With the Pearl Necklace"},
		    {12, "Chat on Fruit"},
		    {13, "Pumpkin"},
		    {14, "Twindifference"},
		    {15, "Stacks Study V"},
		    {16, "I, Fruit"},
		    {17, "To Beat About the Bush"},
		    {18, "In Excess of Success"},
		    {19, "Juiced"},
		    {20, "A Winding Road Home"},
		    {21, "Teckels"},
		    {22, "Trust"},
		    {23, "Until Death"},
		    {24, "What Are Melons?"},
		    {25, "The Outcome of Endeavour"},
		    {26, "Mi O Melee"}
		};
		static ListCommand _KortzCenterPrimaryTarget{"kortzcenterheistprimarytarget", "Primary Target", "Primary target", kortzCenterTargets, 0};

		static std::vector<std::pair<int, const char*>> kortzCenterLoadoutTypes = {
		    {0, "None"},
		    {1, "Street"},
		    {2, "Security"},
		    {3, "Military"}
		};
		static ListCommand _KortzCenterLoadoutType{"kortzcenterheistloadouttype", "Loadout Type", "Loadout type", kortzCenterLoadoutTypes, 0};

		static std::vector<std::pair<int, const char*>> kortzCenterManchezColors = {
		    {0, "Red"},
		    {1, "Blue"},
		    {2, "Green"},
		    {3, "Yellow"}
		};
		static BoolCommand _KortzCenterScopeOut{"kortzcenterheistscopeout", "Scope Out", "Scope out Kortz Center", true};
		static BoolCommand _KortzCenterScopeSecondary{"kortzcenterheistscopesecondary", "Secondary Targets", "Scope secondary targets", true};
		static BoolCommand _KortzCenterScopePOI{"kortzcenterheistscopepoi", "Points of Interest", "Scope points of interest", true};
		static BoolCommand _KortzCenterAlphaMail{"kortzcenterheistalphamail", "Alpha Mail Disguise", "Alpha mail disguise", true};
		static BoolCommand _KortzCenterHazmat{"kortzcenterheisthazmat", "Hazmat Suit", "Hazmat suit", true};
		static BoolCommand _KortzCenterManholeKey{"kortzcenterheistmanholekey", "Manhole Key", "Required for sewer entrance", true};
		static BoolCommand _KortzCenterTacticalEquip{"kortzcenterheisttacticalequip", "Tactical Equipment", "Tactical equipment", true};
		static BoolCommand _KortzCenterStaffKeycard{"kortzcenterheiststaffkeycard", "Staff Key Card", "Staff key card", true};
		static BoolCommand _KortzCenterUnmarkedWeapons{"kortzcenterheistunmarkedweapons", "Unmarked Weapons", "Unmarked weapons", true};
		static BoolCommand _KortzCenterCaracara{"kortzcenterheistcaracara", "Armored Caracara", "Armored Caracara", true};
		static BoolCommand _KortzCenterAnnihilator{"kortzcenterheistannihilator", "Annihilator Stealth", "Annihilator stealth", true};
		static BoolCommand _KortzCenterManchez{"kortzcenterheistmanchez", "Manchez", "Manchez", true};
		static ListCommand _KortzCenterManchezColor{"kortzcenterheistmanchezcolor", "Manchez Color", "Manchez color", kortzCenterManchezColors, 0};
		static BoolCommand _KortzCenterHardMode{"kortzcenterheisthardmode", "Hard Mode", "Hard mode enabled", true};
		static BoolCommand _KortzCenterWeakGuards{"kortzcenterheistweakguards", "Weak Guards", "Weak guards enabled", true};
		static BoolCommand _KortzCenterHackingDevice{"kortzcenterheisthackingdevice", "Hacking Device", "Hacking device", true};
		static BoolCommand _KortzCenterAccessCode{"kortzcenterheistaccesscode", "Access Code", "Access code", true};
		static BoolCommand _KortzCenterGuardShipments{"kortzcenterheistguardshipments", "Guard Shipments", "Guard shipments", true};
		static BoolCommand _KortzCenterGuardRoutes{"kortzcenterheistguardroutes", "Guard Routes (Buy)", "Guard routes purchased", true};
		static BoolCommand _KortzCenterGlassCutter{"kortzcenterheistglasscutter", "Glass Cutter (Buy)", "Glass cutter purchased", true};
		static BoolCommand _KortzCenterPowerDrills{"kortzcenterheistpowerdrills", "Power Drills (Buy)", "Power drills purchased", true};
		static BoolCommand _KortzCenterEMPCharges{"kortzcenterheistempcharges", "EMP Charges (Buy)", "EMP charges purchased", true};
		static BoolCommand _KortzCenterGuardRoutesPrep{"kortzcenterheistguardroutesprep", "Guard Routes (Prep)", "Guard routes prep", true};
		static BoolCommand _KortzCenterGlassCutterPrep{"kortzcenterheistglasscutterprep", "Glass Cutter (Prep)", "Glass cutter prep", true};
		static BoolCommand _KortzCenterPowerDrillsPrep{"kortzcenterheistpowerdrillsprep", "Power Drills (Prep)", "Power drills prep", true};
		static BoolCommand _KortzCenterPrepEMP{"kortzcenterheistprepemp", "EMP Charges (Prep)", "EMP charges prep", true};

		class SkipFingerprint : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
					*ScriptLocal(thread, 26866).As<int*>() = 5;
			}
		};

		class SkipSignalNodes : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
					*ScriptLocal(thread, 27914).As<int*>() = 5;
			}
		};

		class SkipDataCrack : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
				{
					for (int i = 0; i <= 7; i++)
						*ScriptLocal(thread, 1388).At(i, 4).As<int*>() = 1;
				}
			}
		};

		class CutGlass : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
					*ScriptLocal(thread, 32855 + 3).At(4, 13).As<float*>() = 100.0f;
			}
		};

		class DisableLaserGrid : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
				{
					*ScriptLocal(thread, 70416).As<int*>() = 4294784;
					*ScriptGlobal(1935711).As<int*>() = 1;
				}
			}
		};

		class EnterAccessCode : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				FiberPool::Push([] {
					if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
					{
						for (int i = 0; i <= 2; i++)
						{
							*ScriptLocal(thread, 32820).At(i, 2).As<int*>() = 0;
							ScriptMgr::Yield(100ms);
							PAD::SET_CONTROL_VALUE_NEXT_FRAME(0, 237, 1.0f);
						}
					}
				});
			}
		};

		class TakePrimaryTarget : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				FiberPool::Push([] {
					if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
					{
						*ScriptLocal(thread, 29355 + 11).As<int*>() = 15;
						*ScriptLocal(thread, 29355 + 11).As<int*>() = 17;
						ScriptMgr::Yield(1000ms);
						PAD::SET_CONTROL_VALUE_NEXT_FRAME(0, 237, 1.0f);
					}
				});
			}
		};

		class TakeSecondaryTarget : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				if (auto thread = Scripts::FindScriptThread("fm_mission_controller_v3"_J))
				{
					*ScriptLocal(thread, 29355 + 11).As<int*>() = 3;
					PAD::SET_CONTROL_VALUE_NEXT_FRAME(0, 219, 1.0f);
				}
			}
		};

		class Setup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				int generalBits = -1;
				if (!_KortzCenterGuardRoutes.GetState()) generalBits &= ~(1 << 5);
				if (!_KortzCenterGlassCutter.GetState()) generalBits &= ~(1 << 6);
				if (!_KortzCenterPowerDrills.GetState()) generalBits &= ~(1 << 7);
				if (!_KortzCenterEMPCharges.GetState()) generalBits &= ~(1 << 8);

				int loadoutType = _KortzCenterLoadoutType.GetState();
				if (loadoutType != 1) generalBits &= ~(1 << 9);  // Street Loadout
				if (loadoutType != 2) generalBits &= ~(1 << 10); // Security Loadout
				if (loadoutType != 3) generalBits &= ~(1 << 11); // Military Loadout

				bool manchez = _KortzCenterManchez.GetState();
				int manchezColor = _KortzCenterManchezColor.GetState();
				if (!(manchez && manchezColor == 0)) generalBits &= ~(1 << 17); // Red Manchez
				if (!(manchez && manchezColor == 1)) generalBits &= ~(1 << 18); // Blue Manchez
				if (!(manchez && manchezColor == 2)) generalBits &= ~(1 << 19); // Green Manchez
				if (!(manchez && manchezColor == 3)) generalBits &= ~(1 << 20); // Yellow Manchez

				if (!_KortzCenterManholeKey.GetState()) generalBits &= ~(1 << 27);
				if (!_KortzCenterHardMode.GetState()) generalBits &= ~(1 << 28);
				if (!_KortzCenterWeakGuards.GetState()) generalBits &= ~(1 << 31);

				int robberyProg = -1;
				if (!_KortzCenterScopeOut.GetState()) robberyProg &= ~(1 << 0);
				if (!_KortzCenterAlphaMail.GetState()) robberyProg &= ~(1 << 1);
				if (!_KortzCenterHazmat.GetState()) robberyProg &= ~(1 << 2);
				if (!_KortzCenterStaffKeycard.GetState()) robberyProg &= ~(1 << 3);
				if (!_KortzCenterTacticalEquip.GetState()) robberyProg &= ~(1 << 4);
				if (!_KortzCenterHackingDevice.GetState()) robberyProg &= ~(1 << 5);
				if (!_KortzCenterAccessCode.GetState()) robberyProg &= ~(1 << 6);
				if (!_KortzCenterUnmarkedWeapons.GetState()) robberyProg &= ~(1 << 7);
				if (!_KortzCenterCaracara.GetState()) robberyProg &= ~(1 << 8);
				if (!_KortzCenterAnnihilator.GetState()) robberyProg &= ~(1 << 9);
				if (!manchez) robberyProg &= ~(1 << 10);
				if (!_KortzCenterPrepEMP.GetState()) robberyProg &= ~(1 << 11);
				if (!_KortzCenterGuardShipments.GetState()) robberyProg &= ~(1 << 12);
				if (!_KortzCenterGuardRoutesPrep.GetState()) robberyProg &= ~(1 << 13);
				if (!_KortzCenterGlassCutterPrep.GetState()) robberyProg &= ~(1 << 14);
				if (!_KortzCenterPowerDrillsPrep.GetState()) robberyProg &= ~(1 << 15);

				int scopingBS = _KortzCenterScopeSecondary.GetState() ? -1 : 0;
				int poiBS = _KortzCenterScopePOI.GetState() ? -1 : 0;

				Stats::SetInt("MPX_K26_GENERAL_BS", generalBits);
				Stats::SetInt("MPX_K26_GENERAL_BS2", -1);
				Stats::SetInt("MPX_K26_ROBBERY_PROG", robberyProg);
				Stats::SetInt("MPX_K26_HEIST_TARGET", _KortzCenterPrimaryTarget.GetState());
				Stats::SetInt("MPX_K26_SCOPING_BS", scopingBS);
				Stats::SetInt("MPX_K26_POI_BS", poiBS);
			}
		};

		static SkipFingerprint _KortzCenterSkipFingerprint{"kortzcenterheistskipfingerprint", "Skip Fingerprint Hack", "Skips fingerprint hacking minigame in computer room"};
		static SkipSignalNodes _KortzCenterSkipSignalNodes{"kortzcenterheistskipsignalnodes", "Skip Signal Nodes", "Skips signal nodes hacking at vault keypad"};
		static SkipDataCrack _KortzCenterSkipDataCrack{"kortzcenterheistskipdatacrack", "Skip Data Crack", "Skips data crack minigame"};
		static EnterAccessCode _KortzCenterEnterAccessCode{"kortzcenterheistenteraccesscode", "Enter Access Code", "Automatically enters the access code at the keypad"};
		static CutGlass _KortzCenterCutGlass{"kortzcenterheistcutglass", "Cut Glass", "Cuts display case glass instantly"};
		static DisableLaserGrid _KortzCenterDisableLaser{"kortzcenterheistdisablelaser", "Disable Laser Grid", "Disables laser security grid"};
		static TakePrimaryTarget _KortzCenterTakePrimary{"kortzcenterheisttakeprimary", "Take Primary Target", "Takes primary target painting (stand near it)"};
		static TakeSecondaryTarget _KortzCenterTakeSecondary{"kortzcenterheisttakesecondary", "Take Secondary Target", "Takes secondary loot (stand near it)"};
		static Setup _KortzCenterSetup{"kortzcenterheistsetup", "Setup", "Sets up Kortz Center heist"};
	}
}
