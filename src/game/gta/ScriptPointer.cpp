#include "ScriptPointer.hpp"
#include "game/gta/Scripts.hpp"
#include "types/script/scrProgram.hpp"

namespace YimMenu
{
	static std::uint32_t ReadThreeByte(std::uint8_t* arr)
	{
		return arr[0] + (arr[1] << 8) + (arr[2] << 16);
	}

	ScriptPointer::ScriptPointer(const std::string& name, const SimplePattern& pattern, std::int32_t offset, bool rip, std::uint32_t address) :
	    m_Name(name),
	    m_Pattern(pattern),
	    m_Offset(offset),
	    m_Rip(rip),
	    m_Address(address)
	{
	}

	ScriptPointer ScriptPointer::Add(std::uint32_t offset)
	{
		return ScriptPointer(m_Name, m_Pattern, m_Offset + offset, m_Rip, m_Address);
	}

	ScriptPointer ScriptPointer::Sub(std::uint32_t offset)
	{
		return ScriptPointer(m_Name, m_Pattern, m_Offset - offset, m_Rip, m_Address);
	}

	ScriptPointer ScriptPointer::Rip()
	{
		return ScriptPointer(m_Name, m_Pattern, m_Offset, true, m_Address);
	}

	ScriptPointer ScriptPointer::Scan(rage::scrProgram* program)
	{
		if (auto location = Scripts::GetCodeLocationByPattern(program, m_Pattern))
		{
			m_Address = location.value() + m_Offset;
			if (m_Rip)
				m_Address = ReadThreeByte(program->GetCodeAddress(m_Address));

			LOG(INFO) << "Found pattern for " << m_Name << " at " << HEX(m_Address) << " in script " << program->m_Name;
			return ScriptPointer(m_Name, m_Pattern, m_Offset, m_Rip, m_Address);
		}

		LOG(FATAL) << "Failed to find pattern for " << m_Name;
		return ScriptPointer(m_Name, m_Pattern, m_Offset, m_Rip, 0);
	}

	ScriptPointer ScriptPointer::Scan(ScriptData* data)
	{
		if (auto location = ScriptData::GetCodeLocationByPattern(data, m_Pattern))
		{
			m_Address = location.value() + m_Offset;
			if (m_Rip)
				m_Address = ReadThreeByte(ScriptData::GetCodeLocation(data, m_Address));

			LOG(INFO) << "Found pattern for " << m_Name << " at " << HEX(m_Address) << " in script " << data->GetName();
			return ScriptPointer(m_Name, m_Pattern, m_Offset, m_Rip, m_Address);
		}

		LOG(FATAL) << "Failed to find pattern for " << m_Name;
		return ScriptPointer(m_Name, m_Pattern, m_Offset, m_Rip, 0);
	}
}