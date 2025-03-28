#include "ScriptFunction.hpp"

namespace YimMenu
{
	ScriptFunction::ScriptFunction(const std::string& name, const joaat_t script, const SimplePattern& pattern) :
		m_Name(name),
		m_Script(script),
		m_Pattern(pattern),
		m_PC(0)
	{
	}

	std::uint32_t ScriptFunction::GetPC(rage::scrProgram* program)
	{
		if (m_PC != 0)
			return m_PC;

		if (auto location = Scripts::GetCodeLocationByPattern(program, m_Pattern))
		{
			m_PC = location.value();
			LOG(INFO) << "Found pattern for " << m_Name << " at " << HEX(m_PC) << " in script " << program->m_Name;
		}
		else
		{
			LOG(FATAL) << "Failed to find pattern for " << m_Name << " in script " << program->m_Name;
		}

		return m_PC;
	}
}