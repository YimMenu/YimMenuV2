#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Tunables.hpp"

namespace YimMenu::Features
{
	class NoIdleKick : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		std::array<Tunable, 8> m_Tunables = std::to_array({
		    Tunable("IDLEKICK_WARNING1"_J),
		    Tunable("IDLEKICK_WARNING2"_J),
		    Tunable("IDLEKICK_WARNING3"_J),
		    Tunable("IDLEKICK_KICK"_J),
		    Tunable("ConstrainedKick_Warning1"_J),
		    Tunable("ConstrainedKick_Warning2"_J),
		    Tunable("ConstrainedKick_Warning3"_J),
		    Tunable("ConstrainedKick_Kick"_J),
		});

		static constexpr auto m_DefaultValues = std::to_array({120000, 300000, 600000, 900000, 30000, 60000, 90000, 120000});

		virtual void OnTick() override
		{
			for (auto& tunable : m_Tunables)
			{
				if (tunable.IsReady())
					tunable.Set(INT_MAX);
			}
		}

		virtual void OnDisable() override
		{
			for (int i = 0; i < m_DefaultValues.size(); i++)
			{
				if (m_Tunables[i].IsReady())
					m_Tunables[i].Set(m_DefaultValues[i]);
			}
		}
	};

	static NoIdleKick _NoIdleKick{"noidlekick", "No Idle Kick", "Prevents you from being kicked while idling."};
}