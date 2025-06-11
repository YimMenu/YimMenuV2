#pragma once

namespace rage
{
	class fwVehiclePool
	{
	public:
		virtual ~fwVehiclePool() = 0;

		void** m_PoolAddress;
		std::uint32_t m_Size;
		char _Padding2[36];
		std::uint32_t* m_BitArray;
		char _Padding3[40];
		std::uint32_t m_ItemCount;

		inline bool IsValid(int i) const
		{
			return (m_BitArray[i >> 5] >> (i & 0x1F)) & 1;
		}

		inline void* GetAt(int i) const
		{
			if (IsValid(i))
				return m_PoolAddress[i];

			return nullptr;
		}
	};
}