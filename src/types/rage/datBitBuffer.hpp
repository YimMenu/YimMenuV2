#pragma once
#include "vector.hpp"

#include <cstdint>

namespace rage
{
	class datBitBuffer
	{
	public:
		datBitBuffer(void* data, uint32_t size, bool read = false)
		{
			m_Data            = data;
			m_BitOffset       = 0;
			m_MaxBit          = size * 8;
			m_BitsRead        = 0;
			m_CurBit          = 0;
			m_HighestBitsRead = 0;
			m_FlagBits        = read ? 1 : 0;
		}

		static void ReadBitsSingle(uint8_t* data, int* out, int size, int offset)
		{
			int v5;           // r11d
			int v6;           // ebx
			uint8_t* v7;      // r14
			char v8;          // cl
			int v9;           // r11d
			unsigned int v10; // r8d
			int v11;          // esi
			__int64 v12;      // r9

			v5 = offset;
			v6 = 1;
			v7 = &data[offset >> 3];
			v8 = offset & 7;
			if (size > 0)
				v5 = size + offset - 1;
			v9 = (v5 >> 3) - (offset >> 3);
			v10
				= (unsigned __int8)(*v7 << v8);
				v11 = 8;
				if (size > 8)
				{
					v12 = 1i64;
					do
					{
						if (v12 > v9)
							break;
						++v6;
						v10
							= (v10 << 8) | (v7[v12++] << v8);
							v11 += 8;
					} while (v11 < size);
				}
				if (v6 <= v9)
					v10
						|= v7[v6] >> (8 - v8);
						*out = v10 >> (((size + 7) & 0xF8) - size);
		}

		static void WriteBitsSingle(uint8_t* data, int value, int size, int offset)
		{
			uint8_t* v4;     // r10
			int v5;          // r9d
			unsigned int v6; // r11d
			uint8_t* v7;     // r10
			unsigned int v8; // r11d
			int v9;          // ebx
			__int64 v10;     // rdx
			char v11;        // cl

			v4  = &data[(__int64)offset >> 3];
			v5  = offset & 7;
			v6  = value << (32 - size);
			*v4 = ((v6 >> 24) >> v5) | *v4 & ~((unsigned int)(-1 << (32 - size)) >> 24 >> v5);
			v7  = v4 + 1;
			v8  = v6 << (8 - v5);
			v9  = -1 << (32 - size) << (8 - v5);
			if (8 - v5 < size)
			{
				v10
					= ((unsigned int)(size - (8 - v5) - 1) >> 3) + 1;
					do
					{
						v11 = (v8 >> 24) | *v7 & ~(v9 >> 24);
						v8 <<= 8;
						*v7++ = v11;
						v9 <<= 8;
						--v10;
					} while (v10);
			}
		}

