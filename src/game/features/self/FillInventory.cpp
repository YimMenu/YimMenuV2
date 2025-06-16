#include "core/commands/Command.hpp"
#include "game/gta/Stats.hpp"

namespace YimMenu::Features
{
	class FillInventory : public Command
	{
		using Command::Command;

		virtual void OnCall() override
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
	};

	static FillInventory _FillInventory{"fillinventory", "Fill Inventory", "Fills all of your snacks and armours."};
}