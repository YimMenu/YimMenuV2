#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/anticheat/CAnticheatContext.hpp"

namespace YimMenu::Hooks
{
	std::uint32_t Anticheat::GetAnticheatInitializedHash2(void* ac_var, std::uint32_t seed)
	{
		auto orig = (*Pointers.AnticheatContext) ? (*Pointers.AnticheatContext)->m_BattlEyeEnabled : false;
		if (*Pointers.AnticheatContext)
			(*Pointers.AnticheatContext)->m_BattlEyeEnabled = true; // integ checks will boot us out if we set this outside this function
		auto ret = BaseHook::Get<Anticheat::GetAnticheatInitializedHash2, DetourHook<decltype(&Anticheat::GetAnticheatInitializedHash2)>>()->Original()(ac_var, seed);
		if (*Pointers.AnticheatContext)
			(*Pointers.AnticheatContext)->m_BattlEyeEnabled = orig;
		return ret;
	}
}