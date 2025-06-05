#include "core/commands/LoopedCommand.hpp"
#include "core/commands/FloatCommand.hpp"
#include "game/backend/Tunables.hpp"

namespace YimMenu::Features
{
	static FloatCommand _RpMultiplierInput{"rp_multiplier_input", "RP Multiplier Input", "RP Mulitplier (< 0 = 0 -> No RP)", std::nullopt, std::nullopt, 1};
	static FloatCommand _CashMultiplierInput{"cash_multiplier_input", "Cash Multiplier Input", "Cash Mulitplier (< 0 = 0 -> No Cash :c )", std::nullopt, std::nullopt, 1};
	static FloatCommand _CmRpMultiplierInput{"cm_rp_multiplier_input", "Contact Mission RP Multiplier Input", "Contact Mission RP Mulitplier (< 0 = 0 -> No Mission RP)", std::nullopt, std::nullopt, 1};
	static FloatCommand _CmCashMultiplierInput{"cm_cash_multiplier_input", "Contact Mission Cash Multiplier Input", "Contact Mission Cash Mulitplier (< 0 = 0 -> No Mission Cash)", std::nullopt, std::nullopt, 1};

	const int cm_CashBase = 20.0;
    const int cm_RPBase = 9.0;

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

	class OverrideCashMultiplier : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		Tunable m_CashMultiplier{"Cash_MULTIPLIER"_J};

		virtual void OnTick() override
		{
			auto state = _CashMultiplierInput.GetState();
			if (state < 0)
			{
				state = 0;
			}

			if (m_CashMultiplier.IsReady())
				m_CashMultiplier.Set(state);
		}

		virtual void OnDisable() override
		{
			if (m_CashMultiplier.IsReady())
				m_CashMultiplier.Set(1.0f);
		}
	};

	class Override_ContactMission_RPMultiplier : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		Tunable m_CM_XPMultiplier{"CONTACT_MISSION_RP_BASE_MULTIPLIER"_J};

		virtual void OnTick() override
		{
			auto state = _RpMultiplierInput.GetState();
			if (state < 0)
			{
				state = 0;
			}

			if (m_CM_XPMultiplier.IsReady())
				m_CM_XPMultiplier.Set(cm_RPBase * state);
		}

		virtual void OnDisable() override
		{
			if (m_CM_XPMultiplier.IsReady())
				m_CM_XPMultiplier.Set(cm_RPBase);
		}
	};

	class Override_ContactMission_CashMultiplier : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		Tunable m_CM_CashMultiplier{"CONTACT_MISSION_CASH_BASE_MULTIPLIER"_J};

		virtual void OnTick() override
		{
			auto state = _RpMultiplierInput.GetState();
			if (state < 0)
			{
				state = 0;
			}

			if (m_CM_CashMultiplier.IsReady())
				m_CM_CashMultiplier.Set(cm_CashBase * state);
		}

		virtual void OnDisable() override
		{
			if (m_CM_CashMultiplier.IsReady())
				m_CM_CashMultiplier.Set(cm_CashBase);
		}
	};

	static OverrideRPMultiplier _OverrideRPMultiplier{"override_rp_multiplier", "Override RP Multiplier", "Multiplies RP by the given value"};
	static OverrideCashMultiplier _OverrideCashMultiplier{"override_cash_multiplier", "Override Cash Multiplier", "Multiplies Cash by the given value"};
	static OverrideRPMultiplier _OverrideCmRPMultiplier{"override_cm_rp_multiplier", "Override Contact Mission RP Multiplier", "Multiplies Mission RP by the given value"};
	static OverrideRPMultiplier _OverrideCmCashMultiplier{"override_cm_cash_multiplier", "Override Contact Mission Cash Multiplier", "Multiplies Mission Cash by the given value"};
}
