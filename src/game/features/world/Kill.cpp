#include "core/commands/Command.hpp"
#include "game/gta/Pools.hpp"

namespace YimMenu::Features
{
	class KillAll : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			for (auto ped : Pools::GetPeds())
			{
				if (!ped.IsPlayer())
					ped.Kill();
			}
		}
	};

	class KillAllEnemies : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			const std::unordered_set<long long> enemiesNotToKill = {
				600300561,
				658984954,
				3678516463
			};

			for (auto ped : Pools::GetPeds())
			{
				if (!ped.IsPlayer() && ped.IsEnemy() && !enemiesNotToKill.contains(ped.GetModel()))
					ped.Kill();
			}
		}
	};

	static KillAll _KillAll{"killallpeds", "Kill All Peds", "Kills all peds in the game world"};
	static KillAllEnemies _KillAllEnemies{"killallenemies", "Kill All Enemies", "Kills all enemies in the game world"};
}