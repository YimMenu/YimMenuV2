#include "core/util/Joaat.hpp"
#include "core/translation/Translation.hpp"
#include "Command.hpp"
#include "Commands.hpp"

namespace YimMenu
{
	Command::Command(std::string name, std::string label, std::string description, int num_args) :
	    m_Name(name),
	    m_Label(Translation::Tr(label)),
	    m_Description(Translation::Tr(description)),
	    m_NumArgs(num_args),
	    m_Hash(Joaat(name))
	{
		Commands::AddCommand(this);
	}

	void Command::Call()
	{
		OnCall();
	}

	void Command::MarkDirty()
	{
		Commands::MarkDirty();
	}
}