#include "StatEditor.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/Natives.hpp"
#include "game/gta/Stats.hpp"
#include "core/frontend/Notifications.hpp"
#include "types/stats/CStatsMgr.hpp"
#include "core/frontend/manager/UIManager.hpp"
#include <functional>
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <format>

namespace YimMenu::Submenus
{
	// --- Constants Namespace ---
	namespace UnlockData
	{
		// Structure to hold unlock item data
		struct UnlockItem
		{
			std::string name;
			std::function<void()> action;
			bool isCategoryUnlockAll = false; // Flag to identify the old "Unlock All" items
		};

	} // namespace UnlockData

	// --- Stat Helper Functions ---
	// Use static helpers directly within this file
	static void SetPackedStatBool(int index, bool value) { Stats::SetPackedBool(index, value); }
	static void SetPackedBoolsRanged(int startIdx, int endIdx, bool value) {
		for (int i = startIdx; i <= endIdx; i++) SetPackedStatBool(i, value);
	}
	static void SetPackedStatInt(int index, int value) { Stats::SetPackedInt(index, value); }
	static void SetMpIntCharacterStat(const char* stat, int value) { Stats::SetInt(stat, value); }
	// Overload for bool stats that might be represented as 0/1 ints
	static void SetMpIntCharacterStat(const char* stat, bool value) { Stats::SetInt(stat, value ? 1 : 0); } 
	static void SetMpIntCharacterStatBit(const char* stat, int bit, bool value) {
		int currentValue = Stats::GetInt(stat);
		if (value) currentValue |= (1 << bit); else currentValue &= ~(1 << bit);
		Stats::SetInt(stat, currentValue);
	}
	static void SetMpIntCharacterStatBits(const char* stat, int startBit, int endBit, bool value) {
		int currentValue = Stats::GetInt(stat);
		for (int i = startBit; i <= endBit; i++) {
			if (value) currentValue |= (1 << i); else currentValue &= ~(1 << i);
		}
		Stats::SetInt(stat, currentValue);
	}
	// Use STATS:: native for awards as before
	static void SetMpIntAwardCharacterStat(const char* stat, int value) {
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY(stat), value, true);
	}
	// Helper for Bool Awards using STATS:: native
	static void SetMpBoolAwardCharacterStat(const char* stat, bool value) {
		STATS::STAT_SET_BOOL(MISC::GET_HASH_KEY(stat), value, true); 
	}


	// --- Unlock Categories Data ---
	// Use std::map for ordered categories in UI
	static std::map<std::string, std::vector<UnlockData::UnlockItem>> unlockCategories = {
		// --- ADVERSARY MODS ---
		{
			"ADVERSARY MODS", {
				{"Participate in any Adversary Mode", []() { SetPackedBoolsRanged(41594, 41646, true); }}, // Note: Broad range covers many modes
				{"Participate in the Featured Series", []() { SetPackedStatBool(36840, true); }},
				{"Win 5 Adversary Modes", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_ADV_WINS", 50); }}, // Set higher to cover tier 3&4 too
				{"Participate in 10 different Adversary Modes", []() { SetPackedBoolsRanged(41594, 41646, true); }},
				{"Win 20 Adversary Modes", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_ADV_WINS", 50); }}, // Set higher to cover tier 4 too
				{"Participate in 25 different Adversary Modes", []() { 
                    SetPackedBoolsRanged(41594, 41646, true); 
                    SetPackedBoolsRanged(41656, 41646, true); // These might overlap or be specific sets, set both just in case
                    SetPackedBoolsRanged(51339, 41646, true); 
                }},
				{"Win 50 Adversary Modes", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_ADV_WINS", 50); }},
				{"Win 5 Adversary Modes in a row", []() { SetPackedStatBool(36921, true); }},
			}
		},
        // --- AGENTS OF SABOTAGE ---
        {
            "AGENTS OF SABOTAGE", {
                {"Acquire the Garment Factory", []() { SetMpIntCharacterStat("mpx_INT_STAT_HACKER_DEN_OWNED", 1); }},
                {"Meet with Pavel", []() { SetPackedStatBool(9539, true); }},
                {"Complete a File", []() { SetPackedStatInt(24903, 25); }}, // Set to max tier goal
                {"Complete 5 Files", []() { SetPackedStatInt(24903, 25); }}, // Set to max tier goal
                {"Complete 2 Files without losing a life", []() { SetPackedStatInt(24904, 2); }},
                {"Earn $25,000,000 in additional Garment Factory earnings", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_DEN24_SAFEEARNINGS", 100000); }}, // Set to max tier goal
                {"Complete all the Files", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_HACKER24_GEN_BS", 5, 12, true); }},
                {"Complete the Priority File 2 weeks in a row", []() { SetPackedStatBool(9549, true); }},
                {"Complete all mission challenges for a File", []() { SetPackedStatBool(9542, true); }}, // Single file challenge
                {"Unlock 9 platinum awards for Agents of Sabotage", []() { SetPackedStatInt(24905, 9); }},
                {"Complete 25 Files", []() { SetPackedStatInt(24903, 25); }},
                {"Complete all mission challenges for all Files", []() { SetPackedBoolsRanged(9543, 9546, true); }},
                {"Earn $100,000 in additional Garment Factory earnings", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_DEN24_SAFEEARNINGS", 100000); }},
            }
        },
		// --- AFTER HOURS ---
		{
			"AFTER HOURS", {
				{"Set up a Nightclub", []() { SetPackedStatBool(22067, true); }},
				{"Complete a Club Management mission", []() { SetMpIntCharacterStat("mpx_INT_STAT_NIGHTCLUB_JOBS_DONE", 25); }}, // Set to higher tier goal
				{"Dance for 5 minutes inside a Nightclub", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_DANCE_DUR", 5); }},
				{"Hire a second Resident DJ", []() { SetPackedStatBool(15533, true); SetPackedBoolsRanged(22082, 22083, true); }},
				{"Source Goods for your Nightclub Basement", []() { SetPackedStatBool(36868, true); }},
				{"Eject a troublemaker from your Nightclub", []() { SetPackedStatBool(36944, true); }},
				{"Hire all Resident DJs", []() { // Combines T1 DJ + T2 DJ + T3 goal
                    SetPackedStatBool(28260, true); // Tale of Us
                    SetPackedStatBool(28261, true); // Solomun
                    SetPackedStatBool(28262, true); // Dixon
                    SetPackedStatBool(28263, true); // Black Madonna
                    SetPackedStatBool(15533, true); // Hire a second DJ flag
                    SetPackedBoolsRanged(22082, 22083, true); // Specific hire flags
                }},
				{"Fill up your Nightclub safe", []() { SetPackedStatBool(41989, true); }},
				{"Complete 25 Club Management missions", []() { SetMpIntCharacterStat("mpx_INT_STAT_NIGHTCLUB_JOBS_DONE", 25); }},
				{"Unlock 8 Platinum Awards for After Hours", []() { SetPackedStatInt(42089, 8); }},
				{"Have 25 celebrity appearances at your Nightclub", []() { SetMpIntCharacterStat("mpx_INT_STAT_NIGHTCLUB_VIP_APPEAR", 25); }},
				{"Keep your Nightclub popularity at 100% for 10 hours", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_NCLUB_POP_MAX_TME", 600); }}, // Value is likely minutes or ticks, 600 = 10 hours
				{"Earn a total of $50,000,000 or more", []() { SetMpIntCharacterStat("mpx_INT_STAT_HUB_EARNINGS", 50000000); }}, // Note: This is a general earnings stat, not specific to Nightclub only
                // Included from old "NIGHTLIFE AND MORE" section if relevant and distinct
                {"Buy a Terrorbyte", []() { SetMpIntCharacterStat("mpx_INT_STAT_SET_HUB_OWNED", 1); }}, // If Terrorbyte ownership is separate
                {"Set up a VIP client", []() { SetPackedStatBool(27991, true); }},
                {"Complete Client Jobs for Paige", []() { SetPackedStatBool(27992, true); }},
                {"Collect $10,000,000 from safe", []() { SetMpIntCharacterStat("mpx_INT_STAT_NIGHTCLUB_EARNINGS", 10000000); SetPackedStatBool(41989, true); }}, // Combined fill and earnings
                {"Earn $20,000,000 from sales", []() { SetMpIntCharacterStat("mpx_INT_STAT_NIGHTCLUB_HUB_PRODUCT_LIFETIME_SELL", 20000000); }}, // Specific sales stat
                // Included from old "AFTER HOURS" section if relevant and distinct
                {"Complete DJ Tale of Us mission", []() { SetPackedStatBool(28260, true); }},
                {"Complete DJ Solomun mission", []() { SetPackedStatBool(28261, true); }},
                {"Complete DJ Dixon mission", []() { SetPackedStatBool(28262, true); }},
                {"Complete DJ Black Madonna mission", []() { SetPackedStatBool(28263, true); }},
                {"Buy all Nightclub upgrades", []() { SetPackedStatBool(28264, true); }},
                {"Dance with other players", []() { SetPackedStatBool(28265, true); }},
                {"Unlock hidden DJ missions", []() { SetPackedStatBool(28269, true); }},
                {"Reach Nightclub level 20", []() { SetMpIntCharacterStat("mpx_INT_STAT_NIGHTCLUB_LIFETIME_DJ_POPULARITY", 100); }}, // Pop relates to level
			}
		},
		// --- ARENA WAR ---
		{
			"ARENA WAR", {
				{"Set up an Arena Workshop", []() { SetPackedStatBool(25009, true); }},
                {"Win an Arena Mode", []() { SetPackedBoolsRanged(41647, 41655, true); }}, // Broad range covers Tier 2 Obj 1 & Tier 3 Obj 2
				{"Reach skill level 5", []() { SetPackedStatInt(22063, 20); }}, // Set to max tier goal
                {"Reach Sponsorship Tier 25", []() { SetMpIntCharacterStat("mpx_INT_STAT_ARENAWARS_AP_TIER", 50); }}, // Set to max tier goal
                {"Win all the Arena Modes", []() { SetPackedBoolsRanged(41647, 41655, true); }},
                {"Unlock 15 Platinum Awards for Arena Wars", []() { SetPackedStatInt(42088, 15); }},
                {"Earn skill level 20 in Arena Wars", []() { SetPackedStatInt(22063, 20); }}, // Using 22063 based on comment T2, 42000 seems unrelated
                {"Reach Sponsorship Tier 50", []() { SetMpIntCharacterStat("mpx_INT_STAT_ARENAWARS_AP_TIER", 50); }},
                // Kept from original code if distinct/useful:
				{"Unlock all Arena War vehicles", []() { SetPackedStatBool(28171, true); }},
				{"Unlock Pegasus Trophy Truck", []() { SetPackedStatBool(28172, true); }},
				{"Unlock Space Docker vehicle", []() { SetPackedStatBool(28173, true); }},
				{"Unlock Taxi vehicle", []() { SetPackedStatBool(28174, true); }},
				{"Unlock Dozer vehicle", []() { SetPackedStatBool(28175, true); }},
				{"Unlock Go Go Monkey Blista", []() { SetPackedStatBool(28176, true); }},
				{"Unlock Clown Van", []() { SetPackedStatBool(28177, true); }},
				{"Unlock Trashmaster", []() { SetPackedStatBool(28178, true); }},
				{"Unlock Barracks Semi", []() { SetPackedStatBool(28179, true); }},
			}
		},
		// --- BIKERS ---
		{
			"BIKERS", {
				{"Become President of a Motorcycle Club", []() { SetPackedStatBool(36871, true); }},
				{"Hire a player to join your Motorcycle Club", []() { SetPackedStatBool(36872, true); }},
				{"Complete a Clubhouse Contract", []() { SetPackedBoolsRanged(36875, 36887, true); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_BIK_CONTRACT_COUNT", 50); }}, // Set bool range and max count
				{"Deliver a customer bike", []() { SetPackedStatBool(36873, true); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_BIK_CUST_DEL_CASH", 2500000); }}, // Set bool and max earnings
				{"Set up any Biker business", []() { SetPackedStatBool(42001, true); }},
				{"Complete a Resupply mission for any Biker business", []() { SetPackedStatBool(36874, true); }},
				{"Complete all Clubhouse Contracts", []() { SetPackedBoolsRanged(36875, 36887, true); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_BIK_CONTRACT_COUNT", 50); }}, // Set bool range and max count
				{"Sell Product from all Biker businesses", []() {
                    SetMpIntCharacterStat("mpx_INT_STAT_LIFETIME_BKR_SELL_COMPLETBC", 1); // Counterfeit Cash
                    SetMpIntCharacterStat("mpx_INT_STAT_LIFETIME_BKR_SEL_COMPLETBC1", 1); // Weed Farm
                    SetMpIntCharacterStat("mpx_INT_STAT_LIFETIME_BKR_SEL_COMPLETBC2", 1); // Document Forgery
                    SetMpIntCharacterStat("mpx_INT_STAT_LIFETIME_BKR_SEL_COMPLETBC3", 1); // Meth Lab
                    SetMpIntCharacterStat("mpx_INT_STAT_LIFETIME_BKR_SEL_COMPLETBC4", 1); // Cocaine Lockup
                }},
				{"Resupply the Clubhouse bar 10 times", []() { SetMpIntCharacterStat("mpx_INT_STAT_BAR_RESUPPLY_CR", 10); }},
				{"Earn $25,000,000 selling Product", []() { SetMpIntCharacterStat("mpx_INT_STAT_LIFETIME_BKR_SELL_EARNINGS0", 25000000); }}, // Index 0 seems to be total MC earnings
				{"Earn $2,500,000 delivering customer bikes", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_BIK_CUST_DEL_CASH", 2500000); }},
				{"Earn $500,000 from your Clubhouse bar", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_CLBH_BAR_EARNINGS", 500000); }},
				{"Complete 50 Clubhouse Contracts", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_BIK_CONTRACT_COUNT", 50); SetPackedBoolsRanged(36875, 36887, true); }}, // Max count and range bools
                // Kept from original code if distinct/useful:
				{"Purchase a Motorcycle Clubhouse", []() { SetPackedStatBool(24123, true); SetPackedStatBool(36871, true); }}, // Set both flags if different
				{"Purchase all MC Businesses", []() {
					SetPackedBoolsRanged(18161, 18165, true); // Ownership flags?
					SetPackedBoolsRanged(22066, 22070, true); // Setup flags?
                    SetPackedStatBool(42001, true); // Set up ANY business flag too
				}},
				{"Complete all MC Business setup missions", []() { SetPackedBoolsRanged(15411, 15415, true); }},
				{"Complete all MC Challenges", []() { SetPackedBoolsRanged(15381, 15390, true); }},
				{"Complete all MC Club Work", []() { SetPackedBoolsRanged(15391, 15400, true); }},
				{"Have all MC Business upgrades", []() { SetPackedBoolsRanged(22071, 22085, true); }},
				{"Store 10 motorcycles in clubhouse", []() { SetPackedStatBool(24124, true); }},
			}
		},
        // --- BOTTOM DOLLAR BOUNTIES ---
        {
            "BOTTOM DOLLAR BOUNTIES", {
                {"Set up a Bail Office", []() { SetMpIntCharacterStat("mpx_INT_STAT_BAIL_OFFICE_OWNED", 1); }},
                {"Meet with Maude Eccles", []() { SetPackedStatBool(9537, true); }}, // Using 9537 as 5445E4F likely hash
                {"Secure or eliminate a bounty target", []() { SetPackedStatBool(7639, true); }},
                {"Secure or eliminate 5 Standard bounty targets", []() { SetPackedStatInt(7669, 10); SetPackedStatInt(7671, 25); }}, // Set higher tier goals too
                {"Secure or eliminate 2 Most Wanted bounty targets", []() { SetPackedStatInt(7672, 2); SetPackedStatInt(7674, 3); }}, // Set higher tier goals too
                {"Earn $250,000 from bounties", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_BOUNTY_EARNINGS", 5000000); }}, // Set max tier goal
                {"Secure or eliminate 10 bounty targets without losing a life", []() { SetPackedStatInt(7670, 10); }},
                {"Secure or eliminate a Most Wanted bounty target 3 days in a row", []() { SetPackedStatInt(7674, 3); }},
                {"Secure or eliminate 25 bounty targets", []() { SetPackedStatInt(7671, 25); }},
                {"Unlock 10 platinum awards for Bottom Dollar Bounties", []() { SetPackedStatInt(26809, 10); }},
                {"Secure all bounty targets alive", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_BOUNTIES_ALIVE_BS", -1); }}, // Set all bits (31 = -1 signed)
                {"Earn $1,000,000 in additional income from Agents", []() { SetMpIntCharacterStat("mpx_INT_STAT_BAIL_PROPERTY_EARNINGS", 1000000); }},
                {"Earn $5,000,000 from bounties", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_BOUNTY_EARNINGS", 5000000); }},
            }
        },
		// --- BUNKER RESEARCH ---
		{
			"BUNKER RESEARCH", { // Note: These unlock items directly, doesn't complete 'research projects' stat
				{"Unlock all Mk I & II weapon upgrades", []() { SetPackedBoolsRanged(15447, 15460, true); }},
				{"Unlock all vehicle weapons", []() { SetPackedBoolsRanged(15461, 15474, true); }},
				{"Unlock all vehicle mods", []() { SetPackedBoolsRanged(15491, 15499, true); }},
				{"Unlock proximity mines", []() { SetPackedStatBool(15461, true); }},
				{"Unlock explosive ammo", []() { SetPackedStatBool(15447, true); }},
				{"Unlock hollow point ammo", []() { SetPackedStatBool(15448, true); }},
				{"Unlock incendiary ammo", []() { SetPackedStatBool(15449, true); }},
				{"Unlock FMJ ammo", []() { SetPackedStatBool(15450, true); }},
				{"Unlock armor piercing ammo", []() { SetPackedStatBool(15451, true); }},
				{"Unlock tracer ammo", []() { SetPackedStatBool(15452, true); }},
				{"Unlock heavy barrel", []() { SetPackedStatBool(15453, true); }},
				{"Unlock thermal scope", []() { SetPackedStatBool(15456, true); }},
				{"Unlock night vision scope", []() { SetPackedStatBool(15457, true); }},
				{"Unlock APC SAM battery", []() { SetPackedStatBool(15468, true); }},
				{"Unlock Tampa dual miniguns", []() { SetPackedStatBool(15471, true); }},
			}
		},
		// --- CAYO PERICO HEIST ---
		{
			"CAYO PERICO HEIST", { // Matches THE CAYO PERICO HEIST from comments
				{"Meet Miguel Madrazo", []() { SetPackedStatBool(30309, true); }},
				{"Set up a Kosatka", []() { SetPackedStatBool(30522, true); }},
				{"Find where the Madrazo files are being held", []() { SetMpIntCharacterStatBit("mpx_INT_STAT_H4_MISSIONS", 0, true); }},
				{"Complete The Cayo Perico Heist as a leader", []() { SetMpIntCharacterStatBit("mpx_INT_STAT_H4_PROGRESS", 1, true); }},
				{"Help Tom Connors or English Dave with a DJ request", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_H4_H4_DJ_MISSIONS", 0, 6, true); }}, // Covers all DJ reqs
				{"Find 10 treasure chests on Cayo Perico", []() { SetMpIntAwardCharacterStat("mpx_INT_AWARD_TREASURE_HUNTER", 10); }},
				{"Complete The Cayo Perico Heist on Hard difficulty", []() { SetPackedStatBool(41677, true); }},
				{"Complete 25 prep work missions without dying", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_CAYO_PRP_NO_DEATHS", 25); }},
				{"Complete all DJ requests for Tom Connors and English Dave", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_H4_H4_DJ_MISSIONS", 0, 6, true); }},
				{"Unlock 15 Platinum Awards for The Cayo Perico Heist", []() { SetPackedStatInt(42094, 15); }},
				{"Steal 5 variations of the primary target", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_H4_PROGRESS", 6, 11, true); }},
				{"Complete The Cayo Perico Heist using all approaches", []() {
					SetMpIntCharacterStat("mpx_INT_STAT_CR_SUBMARINE", 1);
					SetMpIntCharacterStat("mpx_INT_STAT_CR_STRATEGIC_BOMBER", 1);
					SetMpIntCharacterStat("mpx_INT_STAT_CR_SMUGGLER_PLANE", 1);
					SetMpIntCharacterStat("mpx_INT_STAT_CR_STEALTH_HELI", 1);
					SetMpIntCharacterStat("mpx_INT_STAT_CR_PATROL_BOAT", 1);
					SetMpIntCharacterStat("mpx_INT_STAT_CR_SMUGGLER_BOAT", 1);
				}},
				{"Steal $50,000,000 in primary and secondary targets", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_CAYO_H_EARNINGS", 50000000); }},
			}
		},
		// --- CHARACTER STATS ---
		{
			"CHARACTER STATS", { // Kept as is from original code
				{"Max Stamina", []() { SetMpIntCharacterStat("mpx_SCRIPT_INCREASE_STAM", 100); }},
				{"Max Strength", []() { SetMpIntCharacterStat("mpx_SCRIPT_INCREASE_STRN", 100); }},
				{"Max Flying", []() { SetMpIntCharacterStat("mpx_SCRIPT_INCREASE_FLY", 100); }},
				{"Max Stealth", []() { SetMpIntCharacterStat("mpx_SCRIPT_INCREASE_STL", 100); }},
				{"Max Lung Capacity", []() { SetMpIntCharacterStat("mpx_SCRIPT_INCREASE_LUNG", 100); }},
				{"Max Driving", []() { SetMpIntCharacterStat("mpx_SCRIPT_INCREASE_DRIV", 100); }},
				{"Max Shooting", []() { SetMpIntCharacterStat("mpx_SCRIPT_INCREASE_SHO", 100); }},
			}
		},
        // --- DEATHMATCHES ---
        {
            "DEATHMATCHES", {
                {"Participate in any Deathmatch", []() { SetMpIntCharacterStat("mpx_INT_STAT_DM_END", 1); }},
                {"Participate in a Team Deathmatch", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_DM_TDM_PLAYS", 1); }},
                {"Win 5 Deathmatches", []() { SetMpIntAwardCharacterStat("mpx_INT_AWARD_FM_DM_WINS", 50); }}, // Set max tier goal
                {"Play 10 Deathmatches in the Community Series", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_DM_COMMUNITY_PLAYS", 10); }},
                {"Win 20 Deathmatches", []() { SetMpIntAwardCharacterStat("mpx_INT_AWARD_FM_DM_WINS", 50); }}, // Set max tier goal
                {"Kill 5 players without dying 25 times during Deathmatches", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_DTHM_KILL_5_WO_DIE", 25); }},
                {"Win 50 Deathmatches", []() { SetMpIntAwardCharacterStat("mpx_INT_AWARD_FM_DM_WINS", 50); }},
                {"Win 5 Deathmatches in a row", []() { SetPackedStatBool(36922, true); }},
            }
        },
		// --- DIAMOND CASINO & HEIST ---
		{
			"DIAMOND CASINO & HEIST", { // Combines DIAMOND CASINO AND RESORT & DIAMOND CASINO HEIST
                // RESORT section based on comments
                {"Visit The Diamond Casino & Resort", []() { SetPackedStatBool(27089, true); }},
                {"Purchase a Penthouse and visit Agatha Baker", []() { SetPackedStatBool(27090, true); SetPackedStatBool(28291, true); }}, // Set both known flags
                {"Complete Loose Cheng", []() { SetMpIntCharacterStatBit("mpx_INT_STAT_VCM_FLOW_PROGRESS", 6, true); SetMpIntCharacterStatBit("mpx_INT_STAT_VCM_FLOW_PROGRESS", 12, true); }},
                {"Complete Cashing Out", []() { SetMpIntCharacterStatBit("mpx_INT_STAT_VCM_FLOW_PROGRESS", 11, true); SetMpIntCharacterStatBit("mpx_INT_STAT_VCM_FLOW_PROGRESS", 17, true); }},
                {"Recover the bonus item after completing Cashing Out", []() { SetPackedStatBool(36916, true); }},
                {"Complete Casino Work for Agatha Baker", []() { SetMpIntAwardCharacterStat("mpx_INT_AWARD_ODD_JOBS", 100); SetPackedBoolsRanged(36844, 36859, true); }}, // Set count & range
                {"Complete 13 different Casino Work missions", []() { SetPackedBoolsRanged(36844, 36859, true); SetMpIntAwardCharacterStat("mpx_INT_AWARD_ODD_JOBS", 100); }}, // Set range & count
                {"Complete all Casino Story Missions on Hard difficulty", []() { SetPackedBoolsRanged(41548, 41553, true); }},
                {"Take out Avery's bodyguards without being spotted in Cashing Out", []() { SetPackedStatBool(41868, true); }},
                {"Unlock 11 Platinum Awards for The Diamond Casino & Resort", []() { SetPackedStatInt(42093, 11); }},
                {"Complete all Casino Story Missions on Hard difficulty while taking less than 50% damage", []() { SetPackedBoolsRanged(41560, 41565, true); }},
                {"Complete all Casino Story Missions on Hard difficulty using only pistols", []() { SetPackedBoolsRanged(41554, 41559, true); }},
                {"Complete 100 Casino Work missions for Agatha Baker", []() { SetMpIntAwardCharacterStat("mpx_INT_AWARD_ODD_JOBS", 100); SetPackedBoolsRanged(36844, 36859, true); }}, // Set count & range
                // HEIST section based on comments / original code
				{"Meet Lester Crest at Mirror Park", []() { SetMpIntCharacterStatBit("mpx_INT_STAT_CAS_HEIST_FLOW", 1, true); }},
				{"Set up an Arcade", []() { SetPackedStatBool(28270, true); }},
				{"Scope the contents of the Casino Vault", []() { SetPackedStatBool(36842, true); }},
				{"Complete The Diamond Casino Heist as a leader", []() { SetMpIntCharacterStatBit("mpx_INT_STAT_CAS_HEIST_FLOW", 10, true); }},
				{"Complete 25 prep missions", []() { SetMpIntAwardCharacterStat("mpx_INT_AWARD_PREPARATION", 25); }},
				{"Play an arcade game", []() { SetPackedStatBool(32399, true); }},
				{"Complete The Diamond Casino Heist using all approaches", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_CAS_HEIST_FLOW", 11, 13, true); }},
				{"Unlock all crew members", []() { SetMpBoolAwardCharacterStat("mpx_BOOL_AWARD_CREWEDUP", true); }},
				{"Complete The Diamond Casino Heist in under 10 minutes on Hard difficulty", []() { SetPackedStatBool(42025, true); }},
				{"Unlock 15 Platinum Awards for The Diamond Casino Heist", []() { SetPackedStatBool(42086, true); }},
				{"Steal all variations of loot from the vault on Hard difficulty, without being spotted", []() { SetPackedBoolsRanged(41678, 41681, true); }},
				{"Steal $50,000,000 from the vault", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_CASINO_H_EARNINGS", 50000000); }},
				{"Steal $100,000 from the Daily Vault", []() { SetMpIntAwardCharacterStat("mpx_INT_AWARD_DAICASHCRAB", 100000); }},
                // Other items from old "DIAMOND CASINO AND RESORT" section
                {"Get all Twitch Prime rewards", []() { SetPackedStatBool(28292, true); }}, // If still relevant
                {"Collect all playing cards", []() { SetPackedStatBool(28294, true); }}, // If separate from awards
                {"Earn a VIP membership", []() { SetPackedStatBool(28302, true); }},
                {"Play all Casino Games", []() { SetPackedStatBool(28303, true); }},
                {"Win $1,000,000 from gambling", []() { SetMpIntCharacterStat("mpx_INT_STAT_CASINO_CHIPS_WON_GD", 1000000); }},
                {"Buy all Penthouse decorations", []() { SetPackedStatBool(28304, true); }},
			}
		},
		// --- THE DOOMSDAY HEIST ---
		{
			"THE DOOMSDAY HEIST", {
				{"Set up a Facility and meet Lester Crest", []() { SetPackedStatBool(18139, true); }},
				{"Set up The Data Breaches", []() { SetPackedStatBool(36861, true); }},
				{"Complete any Setup for The Data Breaches", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_GANGOPS_FLOW_BITSET_MISS0", 0, 2, true); }}, // Set all setups for Act 1
				{"Complete The Data Breaches as a leader", []() { SetPackedStatBool(41712, true); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_DOOMSDAY_ACTS", 15); }}, // Set flag and max acts count
				{"Set up The Bogdan Problem", []() { SetPackedStatBool(36862, true); }},
				{"Complete The Bogdan Problem as a leader", []() { SetPackedStatBool(41713, true); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_DOOMSDAY_ACTS", 15); }}, // Set flag and max acts count
				{"Set up The Doomsday Scenario", []() { SetPackedStatBool(36863, true); }},
				{"Complete The Doomsday Scenario as a leader", []() { SetPackedStatBool(41714, true); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_DOOMSDAY_ACTS", 15); }}, // Set flag and max acts count
				{"Complete 14 prep missions without dying", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_DOOM_PRP_NO_DEATHS", 14); }},
				{"Unlock 10 Platinum Awards for The Doomsday Heist", []() { SetPackedStatInt(42087, 10); }},
				{"Complete all 3 Acts using only pistols and vehicles", []() { SetPackedStatBool(41685, true); SetPackedStatBool(41690, true); SetPackedStatBool(41696, true); }},
				{"Complete the Elite Challenges for all 3 Acts", []() { SetPackedBoolsRanged(41697, 41699, true); }},
				{"Complete 15 Acts as a leader", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_DOOMSDAY_ACTS", 15); SetPackedStatBool(41712, true); SetPackedStatBool(41713, true); SetPackedStatBool(41714, true); }}, // Max count and leader flags
                // Items kept from old code if distinct
                {"Win an All-In-Order challenge", []() { SetPackedStatBool(36843, true); }}, // Specific Doomsday AIO?
                {"Win a Loyalty challenge", []() { SetPackedStatBool(36844, true); }}, // Specific Doomsday Loyalty?
                {"Win a Criminal Mastermind challenge", []() { SetPackedStatBool(36845, true); }}, // Specific Doomsday CM?
                {"Call in Strike Team mercenaries", []() { SetPackedStatBool(36846, true); }},
                {"Use Orbital Cannon", []() { SetPackedStatBool(36847, true); }},
			}
		},
        // --- FURTHER ADVENTURES IN FINANCE AND FELONY ---
        {
            "FURTHER ADVENTURES IN FINANCE AND FELONY", {
                {"Become CEO of an Organization", []() { SetPackedStatBool(36888, true); }},
                {"Hire a player to join your Organization", []() { SetPackedStatBool(36889, true); }},
                {"Complete a VIP Work", []() { SetPackedBoolsRanged(36892, 36915, true); }}, // Does all VIP work
                {"Export Mixed Goods to the Docks", []() { SetPackedStatBool(36890, true); }},
                {"Own a Special Cargo Warehouse", []() { SetMpIntCharacterStat("mpx_INT_STAT_WARHOUSESLOT0", 1); }}, // Assuming slot 0 is enough to trigger
                {"Source Cargo for your Warehouse", []() { SetMpIntCharacterStat("mpx_INT_STAT_LIFETIME_BUY_COMPLETE", 1); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_FAIFAF_CRATES_COL", 250); }}, // Set T2 trigger and T4 goal
                {"Source all types of Cargo", []() { SetPackedBoolsRanged(7559, 7553, true); }}, // Note: Range looks reversed in comment, check in-game if possible
                {"Sell 111 crates of Cargo in one Sell mission", []() { SetPackedStatBool(36891, true); }},
                {"Complete 5 different VIP Works", []() { SetPackedBoolsRanged(36892, 36915, true); }}, // Does all VIP work
                {"Complete 10 different VIP Works and Challenges", []() { SetPackedBoolsRanged(36892, 36915, true); }}, // Does all VIP work
                {"Source all types of Special Items", []() { SetPackedBoolsRanged(36860, 36865, true); }},
                {"Source 250 crates of Cargo", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_FAIFAF_CRATES_COL", 250); }},
                {"Earn $50,000,000 selling Cargo", []() { SetMpIntCharacterStat("mpx_INT_STAT_LIFETIME_CONTRA_EARNINGS", 50000000); }},
            }
        },
		// --- GERALD'S LAST PLAY ---
		{
			"GERALD'S LAST PLAY", { // Seems OK from original check
				{"Complete a Last Play mission for Gerald", []() { SetPackedBoolsRanged(41404, 41409, true); }},
				{"Complete a Last Play mission without dying", []() { SetPackedStatBool(41410, true); }},
				{"Complete all Last Play missions", []() { SetPackedBoolsRanged(41404, 41409, true); }},
				{"Complete a Last Play mission on Hard difficulty", []() { SetPackedStatBool(41709, true); }},
				{"Complete all Last Play missions on Hard difficulty", []() { SetPackedBoolsRanged(41411, 41416, true); }},
				{"Complete all Last Play missions on Hard difficulty without using snacks or armor", []() { SetPackedBoolsRanged(41417, 41422, true); }},
				{"Complete all Last Play missions taking less than 50% damage", []() { SetPackedBoolsRanged(41423, 41428, true); }},
				{"Complete all Last Play missions with over 80% accuracy", []() { SetPackedBoolsRanged(41429, 41434, true); }},
			}
		},
        // --- GUNRUNNING ---
        {
            "GUNRUNNING", {
                {"Set up a Bunker", []() { SetMpIntCharacterStat("mpx_INT_STAT_FACTORYSETUP5", 1); }}, // Assuming index 5 is bunker
                {"Complete a Resupply mission", []() { SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_BIKER_BUY_COMPLET5", 25); }}, // Set max tier goal
                {"Complete a research project", []() { SetPackedStatInt(9359, 25); }}, // Set max tier goal
                {"Deliver excess weapon parts to Ammu-Nation", []() { SetPackedStatBool(36870, true); }},
                {"Complete a Mobile Operation", []() { SetMpIntCharacterStat("mpx_INT_STAT_WVM_FLOW_BITSET_MISSIONS0", -1); }}, // Set all bits? Check value
                {"Complete a Sell mission", []() {
                    SetMpIntCharacterStat("mpx_INT_STAT_LIFETIME_BKR_SEL_COMPLETBC5", 1); // Bunker sell complete flag?
                    SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_BIKER_SELL_COMPLET5", 1); // Another bunker sell flag?
                    SetMpIntCharacterStat("mpx_INT_STAT_LIFETIME_BKR_SELL_EARNINGS5", 25000000); // Max earnings goal
                 }},
                {"Complete all Challenges for 1 weapon at the Bunker Shooting Range", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_SR_WEAPON_BIT_SET", 1, 17, true); }}, // Does all challenges
                {"Complete 25 Resupply missions", []() { SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_BIKER_BUY_COMPLET5", 25); }},
                {"Upgrade 5 weapons to Mk II", []() { SetPackedBoolsRanged(42002, 42013, true); }}, // Unlocks all MkII weapons, covers goal
                {"Complete all Mobile Operations on Hard difficulty in under 10 minutes", []() { SetPackedBoolsRanged(36831, 36838, true); }}, // Assumes this range covers the hard/time MOC challenges
                {"Complete all challenges at the Bunker Shooting Range", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_SR_WEAPON_BIT_SET", 1, 17, true); }},
                {"Research 25 projects", []() { SetPackedStatInt(9359, 25); }},
                {"Earn $25,000,000 selling Weapons", []() { SetMpIntCharacterStat("mpx_INT_STAT_LIFETIME_BKR_SELL_EARNINGS5", 25000000); }},
            }
        },
        // --- IMPORT / EXPORT ---
        {
            "IMPORT / EXPORT", {
                {"Own a Vehicle Warehouse", []() { SetMpIntCharacterStat("mpx_INT_STAT_OWNED_IE_WAREHOUSE", 1); }},
                {"Complete a Vehicle Cargo mission", []() { SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_IE_EXPORT_COMPLETED", 25); SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_IE_MISSION_EARNINGS", 25000000); }}, // Set T1 trigger and T4 goals
                {"Complete a Special Vehicle Work", []() { SetPackedBoolsRanged(42029, 42036, true); SetPackedBoolsRanged(41540, 41547, true); }}, // Complete all SVW and Hard SVW
                {"Source all vehicles for one Collector", []() { SetPackedBoolsRanged(41874, 41883, true); }}, // Does all collectors
                {"Sell 1 vehicle in perfect condition", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_VEH_CARGO_SELL_PER", 50); }}, // Set T4 goal
                {"Sell 5 vehicles to Specialist Dealers", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_VEH_CARGO_SPECIAL", 5); }},
                {"Complete 25 Vehicle Cargo missions", []() { SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_IE_EXPORT_COMPLETED", 25); }},
                {"Fill a Vehicle Warehouse with 40 stolen vehicles", []() { SetPackedStatBool(41988, true); }},
                {"Complete all Special Vehicle Works", []() { SetPackedBoolsRanged(42029, 42036, true); SetPackedBoolsRanged(41540, 41547, true); }}, // Complete all SVW and Hard SVW
                {"Source all vehicles for all Collectors", []() { SetPackedBoolsRanged(41874, 41883, true); }},
                {"Complete all Special Vehicle Works on Hard difficulty", []() { SetPackedBoolsRanged(41540, 41547, true); }},
                {"Sell 50 vehicles in perfect condition", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_VEH_CARGO_SELL_PER", 50); }},
                {"Earn $25,000,000 selling Vehicle Cargo", []() { SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_IE_MISSION_EARNINGS", 25000000); }},
            }
        },
        // --- LOS SANTOS DRUG WARS ---
        {
            "LOS SANTOS DRUG WARS", {
                {"Complete all missions for The First Dose", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_XM22_MISSIONS_SA", 0, 5, true); SetPackedBoolsRanged(41660, 41670, true); }}, // Set mission bits & no death flags
                {"Set up an Acid Lab", []() { SetPackedStatBool(42037, true); }},
                {"Complete 10 Source Supplies missions for the Acid Lab", []() { SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_BIKER_BUY_COMPLET6", 100); }}, // Set max tier goal
                {"Complete all missions for The Last Dose", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_XM22_MISSIONS_SA", 6, 10, true); SetPackedBoolsRanged(41660, 41670, true); }}, // Set mission bits & no death flags
                {"Complete all Fooligan Jobs", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_XM22_FLOW", 20, 24, true); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_LSDW_FJ_NO_DEATHS", 25); }}, // Set flow bits & no death goal
                {"Earn $1,000,000 selling Acid", []() { SetMpIntCharacterStat("mpx_INT_STAT_LIFETIME_BKR_SELL_EARNINGS6", 10000000); }}, // Set max tier goal
                {"Unlock all custom acid names", []() {
                    SetMpIntCharacterStatBit("mpx_INT_STAT_XM22_FLOW", 0, true); // Name unlock flag?
                    SetMpIntCharacterStatBits("mpx_INT_STAT_XM22_FLOW", 20, 24, true); // Fooligan jobs needed?
                    SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_BIKER_BUY_COMPLET6", 10); // Source Supplies needed?
                    SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_BIKER_SELL_COMPLET6", 10); // Sell missions needed?
                    SetPackedStatInt(41241, 5); // Related packed int?
                    SetMpIntCharacterStatBit("mpx_INT_STAT_XM22_MISSIONS_SA", 5, true); // First Dose needed?
                    SetMpIntCharacterStatBit("mpx_INT_STAT_XM22_MISSIONS_SA", 10, true); // Last Dose needed?
                    SetMpIntCharacterStatBit("mpx_INT_STAT_XM22_MISSIONS_SA", 26, true); // Unknown bit?
                    SetMpIntCharacterStat("mpx_INT_STAT_LIFETIME_BKR_SELL_EARNINGS6", 1000000); // Earnings needed?
                 }},
                {"Complete 25 Fooligan Jobs without dying", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_LSDW_FJ_NO_DEATHS", 25); SetMpIntCharacterStatBits("mpx_INT_STAT_XM22_FLOW", 20, 24, true); }},
                {"Take out 100 hostile versions of yourself", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_DAX_CLONE_KILLS", 100); }},
                {"Unlock all Platinum Awards for Los Santos Drug Wars", []() { SetPackedStatInt(42084, 24); }},
                {"Complete 100 Source Supplies missions for the Acid Lab", []() { SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_BIKER_BUY_COMPLET6", 100); }},
                {"Complete all missions in The First Dose and The Last Dose without dying", []() { SetPackedBoolsRanged(41660, 41670, true); SetMpIntCharacterStatBits("mpx_INT_STAT_XM22_MISSIONS_SA", 0, 10, true); }},
                {"Earn $10,000,000 selling Acid", []() { SetMpIntCharacterStat("mpx_INT_STAT_LIFETIME_BKR_SELL_EARNINGS6", 10000000); }},
            }
        },
        // --- LOS SANTOS TUNERS ---
        {
            "LOS SANTOS TUNERS", {
                {"Visit and become a member of the LS Car Meet", []() { SetMpIntCharacterStat("mpx_INT_STAT_CAR_CLUB_MEMBERSHIP", 1); SetPackedStatBool(31737, true); }},
                {"Take a vehicle into the LS Car Meet Test Track", []() { SetPackedStatBool(41870, true); }},
                {"Set up an Auto Shop", []() { SetPackedStatBool(31753, true); }},
                {"Complete any Robbery Contract", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_TUNER_COMP_BS", 0, 7, true); SetMpIntCharacterStat("mpx_INT_STAT_TUNER_COUNT", 25); }}, // Set bits and max count goal
                {"Service and deliver 10 customer vehicles", []() { SetMpIntAwardCharacterStat("mpx_INT_AWARD_AUTO_SHOP", 10); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_TUNER_CUS_DEL_CASH", 5000000); }}, // Set award and max earnings goal
                {"Reach LS Car Meet reputation level 10", []() { SetMpIntAwardCharacterStat("mpx_INT_AWARD_CAR_CLUB_MEM", 100); }}, // Set max rep goal
                {"Complete all Robbery Contracts", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_TUNER_COMP_BS", 0, 7, true); SetMpIntCharacterStat("mpx_INT_STAT_TUNER_COUNT", 25); }}, // Set bits and max count goal
                {"Complete a Prize Ride Challenge", []() { SetPackedStatBool(32397, true); }},
                {"Deliver all 10 Exotic Exports vehicles in a day", []() { SetMpIntAwardCharacterStat("mpx_INT_AWARD_GROUNDWORK", 1); }},
                {"Unlock 10 Platinum Awards for Los Santos Tuners", []() { SetPackedStatInt(30226, 10); }}, // Assuming index 30226 is correct
                {"Complete 25 Robbery Contracts", []() { SetMpIntCharacterStat("mpx_INT_STAT_TUNER_COUNT", 25); SetMpIntCharacterStatBits("mpx_INT_STAT_TUNER_COMP_BS", 0, 7, true); }}, // Set count and bits
                {"Earn $5,000,000 delivering customer vehicles", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_TUNER_CUS_DEL_CASH", 5000000); SetMpIntAwardCharacterStat("mpx_INT_AWARD_AUTO_SHOP", 10); }}, // Set earnings and award
                {"Reach LS Car Meet reputation level 100", []() { SetMpIntAwardCharacterStat("mpx_INT_AWARD_CAR_CLUB_MEM", 100); }},
            }
        },
		// --- LOWRIDERS ---
		{
			"LOWRIDERS", { // Corrected based on comment list
				{"Complete a Lowrider mission for Lamar", []() { SetPackedBoolsRanged(42015, 42022, true); SetMpIntCharacterStatBits("mpx_INT_STAT_LOW_FLOW_CS_DRV_SEEN", 0, 10, true); }}, // Use bool range and seen bits
				{"Complete a Lowrider mission without dying", []() { SetPackedStatBool(41539, true); }},
				{"Complete all Lowrider missions", []() { SetPackedBoolsRanged(42015, 42022, true); SetMpIntCharacterStatBits("mpx_INT_STAT_LOW_FLOW_CS_DRV_SEEN", 0, 10, true); }}, // Use bool range and seen bits
				{"Complete a Lowrider mission on Hard difficulty", []() { SetPackedStatBool(41711, true); }},
				{"Complete all Lowrider missions on Hard difficulty", []() { SetPackedBoolsRanged(41507, 41514, true); }},
				{"Complete all Lowrider missions on Hard difficulty without using snacks or armor", []() { SetPackedBoolsRanged(41515, 41522, true); }},
				{"Complete all Lowrider missions taking less than 50% damage", []() { SetPackedBoolsRanged(41523, 41530, true); }},
				{"Complete all Lowrider missions with over 80% accuracy", []() { SetPackedBoolsRanged(41531, 41538, true); }},
                // Kept from original code
                {"Own a lowrider from Benny's", []() { SetPackedStatBool(36835, true); }},
                {"Own all lowrider classics", []() { SetPackedStatBool(36834, true); }},
                {"Win a Lowrider versus mission", []() { SetPackedStatBool(36832, true); }},
			}
		},
		// --- MADRAZO DISPATCH SERVICES ---
		{
			"MADRAZO DISPATCH SERVICES", { // Corrected based on comment list
				{"Complete a Dispatch Mission for Martin Madrazo", []() { SetPackedBoolsRanged(41476, 41481, true); }},
				{"Complete a Dispatch Mission without dying", []() { SetPackedStatBool(41506, true); }},
				{"Complete all Dispatch Missions", []() { SetPackedBoolsRanged(41476, 41481, true); }},
				{"Complete a Dispatch Mission on Hard difficulty", []() { SetPackedStatBool(41710, true); }}, // Comment uses 41710, code used 41712 originally
				{"Complete all Dispatch Missions on Hard difficulty", []() { SetPackedBoolsRanged(41482, 41487, true); }},
				{"Complete all Dispatch Missions on Hard difficulty without using snacks or armor", []() { SetPackedBoolsRanged(41488, 41493, true); }},
				{"Complete all Dispatch Missions taking less than 50% damage", []() { SetPackedBoolsRanged(41494, 41499, true); }},
				{"Complete all Dispatch Missions with over 80% accuracy", []() { SetPackedBoolsRanged(41500, 41505, true); }},
			}
		},
        // --- OPERATION PAPER TRAIL ---
        {
            "OPERATION PAPER TRAIL", { // Seems OK from original check
                {"Complete an Operation Paper Trail mission for Agent ULP", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_ULP_MISSION_PROGRESS", 0, 13, true); }},
                {"Complete an Operation Paper Trail mission without dying", []() { SetPackedBoolsRanged(41333, 41338, true); }},
                {"Complete all Operation Paper Trail missions", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_ULP_MISSION_PROGRESS", 0, 13, true); }},
                {"Complete an Operation Paper Trail mission on Hard difficulty", []() { SetPackedStatBool(41707, true); }},
                {"Complete all Operation Paper Trail missions on Hard difficulty", []() { SetPackedBoolsRanged(41339, 41344, true); }},
                {"Complete all Operation Paper Trail missions on Hard difficulty without using snacks or armor", []() { SetPackedBoolsRanged(41345, 41350, true); }},
                {"Complete all Operation Paper Trail missions taking less than 50% damage", []() { SetPackedBoolsRanged(41351, 41356, true); }},
                {"Complete all Operation Paper Trail missions with over 80% accuracy", []() { SetPackedBoolsRanged(41357, 41362, true); }},
            }
        },
        // --- ORIGINAL HEISTS ---
        {
            "ORIGINAL HEISTS", {
                {"Own a high-end or custom Apartment", []() { SetPackedStatBool(36867, true); }},
                {"Set up The Fleeca Job", []() { SetPackedStatBool(36933, true); }},
                {"Complete a Setup for The Fleeca Job as a leader", []() { SetPackedStatBool(41700, true); }},
                {"Complete The Fleeca Job as a leader", []() { SetPackedStatBool(41715, true); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_HEIST_EARNINGS", 50000000); }}, // Set flag and max earnings
                {"Complete Prison Break as a leader", []() { SetPackedStatBool(41716, true); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_HEIST_EARNINGS", 50000000); }}, // Set flag and max earnings
                {"Complete The Humane Labs Raid as a leader", []() { SetPackedStatBool(41717, true); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_HEIST_EARNINGS", 50000000); }}, // Set flag and max earnings
                {"Complete Series A Funding as a leader", []() { SetPackedStatBool(41718, true); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_HEIST_EARNINGS", 50000000); }}, // Set flag and max earnings
                {"Complete The Pacific Standard Job as a leader", []() { SetPackedStatBool(41719, true); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_HEIST_EARNINGS", 50000000); }}, // Set flag and max earnings
                {"Complete all heists with the same crew (Loyalty)", []() { SetPackedStatInt(42100, 5); }}, // Set Loyalty progress (assuming 5 = all heists)
                {"Unlock 15 Platinum Awards for heists", []() { SetPackedStatInt(42090, 15); }},
                {"Earn $50,000,000 across all heists", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_HEIST_EARNINGS", 50000000); }},
                {"Complete the Elite Challenge for each heist", []() { SetPackedBoolsRanged(41701, 41704, true); SetPackedStatBool(36917, true); }}, // Set 4 ranges + Fleeca elite
                {"Complete the Criminal Mastermind challenge", []() { SetPackedStatBool(42000, true); }},
            }
        },
		// --- OSCAR GUZMAN FLIES AGAIN ---
		{
			"OSCAR GUZMAN FLIES AGAIN", { // Seems OK from original check
				{"Complete Up and Running for Oscar Guzman Flies Again", []() { SetPackedStatBool(51280, true); }},
				{"Complete Oscar Guzman Flies Again", []() { SetPackedStatBool(51285, true); }},
				{"Complete an Oscar Guzman Flies Again mission without dying", []() { SetPackedStatBool(51278, true); }},
				{"Complete an Oscar Guzman Flies Again mission on Hard", []() { SetPackedBoolsRanged(51286, 51291, true); }},
				{"Complete all Oscar Guzman Flies Again missions on Hard", []() { SetPackedBoolsRanged(51286, 51291, true); }},
				{"Earn $5,000,000 from Oscar Guzman Flies Again", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_MFH_EARNINGS", 5000000); }},
				{"Complete all Oscar Guzman Flies Again missions on Hard without using snacks or armor", []() { SetPackedBoolsRanged(51292, 51297, true); }},
				{"Complete Oscar Guzman Flies Again in under 60 minutes", []() { SetPackedStatBool(51279, true); }},
			}
		},
		// --- PREMIUM DELUXE REPO WORK ---
		{
			"PREMIUM DELUXE REPO WORK", { // Corrected based on comment list
				{"Complete a Repo Work mission for Simeon Yetarian", []() { SetPackedBoolsRanged(41436, 41443, true); }},
				{"Complete a Repo Work mission without dying", []() { SetPackedStatBool(41435, true); }},
				{"Complete all Repo Work missions", []() { SetPackedBoolsRanged(41436, 41443, true); }},
				{"Complete a Repo Work mission on Hard difficulty", []() { SetPackedStatBool(41705, true); }}, // Comment uses 41705, code used 41711 originally
				{"Complete all Repo Work missions on Hard difficulty", []() { SetPackedBoolsRanged(41444, 41451, true); }},
				{"Complete all Repo Work missions on Hard difficulty without using snacks or armor", []() { SetPackedBoolsRanged(41452, 41459, true); }},
				{"Complete all Repo Work missions taking less than 50% damage", []() { SetPackedBoolsRanged(41460, 41467, true); }},
				{"Complete all Repo Work missions with over 80% accuracy", []() { SetPackedBoolsRanged(41468, 41475, true); }},
			}
		},
        // --- RACING ---
        {
            "RACING", {
                {"Participate in any Race", []() { SetPackedStatBool(42023, true); }},
                {"Win a Race in 5 different race types", []() { SetPackedBoolsRanged(41363, 41367, true); }}, // Just guessing a range for 5 types, might need specific bools
                {"Win 5 Races against another player", []() { SetMpIntCharacterStat("mpx_INT_STAT_RACES_WON", 50); }}, // Set max tier goal
                {"Win 25 Races against another player", []() { SetMpIntCharacterStat("mpx_INT_STAT_RACES_WON", 50); }}, // Set max tier goal
                {"Beat the par time in 25 Time Trials", []() {
                    SetMpIntCharacterStatBits("mpx_INT_STAT_PROG_HUB_T_TRIAL_PAR_TIME", 0, 25, true); // Standard TTs
                    SetMpIntCharacterStatBits("mpx_INT_STAT_PROG_HUB_T_TRL_PAR_TIME_RC", 0, 25, true); // RC TTs
                    SetMpIntCharacterStatBits("mpx_INT_STAT_PROG_HUB_T_TRL_PAR_TIME_HSW", 0, 25, true); // HSW TTs
                    SetMpIntCharacterStatBits("mpx_INT_STAT_PROG_HUB_T_TRL_PAR_TIME_BKE", 0, 25, true); // Junk Bike TTs?
                }},
                {"Win 20 Races in the Community Series", []() { SetPackedStatInt(41246, 20); }},
                {"Achieve the fastest lap 50 times on any Rockstar-created Race", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_FST_LPS_RSTAR_RAC", 50); }},
                {"Win 50 Races against another player", []() { SetMpIntCharacterStat("mpx_INT_STAT_RACES_WON", 50); }},
            }
        },
		// --- SAN ANDREAS MERCENARIES ---
		{
			"SAN ANDREAS MERCENARIES", { // Seems OK from original check
				{"Complete a Project Overthrow mission for Charlie Reed", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_SUM23_AVOP_PROGRESS", 0, 11, true); }},
				{"Complete a Project Overthrow mission without dying", []() { SetPackedStatBool(41566, true); }},
				{"Complete all Project Overthrow missions", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_SUM23_AVOP_PROGRESS", 0, 11, true); }},
				{"Complete a Project Overthrow mission on Hard difficulty", []() { SetPackedStatBool(41706, true); }},
				{"Complete all Project Overthrow missions on Hard difficulty", []() { SetPackedBoolsRanged(41567, 41572, true); }},
				{"Complete all Project Overthrow missions on Hard difficulty without using snacks or armor", []() { SetPackedBoolsRanged(41573, 41578, true); }},
				{"Complete all Project Overthrow missions taking less than 50% damage", []() { SetPackedBoolsRanged(41579, 41584, true); }},
				{"Complete all Project Overthrow missions with over 80% accuracy", []() { SetPackedBoolsRanged(41585, 41590, true); }},
			}
		},
        // --- SMUGGLER'S RUN ---
        {
            "SMUGGLER'S RUN", {
                {"Set up a Hangar", []() { SetPackedStatBool(15966, true); }},
                {"Complete a Source Cargo mission", []() { SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_HANGAR_BUY_COMPLET", 100); SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_HANGAR_EARNINGS", 50000000); }}, // Set T1 trigger and T4 goals
                {"Send a staff member to source Air-Freight Cargo", []() { SetPackedStatBool(41676, true); }},
                {"Turn a Pegasus vehicle into a Personal Aircraft", []() { SetPackedStatBool(32398, true); }},
                {"Complete 10 Source Cargo missions", []() { SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_HANGAR_BUY_COMPLET", 100); }}, // Set max tier goal
                {"Complete an Air-Freight Cargo Sell mission", []() { SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_HANGAR_SEL_COMPLET", 1); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_SMUGGLER_CRATES", 1000); }}, // Set T2 trigger and T4 goal
                {"Complete 25 Source Cargo missions", []() { SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_HANGAR_BUY_COMPLET", 100); }}, // Set max tier goal
                {"Fill your Hangar with Air-Freight Cargo", []() { SetPackedStatBool(41987, true); }},
                {"Sell 50 crates of the same type of Air-Freight Cargo in one sale", []() { SetPackedStatBool(36924, true); }}, // Sets the single sale flag
                {"Complete 100 Source Cargo missions", []() { SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_HANGAR_BUY_COMPLET", 100); }},
                {"Sell 1,000 crates of Air-Freight Cargo", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_SMUGGLER_CRATES", 1000); }},
                {"Sell all types of Air-Freight Cargo", []() { SetPackedBoolsRanged(36925, 36932, true); }},
                {"Earn $50,000,000 selling Air-Freight Cargo", []() { SetMpIntCharacterStat("mpx_INT_STAT_LFETIME_HANGAR_EARNINGS", 50000000); }},
            }
        },
		// --- A SUPERYACHT LIFE ---
		{
			"A SUPERYACHT LIFE", { // Seems OK from original check
				{"Complete a Superyacht Life mission for Brendan Darcy", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_YACHT_MISSION_FLOW", 4, 15, true); }},
				{"Complete a Superyacht Life mission without dying", []() { SetPackedStatBool(41379, true); }},
				{"Complete all Superyacht Life missions", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_YACHT_MISSION_FLOW", 4, 15, true); }},
				{"Complete a Superyacht Life mission on Hard difficulty", []() { SetPackedStatBool(41708, true); }},
				{"Complete all Superyacht Life missions on Hard difficulty", []() { SetPackedBoolsRanged(41380, 41385, true); }},
				{"Complete all Superyacht Life missions on Hard difficulty without using snacks or armor", []() { SetPackedBoolsRanged(41386, 41391, true); }},
				{"Complete all Superyacht Life missions taking less than 50% damage", []() { SetPackedBoolsRanged(41392, 41397, true); }},
				{"Complete all Superyacht Life missions with over 80% accuracy", []() { SetPackedBoolsRanged(41398, 41403, true); }},
			}
		},
        // --- SURVIVALS ---
        {
            "SURVIVALS", {
                {"Play a Survival mode", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_SURVIVALS_PLAYED", 1); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_SURV_WAVES", 250); }}, // Set T1 trigger and T4 goal
                {"Survive 5 waves in Survival without dying", []() { SetPackedStatBool(41672, true); SetMpIntAwardCharacterStat("mpx_INT_AWARD_FMHORDWAVESSURVIVE", 10); }}, // Set T2 flag and T3 goal
                {"Clear 50 waves in Survival", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_SURV_WAVES", 250); }}, // Set max tier goal
                {"Survive 10 waves in Survival without dying", []() { SetMpIntAwardCharacterStat("mpx_INT_AWARD_FMHORDWAVESSURVIVE", 10); }},
                {"Get 100 headshots in a game of Survival", []() { SetPackedStatBool(41673, true); }},
                {"Complete 10 waves in Survival mode playing solo", []() { SetPackedStatBool(41332, true); }},
                {"Reach wave 16 playing Endless Waves", []() { SetPackedStatBool(41331, true); }},
                {"Clear 250 waves in Survival", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_SURV_WAVES", 250); }},
            }
        },
        // --- THE CHOP SHOP ---
        {
            "THE CHOP SHOP", {
                {"Set up a Salvage Yard", []() { SetMpIntCharacterStat("mpx_INT_STAT_SALVAGE_YARD_OWNED", 1); }},
                {"Meet with Yusuf Amir", []() { SetPackedStatBool(42038, true); }},
                {"Complete a Salvage Yard Robbery", []() { SetPackedStatBool(42041, true); SetPackedStatBool(42042, true); SetPackedBoolsRanged(42047, 42051, true); }}, // Set T1 trigger, T3 all robs, T4 all challenges
                {"Sell a vehicle", []() { SetPackedStatBool(42044, true); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_SALV23_EARN_SELL", 10000000); }}, // Set T2 trigger and T4 goal
                {"Salvage a vehicle", []() { SetPackedStatBool(42045, true); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_SALV23_EARN_SALV", 2500000); }}, // Set T2 trigger and T4 goal
                {"Earn $250,000 from salvaging vehicles", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_SALV23_EARN_SALV", 2500000); }}, // Set T4 goal
                {"Complete all Salvage Yard Robberies", []() { SetPackedStatBool(42042, true); SetPackedBoolsRanged(42047, 42051, true); }}, // Set T3 all robs, T4 all challenges
                {"Sell 5 vehicles in perfect condition from Salvage Yard Robberies", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_SALV23_EARN_PERF", 5); }},
                {"Complete all bonus challenges for a Salvage Yard Robbery", []() { SetPackedStatBool(42046, true); SetPackedBoolsRanged(42047, 42051, true); }}, // Set T3 trigger and T4 goal
                {"Unlock 10 Platinum Awards for The Chop Shop", []() { SetPackedStatInt(51052, 10); }},
                {"Earn $2,500,000 from salvaging vehicles", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_SALV23_EARN_SALV", 2500000); }},
                {"Complete all bonus challenges for all Salvage Yard Robberies", []() { SetPackedBoolsRanged(42047, 42051, true); }},
                {"Earn $10,000,000 from selling stolen vehicles", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_SALV23_EARN_SELL", 10000000); }},
            }
        },
		// --- THE CLUCKIN' BELL FARM RAID ---
		{
			"THE CLUCKIN' BELL FARM RAID", { // Seems OK from original check
				{"Steal the setup funds for The Cluckin' Bell Farm Raid", []() { SetPackedStatBool(28272, true); }},
				{"Complete The Cluckin' Bell Farm Raid", []() { SetPackedStatBool(28287, true); }},
				{"Complete a Cluckin' Bell Farm Raid mission without dying", []() { SetPackedStatBool(28286, true); }},
				{"Complete Scene of the Crime without being spotted", []() { SetPackedStatBool(28285, true); }},
				{"Complete Scene of the Crime using both approaches", []() { SetPackedBoolsRanged(28283, 28284, true); }},
				{"Earn $5,000,000 from The Cluckin' Bell Farm Raid", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_CBR_EARNINGS", 5000000); }},
				{"Complete The Cluckin' Bell Farm Raid in less than 45 minutes as a leader", []() { SetPackedStatBool(28282, true); }},
				{"Complete Scene of the Crime using all available setup equipment", []() { SetPackedBoolsRanged(28273, 28281, true); }},
			}
		},
		// --- THE CONTRACT ---
		{
			"THE CONTRACT", { // Corrected based on comment list
				{"Set up the Agency", []() { SetPackedStatBool(28257, true); }},
				{"Complete a Security Contract", []() { SetMpIntCharacterStat("mpx_INT_STAT_FIXER_COUNT", 100); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_FIXER_SEC_CON_SPEC", 100); SetMpIntCharacterStat("mpx_INT_STAT_FIXER_EARNINGS", 5000000); }}, // Set T1 trigger, T4 goals
				{"Meet the VIP", []() { SetMpIntCharacterStatBit("mpx_INT_STAT_FIXER_GENERAL_BS", 0, true); }},
				{"Complete any Data Leak during the VIP Contract", []() {
                    SetMpBoolAwardCharacterStat("mpx_BOOL_AWARD_PARTY_NIGHT", true);
                    SetMpBoolAwardCharacterStat("mpx_BOOL_AWARD_BILLIONAIRE_GAMES", true);
                    SetMpBoolAwardCharacterStat("mpx_BOOL_AWARD_HOOD_PASS", true);
                    SetMpIntCharacterStatBit("mpx_INT_STAT_FIXER_GENERAL_BS", 2, true); // Also complete the VIP contract
                 }},
				{"Complete 10 Payphone Hits", []() { SetMpIntAwardCharacterStat("mpx_INT_AWARD_COLD_CALLER", 10); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_FXER_PAY_HIT_BONUS", 100); }}, // Set T2 award and T4 bonus goal
				{"Complete 10 Security Contracts", []() { SetMpIntCharacterStat("mpx_INT_STAT_FIXER_COUNT", 100); SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_FIXER_SEC_CON_SPEC", 100); }}, // Set T4 goals
				{"Complete the VIP Contract", []() { SetMpIntCharacterStatBit("mpx_INT_STAT_FIXER_GENERAL_BS", 2, true); }},
				{"Complete 25 Payphone Hits with the Assassination Bonus", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_FXER_PAY_HIT_BONUS", 100); SetMpIntAwardCharacterStat("mpx_INT_AWARD_COLD_CALLER", 10); }}, // Set T3/T4 bonus goal and T2 award
                {"Complete all Short Trips playing as Franklin and Lamar", []() {
                    SetMpBoolAwardCharacterStat("mpx_BOOL_AWARD_SHORTFRANK_1", true);
                    SetMpBoolAwardCharacterStat("mpx_BOOL_AWARD_SHORTFRANK_2", true);
                    SetMpBoolAwardCharacterStat("mpx_BOOL_AWARD_SHORTFRANK_3", true);
                    SetMpBoolAwardCharacterStat("mpx_BOOL_AWARD_SHORTLAMAR_1", true);
                    SetMpBoolAwardCharacterStat("mpx_BOOL_AWARD_SHORTLAMAR_2", true);
                    SetMpBoolAwardCharacterStat("mpx_BOOL_AWARD_SHORTLAMAR_3", true);
                 }},
                {"Unlock 10 Platinum Awards for The Contract", []() { SetPackedStatInt(42085, 10); }},
                {"Complete 100 Security Contracts on Specialist or Specialist+ difficulty", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_FIXER_SEC_CON_SPEC", 100); SetMpIntCharacterStat("mpx_INT_STAT_FIXER_COUNT", 100); }},
                {"Complete 100 Payphone Hits with the Assassination Bonus", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_FXER_PAY_HIT_BONUS", 100); SetMpIntAwardCharacterStat("mpx_INT_AWARD_COLD_CALLER", 10); }},
                {"Earn $5,000,000 from Security Contracts", []() { SetMpIntCharacterStat("mpx_INT_STAT_FIXER_EARNINGS", 5000000); SetMpIntCharacterStat("mpx_INT_STAT_FIXER_COUNT", 100); }},
                // Items from old code if distinct
                {"Complete On Course", []() { SetMpIntCharacterStatBit("mpx_INT_STAT_FIXER_STORY_BS", 0, true); SetMpIntCharacterStatBit("mpx_INT_STAT_FIXER_GENERAL_BS", 2, true); }}, // Part of VIP contract
                {"Help recover Dr. Dre's phone", []() { SetMpIntCharacterStatBit("mpx_INT_STAT_FIXER_STORY_BS", 1, true); SetMpIntCharacterStatBit("mpx_INT_STAT_FIXER_GENERAL_BS", 2, true); }}, // Part of VIP contract
                {"Complete Don't Fuck With Dre", []() { SetMpIntCharacterStatBit("mpx_INT_STAT_FIXER_STORY_BS", 10, true); SetMpIntCharacterStatBit("mpx_INT_STAT_FIXER_GENERAL_BS", 2, true); }}, // Part of VIP contract
                {"Complete all VIP Contract missions", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_FIXER_STORY_BS", 0, 12, true); SetMpIntCharacterStatBit("mpx_INT_STAT_FIXER_GENERAL_BS", 2, true); }}, // Set bits and completion flag
                {"Complete Studio Time", []() { SetMpIntCharacterStatBit("mpx_INT_STAT_FIXER_STORY_STRAND", 0, true); }}, // Part of Short Trips
                {"Play all released tracks in Night Club", []() { SetPackedStatBool(41682, true); }}, // If related to contract?
                {"Complete with 3 different Agency staff", []() { SetMpIntCharacterStatBits("mpx_INT_STAT_FIXER_COMPLETED_BS", 5, 7, true); }}, // If this is a valid unlock
			}
		},
		// --- VEHICLE ENTHUSIAST ---
		{
			"VEHICLE ENTHUSIAST", { // Seems OK from original check
				{"Own a Garage with at least 10 spaces", []() { SetPackedStatBool(41864, true); }},
				{"Customize a vehicle in Los Santos Customs", []() { SetPackedStatBool(42014, true); SetMpIntCharacterStat("mpx_INT_STAT_VEHICLES_CUSTOMISED", 50); }}, // Set flag and max goal
				{"Own a Pegasus vehicle", []() { SetPackedStatBool(41865, true); }},
				{"Test drive or purchase a vehicle from Premium Deluxe Motorsport or Luxury Autos", []() { SetPackedStatBool(41863, true); }},
				{"Upgrade a vehicle to its custom variant at Benny's Original Motor Works", []() { SetPackedStatBool(41840, true); }},
				{"Upgrade a vehicle with HSW Performance Upgrades at Hao's Special Works", []() { SetPackedStatBool(41839, true); }},
				{"Upgrade a vehicle into an Arena Contender at an Arena Workshop", []() { SetPackedStatBool(41841, true); }},
				{"Customize a vehicle with Imani tech at an Agency", []() { SetPackedStatBool(41838, true); }},
				{"Earn 5 gold medals in the Flight School challenges", []() { SetPackedStatInt(42092, 5); }},
				{"Unlock 10 Platinum Awards for Vehicles", []() { SetPackedStatInt(42091, 10); }},
				{"Own 100 vehicles including 1 Special Vehicle", []() {
					SetMpIntCharacterStat("mpx_INT_STAT_HUB_VEH_ENTH_OWNED_VEHS", 99); // Set counter just below 100
					SetPackedStatBool(41866, true); // Set the special vehicle flag
				}},
				{"Own a vehicle in each of the 15 different vehicle classes", []() { SetPackedBoolsRanged(41842, 41862, true); }}, // Assume 15 classes = 21 flags? Check range
				{"Customize 50 vehicles", []() { SetMpIntCharacterStat("mpx_INT_STAT_VEHICLES_CUSTOMISED", 50); }},
			}
		},
		// --- WEAPONS EXPERT ---
		{
			"WEAPONS EXPERT", { // Seems OK from original check
				{"Own 5 different weapons", []() { SetPackedStatBool(36934, true); SetPackedStatBool(36941, true); }}, // Set flag and max goal
				{"Equip Body Armor", []() { SetPackedStatBool(36935, true); }},
				{"Add an attachment to a weapon", []() { SetPackedStatBool(36936, true); }},
				{"Customize your weapon loadout at a Gun Locker", []() { SetPackedStatBool(36937, true); }},
				{"Customize a weapon at a Weapon Workshop", []() { SetPackedStatBool(36938, true); }},
				{"Request and collect a Merryweather Ammo Drop", []() { SetPackedStatBool(36920, true); }},
				{"Win a Challenge for each weapon type against another player in the Ammu-Nation Shooting Range", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_WEAP_TYPE_ANSR", -1); }}, // Set all bits
				{"Own 1 of each weapon type", []() { SetPackedStatInt(41242, 8); }}, // Assuming 8 types tracked here
				{"Visit the Gun Van every day for 10 days", []() { SetPackedStatBool(36942, true); }},
				{"Win 10 Challenges against another player in the Ammu-Nation Shooting Range", []() { SetMpIntCharacterStat("mpx_INT_STAT_PROG_HUB_10_CHAL_ANSR", 10); }},
				{"Own all of the Mk II weapons", []() { SetPackedBoolsRanged(42002, 42013, true); }},
				{"Own 50 weapons", []() { SetPackedStatBool(36941, true); }},
				{"Unlock all Mk II ammo types", []() { SetPackedBoolsRanged(15456, 15460, true); SetPackedBoolsRanged(15447, 15452, true); }}, // Set scope ammo + regular ammo types from research
			}
		}
	};


	// --- Unlock Logic Functions ---

	// Unlocks all items within a specific category
	static void UnlockSingleCategory(const std::string& categoryName)
	{
		if (auto it = unlockCategories.find(categoryName); it != unlockCategories.end())
		{
			Notifications::Show("Unlock Editor", std::format("Unlocking category: {}", categoryName), NotificationType::Info);
			int unlockedCount = 0;
            FiberPool::Push([&]() { // Push to fiber pool to avoid blocking UI thread
                for (const auto& item : it->second)
                {
                    item.action();
                    unlockedCount++;
                    // Optional small yield between items if needed, though likely unnecessary for stats
                    // script::get_current()->yield(0ms); 
                }
                Notifications::Show("Unlock Editor", std::format("Category '{}' unlocked ({} items processed).", categoryName, unlockedCount), NotificationType::Success);
            });

		}
		else
		{
			Notifications::Show("Unlock Editor", std::format("Error: Category '{}' not found.", categoryName), NotificationType::Error);
		}
	}

	// Unlocks every individual item across all categories
	static void UnlockEverything()
	{
		Notifications::Show("Unlock Editor", "Starting Unlock Everything process...", NotificationType::Info);
		int totalUnlocked = 0;
		// FiberPool::Push([] { // DIAGNOSTIC: Temporarily comment out pushing to fiber pool
		auto unlock_logic = [] { // Define the logic in a lambda
			int categoryCount = 0;
			int totalItems = 0;
			for (const auto& categoryPair : unlockCategories)
			{
				for (const auto& item : categoryPair.second)
				{
                    // Skip the old "Unlock All" item if it wasn't removed from the map yet
                    if (item.isCategoryUnlockAll) continue;

					item.action();
					totalItems++;
				}
				categoryCount++;
				// Optional: Add small yield between categories if needed
				// script::get_current()->yield(); // Ensure this is commented out or use appropriate project yield mechanism
			}
			Notifications::Show("Unlock Editor", std::format("Unlock Everything complete. {} items across {} categories processed.", totalItems, categoryCount), NotificationType::Success);
		};
		unlock_logic(); // Execute the lambda immediately (synchronously)
		// }); // End of commented out FiberPool::Push
	}


	// --- Main Menu Builder ---
	std::shared_ptr<Category> BuildUnlockEditorMenu()
	{
		auto menu = std::make_shared<Category>("Unlock Editor");

		// Add main group with Unlock Everything button
		auto globalGroup = std::make_shared<Group>("Global Actions");
		globalGroup->AddItem(std::make_unique<ImGuiItem>([] {
			// Use a slightly larger button for the global action
			if (ImGui::Button("Unlock Everything Globally", ImVec2(-1, 30))) // -1 = full width
			{
				// TODO: Consider adding a confirmation dialog here
				// UIManager::AddModal("Confirm Unlock All", [] { ... ImGui::Text... ImGui::Button("Yes")... ImGui::Button("No") ... });
				UnlockEverything();
			}
			ImGui::Separator();
			ImGui::TextWrapped("Warning: Unlocking everything globally applies numerous stat changes at once. Use responsibly and understand potential risks.");
		}));
		menu->AddItem(std::move(globalGroup));

		// Add each category as a group
		for (const auto& categoryPair : unlockCategories)
		{
			const std::string& categoryName = categoryPair.first;
			const auto& items = categoryPair.second; // Capture items by const reference

			auto categoryGroup = std::make_shared<Group>(categoryName);

			// Add "Unlock All in Category" button first
			categoryGroup->AddItem(std::make_unique<ImGuiItem>([categoryName] { // Capture categoryName by value
				if (ImGui::Button(std::format("Unlock All in {}", categoryName).c_str(), ImVec2(-1, 0))) // Full width
				{
					// TODO: Consider adding a confirmation dialog here too
					UnlockSingleCategory(categoryName);
				}
				ImGui::Separator(); // Separate from individual items
			}));

			// Add individual item buttons
            // Use a child window for scrolling if a category has many items
            categoryGroup->AddItem(std::make_unique<ImGuiItem>([items, categoryName] { // Capture items and categoryName
                // Calculate approximate height needed, clamp to a max height
                float estimatedHeight = items.size() * (ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().ItemSpacing.y);
                float maxHeight = ImGui::GetTextLineHeightWithSpacing() * 15; // Max height for ~15 items
                float windowHeight = std::min(estimatedHeight, maxHeight);

                ImGui::BeginChild(std::format("##Scroll_{}", categoryName).c_str(), ImVec2(0, windowHeight), true);
                for (const auto& item : items)
                {
                    // Use full width for individual buttons for consistency
                    if (ImGui::Button(item.name.c_str(), ImVec2(-1, 0)))
                    {
                        FiberPool::Push([action = item.action, name = item.name] { // Capture action and name by value for the fiber
                            action(); // Execute the unlock action
                            Notifications::Show("Unlock Editor", std::format("'{}' unlocked!", name), NotificationType::Success);
                        });
                    }
                }
                ImGui::EndChild();
            }));

			menu->AddItem(std::move(categoryGroup));
		}

		return menu;
	}

} // namespace YimMenu::Submenus

