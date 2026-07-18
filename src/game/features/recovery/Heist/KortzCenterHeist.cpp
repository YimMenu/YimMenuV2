#include "core/commands/Command.hpp"
#include "core/commands/BoolCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "core/commands/IntCommand.hpp"
#include "game/gta/Stats.hpp"

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

		// --- General Purchases (MPX_K26_GENERAL_BS bits 5-8) ---
		static BoolCommand _KortzCenterGuardRoutes{"kortzcenterheistguardroutes", "Guard Routes", "Guard routes purchased", true};
		static BoolCommand _KortzCenterGlassCutter{"kortzcenterheistglasscutter", "Glass Cutter", "Glass cutter purchased", true};
		static BoolCommand _KortzCenterPowerDrills{"kortzcenterheistpowerdrills", "Power Drills", "Power drills purchased", true};
		static BoolCommand _KortzCenterEMPCharges{"kortzcenterheistempcharges", "EMP Charges", "EMP charges purchased", true};

		// --- Prep Work (MPX_K26_ROBBERY_PROG bits 0-15) ---
		static BoolCommand _KortzCenterScopeOut{"kortzcenterheistscopeout", "Scope Out", "Scope out Kortz Center", true};
		static BoolCommand _KortzCenterAlphaMail{"kortzcenterheistalphamail", "Alpha Mail Disguise", "Alpha mail disguise", true};
		static BoolCommand _KortzCenterHazmat{"kortzcenterheisthazmat", "Hazmat Suit", "Hazmat suit", true};
		static BoolCommand _KortzCenterStaffKeycard{"kortzcenterheiststaffkeycard", "Staff Key Card", "Staff key card", true};
		static BoolCommand _KortzCenterTacticalEquip{"kortzcenterheisttacticalequip", "Tactical Equipment", "Tactical equipment", true};
		static BoolCommand _KortzCenterHackingDevice{"kortzcenterheisthackingdevice", "Hacking Device", "Hacking device", true};
		static BoolCommand _KortzCenterAccessCode{"kortzcenterheistaccesscode", "Access Code", "Access code", true};
		static BoolCommand _KortzCenterUnmarkedWeapons{"kortzcenterheistunmarkedweapons", "Unmarked Weapons", "Unmarked weapons", true};
		static BoolCommand _KortzCenterCaracara{"kortzcenterheistcaracara", "Armored Caracara", "Armored Caracara", true};
		static BoolCommand _KortzCenterAnnihilator{"kortzcenterheistannihilator", "Annihilator Stealth", "Annihilator stealth", true};
		static BoolCommand _KortzCenterManchez{"kortzcenterheistmanchez", "Manchez", "Manchez", true};
		static BoolCommand _KortzCenterPrepEMP{"kortzcenterheistprepemp", "EMP Charges (Prep)", "EMP charges prep", true};
		static BoolCommand _KortzCenterGuardShipments{"kortzcenterheistguardshipments", "Guard Shipments", "Guard shipments", true};
		static BoolCommand _KortzCenterGuardRoutesPrep{"kortzcenterheistguardroutesprep", "Guard Routes (Prep)", "Guard routes prep", true};
		static BoolCommand _KortzCenterGlassCutterPrep{"kortzcenterheistglasscutterprep", "Glass Cutter (Prep)", "Glass cutter prep", true};
		static BoolCommand _KortzCenterPowerDrillsPrep{"kortzcenterheistpowerdrillsprep", "Power Drills (Prep)", "Power drills prep", true};

		// --- Scoping ---
		static BoolCommand _KortzCenterScopeSecondary{"kortzcenterheistscopesecondary", "Secondary Targets", "Scope secondary targets", true};
		static BoolCommand _KortzCenterScopePOI{"kortzcenterheistscopepoi", "Points of Interest", "Scope points of interest", true};

		// --- Cooldown Resets ---
		class ResetCooldown : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_K26_HEIST_COOLDOWN", 0);
			}
		};

		class ResetCooldownHard : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_K26_HEIST_COOLDOWN_HARD", 0);
			}
		};

		// --- Manhole Key Location ---
		static std::vector<std::pair<int, const char*>> manholeKeyLocs = {
		    {0,  "Random"},
		    {1,  "Garage A"},
		    {2,  "Garage B"},
		    {3,  "Garage C"},
		    {4,  "Office Desk"},
		    {5,  "Security Room"},
		    {6,  "Cafeteria"},
		    {7,  "Maintenance"},
		    {8,  "Parking L2"},
		    {9,  "Parking L3"},
		    {10, "Rooftop"},
		    {11, "Alley Trash"},
		    {12, "Construction"},
		    {13, "Subway"},
		    {14, "Bus Stop"},
		    {15, "Street Drain"}
		};
		static ListCommand _KortzCenterKeyLoc{"kortzcenterheistkeyloc", "Manhole Key", "Manhole key location", manholeKeyLocs, 0};

		class SetKeyLoc : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_K26_MANHOLE_KEY_LOC", _KortzCenterKeyLoc.GetState());
			}
		};

		// --- Secondary Loot Seed ---
		static IntCommand _KortzCenterSeed{"kortzcenterheistseed", "Loot Seed", "Seed for secondary loot value", 0, 9999, 0};

		class SetSeed : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				Stats::SetInt("MPX_K26_HEIST_SEED", _KortzCenterSeed.GetState());
			}
		};

		// --- Setup ---
		class Setup : public Command
		{
			using Command::Command;

			virtual void OnCall() override
			{
				// GENERAL_BS: start at -1 (all bits set), clear unchecked bits
				int generalBits = -1;
				if (!_KortzCenterGuardRoutes.GetState())   generalBits &= ~(1 << 5);
				if (!_KortzCenterGlassCutter.GetState())   generalBits &= ~(1 << 6);
				if (!_KortzCenterPowerDrills.GetState())   generalBits &= ~(1 << 7);
				if (!_KortzCenterEMPCharges.GetState())    generalBits &= ~(1 << 8);

				// ROBBERY_PROG: start at -1, clear unchecked bits
				int robberyProg = -1;
				if (!_KortzCenterScopeOut.GetState())        robberyProg &= ~(1 << 0);
				if (!_KortzCenterAlphaMail.GetState())       robberyProg &= ~(1 << 1);
				if (!_KortzCenterHazmat.GetState())          robberyProg &= ~(1 << 2);
				if (!_KortzCenterStaffKeycard.GetState())    robberyProg &= ~(1 << 3);
				if (!_KortzCenterTacticalEquip.GetState())   robberyProg &= ~(1 << 4);
				if (!_KortzCenterHackingDevice.GetState())   robberyProg &= ~(1 << 5);
				if (!_KortzCenterAccessCode.GetState())      robberyProg &= ~(1 << 6);
				if (!_KortzCenterUnmarkedWeapons.GetState()) robberyProg &= ~(1 << 7);
				if (!_KortzCenterCaracara.GetState())        robberyProg &= ~(1 << 8);
				if (!_KortzCenterAnnihilator.GetState())     robberyProg &= ~(1 << 9);
				if (!_KortzCenterManchez.GetState())         robberyProg &= ~(1 << 10);
				if (!_KortzCenterPrepEMP.GetState())         robberyProg &= ~(1 << 11);
				if (!_KortzCenterGuardShipments.GetState())  robberyProg &= ~(1 << 12);
				if (!_KortzCenterGuardRoutesPrep.GetState()) robberyProg &= ~(1 << 13);
				if (!_KortzCenterGlassCutterPrep.GetState()) robberyProg &= ~(1 << 14);
				if (!_KortzCenterPowerDrillsPrep.GetState()) robberyProg &= ~(1 << 15);

				// Scoping
				int scopingBS = _KortzCenterScopeSecondary.GetState() ? -1 : 0;
				int poiBS     = _KortzCenterScopePOI.GetState() ? -1 : 0;

				// Write all stats
				Stats::SetInt("MPX_K26_GENERAL_BS", generalBits);
				Stats::SetInt("MPX_K26_GENERAL_BS2", -1);
				Stats::SetInt("MPX_K26_ROBBERY_PROG", robberyProg);
				Stats::SetInt("MPX_K26_HEIST_TARGET", _KortzCenterPrimaryTarget.GetState());
				Stats::SetInt("MPX_K26_SCOPING_BS", scopingBS);
				Stats::SetInt("MPX_K26_POI_BS", poiBS);
			}
		};

		static Setup _KortzCenterSetup{"kortzcenterheistsetup", "Setup", "Sets up Kortz Center heist"};

		// Static instances for new commands
		static ResetCooldown _KortzCenterResetCooldown{"kortzcenterheistresetcd", "Reset Cooldown", "Resets the normal heist cooldown"};
		static ResetCooldownHard _KortzCenterResetCooldownHard{"kortzcenterheistresethardcd", "Reset Hard Cooldown", "Resets the hard mode cooldown"};
		static SetKeyLoc _KortzCenterSetKeyLoc{"kortzcenterheistsetkeyloc", "Set Key Location", "Sets the manhole key location"};
		static SetSeed _KortzCenterSetSeed{"kortzcenterheistsetseed", "Set Loot Seed", "Sets the secondary loot seed value"};
	}
}
