#pragma once
#include "core/memory/Pattern.hpp"

namespace rage
{
	class scrProgram;
}

namespace YimMenu
{
	class ScriptData
	{
		std::uint8_t** m_Data;
		std::uint32_t m_Pages;
		std::uint32_t m_Size;
		const char* m_Name;

	public:
		inline std::uint8_t** GetData() const
		{
			return m_Data;
		}

		inline std::uint32_t GetSize() const
		{
			return m_Size;
		}

		inline const char* GetName() const
		{
			return m_Name;
		}

		ScriptData(rage::scrProgram* program);
		~ScriptData();

		static uint8_t* GetCodeLocation(ScriptData* data, int idx);
		static std::optional<uint32_t> GetCodeLocationByPattern(ScriptData* data, const SimplePattern& pattern);
	};
}