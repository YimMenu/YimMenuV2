#include "LuaLibrary.hpp"
#include "LuaManager.hpp"

namespace YimMenu
{
	LuaLibrary::LuaLibrary()
	{
		LuaManager::RegisterLibrary(this);
	}
}