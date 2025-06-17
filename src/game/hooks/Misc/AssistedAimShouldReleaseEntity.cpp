#include "core/hooking/DetourHook.hpp"
#include "core/commands/BoolCommand.hpp"
#include "game/hooks/Hooks.hpp"
#include "types/entity/CDynamicEntity.hpp"
#include "game/gta/Ped.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu::Hooks
{
	static BoolCommand _AimbotReleaseDeadPed{"aimbotreleasedeadped", "Release Dead Target", "Releases the lock-on to the target after they are dead"};

	bool Misc::AssistedAimShouldReleaseEntity(__int64 a1)
	{
		auto entity = *(CDynamicEntity**)(a1 + 0x38);

		if (entity && entity->IsPed() && Ped(entity).IsDead())
		{
			*(CDynamicEntity**)(a1 + 0x38) = nullptr;
			if (!Pointers.AssistedAimFindNewTarget(a1))
			{
				*(CDynamicEntity**)(a1 + 0x38) = entity; // failed, restore original entity to avoid issues
				if (_AimbotReleaseDeadPed.GetState())
					return true;
			}
		}

		return BaseHook::Get<Misc::AssistedAimShouldReleaseEntity, DetourHook<decltype(&Misc::AssistedAimShouldReleaseEntity)>>()->Original()(a1);
	}
}