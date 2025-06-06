#pragma once
#include "types/script/types.hpp"

namespace YimMenu
{
	class VehicleHelper
	{
	public:
		static bool CheckModBlacklist(Hash model, int mod_slot, int mod);
		static const char* GetModSlotName(Hash model, int vehicle, int mod_slot);
		static const char* GetModeName(Hash model, int vehicle, int mod_slot, int mod, int mod_count);
		static bool IsBennys(int veh);
	};
}
