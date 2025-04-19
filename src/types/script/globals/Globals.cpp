#include "GlobalPlayerBD.hpp"
#include "GPBD_FM.hpp"
#include "GPBD_FM_3.hpp"
#include "GPBD_Kicking.hpp"
#include "GPBD_MissionName.hpp"
#include "GSBD.hpp"
#include "GSBD_BlockB.hpp"
#include "GSBD_FM.hpp"
#include "GSBD_FM_Events.hpp"
#include "GSBD_Kicking.hpp"
#include "GSBD_PropertyInstances.hpp"
#include "g_AMC_playerBD.hpp"
#include "GSBD_RandomEvents.hpp"
#include "game/gta/ScriptGlobal.hpp"

#define DEFINE_GLOBAL_ACCESSOR(str, global) str* str::Get()\
											{                                               \
												auto glb = YimMenu::ScriptGlobal(global);	\
												if (!glb.CanAccess())                       \
													return nullptr;                         \
												return glb.As<str*>();                      \
											}

DEFINE_GLOBAL_ACCESSOR(GlobalPlayerBD, 2657994);
DEFINE_GLOBAL_ACCESSOR(GPBD_FM, 1845270);
DEFINE_GLOBAL_ACCESSOR(GPBD_FM_3, 1887694);
DEFINE_GLOBAL_ACCESSOR(GPBD_Kicking, 1874328);
DEFINE_GLOBAL_ACCESSOR(GPBD_MissionName, 1873815);
DEFINE_GLOBAL_ACCESSOR(GSBD, 2648917);
DEFINE_GLOBAL_ACCESSOR(GSBD_BlockB, 2650415);
DEFINE_GLOBAL_ACCESSOR(GSBD_FM, 1835557);
DEFINE_GLOBAL_ACCESSOR(GSBD_FM_Events, 1917230);
DEFINE_GLOBAL_ACCESSOR(GSBD_Kicking, 1877529);
DEFINE_GLOBAL_ACCESSOR(GSBD_PropertyInstances, 1937699);
DEFINE_GLOBAL_ACCESSOR(g_AMC_playerBD, 2699624);
DEFINE_GLOBAL_ACCESSOR(GSBD_RandomEvents, 1882524);