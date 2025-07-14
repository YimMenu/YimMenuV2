#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Pools.hpp"
#include "game/backend/Self.hpp"
#include <game/gta/Natives.hpp>

namespace YimMenu::Features
{
	class InfiniteBoundary : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;
		virtual void OnTick() override
		{
			PLAYER::EXTEND_WORLD_BOUNDARY_FOR_PLAYER(-42069420.0, -42069420.0, -42069420.0);
			PLAYER::EXTEND_WORLD_BOUNDARY_FOR_PLAYER(42069420.0, 42069420.0, 42069420.0);
		}
	};

	static InfiniteBoundary Infinitebundary{"infiniteboundary", "Infinite Boundary", "You won't die because of border restrictions."};

}