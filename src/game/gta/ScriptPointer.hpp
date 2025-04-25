#pragma once
#include "game/gta/ScriptData.hpp"

namespace YimMenu
{
	class ScriptPointer
	{
		const std::string m_Name;
		SimplePattern m_Pattern;
		std::int32_t m_Offset;
		bool m_Rip;
		std::uint32_t m_Address;

	public:
		ScriptPointer(const std::string& name, const SimplePattern& pattern, std::int32_t offset = 0, bool rip = false, std::uint32_t address = 0);

		ScriptPointer Add(std::uint32_t offset);
		ScriptPointer Sub(std::uint32_t offset);
		ScriptPointer Rip();
		ScriptPointer Scan(rage::scrProgram* program);
		ScriptPointer Scan(ScriptData* data); // For script patches

		template<typename T>
		T As()
		{
			return (T)m_Address;
		}

		std::string GetName() const
		{
			return m_Name;
		}
	};
}