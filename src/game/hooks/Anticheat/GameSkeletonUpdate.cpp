#include "game/hooks/Hooks.hpp"
#include "core/util/Joaat.hpp"
#include "types/rage/gameSkeleton.hpp"

namespace YimMenu::Hooks
{
	void Anticheat::GameSkeletonUpdate(rage::gameSkeleton* skeleton, int type)
	{
		for (auto mode = skeleton->m_UpdateModes; mode; mode = mode->m_Next)
		{
			if (mode->m_Type != type)
				continue;

			for (auto group = mode->m_Head; group; group = group->m_Next)
			{
				if (group->m_Hash != "Common Main"_J)
				{
					group->Run();
					continue;
				}

				for (auto item = static_cast<rage::gameSkeletonUpdateGroup*>(group)->m_Head; item; item = item->m_Next)
				{
					if (item->m_Hash != 0xA0F39FB6 && item->m_Hash != "TamperActions"_J)
					{
						item->Run();
					}
				}
			}

			break;
		}
	}
}