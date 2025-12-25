#include "LuaResource.hpp"
#include "LuaManager.hpp"

namespace YimMenu
{
	void LuaResourceType::Register()
	{
		m_Index = LuaManager::RegisterResourceType(this);
	}
}