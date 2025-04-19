#include "VehicleRewardData.hpp"
#include "FMRandomEvents.hpp"
#include "game/gta/ScriptLocal.hpp"
#include "game/pointers/ScriptPointers.hpp"

#define DEFINE_LOCAL_ACCESSOR(str, hash)                          \
	str* str::Get(rage::scrThread* thread)                        \
	{                                                             \
		auto address = YimMenu::ScriptPointers::GetPointer(hash); \
		auto lcl     = YimMenu::ScriptLocal(thread, address);     \
		if (!address || !lcl.CanAccess())                         \
			return nullptr;                                       \
		return lcl.As<str*>();                                    \
	}

DEFINE_LOCAL_ACCESSOR(VEHICLE_REWARD_DATA, "VehicleRewardData"_J);
DEFINE_LOCAL_ACCESSOR(RANDOM_EVENTS_FREEMODE_DATA, "FMRandomEvents"_J);