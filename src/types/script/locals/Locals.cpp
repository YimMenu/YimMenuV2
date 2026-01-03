#include "FMRandomEvents.hpp"
#include "VehicleRewardData.hpp"
#include "StandardTimeTrialData.hpp"
#include "RCBanditoTimeTrialData.hpp"
#include "HSWTimeTrialData.hpp"
#include "BikeTimeTrialData.hpp"
#include "LauncherClientData.hpp"
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
DEFINE_LOCAL_ACCESSOR(RANDOM_EVENTS_FREEMODE_DATA, 16162);
DEFINE_LOCAL_ACCESSOR(StandardTimeTrialData, 14739);
DEFINE_LOCAL_ACCESSOR(RCBanditoTimeTrialData, 14789);
DEFINE_LOCAL_ACCESSOR(HSWTimeTrialData, 14833);
DEFINE_LOCAL_ACCESSOR(BikeTimeTrialData, 15630);

// am_launcher
DEFINE_LOCAL_ACCESSOR(LauncherClientData, 247);