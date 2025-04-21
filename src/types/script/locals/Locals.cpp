#include "FMRandomEvents.hpp"
#include "VehicleRewardData.hpp"
#include "game/gta/ScriptLocal.hpp"

#define DEFINE_LOCAL_ACCESSOR(str, local)               \
	str* str::Get(rage::scrThread* thread)              \
	{                                                   \
		auto lcl = YimMenu::ScriptLocal(thread, local); \
		if (!lcl.CanAccess())                           \
			return nullptr;                             \
		return lcl.As<str*>();                          \
	}

DEFINE_LOCAL_ACCESSOR(VEHICLE_REWARD_DATA, 129);
DEFINE_LOCAL_ACCESSOR(RANDOM_EVENTS_FREEMODE_DATA, 15919);