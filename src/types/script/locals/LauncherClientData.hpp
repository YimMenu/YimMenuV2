#pragma once
#include "../types.hpp"
#include "../globals/LauncherServerData.hpp"

struct LauncherClientDataEntry
{
	SCR_INT ClientState;
	SCR_INT Flags;
	alignas(8) eLauncherState LauncherState;
};
static_assert(sizeof(LauncherClientDataEntry) == 3 * 8);

struct LauncherClientData
{
	SCR_ARRAY<LauncherClientDataEntry, 32> Entries;

	static LauncherClientData* Get(rage::scrThread* thread);
};
static_assert(sizeof(LauncherClientData) == 97 * 8);