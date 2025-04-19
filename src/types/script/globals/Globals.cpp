#include "GlobalPlayerBD.hpp"
#include "GPBD_FM.hpp"
#include "GPBD_FM_2.hpp"
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
#include "game/pointers/ScriptPointers.hpp"

#define DEFINE_GLOBAL_ACCESSOR(str, hash)                                 \
	str* str::Get()                                                       \
	{                                                                     \
		auto address = YimMenu::ScriptPointers::GetPointer(hash);         \
		auto glb     = YimMenu::ScriptGlobal(address);                    \
		if (!address || !glb.CanAccess())                                 \
			return nullptr;                                               \
		return glb.As<str*>();                                            \
	}

DEFINE_GLOBAL_ACCESSOR(GlobalPlayerBD, "GlobalPlayerBD"_J);
DEFINE_GLOBAL_ACCESSOR(GPBD_FM, "GPBD_FM"_J);
DEFINE_GLOBAL_ACCESSOR(GPBD_FM_2, "GPBD_FM_2"_J);
DEFINE_GLOBAL_ACCESSOR(GPBD_FM_3, "GPBD_FM_3"_J);
DEFINE_GLOBAL_ACCESSOR(GPBD_Kicking, "GPBD_Kicking"_J);
DEFINE_GLOBAL_ACCESSOR(GPBD_MissionName, "GPBD_MissionName"_J);
DEFINE_GLOBAL_ACCESSOR(GSBD, "GSBD"_J);
DEFINE_GLOBAL_ACCESSOR(GSBD_BlockB, "GSBD_BlockB"_J);
DEFINE_GLOBAL_ACCESSOR(GSBD_FM, "GSBD_FM"_J);
DEFINE_GLOBAL_ACCESSOR(GSBD_FM_Events, "GSBD_FM_Events"_J);
DEFINE_GLOBAL_ACCESSOR(GSBD_Kicking, "GSBD_Kicking"_J);
DEFINE_GLOBAL_ACCESSOR(GSBD_PropertyInstances, "GSBD_PropertyInstances"_J);
DEFINE_GLOBAL_ACCESSOR(g_AMC_playerBD, "g_AMC_playerBD"_J);
DEFINE_GLOBAL_ACCESSOR(GSBD_RandomEvents, "GSBD_RandomEvents"_J);