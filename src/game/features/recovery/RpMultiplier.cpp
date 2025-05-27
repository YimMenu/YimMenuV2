#include "core/commands/Command.hpp"
#include "core/commands/IntCommand.hpp"
#include "game/backend/Tunables.hpp"

namespace YimMenu::Features
{
	static IntCommand _RpMultiplierInput{"rpmultiplierinput", "RP Multiplier Input", "RP Mulitplier (< 0 = 0 -> No RP)", std::nullopt, std::nullopt, 1};

	class RPMultiplier : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			int state = _RpMultiplierInput.GetState();
			if (state < 0)
			{
				state = 0;
			}
			*Tunables::GetTunable("XP_MULTIPLIER"_J).As<float*>() = state;
		}
	};

	static RPMultiplier _RPMultiplier{"rpmultiplier", "Set RP Multiplier", "Multiplies RP by the given value"};
}