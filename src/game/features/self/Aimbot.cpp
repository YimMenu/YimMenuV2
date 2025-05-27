#include "core/commands/BoolCommand.hpp"
#include "game/pointers/Pointers.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Pools.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

#include <set>

namespace YimMenu::Features
{
	class Aimbot : public LoopedCommand
	{
		bool running = false;
		using LoopedCommand::LoopedCommand;

		std::set<int> killed_peds = {  };

		virtual void OnEnable() override
		{
			Pointers.ShouldNotTargetEntityPatch->Apply();
			Pointers.GetAssistedAimTypePatch->Apply();
		}

		virtual void OnTick() override
		{
			if (running) return;
			running = true;
			for (Ped ped : Pools::GetPeds())
			{
				if (!killed_peds.contains(ped.GetHandle()) && !ped.IsPlayer() && ped.IsDead() && ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(ped.GetHandle(), Self::GetPed().GetHandle(), false))
				{
					killed_peds.insert(ped.GetHandle());
					PAD::DISABLE_CONTROL_ACTION(0, 25, true);
				}
			}
			running = false;
		}

		virtual void OnDisable() override
		{
			Pointers.ShouldNotTargetEntityPatch->Restore();
			Pointers.GetAssistedAimTypePatch->Restore();
		}
	};

	class AimbotAimForHead : BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			Pointers.GetLockOnPosPatch->Apply();
		}

		virtual void OnDisable() override
		{
			Pointers.GetLockOnPosPatch->Restore();
		}
	};

	class AimbotTargetDrivers : BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			Pointers.ShouldAllowDriverLockOnPatch->Apply();
		}

		virtual void OnDisable() override
		{
			Pointers.ShouldAllowDriverLockOnPatch->Restore();
		}
	};

	static Aimbot _Aimbot{"aimbot", "Aimbot", "Locks on to enemies and other players"};
	static AimbotAimForHead _AimbotAimForHead{"aimbotaimforhead", "Aim For Head", "Targets the head when locking on to enemies and other players"};
	static AimbotTargetDrivers _AimbotTargetDrivers{"aimbottargetdrivers", "Target Drivers", "Allows aimbot to lock on to enemies and other players in vehicles"};
}