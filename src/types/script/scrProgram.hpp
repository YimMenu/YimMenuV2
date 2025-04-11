#pragma once
#include "types/rage/pgBase.hpp"
#include "scrNativeHandler.hpp"

#include <cstdint>

namespace rage
{
	class scrProgram : public pgBase
	{
	public:
		std::uint8_t** m_CodeBlocks;           // 0x10
		std::uint32_t m_Hash;                  // 0x18
		std::uint32_t m_CodeSize;              // 0x1C
		std::uint32_t m_ArgCount;              // 0x20
		std::uint32_t m_LocalCount;            // 0x24
		std::uint32_t m_GlobalCount;           // 0x28
		std::uint32_t m_NativeCount;           // 0x2C
		void* m_LocalData;                     // 0x30
		void** m_GlobalData;                   // 0x38
		scrNativeHandler* m_NativeEntrypoints; // 0x40
		std::uint32_t m_ProcCount;             // 0x48
		char pad_004C[4];                      // 0x4C
		const char** m_ProcNames;              // 0x50
		std::uint32_t m_NameHash;              // 0x58
		std::uint32_t m_RefCount;              // 0x5C
		const char* m_Name;                    // 0x60
		const char** m_StringsData;            // 0x68
		std::uint32_t m_StringsCount;          // 0x70
		char m_Breakpoints[0x0C];              // 0x74

		bool IsValid() const
		{
			return m_CodeSize != 0;
		}

		std::uint32_t GetNumCodePages() const
		{
			return (m_CodeSize + 0x3FFF) >> 14;
		}

		std::uint32_t GetCodePageSize(std::uint32_t page) const
		{
			auto num = GetNumCodePages();
			if (page < num)
			{
				if (page == num - 1)
					return (m_CodeSize & 0x3FFF);
				return 0x4000;
			}

			return 0;
		}

		std::uint32_t GetFullCodeSize() const
		{
			return m_CodeSize;
		}

		std::uint8_t* GetCodePage(std::uint32_t page) const
		{
			return m_CodeBlocks[page];
		}

		std::uint8_t* GetCodeAddress(std::uint32_t index) const
		{
			if (index < m_CodeSize)
				return &m_CodeBlocks[index >> 14][index & 0x3FFF];

			return nullptr;
		}

		const char* GetString(std::uint32_t index) const
		{
			if (index < m_StringsCount)
				return &m_StringsData[index >> 14][index & 0x3FFF];

			return nullptr;
		}

		scrNativeHandler* GetAddressOfNativeEntrypoint(scrNativeHandler entrypoint)
		{
			for (std::uint32_t i = 0; i < m_NativeCount; ++i)
			{
				if (m_NativeEntrypoints[i] == entrypoint)
				{
					return m_NativeEntrypoints + i;
				}
			}

			return nullptr;
		}
	};
	static_assert(sizeof(scrProgram) == 0x80);
}