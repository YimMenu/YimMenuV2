#pragma once
#include <cstdint>
#include <ctime>

namespace rage
{
	template<typename T>
	class ObfVar
	{
	private:
		T m_unk1;
		T m_unk2;
		T m_unk3;
		T m_unk4;

	public:
		T getData()
		{
			auto v105 = m_unk4;
			auto v28 = m_unk1 & v105;
			auto v94 = m_unk2 & ~v105;
			return v28 | v94;
		}

		operator T()
		{
			return getData();
		}

		void setData(T val)
		{
			auto seed = time(nullptr);
			m_unk3 = seed;
			seed = time(nullptr);
			m_unk4 = seed;

			auto v48 = val & ~seed;
			m_unk1 = seed & val;
			m_unk2 = v48;
		}

		void operator=(T val)
		{
			setData(val);
		}
	};

	using Obf16 = ObfVar<unsigned short>;
	using Obf32 = ObfVar<unsigned int>;
}