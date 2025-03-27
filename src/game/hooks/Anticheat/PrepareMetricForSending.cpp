#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"

namespace YimMenu::Hooks
{
	bool Anticheat::PrepareMetricForSending(rage::JsonSerializer* ser, void* a2, void* a3, rage::rlMetric* metric)
	{
		return false; // don't send any telemetry
	}
}