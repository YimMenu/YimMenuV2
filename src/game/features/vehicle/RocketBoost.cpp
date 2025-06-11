#include "core/commands/LoopedCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	static std::vector<std::pair<int, const char*>> g_BoostBehavior = {
	    {0, "Infinite"},
	    {1, "Instant recharge"}};

	static ListCommand _BoostBehavior{"boostbehavior", "Boost behavior", "Desired rocket boost behavior", g_BoostBehavior, 0};

	class ModifyRocketBoost : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (auto vehicle = Self::GetVehicle())
			{
				if (vehicle.SupportsBoost())
				{
					auto desiredBehavior = _BoostBehavior.GetState();

					/* Infinite */
					if (desiredBehavior == 0)
						vehicle.SetBoostCharge();

					/* Instant charge */
					else if (desiredBehavior == 1)
						if (!vehicle.IsBoostActive())
							vehicle.SetBoostCharge();
				}
			}
		}
	};

	static ModifyRocketBoost _ModifyRocketBoost{"modifyboostbehavior", "Modify boost behavior", "Modify rocket boost behavior for vehicles that support it"};
};