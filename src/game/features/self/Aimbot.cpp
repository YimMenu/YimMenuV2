#include "core/commands/BoolCommand.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu::Features
{
	class Aimbot : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			Pointers.ShouldNotTargetEntityPatch->Apply();
			Pointers.GetAssistedAimTypePatch->Apply();
		}

		virtual void OnDisable() override
		{
			Pointers.ShouldNotTargetEntityPatch->Restore();
			Pointers.GetAssistedAimTypePatch->Restore();
		}
	};

	static Aimbot _Aimbot{"aimbot", "Aimbot", "Locks on to enemies and other players"};
}