	// copied IDA code, please improve!
	// TODO: this appears to be ARM code, not sure how FiveM got this or if this works with x64
	inline bool CopyBits(const void* dest, const void* source, int length, int destBitOffset, int sourceBitOffset)
	{
		auto result = (uint64_t)dest;
		auto a2 = source;
		auto a3 = length;
		int a4 = destBitOffset;
		auto a5 = sourceBitOffset;

		uint64_t v5; // x21
		int v6; // w20
		uint64_t v7; // x19
		int v8; // w11
		uint8_t* v9; // x22
		int v10; // w8
		int v11; // w10
		unsigned int v12; // w9
		unsigned int v13; // w14
		unsigned int v14; // w9
		unsigned int v15; // w10
		int v16; // w11
		uint64_t v17; // x11
		uint8_t* v18; // x12
		int v19; // w13
		unsigned int v20; // w8
		char v21; // w9
		char* v22; // x0
		int v23; // w14
		char v24; // t1
		char v25; // w10
		unsigned int v26; // w11
		int64_t v27; // x23
		uint8_t* v28; // x13
		int v29; // w16
		int v30; // t1
		unsigned int v31; // w10
		uint64_t v32; // x11
		int v33; // w8
		unsigned int v34; // w9
		unsigned int v35; // w10
		unsigned int v36; // w9
		unsigned int v37; // w10
		uint8_t* v38; // x11
		int v39; // w12
		int64_t v40; // x11
		int v41; // w12
		unsigned int v42; // w8
		unsigned int v43; // w9
		char v44; // w13
		unsigned int v45; // w8
		unsigned int v46; // w9
		uint64_t v47; // x10
		uint8_t* v48; // x11
		int v49; // w12

		v5 = a4;
		v6 = (signed int)a3;
		v7 = result;
		v8 = a5 & 7;
		v9 = (uint8_t*)a2 + (a5 >> 3);
		if (a5 & 7)
		{
			v10 = 8 - v8;
			if (8 - v8 > (signed int)a3)
				v10 = (signed int)a3;
			v11 = 8 - (v5 & 7);
			v12 = -1 << (32 - v10);
			v13 = ((*v9 << v8) & 0xFFu) >> (8 - v10) << (32 - v10);
			*(uint8_t*)(result + ((int64_t)((uint64_t)a4 << 32) >> 35)) = (v13 >> 24 >> (v5 & 7)) | *(uint8_t*)(result + ((int64_t)((uint64_t)a4 << 32) >> 35)) & ~(v12 >> 24 >> (v5 & 7));
			if (v11 < v10)
			{
				v14 = v12 << v11;
				v15 = v13 << v11;
				v16 = v8 - 9;
				if (v16 < ~(uint32_t)a3)
					v16 = !(uint32_t)a3;
				v17 = (((unsigned int)(v5 & 7) - 10 - v16) >> 3) + 1;
				v18 = (uint8_t*)(result + ((int64_t)((uint64_t)a4 << 32) >> 35) + 1);
				do
				{
					--v17;
					v19 = *v18 & ~(v14 >> 24) | (v15 >> 24);
					v15 <<= 8;
					*v18++ = v19;
					v14 <<= 8;
				}
				while (v17);
			}
			++v9;
			v6 = (uint32_t)a3 - v10;
			v5 = (unsigned int)(v10 + v5);
		}
		if (v6 >= 1)
		{
			v20 = (unsigned int)v6 >> 3;
			if ((unsigned int)v6 >> 3)
			{
				v21 = v5 & 7;
				v22 = (char*)(result + (v5 << 32 >> 35));
				if (v5 & 7)
				{
					v24 = *v22;
					result = (uint64_t)(v22 + 1);
					v23 = v24;
					v25 = 8 - v21;
					v26 = 0xFFu >> v21;
					v27 = v20 - 1 + 1LL;
					v28 = v9;
					do
					{
						v29 = *(int8_t*)result;
						--v20;
						*(uint8_t*)(result - 1) = ((unsigned int)*v28 >> v21) | (255 << (8 - v21)) & v23;
						v30 = *v28++;
						v23 = (v30 << v25) | v26 & v29;
						*(uint8_t*)result++ = ((uint8_t)v30 << v25) | v26 & v29;
					}
					while (v20);
					v31 = v6 & 7;
					if (!(v6 & 7))
						return true;
				}
				else
				{
					v27 = v20;
					result = (long long)memcpy(v22, v9, v20);
					v31 = v6 & 7;
					if (!(v6 & 7))
						return true;
				}
				v40 = (int64_t)((uint64_t)((unsigned int)v5 + (v6 & 0xFFFFFFF8)) << 32) >> 35;
				v41 = ((uint8_t)v5 + (v6 & 0xF8)) & 7;
				v42 = -1 << (32 - v31);
				v43 = v9[v27] >> (8 - v31) << (32 - v31);
				v44 = 8 - v41;
				*(uint8_t*)(v7 + v40) = (v43 >> 24 >> v41) | *(uint8_t*)(v7 + v40) & ~(v42 >> 24 >> v41);
				if (8 - v41 < v31)
				{
					v45 = v42 << v44;
					v46 = v43 << v44;
					v47 = ((v31 + v41 - 9) >> 3) + 1;
					v48 = (uint8_t*)(v7 + v40 + 1);
					do
					{
						--v47;
						v49 = *v48 & ~(v45 >> 24) | (v46 >> 24);
						v46 <<= 8;
						*v48++ = v49;
						v45 <<= 8;
					}
					while (v47);
				}
			}
			else
			{
				v32 = v5 << 32 >> 35;
				v33 = 8 - (v5 & 7);
				v34 = -1 << (32 - v6);
				v35 = (unsigned int)*v9 >> (8 - v6) << (32 - v6);
				*(uint8_t*)(result + v32) = (v35 >> 24 >> (v5 & 7)) | *(uint8_t*)(result + v32) & ~(v34 >> 24 >> (v5 & 7));
				if (v33 < v6)
				{
					v36 = v34 << v33;
					v37 = v35 << v33;
					v38 = (uint8_t*)(result + v32 + 1);
					do
					{
						v33 += 8;
						v39 = *v38 & ~(v36 >> 24) | (v37 >> 24);
						v37 <<= 8;
						*v38++ = v39;
						v36 <<= 8;
					}
					while (v33 < v6);
				}
			}
		}

		return true;
	}

