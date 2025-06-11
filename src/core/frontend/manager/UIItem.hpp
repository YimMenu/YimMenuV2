#pragma once
#include "core/util/Joaat.hpp"

namespace YimMenu
{
	// Preferably, all items should be saved in a global instance to make UI elements searchable
	class UIItem
	{
	public:
		virtual void Draw() = 0;
		virtual bool CanDraw()
		{
			return true;
		}
	};
}