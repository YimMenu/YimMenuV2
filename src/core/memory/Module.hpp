#pragma once
#include "PointerCalculator.hpp"
#include "common.hpp"

#include <type_traits>

#include <winternl.h>

namespace YimMenu
{
	template<typename T>
	concept Symbol = std::is_convertible_v<T, int> || std::is_convertible_v<T, std::string_view>;

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
		 * @brief Parses the EAT of the module for the requested symbol name
		 * 
		 * @param symbolName The function name
		 * @return void* Function address of the exported function
		 */
		template<typename R = void*>
		R GetExport(const std::string_view symbolName) const;
		/**
		 * @brief Parses the EAT of the module for the requested symbol ordinal
		 * 
		 * @param ordinal The function ordinal
		 * @return void* Function address of the exported function
		 */
		template<typename R = void*>
		R GetExport(const int ordinal) const;
		/**
		 * @brief Checks if the module exports a function with the given name
		 * 
		 * @param symbolName The function name
		 * @return true If the function is exported
		 * @return false If the function is not exported
		 */
		[[nodiscard]]
		bool IsExported(const std::string_view symbolName) const;
		/**
		 * @brief Checks if the module exports a function with the given ordinal
		 * 
		 * @param ordinal The function ordinal
		 * @return true If the function is exported
		 * @return false If the function is not exported
		 */
		[[nodiscard]]
		bool IsExported(const int ordinal) const;
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
		template<typename R = void*, Symbol T>
		R GetExportImpl(const T symbol) const;

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

	template<typename R>
	inline R Module::GetExport(const std::string_view name) const
	{
		auto result = GetExportImpl<R, decltype(name)>(name);
		if (result)
			return result;

		LOG(FATAL) << "Cannot find export: " << name;
		return nullptr;
	}

	template<typename R>
	inline R Module::GetExport(const int ordinal) const
	{
		auto result = GetExportImpl<R, decltype(ordinal)>(ordinal);
		if (result)
			return result;

		LOG(FATAL) << "Cannot find export: " << ordinal;
		return nullptr;
	}

	inline bool Module::IsExported(const std::string_view symbolName) const
	{
		return GetExportImpl<void*, decltype(symbolName)>(symbolName) != nullptr;
	}

	inline bool Module::IsExported(const int ordinal) const
	{
		return GetExportImpl<void*, decltype(ordinal)>(ordinal) != nullptr;
	}

	template<typename R, Symbol T>
	inline R Module::GetExportImpl(const T symbol) const
	{
		const auto ntHeader = GetNtHeader();
		if (!ntHeader)
			return nullptr;

		const auto imageDataDirectory = ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
		const auto exportDirectory = m_Base.Add(imageDataDirectory.VirtualAddress).As<IMAGE_EXPORT_DIRECTORY*>();
		const auto namesOffsets = m_Base.Add(exportDirectory->AddressOfNames).As<DWORD*>();
		const auto ordinalOffsets = m_Base.Add(exportDirectory->AddressOfNameOrdinals).As<uint16_t*>();
		const auto funcOffsets = m_Base.Add(exportDirectory->AddressOfFunctions).As<DWORD*>();

		for (std::size_t i = 0; i < exportDirectory->NumberOfNames; i++)
		{
			if constexpr (std::is_convertible_v<T, int>)
			{
				if (exportDirectory->Base + ordinalOffsets[i] != symbol)
					continue;

				return m_Base.Add(funcOffsets[ordinalOffsets[i]]).As<R>();
			}
			else if constexpr (std::is_convertible_v<T, std::string_view>)
			{
				const auto functionName = m_Base.Add(namesOffsets[i]).As<const char*>();
				if (strcmp(functionName, symbol.data()))
					continue;

				return m_Base.Add(funcOffsets[ordinalOffsets[i]]).As<R>();
			}
			else
			{
				static_assert(false, "Unsupported symbol type");
			}
		}

		return nullptr;
	}
}