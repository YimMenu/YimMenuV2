#include "ScriptFunction.hpp"

namespace YimMenu
{
	ScriptFunction::ScriptFunction(const std::string& name, const joaat_t script, const SimplePattern& pattern, std::int32_t offset, bool rip) :
		m_Name(name),
		m_Script(script),
		m_Pattern(pattern),
		m_Offset(offset),
		m_Rip(rip),
		m_PC(0)
	{
	}

	std::uint32_t ScriptFunction::GetPC(rage::scrProgram* program)
	{
		if (m_PC != 0)
			return m_PC;

		if (auto location = Scripts::GetCodeLocationByPattern(program, m_Pattern))
		{
			m_PC = location.value() + m_Offset;
			if (m_Rip)
				m_PC = ReadThreeByte(program->GetCodeAddress(m_PC));
			LOG(INFO) << "Found pattern for " << m_Name << " at " << HEX(m_PC) << " in script " << program->m_Name;
		}
		else
		{
			LOG(FATAL) << "Failed to find pattern for " << m_Name << " in script " << program->m_Name;
		}

		return m_PC;
	}
}