		inline bool IsReadBuffer() const
		{
			return m_FlagBits & 1;
		}

		inline bool IsSizeCalculator() const
		{
			return m_FlagBits & 2;
		}

		void Seek(int bits)
		{
			m_BitsRead += bits;

			if (IsReadBuffer())
			{
				if (m_HighestBitsRead > m_CurBit)
					m_CurBit = m_HighestBitsRead;
			}
			else
			{
				if (m_BitsRead > m_CurBit)
					m_CurBit = m_BitsRead;
			}
		}

		inline bool ReadDword(int* out, int size)
		{
			if (IsSizeCalculator())
				return false;

			if (m_BitsRead + size > (IsReadBuffer() ? m_MaxBit : m_CurBit))
				return false;

			ReadBitsSingle(static_cast<uint8_t*>(m_Data), out, size, m_BitsRead + m_BitOffset);
			Seek(size);
			return true;
		}

		inline bool WriteDword(int val, int size)
		{
			if (IsReadBuffer())
				return false;

			if (m_BitsRead + size > m_MaxBit)
				return false;

			if (!IsSizeCalculator())
				WriteBitsSingle(static_cast<uint8_t*>(m_Data), val, size, m_BitsRead + m_BitOffset);
			Seek(size);
			return true;
		}

		inline bool ReadQword(uint64_t* out, int size)
		{
			if (size <= 32)
				return ReadDword(reinterpret_cast<int*>(out), size);

			return ReadDword(reinterpret_cast<int*>(out), 32) && !ReadDword(reinterpret_cast<int*>(out) + 1, size - 32);
		}

		inline bool WriteQword(uint64_t value, int size)
		{
			if (size <= 32)
				return WriteDword(static_cast<uint32_t>(value), size);

			int low  = (int)(value) & 0xFFFFFFFF;
			int high = (int)((uint64_t)value >> 32);

			return WriteDword(low, 32) && WriteDword(high, size - 32);
		}

		inline bool ReadInt64(int64_t* value, int size)
		{
			unsigned int last_bit{};
			uint64_t rest{};

			if (!ReadQword((uint64_t*)&last_bit, 1) || ReadQword(&rest, size - 1))
				return false;

			*value = ((uint64_t)last_bit << 63) | rest ^ -(int64_t)last_bit;
			return true;
		}

		inline bool WriteInt64(int64_t value, int size)
		{
			auto last_bit = value >> 63;
			if (!WriteQword(last_bit, 1) || !WriteQword((uint64_t)value ^ -(__int64)(unsigned int)last_bit, size - 1))
				return false;

			return true;
		}

		// unsigned
		// TODO: signed likely only works for 64 bit values!
		template<typename T>
		T Read(int size, bool _signed = false)
		{
			static_assert(sizeof(T) <= 8);

			uint64_t data{};
			int64_t data_signed{};
			if (_signed)
				ReadInt64(&data_signed, size);
			else
				ReadQword(&data, size);

			if (_signed)
				return T(data_signed);
			else
				return T(data);
		}

		// unsigned
		// TODO: signed likely only works for 64 bit values!
		template<typename T>
		void Write(T data, int size, bool _signed = false)
		{
			static_assert(sizeof(T) <= 8);

			if (_signed)
				WriteInt64(int64_t(data), size);
			else
				WriteQword(uint64_t(data), size);
		}

