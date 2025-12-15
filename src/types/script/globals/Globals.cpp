#include "GPBD_FM.hpp"
#include "GPBD_FM_2.hpp"
#include "GPBD_FM_3.hpp"
#include "GPBD_Flow.hpp"
#include "GPBD_Kicking.hpp"
#include "GPBD_MissionName.hpp"
#include "GSBD.hpp"
#include "GSBD_BlockB.hpp"
#include "GSBD_FM.hpp"
#include "GSBD_FM_Events.hpp"
#include "GSBD_Kicking.hpp"
#include "GSBD_PropertyInstances.hpp"
#include "GSBD_RandomEvents.hpp"
#include "GlobalPlayerBD.hpp"
#include "g_AMC_playerBD.hpp"
#include "MPSV.hpp"
#include "g_SavedMPGlobals.hpp"
#include "FreemodeGeneral.hpp"
#include "DailyObjectivesState.hpp"
#include "WeeklyChallenge.hpp"
#include "FreemodeDelivery.hpp"
#include "LauncherServerData.hpp"
#include "game/gta/ScriptGlobal.hpp"

#define DEFINE_GLOBAL_ACCESSOR(str, global)       \
	str* str::Get()                               \
	{                                             \
		auto glb = YimMenu::ScriptGlobal(global); \
		if (!glb.CanAccess())                     \
			return nullptr;                       \
		return glb.As<str*>();                    \
	}

DEFINE_GLOBAL_ACCESSOR(GlobalPlayerBD, 2658294);
DEFINE_GLOBAL_ACCESSOR(GPBD_FM, 1845299);
DEFINE_GLOBAL_ACCESSOR(GPBD_FM_2, 1882717);
DEFINE_GLOBAL_ACCESSOR(GPBD_FM_3, 1892798);
DEFINE_GLOBAL_ACCESSOR(GPBD_Flow, 1984460);
DEFINE_GLOBAL_ACCESSOR(GPBD_Kicking, 1874069);
DEFINE_GLOBAL_ACCESSOR(GPBD_MissionName, 1873556);
DEFINE_GLOBAL_ACCESSOR(GSBD, 2649162);
DEFINE_GLOBAL_ACCESSOR(GSBD_BlockB, 2650426);
DEFINE_GLOBAL_ACCESSOR(GSBD_FM, 1835559);
DEFINE_GLOBAL_ACCESSOR(GSBD_FM_Events, 1922750);
DEFINE_GLOBAL_ACCESSOR(GSBD_Kicking, 1877270);
DEFINE_GLOBAL_ACCESSOR(GSBD_PropertyInstances, 1943919);
DEFINE_GLOBAL_ACCESSOR(g_AMC_playerBD, 2700188);
DEFINE_GLOBAL_ACCESSOR(GSBD_RandomEvents, 1882265);
DEFINE_GLOBAL_ACCESSOR(MPSV, 1583772);
DEFINE_GLOBAL_ACCESSOR(g_SavedMPGlobals, 2359296);
DEFINE_GLOBAL_ACCESSOR(FreemodeGeneral, 2733138);
DEFINE_GLOBAL_ACCESSOR(DailyObjectivesState, 1574745);
DEFINE_GLOBAL_ACCESSOR(WeeklyChallenge, 2732069);
DEFINE_GLOBAL_ACCESSOR(FreemodeDelivery, 1957402);
DEFINE_GLOBAL_ACCESSOR(LauncherServerData, 2700002);