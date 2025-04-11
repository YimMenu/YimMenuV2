#pragma once
#include "netPlayer.hpp"

class CPlayerInfo;
class CNetGamePlayer : public rage::netPlayer
{
public:
	void* m_Unk;               // 0xE0
	CPlayerInfo* m_PlayerInfo; // 0xE8
	char m_Pad2[0x280];        // 0xF0
}; //Size: 0x02C0
static_assert(sizeof(CNetGamePlayer) == 0x370);