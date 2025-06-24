#include "Self.hpp"

#include "core/backend/ScriptMgr.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/gta/Natives.hpp"
#include "types/ped/CPedFactory.hpp"

namespace YimMenu
{
	Self::Self() :
	    m_SelfPed(nullptr),
	    m_SelfPlayer(nullptr),
	    m_Vehicle(nullptr)
	{
	}

	void Self::RunScriptImpl()
	{
		while (g_Running)
		{
			UpdateImpl();
			ScriptMgr::Yield();
		}
	}

	void Self::UpdateImpl()
	{
		CPed* ped_ptr = nullptr;
		if (auto factory = *Pointers.PedFactory)
			ped_ptr = factory->m_LocalPed;
		m_SelfPed = Ped(ped_ptr, PLAYER::PLAYER_PED_ID());
		m_SelfPlayer = Player(PLAYER::PLAYER_ID());
		if (m_SelfPed.IsValid())
		{
			m_Vehicle = m_SelfPed.GetVehicle();
		}
	}
}