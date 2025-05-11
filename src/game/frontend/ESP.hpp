#pragma once
#include "game/gta/Player.hpp"

namespace YimMenu
{
	enum ObjectType
	{
		Generic,
		Camera,
		Cache,
		SignalJammer
	};
	class ESP
	{
	public:
		static void Draw();
		static void DrawPlayer(Player plyr, ImDrawList* draw_list);
		static void DrawPed(Ped plyr, ImDrawList* drawList);
		static void DrawRandomEvent(int event, ImDrawList* drawList);
		static void DrawObject(Entity object, ImDrawList* drawList, ObjectType objectType = Generic);
	};
}