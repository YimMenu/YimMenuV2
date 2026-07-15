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

DEFINE_GLOBAL_ACCESSOR(GlobalPlayerBD, 2658296);
DEFINE_GLOBAL_ACCESSOR(GPBD_FM, 1845347);
DEFINE_GLOBAL_ACCESSOR(GPBD_FM_2, 1882797);
DEFINE_GLOBAL_ACCESSOR(GPBD_FM_3, 1893070);
DEFINE_GLOBAL_ACCESSOR(GPBD_Flow, 1985024);
DEFINE_GLOBAL_ACCESSOR(GPBD_Kicking, 1874149);
DEFINE_GLOBAL_ACCESSOR(GPBD_MissionName, 1873636);
DEFINE_GLOBAL_ACCESSOR(GSBD, 2649164);
DEFINE_GLOBAL_ACCESSOR(GSBD_BlockB, 2650428);
DEFINE_GLOBAL_ACCESSOR(GSBD_FM, 1835603);
DEFINE_GLOBAL_ACCESSOR(GSBD_FM_Events, 1923118);
DEFINE_GLOBAL_ACCESSOR(GSBD_Kicking, 1877350);
DEFINE_GLOBAL_ACCESSOR(GSBD_PropertyInstances, 1944313);
DEFINE_GLOBAL_ACCESSOR(g_AMC_playerBD, 2700299);
DEFINE_GLOBAL_ACCESSOR(GSBD_RandomEvents, 1882345);
DEFINE_GLOBAL_ACCESSOR(MPSV, 1583778);
DEFINE_GLOBAL_ACCESSOR(g_SavedMPGlobals, 2359296);
DEFINE_GLOBAL_ACCESSOR(FreemodeGeneral, 2733326);
DEFINE_GLOBAL_ACCESSOR(DailyObjectivesState, 1574746);
DEFINE_GLOBAL_ACCESSOR(WeeklyChallenge, 2732247);
DEFINE_GLOBAL_ACCESSOR(FreemodeDelivery, 1957909);
DEFINE_GLOBAL_ACCESSOR(LauncherServerData, 2700113);