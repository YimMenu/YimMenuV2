#pragma once
#include "PointerCalculator.hpp"
#include "common.hpp"

#include <winternl.h>

namespace YimMenu
{
	class Module
	{
	public:
		Module(LDR_DATA_TABLE_ENTRY* dllEntry);
		~Module() = default;

		const std::string_view Name() const;
		inline const std::uintptr_t Base() const;
		inline const std::uintptr_t Size() const;
		inline const std::uintptr_t End() const;

		/**
		 * @brief Parses the EAT of the module for the requested symbolname
		 * 
		 * @param symbolName 
		 * @return void* Function address of the exported function
		 */
		template<typename T = void*>
		T GetExport(const std::string_view symbolName) const;
		template<typename T = void*>
		T GetExport(int ordinal) const;
		/**
		 * @brief Gets the address of the import function
		 * 
		 * @param moduleName The module to get the import from
		 * @param symbolName The function name
		 * @return void** 
		 */
		void** GetImport(const std::string_view moduleName, const std::string_view symbolName) const;

		bool Valid() const;

		IMAGE_NT_HEADERS* GetNtHeader() const;

	private:
		const std::filesystem::path m_Path;
		const std::string m_Name;
		PointerCalculator m_Base;
		std::uintptr_t m_Size;
	};

	inline const std::uintptr_t Module::Base() const
	{
		return m_Base.As<std::uintptr_t>();
	}

	inline const std::uintptr_t Module::Size() const
	{
		return m_Size;
	}

	inline const std::uintptr_t Module::End() const
	{
		return Base() + m_Size;
	}

	template<typename T>
	inline T Module::GetExport(const std::string_view symbolName) const
	{
		const auto ntHeader = GetNtHeader();
		if (!ntHeader)
			return nullptr;

		const auto imageDataDirectory = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
		const auto exportDirectory    = m_Base.Add(imageDataDirectory.VirtualAddress).As<IMAGE_EXPORT_DIRECTORY*>();
		const auto namesOffsets       = m_Base.Add(exportDirectory->AddressOfNames).As<DWORD*>();
		const auto funcOffsets        = m_Base.Add(exportDirectory->AddressOfFunctions).As<DWORD*>();

		for (std::size_t i = 0; i < exportDirectory->NumberOfFunctions; i++)
		{
			const auto functionName = m_Base.Add(namesOffsets[i]).As<const char*>();
			if (strcmp(functionName, symbolName.data()))
				continue;

			return m_Base.Add(funcOffsets[i]).As<T>();
		}

		LOG(FATAL) << "Cannot find export: " << symbolName;
		return nullptr;
	}

	template<typename T>
	inline T Module::GetExport(int ordinal) const
	{
		const auto ntHeader = GetNtHeader();
		if (!ntHeader)
			return nullptr;

		const auto imageDataDirectory = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
		const auto exportDirectory    = m_Base.Add(imageDataDirectory.VirtualAddress).As<IMAGE_EXPORT_DIRECTORY*>();
		const auto ordinalOffsets     = m_Base.Add(exportDirectory->AddressOfNameOrdinals).As<uint16_t*>();
		const auto funcOffsets        = m_Base.Add(exportDirectory->AddressOfFunctions).As<DWORD*>();

		for (std::size_t i = 0; i < exportDirectory->NumberOfFunctions; i++)
		{
			if (ordinalOffsets[i] != ordinal)
				continue;

			return m_Base.Add(funcOffsets[i]).As<T>();
		}

		LOG(FATAL) << "Cannot find export: " << ordinal;
		return nullptr;
	}
}