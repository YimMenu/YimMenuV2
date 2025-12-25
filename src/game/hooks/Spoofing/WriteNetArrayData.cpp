#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/backend/Players.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/network/netArrayHandler.hpp"
#include "types/script/globals/GSBD.hpp"

namespace YimMenu::Hooks
{
	class FreemodeStateKick
	{
		bool m_Enabled;
		eFreemodeState m_LastState;

	public:
		FreemodeStateKick(Player player, void* array) :
			m_Enabled(), m_LastState()
		{
			if (player.GetData().m_RunFreemodeStateKick && array == GSBD::Get())
			{
				m_Enabled = true;
				m_LastState = GSBD::Get()->FreemodeState;
				GSBD::Get()->FreemodeState = eFreemodeState::CLOSING;
				Pointers.NetArrayCachedDataPatch->Apply();
			}
		}

		~FreemodeStateKick()
		{
			if (m_Enabled)
			{
				GSBD::Get()->FreemodeState = m_LastState;
				Pointers.NetArrayCachedDataPatch->Restore();
			}
		}
	};

	int Hooks::Spoofing::WriteNetArrayData(rage::netArrayHandler* _this, CNetGamePlayer* target, rage::datBitBuffer* bit_buffer, uint16_t counter, uint32_t* elem_start, bool silent)
	{
		FreemodeStateKick kick(target, static_cast<void*>(_this->m_Array));

		return BaseHook::Get<Spoofing::WriteNetArrayData, DetourHook<decltype(&Spoofing::WriteNetArrayData)>>()->Original()(_this, target, bit_buffer, counter, elem_start, silent);
	}
}