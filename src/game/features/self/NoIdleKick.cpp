#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Tunables.hpp"

namespace YimMenu::Features
{
	class NoIdleKick : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		const std::vector<joaat_t> m_TunableHashes = {"IDLEKICK_WARNING1"_J, "IDLEKICK_WARNING2"_J, "IDLEKICK_WARNING3"_J, "IDLEKICK_KICK"_J, "ConstrainedKick_Warning1"_J, "ConstrainedKick_Warning2"_J, "ConstrainedKick_Warning3"_J, "ConstrainedKick_Kick"_J};
		const std::vector<int> m_DefaultValues = {120000, 300000, 600000, 900000, 30000, 60000, 90000, 120000};

		virtual void OnTick() override
		{
			for (auto tunable : m_TunableHashes)
			{
				if (auto tunablePtr = Tunables::GetTunable(tunable).As<int*>())
				{
					*tunablePtr = INT_MAX;
				}
			}
		}

		virtual void OnDisable() override
		{
			for (int i = 0; i < m_DefaultValues.size(); i++)
			{
				if (auto tunablePtr = Tunables::GetTunable(m_TunableHashes[i]).As<int*>())
				{
					// TO-DO: Add methods for getting the default script value and cloud value to the Tunables class
					*tunablePtr = m_DefaultValues[i];
				}
			}
		}
	};

	static NoIdleKick _NoIdleKick{"noidlekick", "No Idle Kick", "Prevents you from being kicked while idling."};
}