#pragma once

#include <memory>
#include <span>
#include <vector>

namespace YimMenu
{
	class BytePatch
	{
	public:
		virtual ~BytePatch();

		void Apply() const;

		void Restore() const;

		void Remove() const;

		template<typename TAddr>
		static const std::unique_ptr<BytePatch>& Make(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value)
		{
			return m_Patches.emplace_back(std::unique_ptr<BytePatch>(new BytePatch(address, value)));
		}

		template<typename TAddr, typename T>
		static const std::unique_ptr<BytePatch>& Make(TAddr address, const std::vector<T>& values)
		{
			return m_Patches.emplace_back(std::unique_ptr<BytePatch>(new BytePatch(address, values)));
		}

		static void RestoreAll();

	private:
		template<typename TAddr>
		BytePatch(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value) :
		    m_Address(address)
		{
			m_Size           = sizeof(std::remove_pointer_t<std::remove_reference_t<TAddr>>);
			m_OriginalBytes = std::make_unique<uint8_t[]>(m_Size);
			m_Value          = std::make_unique<uint8_t[]>(m_Size);

			memcpy(m_OriginalBytes.get(), m_Address, m_Size);
			memcpy(m_Value.get(), &value, m_Size);
		}

		template<typename TAddr, typename T>
		BytePatch(TAddr address, const std::vector<T>& values) :
		    m_Address((void*)address)
		{
			m_Size = values.size();

			m_OriginalBytes = std::make_unique<uint8_t[]>(m_Size);
			memcpy(m_OriginalBytes.get(), m_Address, m_Size);

			m_Value = std::make_unique<uint8_t[]>(m_Size);
			for (size_t i = 0; i < m_Size; i++)
				m_Value[i] = values[i];
		}

	protected:
		static inline std::vector<std::unique_ptr<BytePatch>> m_Patches;

	private:
		void* m_Address;
		std::unique_ptr<uint8_t[]> m_Value;
		std::unique_ptr<uint8_t[]> m_OriginalBytes;
		std::size_t m_Size;

		friend bool operator==(const std::unique_ptr<BytePatch>& a, const BytePatch* b);
	};
}