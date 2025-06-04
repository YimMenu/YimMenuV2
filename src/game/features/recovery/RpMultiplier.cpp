#include "core/commands/LoopedCommand.hpp"
#include "core/commands/FloatCommand.hpp"
#include "game/backend/Tunables.hpp"

namespace YimMenu::Features
{
	static FloatCommand _RpMultiplierInput{"rpmultiplierinput", "RP Multiplier Input", "RP Mulitplier (< 0 = 0 -> No RP)", std::nullopt, std::nullopt, 1};

	class OverrideRPMultiplier : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		Tunable m_XPMultiplier{"XP_MULTIPLIER"_J};

		virtual void OnTick() override
		{
			auto state = _RpMultiplierInput.GetState();
			if (state < 0)
			{
				state = 0;
			}

			if (m_XPMultiplier.IsReady())
				m_XPMultiplier.Set(state);
		}

		virtual void OnDisable() override
		{
			if (m_XPMultiplier.IsReady())
				m_XPMultiplier.Set(1.0f);
		}
	};

	static OverrideRPMultiplier _OverrideRPMultiplier{"overriderpmultiplier", "Override RP Multiplier", "Multiplies RP by the given value"};
}