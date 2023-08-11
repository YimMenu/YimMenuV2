#include "ScriptLocal.hpp"

namespace NewBase
{
	void* ScriptLocal::Get() const
	{
		return reinterpret_cast<uintptr_t*>((uintptr_t)m_StackPtr + (m_Index * sizeof(uintptr_t)));
	}
}