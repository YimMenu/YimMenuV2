#pragma once

class CPed;
class CPlayerInfo;
class CPedFactory
{
public:
	enum class PedCreateFlags
	{
		IS_NETWORKED = (1 << 0),
		IS_PLAYER = (1 << 1)
	};

	virtual ~CPedFactory() = default;
	virtual CPed* CreatePed(std::uint8_t* flags, std::uint16_t* model_index, void* matrix, bool default_component_variation, bool register_network_object, bool give_default_loadout, bool, bool) = 0; // 0x08
	virtual CPed* CreateClone(std::uint8_t* flags, std::uint16_t* model_index, void* matrix, bool default_component_variation, bool, bool register_network_object, bool) = 0;                          // 0x10
	virtual CPed* ClonePed(CPed* ped, bool register_network_object, bool link_blends, bool clone_compressed_damage) = 0;                                                                               // 0x18
	virtual CPed* ClonePedToTarget(CPed* source, CPed* target, bool clone_compressed_damage) = 0;                                                                                                      // 0x20
	virtual CPed* CreatePlayer(std::uint8_t* flags, std::uint16_t model_index, void* matrix, CPlayerInfo* player_info) = 0;                                                                            // 0x28
	virtual void DestroyPed(CPed* ped) = 0;                                                                                                                                                            // 0x30

	class CPed* m_LocalPed; //0x0008
}; //Size: 0x0010
static_assert(sizeof(CPedFactory) == 0x10);