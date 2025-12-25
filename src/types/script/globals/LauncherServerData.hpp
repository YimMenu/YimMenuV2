#pragma once
#include "types/script/types.hpp"
#include "types/script/Timer.hpp"

enum class eHostScriptState
{
	INITIALIZING,
	RUNNING,
	PREPARING_TO_SHUT_DOWN,
	SHUTTING_DOWN
};

enum class eLauncherFlags
{
	RUN_IMMEDIATELY = 1
};

enum class eLauncherState
{
	EMPTY,
	FIND_SCRIPT,
	UNK_2, // unused
	PICK_MISSION_VARIATION,
	UNK_4,
	WAIT_FOR_ACK,
	START_SCRIPT,
	WAIT_FOR_TERMINATION,
	RESET
};

struct LAUNCHER_SCRIPT
{
	SCR_INT EventIndex;
	SCR_INT LauncherIndex; // this is the script index we want to set
	SCR_FLOAT Probability;
	SCR_INT PAD_0003; // unused
	SCR_BOOL Terminated;
};
static_assert(sizeof(LAUNCHER_SCRIPT) == 5 * 8);

struct LauncherServerData
{
	alignas(8) eHostScriptState HostState;
	SCR_BITSET<eLauncherFlags> Flags;
	alignas(8) eLauncherState LauncherState;
	LAUNCHER_SCRIPT CurrentScript;
	SCR_ARRAY<LAUNCHER_SCRIPT, 21> QueuedScripts;
	SCR_ARRAY<uint64_t, 21> QueuedEvents;
	uint64_t PAD_0136[41]; // unused
	TIMER CrateDropTimer;
	TIMER ScriptLaunchTimer;
	SCR_INT TimeToWaitForLaunch;
	SCR_INT CurrentEvent;
	SCR_INT ScriptParam1;
	SCR_INT ScriptParam2;
	SCR_INT ScriptParam3;

	static LauncherServerData* Get();
};
static_assert(sizeof(LauncherServerData) == 186 * 8);