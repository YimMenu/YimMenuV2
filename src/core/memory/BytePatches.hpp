#pragma once

#include <memory>
#include <span>
#include <vector>

namespace YimMenu
{
	class BytePatches
	{
	public:
		class Patch
		{
			void* m_Address;
			std::unique_ptr<uint8_t[]> m_Value;
			std::unique_ptr<uint8_t[]> m_OriginalBytes;
			std::size_t m_Size;
			bool m_Applied;

		public:
			template<typename TAddr>
			Patch(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value) :
			    m_Address(address),
			    m_Applied(false)
			{
				m_Size = sizeof(std::remove_pointer_t<std::remove_reference_t<TAddr>>);
				m_OriginalBytes = std::make_unique<uint8_t[]>(m_Size);
				m_Value = std::make_unique<uint8_t[]>(m_Size);

				memcpy(m_OriginalBytes.get(), m_Address, m_Size);
				memcpy(m_Value.get(), &value, m_Size);
			}

			Patch(void* address, std::span<std::uint8_t const> const values) :
			    m_Address(address),
			    m_Applied(false)
			{
				m_Size = values.size();

				m_OriginalBytes = std::make_unique<uint8_t[]>(m_Size);
				memcpy(m_OriginalBytes.get(), m_Address, m_Size);

				m_Value = std::make_unique<uint8_t[]>(m_Size);
				for (size_t i = 0; i < m_Size; i++)
					m_Value[i] = values[i];
			}

			~Patch();

			void Apply();
			void Restore();

			friend bool operator==(const std::shared_ptr<Patch>& a, const Patch* b);
		};

	private:
		static inline std::vector<std::shared_ptr<Patch>> m_Patches{};
		static inline std::mutex m_Mutex;

	public:
		template<typename TAddr>
		static std::shared_ptr<Patch> Add(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value)
		{
			std::lock_guard lock(m_Mutex);
			return m_Patches.emplace_back(std::make_shared<Patch>(address, value));
		}

		static std::shared_ptr<Patch> Add(void* address, std::span<std::uint8_t const> const values)
		{
			std::lock_guard lock(m_Mutex);
			return m_Patches.emplace_back(std::make_shared<Patch>(address, values));
		}

		static void Remove(std::shared_ptr<Patch>& patch); // do we need this?
		static void RestoreAll();
	};

	using BytePatch = std::shared_ptr<BytePatches::Patch>;
}