#include "ScriptData.hpp"
#include "types/script/scrProgram.hpp"

namespace YimMenu
{
	ScriptData::ScriptData(rage::scrProgram* program)
	{
		auto pages = new uint8_t*[program->GetNumCodePages()];

		for (auto i = 0u; i < program->GetNumCodePages(); i++)
		{
			pages[i] = new uint8_t[program->GetCodePageSize(i)];
			std::memcpy(pages[i], program->GetCodePage(i), program->GetCodePageSize(i));
		}

		m_Data = pages;
		m_Pages = program->GetNumCodePages();
		m_Size = program->GetFullCodeSize();
		m_Name = program->m_Name;
	}

	ScriptData::~ScriptData()
	{
		for (auto i = 0u; i < m_Pages; i++)
		{
			delete[] m_Data[i];
		}

		delete[] m_Data;
		m_Data = nullptr;
		m_Name = nullptr;
	}

	std::uint8_t* ScriptData::GetCodeLocation(ScriptData* data, int idx)
	{
		return &data->GetData()[idx >> 14][idx & 0x3FFF];
	}

	std::optional<std::uint32_t> ScriptData::GetCodeLocationByPattern(ScriptData* data, const SimplePattern& pattern)
	{
		std::uint32_t codeSize = data->GetSize();
		for (uint32_t i = 0; i < (codeSize - pattern.m_Bytes.size()); i++)
		{
			for (uint32_t j = 0; j < pattern.m_Bytes.size(); j++)
			{
				if (pattern.m_Bytes[j].has_value())
				{
					int loc = i + j;
					if (pattern.m_Bytes[j] != *GetCodeLocation(data, loc))
						goto incorrect;
				}
			}

			return i;
		incorrect:
			continue;
		}

		return std::nullopt;
	}
}