		void WriteArray(const void* array, int bits)
		{
			if (!IsReadBuffer())
			{
				if (!IsSizeCalculator())
					CopyBits(reinterpret_cast<void*>(reinterpret_cast<std::uint64_t>(m_Data) + (m_BitOffset >> 3)), array, bits, m_BitsRead + (m_BitOffset & 7), 0);
				Seek(bits);
			}
		}

		void WriteArrayBytes(const void* array, int bytes)
		{
			WriteArray(array, bytes * 8);
		}

		void ReadArray(void* array, int bits)
		{
			if (!IsReadBuffer())
				return;
			
			if (!IsSizeCalculator())
				CopyBits(array, reinterpret_cast<void*>(reinterpret_cast<std::uint64_t>(m_Data) + (m_BitOffset >> 3)), bits, 0, m_BitsRead + (m_BitOffset & 7));
			Seek(bits);
		}

		void ReadArrayBytes(void* array, int bytes)
		{
			ReadArray(array, bytes * 8);
		}

		void WriteString(const char* string, int max_len)
		{
			int len = strnlen(string, max_len - 1) + 1;
			bool extended = len > 127;

			Write<bool>(extended, 1);
			Write<int>(len, extended ? 15 : 7);
			WriteArrayBytes(string, len);
		}

		void ReadString(char* string, int max_len)
		{
			auto extended = Read<bool>(1);
			auto len = Read<int>(extended ? 15 : 7);
			if (len <= max_len)
			{
				ReadArrayBytes(string, len);
				string[len - 1] = 0;
			}
		}

		float ReadFloat(int size, float divisor)
		{
			int integer = Read<int>(size);

			float max = (1 << size) - 1;
			return ((float)integer / max) * divisor;
		}

		void WriteFloat(int size, float divisor, float value)
		{
			float max   = (1 << size) - 1;
			int integer = (int)((value / divisor) * max);

			Write<int>(integer, size);
		}

		float ReadSignedFloat(int size, float divisor)
		{
			int integer = Read<int>(size, true);

			float max = (1 << (size - 1)) - 1;
			return ((float)integer / max) * divisor;
		}

		void WriteSignedFloat(int size, float divisor, float value)
		{
			float max   = (1 << (size - 1)) - 1;
			int integer = (int)((value / divisor) * max);

			Write<int>(integer, size, true);
		}

		rage::fvector3 ReadPosition(int size)
		{
			rage::fvector3 pos;

			pos.x = ReadSignedFloat(size, 27648.0f);
			pos.y = ReadSignedFloat(size, 27648.0f);
			pos.z = ReadFloat(size, 4416.0f) - 1700.0f;

			return pos;
		}

		void WritePosition(int size, rage::fvector3& pos)
		{
			WriteSignedFloat(size, 27648.0f, pos.x);
			WriteSignedFloat(size, 27648.0f, pos.y);
			WriteFloat(size, 4416.0f, pos.z + 1700.0f);
		}

		rage::fvector3 ReadVector3(int size, float divisor)
		{
			rage::fvector3 vec;

			vec.x = ReadSignedFloat(size, divisor);
			vec.y = ReadSignedFloat(size, divisor);
			vec.z = ReadSignedFloat(size, divisor);

			return vec;
		}

		void WriteVector3(int size, float divisor, rage::fvector3& vec)
		{
			WriteSignedFloat(size, divisor, vec.x);
			WriteSignedFloat(size, divisor, vec.y);
			WriteSignedFloat(size, divisor, vec.z);
		}

		void AlignToByteBoundary()
		{
			Seek(((m_BitsRead + 7) >> 3) - m_BitsRead);
		}

	public:
		void* m_Data;               //0x0000
		uint32_t m_BitOffset;       //0x0008
		uint32_t m_MaxBit;          //0x000C
		uint32_t m_BitsRead;        //0x0010
		uint32_t m_CurBit;          //0x0014
		uint32_t m_HighestBitsRead; //0x0018
		uint8_t m_FlagBits;         //0x001C
	};
}