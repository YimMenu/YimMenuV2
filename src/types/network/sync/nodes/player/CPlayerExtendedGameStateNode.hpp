#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

class CPlayerExtendedGameStateNode : CSyncDataNodeInfrequent
{
public:
	float m_WaypointX;      //0x00C0
	float m_WaypointY;      //0x00C4
	bool unk1;              //0x00C5
	bool unk2;              //0x00C6
	bool unk3;              //0x00C7
	bool unk4;              //0x00C8
	bool unk5;              //0x00C9
	bool m_HasWaypointData; //0x00CA
	bool m_IsWaypointSet;   //0x00CB
};