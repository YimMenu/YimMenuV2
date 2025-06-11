#pragma once
#include "types/network/sync/CProjectBaseSyncDataNode.hpp"

struct ClanData
{
	int64_t m_clan_member_id;    //0x0000
	int64_t m_clan_id;           //0x0008
	int32_t m_clan_color;        //0x0010
	int32_t m_clan_member_count; //0x0014
	int32_t m_clan_created_time; //0x0018
	bool m_is_system_clan;       //0x001C
	bool m_is_clan_open;         //0x001D
	char m_clan_name[25];        //0x001E
	char m_clan_tag[5];          //0x0037
	char m_clan_motto[65];       //0x003C
	char pad_007D[3];            //0x007D
	int64_t m_clan_id_2;         //0x0080
	char m_clan_rank_name[25];   //0x0088
	char pad_00A1[3];            //0x00A1
	int32_t m_clan_rank_order;   //0x00A4
	int64_t m_clan_rank_flags;   //0x00A8
	char unk_00B0[8];            //0x00B0
};

class CPlayerGamerDataNode : CSyncDataNodeInfrequent
{
public:
	ClanData m_CanData;               //0x00C0
	bool m_NeedCrewRankSysFlags;      //0x0178
	bool m_NeedCrewRankTitle;         //0x0179
	char m_CrewRankTitle[25];         //0x017A
	bool m_HasStartedTransition;      //0x0193
	bool m_HasTransitionInfo;         //0x0194
	char m_TransitionInfoBuffer[169]; //0x0195
	int m_PlayerPrivilegeFlags;       //0x0240
	uint32_t m_MatchmakingGroup;      //0x0244
	bool m_NeedMuteData;              //0x0248
	int32_t m_MuteCount;              //0x024C
	int32_t m_MuteTalkersCount;       //0x0250
	uint32_t m_unk;                   //0x0254
	int32_t m_AccountId;              //0x0258
};
static_assert(sizeof(CPlayerGamerDataNode) == 0x260);