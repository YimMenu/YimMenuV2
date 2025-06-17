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
#include "game/gta/ScriptGlobal.hpp"

#define DEFINE_GLOBAL_ACCESSOR(str, global)       \
	str* str::Get()                               \
	{                                             \
		auto glb = YimMenu::ScriptGlobal(global); \
		if (!glb.CanAccess())                     \
			return nullptr;                       \
		return glb.As<str*>();                    \
	}

DEFINE_GLOBAL_ACCESSOR(GlobalPlayerBD, 2658019);
DEFINE_GLOBAL_ACCESSOR(GPBD_FM, 1845274);
DEFINE_GLOBAL_ACCESSOR(GPBD_FM_2, 1845274);
DEFINE_GLOBAL_ACCESSOR(GPBD_FM_3, 1888882);
DEFINE_GLOBAL_ACCESSOR(GPBD_Flow, 1980192);
DEFINE_GLOBAL_ACCESSOR(GPBD_Kicking, 1873852);
DEFINE_GLOBAL_ACCESSOR(GPBD_MissionName, 1873339);
DEFINE_GLOBAL_ACCESSOR(GSBD, 2648932);
DEFINE_GLOBAL_ACCESSOR(GSBD_BlockB, 2650431);
DEFINE_GLOBAL_ACCESSOR(GSBD_FM, 1845274);
DEFINE_GLOBAL_ACCESSOR(GSBD_FM_Events, 1918514);
DEFINE_GLOBAL_ACCESSOR(GSBD_Kicking, 1877053);
DEFINE_GLOBAL_ACCESSOR(GSBD_PropertyInstances, 1939705);
DEFINE_GLOBAL_ACCESSOR(g_AMC_playerBD, 2699749);
DEFINE_GLOBAL_ACCESSOR(GSBD_RandomEvents, 1882048);
DEFINE_GLOBAL_ACCESSOR(MPSV, 1586547);
DEFINE_GLOBAL_ACCESSOR(g_SavedMPGlobals, 2359296);
DEFINE_GLOBAL_ACCESSOR(FreemodeGeneral, 2740191);
DEFINE_GLOBAL_ACCESSOR(DailyObjectivesState, 1574745);
DEFINE_GLOBAL_ACCESSOR(WeeklyChallenge, 2739243);
DEFINE_GLOBAL_ACCESSOR(FreemodeDelivery, 1953035);