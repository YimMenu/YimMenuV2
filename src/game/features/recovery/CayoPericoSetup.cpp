#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"

namespace YimMenu::Features
{
	class CayoPericoSetup : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Stats::SetInt("MPX_H4CNF_BS_GEN", 131071);
			Stats::SetInt("MPX_H4CNF_BS_ENTR", 63);
			Stats::SetInt("MPX_H4CNF_BS_ABIL", 63);
			Stats::SetInt("MPX_H4CNF_WEAPONS", 2);
			Stats::SetInt("MPX_H4CNF_WEP_DISRP", 3);
			Stats::SetInt("MPX_H4CNF_ARM_DISRP", 3);
			Stats::SetInt("MPX_H4CNF_HEL_DISRP", 3);
			Stats::SetInt("MPX_H4CNF_TARGET", 5);
			Stats::SetInt("MPX_H4CNF_TROJAN", 4);
			Stats::SetInt("MPX_H4CNF_APPROACH", -1);
			Stats::SetInt("MPX_H4LOOT_CASH_I", 0);
			Stats::SetInt("MPX_H4LOOT_CASH_C", 0);
			Stats::SetInt("MPX_H4LOOT_WEED_I", 0);
			Stats::SetInt("MPX_H4LOOT_WEED_C", 0);
			Stats::SetInt("MPX_H4LOOT_COKE_I", 0);
			Stats::SetInt("MPX_H4LOOT_COKE_C", 0);
			Stats::SetInt("MPX_H4LOOT_GOLD_I", -1);
			Stats::SetInt("MPX_H4LOOT_GOLD_C", -1);
			Stats::SetInt("MPX_H4LOOT_PAINT", -1);
			Stats::SetInt("MPX_H4_PROGRESS", 131055);
			Stats::SetInt("MPX_H4LOOT_CASH_I_SCOPED", 0);
			Stats::SetInt("MPX_H4LOOT_CASH_C_SCOPED", 0);
			Stats::SetInt("MPX_H4LOOT_WEED_I_SCOPED", 0);
			Stats::SetInt("MPX_H4LOOT_WEED_C_SCOPED", 0);
			Stats::SetInt("MPX_H4LOOT_COKE_I_SCOPED", 0);
			Stats::SetInt("MPX_H4LOOT_COKE_C_SCOPED", 0);
			Stats::SetInt("MPX_H4LOOT_GOLD_I_SCOPED", -1);
			Stats::SetInt("MPX_H4LOOT_GOLD_C_SCOPED", -1);
			Stats::SetInt("MPX_H4LOOT_PAINT_SCOPED", -1);
			Stats::SetInt("MPX_H4_MISSIONS", 65535);
			Stats::SetInt("MPX_H4_PLAYTHROUGH_STATUS", 40000);
		}
	};

	static CayoPericoSetup _CayoPericoSetup{"skipcayosetup", "Setup Cayo Perico Heist", "Gives the best cayo perico loadout."};
}