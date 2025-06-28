#include "core/commands/LoopedCommand.hpp"
#include "core/commands/FloatCommand.hpp"
#include "game/backend/Tunables.hpp"

namespace YimMenu::Features
{
	static FloatCommand _CashMultiplierInput{"cashmultiplierinput", "Cash Multiplier Input", "Cash Mulitplier (< 0 = 0 -> No Cash)", std::nullopt, std::nullopt, 1};

	class OverrideCASHMultiplier : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		Tunable m_CASHMultiplier{"CASH_MULTIPLIER"_J};

		virtual void OnTick() override
		{
			auto state = _CashMultiplierInput.GetState();
			if (state < 0)
			{
				state = 0;
			}

			if (m_CASHMultiplier.IsReady())
				m_CASHMultiplier.Set(state);
		}

		virtual void OnDisable() override
		{
			if (m_CASHMultiplier.IsReady())
				m_CASHMultiplier.Set(1.0f);
		}
	};

	static OverrideCASHMultiplier _OverrideCASHMultiplier{"overridecashmultiplier", "Override Cash Multiplier", "Multiplies Cash by the given value! Use with caution"};
}
