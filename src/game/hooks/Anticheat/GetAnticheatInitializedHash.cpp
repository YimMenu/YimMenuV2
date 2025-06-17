#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"

namespace YimMenu::Hooks
{
	std::uint32_t Anticheat::GetAnticheatInitializedHash()
	{
		return 0x124EA49D;
	}
}