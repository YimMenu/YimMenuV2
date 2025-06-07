#include "../../gta/Scripts.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/commands/Command.hpp"
#include "game/gta/Scripts.hpp"

namespace YimMenu::Features
{
	class OpenMCT : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			FiberPool::Push([] {
				Scripts::RunScript("apparcadebusinesshub", 1424);
			});
		}
	};

	class OpenTerrorByte : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			FiberPool::Push([] {
				Scripts::RunScript("apphackertruck", 4592);
			});
		}
	};

	class OpenAvengerOperations : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			FiberPool::Push([] {
				Scripts::RunScript("appavengeroperations", 4592);
			});
		}
	};

	class OpenContracts : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			FiberPool::Push([] {
				Scripts::RunScript("appfixersecurity", 4592);
			});
		}
	};

	class OpenNightclub : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			FiberPool::Push([] {
				Scripts::RunScript("appbusinesshub", 4592);
			});
		}
	};

	class OpenBunker : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			FiberPool::Push([] {
				Scripts::RunScript("appbunkerbusiness", 1424);
			});
		}
	};

	class OpenHangar : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			FiberPool::Push([] {
				Scripts::RunScript("appsmuggler", 4592);
			});
		}
	};

	static OpenMCT _OpenMCT{"openmct", "Open Master Control Terminal", "Opens Master Control Terminal"};
	static OpenTerrorByte _OpenTerrorByte{"openterrorbyte", "Open Terrorbyte", "Opens Terrorbyte Computer"};
	static OpenAvengerOperations _OpenAvengerOperations{"openavengeroperations", "Open Avenger Operations", "Opens Avenger Operations Computer"};
	static OpenContracts _OpenContracts{"opencontracts", "Open Franklin Contracts", "Opens Franklins Contracts Computer"};
	static OpenNightclub _OpenNightclub{"opennightclub", "Open Nightclub", "Opens Nightclub Computer"};
	static OpenBunker _OpenBunker{"openbunker", "Open Bunker", "Opens Bunker Computer"};
	static OpenHangar _OpenHangar{"openhangar", "Open Hangar", "Opens Hangar Computer"};
}