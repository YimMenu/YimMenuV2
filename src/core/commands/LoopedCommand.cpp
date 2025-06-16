#include "LoopedCommand.hpp"
#include "Commands.hpp"

namespace YimMenu
{
	LoopedCommand::LoopedCommand(std::string name, std::string label, std::string description) :
	    BoolCommand(name, label, description)
	{
		Commands::AddLoopedCommand(this);
	}

	void LoopedCommand::Tick()
	{
		OnTick();
	}
}