#pragma once
#include <cstdint>

namespace rage
{
	class fwBasePool
	{
	public:
		virtual ~fwBasePool() = 0; // 0x0000
		uintptr_t m_Entries;       // 0x0008
		uint8_t* m_Flags;          // 0x0010
		uint32_t m_Size;           // 0x0018
		uint32_t m_ItemSize;       // 0x001C
		uint32_t m_NextSlotIndex;  // 0x0020
		uint32_t m_0024;           // 0x0024
		uint32_t m_FreeSlotIndex;  // 0x0028

		bool Full() const
		{
			return m_Size - (m_FreeSlotIndex & 0x3FFFFFFF) <= 256;
		}

		int64_t GetNumFreeSlots() const
		{
			return static_cast<int64_t>(m_Size) - static_cast<int>((m_FreeSlotIndex * 4) >> 2);
		}

		int32_t GetScriptGuid(int32_t Index) const
		{
			return (Index << 8) + m_Flags[Index];
		}

		int32_t GetIndex(int32_t ScriptGuid) const
		{
			return ScriptGuid >> 8;
		}

		bool IsValid(int32_t Index) const
		{
			return !(m_Flags[Index] & 0x80);
		}

		void* GetAt(size_t Index) const
		{
			if (m_Flags[Index])
			{
				if (_fwObj* obj = reinterpret_cast<_fwObj*>(m_Entries + Index * m_ItemSize); obj->m_0010)
					return obj;
			}

			return nullptr;
		}

		// Helper class to check object validity (m_0010)
		class _fwObj
		{
		public:
			virtual ~_fwObj() = 0;
			uint64_t m_0008;
			void* m_0010;
		};

	}; //Size: 0x0030
	static_assert(sizeof(fwBasePool) == 0x30);
}